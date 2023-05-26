
#include <stdint.h>
#include <inttypes.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_ip.h>

#include <arpa/inet.h> //inet_ntop
#include <netinet/tcp.h> //tcp header
#include <rte_tcp.h>
#include <rte_udp.h>

#include "../includes/klib/khash.h" //hash tabel


#include <unistd.h>

#define RX_RING_SIZE 128
#define TX_RING_SIZE 512
#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32

#define DEBUGGING 0
#define QUEUE_LENGTH 1024

#define NUMQUEUES 2

#define MAX_TCP_PKT_SIZE 1448
#define TCP_WINDOW_SCALING 1024 //(this is a Window Scale option value of 10)

#define SEQ_GT(a,b) ((int)((a)-(b)) > 0)
#define SEQ_LT(a,b) ((int)((a)-(b)) < 0)
#define SEQ_GEQ(a,b) ((int)((a)-(b)) >= 0)
#define SEQ_LEQ(a,b) ((int)((a)-(b)) <= 0)

#define INTERFACE_ID_1 "0000:61:00.0"
#define INTERFACE_ID_2 "0000:61:00.1"

#if DEBUGGING > 0
char debug[2048];
char tmp[60] = "";
#endif

int pnum = 1;

struct packetQueueElement {
    struct rte_mbuf *packet;
    uint16_t port;
    int id;
    int pid;
};

typedef struct {
    struct packetQueueElement **queue;
    int head;
    int tail;
    pthread_mutex_t *mutex;
} packetQueue;

typedef struct { //s_ip < c_ip
    uint32_t srv_seq;
    uint32_t cli_seq;
    uint8_t srv_state;
    uint8_t cli_state;
    uint32_t srv_window;
    uint32_t cli_window;
} tcpState;


KHASH_MAP_INIT_INT(rules, int)
KHASH_MAP_INIT_INT(states, tcpState)

kh_rules_t *connections;
kh_states_t *states;


packetQueue *decideQueue;
packetQueue **flowQueues;
packetQueue **forwardQueues;

uint16_t portids[2];



static inline void addToQueue(packetQueue *queue, struct packetQueueElement *toBeAdded) {
    struct packetQueueElement *swap;
    pthread_mutex_lock(queue->mutex);
    swap = queue->queue[queue->tail];
    queue->queue[queue->tail] = toBeAdded;
    toBeAdded = swap;
    queue->tail = queue->tail + 1;
    if(queue->tail >= QUEUE_LENGTH){
        queue->tail = 0;
    }
    pthread_mutex_unlock(queue->mutex);
}



static inline void addToDecideQueue(struct rte_mbuf *pkt, uint16_t port) {
    struct rte_mbuf *swap;
    pthread_mutex_lock(decideQueue->mutex);
    swap = pkt;
    pkt = decideQueue->queue[decideQueue->tail]->packet;
    (decideQueue->queue[decideQueue->tail]->packet) = swap;

    decideQueue->queue[decideQueue->tail]->pid = pnum;
    decideQueue->queue[decideQueue->tail]->port = port;
    decideQueue->tail = decideQueue->tail + 1;
    if(decideQueue->tail >= QUEUE_LENGTH){
        decideQueue->tail = 0;
    }
    pnum = pnum + 1;
    pthread_mutex_unlock(decideQueue->mutex);
}


static inline struct packetQueueElement *getFromQueue(packetQueue *queue, struct packetQueueElement *ret) {
    struct packetQueueElement *element;

    pthread_mutex_lock(queue->mutex);
    if (queue->head == queue->tail) {
        pthread_mutex_unlock(queue->mutex);
        return ret;
    }

    element = queue->queue[queue->head];
    queue->queue[queue->head] = ret;
    ret = element;

    queue->head = queue->head + 1;
    if(queue->head >= QUEUE_LENGTH){
        queue->head = 0;
    }
    pthread_mutex_unlock(queue->mutex);

    return ret;

}

static inline void initQueue(packetQueue **toBeInitialized) {
    packetQueue *queue;
    queue = malloc(sizeof(packetQueue));
    queue->mutex = malloc(sizeof(pthread_mutex_t));
    queue->queue = calloc(QUEUE_LENGTH, sizeof(struct packetQueueElement*));

    queue->tail = 0;
    queue->head = 0;
    pthread_mutex_init(queue->mutex, NULL);
    for (int i = 0; i < QUEUE_LENGTH ; ++i) {
        queue->queue[i] = malloc(sizeof(struct packetQueueElement));
        queue->queue[i]->packet = malloc(sizeof(struct rte_mbuf));
        queue->queue[i]->port = 0;
        queue->queue[i]->id = 0;
        queue->queue[i]->pid = -1;
    }
    *toBeInitialized = queue;
}





int hash(const uint8_t *proto, const unsigned long *s_addr, const u_int16_t *s_port, const unsigned long *c_addr,
         const uint16_t *c_port) {
    int erg = (int) ((*s_addr ^ *s_port) ^ (*c_addr ^ *c_port) ^ *proto);
    return erg;
}




void addConnection(const int *key, const int num) {
    int ret;
    khint_t k;
    k = kh_put_rules(connections, (khint32_t) * key, &ret);
    if (!ret) {
        kh_del_rules(connections, k);
    }
    kh_value(connections, k) = num;
}

int *getConnection(const int *key) {
    khint_t k;
    int *s;
    k = kh_get_rules(connections, (khint32_t) * key);         // query the hash table
    if (k == kh_end(connections)) {
        return NULL;
    }
    s = &kh_value(connections, k);
    return s;
}


void addState(const int * key, const tcpState *s){
    int ret;
    khint_t k;
    k = kh_put_states(states, (khint32_t) *key, &ret);
    if (!ret) {
        kh_del_states(states, k);
    }
    kh_value(states, k) = *s;
}

tcpState* getState(const int *key){
    khint_t k;
    tcpState *s;
    k = kh_get_states(states, (khint32_t) *key);
    if (k == kh_end(states)) {
        return NULL;
    }
    s = &kh_value(states, k);
    return s;
}

void readRules(const char *file, const int amountOfQueues) {
    char buffer[1024], ip1[INET_ADDRSTRLEN], ip2[INET_ADDRSTRLEN];
    int i, j, rulehash, queuenum = 0, numRules = 0;
    uint16_t port1, port2;
    uint8_t proto;
    unsigned long netip1, netip2;
    struct in_addr inp;
    FILE *fp;

    connections = kh_init_rules();
    states = kh_init_states();

    tcpState s;
    s.cli_state = TCP_CLOSE;
    s.cli_seq = 0;
    s.cli_window = 0;
    s.srv_seq = 0;
    s.srv_window = 0;
    s.srv_state = TCP_CLOSE;


    fp = fopen(file, "r");
    while (fgets(buffer, 1024, fp) != NULL) {

        if (buffer[0] != '#') {
            i = 0;
            for (proto = 0; buffer[i] != ','; i = i + 1) {
                proto = (uint8_t) ((10 * proto) + (buffer[i] - '0'));
            }
            i = i + 1;
            for (j = 0; buffer[i] != ','; i = i + 1) {
                ip1[j] = buffer[i];
                j = j + 1;
            }
            ip1[j] = '\0';
            i = i + 1;
            for (port1 = 0; buffer[i] != ','; i = i + 1) {
                port1 = (uint16_t) (port1 * 10 + (buffer[i] - '0'));
            }
            port1 = htons(port1);
            i = i + 1;
            for (j = 0; buffer[i] != ','; i = i + 1) {
                ip2[j] = buffer[i];
                j = j + 1;
            }
            ip2[j] = '\0';
            i = i + 1;
            for (port2 = 0; buffer[i] != '\n'; i = i + 1) {
                port2 = (uint16_t) (port2 * 10 + (buffer[i] - '0'));
            }
            port2 = htons(port2);
            if (inet_aton(ip1, &inp) == 0) {
                printf("Invalid adress %s in line \n%s\n", ip1, buffer);
                printf("Error: %s\n", strerror(errno));
            }
            netip1 = inp.s_addr;
            if (inet_aton(ip2, &inp) == 0) {
                printf("Invalid adress %s in line \n%s\n", ip2, buffer);
                printf("Error: %s\n", strerror(errno));
            }
            netip2 = inp.s_addr;

            queuenum = numRules % amountOfQueues;
            rulehash = hash(&proto, &netip1, &port1, &netip2, &port2);
            addConnection(&rulehash, queuenum);
            if(proto == IPPROTO_TCP){
                addState(&rulehash, &s);
            }
            numRules++;
        }
    }
}


static const struct rte_eth_conf port_conf_default = {
        .rxmode = {.max_rx_pkt_len = RTE_ETHER_MAX_LEN}
};


/*
 * Initializes a given port using global settings and with the RX buffers
 * coming from the mbuf_pool passed as a parameter.
 */
static inline int
port_init(uint16_t port, struct rte_mempool *mbuf_pool) {
    struct rte_eth_conf port_conf = port_conf_default;
    const uint16_t rx_rings = 1, tx_rings = 1;
    int retval;
    uint16_t q;
    char name[RTE_ETH_NAME_MAX_LEN];

    if (port >= rte_eth_dev_count_avail())
        return -1;
    // Configure the Ethernet device.
    retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
    if (retval != 0)
        return retval;


    retval = rte_eth_dev_get_name_by_port(port, name);
    if (retval < 0)
        return retval;


    // Allocate and set up 1 RX queue per Ethernet port.
    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(port, q, RX_RING_SIZE,
                                        rte_eth_dev_socket_id(port), NULL, mbuf_pool);
        if (retval < 0)
            return retval;
    }
    // Allocate and set up 1 TX queue per Ethernet port.
    for (q = 0; q < tx_rings; q++) {
        retval = rte_eth_tx_queue_setup(port, q, TX_RING_SIZE,
                                        rte_eth_dev_socket_id(port), NULL);
        if (retval < 0)
            return retval;
    }
    // Start the Ethernet port.
    retval = rte_eth_dev_start(port);
    if (retval < 0)
        return retval;
    // Display the port MAC address.
    struct rte_ether_addr addr;
    rte_eth_macaddr_get(port, &addr);
    printf("Port %u MAC: %02" PRIx8 " %02" PRIx8 " %02" PRIx8
           " %02" PRIx8 " %02" PRIx8 " %02" PRIx8 "\n",
           (unsigned) port,
           addr.addr_bytes[0], addr.addr_bytes[1],
           addr.addr_bytes[2], addr.addr_bytes[3],
           addr.addr_bytes[4], addr.addr_bytes[5]);
    // Enable RX in promiscuous mode for the Ethernet device.
    rte_eth_promiscuous_enable(port);
    return 0;
}

static inline void destruct(struct packetQueueElement *pElement) {
    rte_pktmbuf_free(pElement->packet);
    pElement->port = 0;
    pElement->id = 0;
    pElement->pid = -1;
}



static const uint16_t receive(uint16_t port, struct rte_mbuf *bufs[32]) {


    return rte_eth_rx_burst(port, 0, bufs, BURST_SIZE);

}


static void forward(uint16_t port, struct rte_mbuf *buf) {
    // Send burst of TX packets, to second port of pair.

    const uint16_t nb_tx = rte_eth_tx_burst(port, 0, &buf, 1);

    if (unlikely(nb_tx < 1)) {
        rte_pktmbuf_free(buf);
    }
}


int recieveWrapper(void *pVoid){
    int i;
    struct rte_mbuf *bufs[BURST_SIZE];
    *bufs = calloc(BURST_SIZE, sizeof(struct rte_mbuf));
    const int* recv_port = pVoid;
    const int snd_port = (const int) (*recv_port ^ 1);
    uint16_t nb_rx;



    while(1){

        nb_rx = receive(portids[*recv_port], bufs);
        if (likely(nb_rx > 0)) {
            for (i = 0; i < nb_rx; i = i + 1) {
                addToDecideQueue(bufs[i], snd_port);
            }
        }
    }
}


int forwardWrapper(void *pVoid){

    const int *nic = pVoid;
    struct  rte_mbuf *buf;
    uint16_t port;

    struct packetQueueElement *toSend = malloc(sizeof(struct packetQueueElement));
    struct packetQueueElement *old;
    toSend->port = 0;
    toSend->id = 0;
    toSend->pid = -1;

    int running = 1;

    while (running) {
        old = toSend;
        do{
            toSend = getFromQueue(forwardQueues[*nic], toSend);
        }while(toSend == old);



        buf = toSend->packet;
        port = toSend->port;

#if DEBUGGING > 4
        sprintf(tmp, "pkt %i sent\n", toSend->pid);
        strcat(debug, tmp);
#endif

        forward(port, buf);

        toSend->id = 0;
        toSend->pid = -1;
        toSend->port = 0;
    }
}



static inline int inspectPacket(struct rte_mbuf *buffer, int *id) {


    //struct ether_header *eh = (struct ether_header *) buffer;
    struct rte_ipv4_hdr *iph = rte_pktmbuf_mtod_offset(buffer, struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));
    struct rte_tcp_hdr *tcph = rte_pktmbuf_mtod_offset(buffer, struct rte_tcp_hdr *, sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));

    uint8_t *snd_state, *rec_state;
    uint8_t futurSndState, futurRecvState;
    tcp_seq seq, ack_seq;
    int ackChallenge = 0;
    int total_iplength, ip_hdr_length;
    uint8_t tcp_hdr_length;

    tcpState *conState = getState(id);
    if (conState == NULL) {
        return 0;
    }


    if (iph->src_addr < iph->dst_addr) {//s_ip < c_ip
        snd_state = &(conState->srv_state);
        rec_state = &(conState->cli_state);
    } else {
        snd_state = &(conState->cli_state);
        rec_state = &(conState->srv_state);
    }



    const int flags = tcph->tcp_flags & ((TH_ACK + TH_FIN) + (TH_SYN + TH_RST));

    // darf dieser state das packet schicken?
    switch (*snd_state) {
        case TCP_ESTABLISHED: //ack fin+ack
            switch (flags) {
                case TH_ACK:
                    futurSndState = futurRecvState = TCP_ESTABLISHED;
                    break;
                case TH_FIN + TH_ACK:
                    futurSndState = TCP_FIN_WAIT1;
                    futurRecvState = TCP_CLOSE_WAIT;
                    break;
                case TH_ACK + TH_RST:
                    futurSndState = futurRecvState = TCP_CLOSE;
                    break;
                default:
                    return 0;
            }
            break;
        case TCP_CLOSE://syn
            if (flags != TH_SYN) {
                return 0;
            }
            futurSndState = TCP_SYN_SENT;
            futurRecvState = TCP_SYN_RECV;
            break;
        case TCP_SYN_RECV://syn ack fin syn+ack
            switch (flags) {
                case TH_SYN + TH_ACK:
                    futurSndState = *snd_state;
                    futurRecvState = TCP_ESTABLISHED;
                    break;
                case TH_SYN:
                    futurSndState = futurRecvState = TCP_SYN_RECV;
                    break;
                case TH_FIN + TH_ACK:
                    futurSndState = TCP_FIN_WAIT1;
                    futurRecvState = TCP_CLOSE_WAIT;
                    break;
                case TH_RST + TH_ACK:
                    futurSndState = futurRecvState = TCP_CLOSE;
                    break;
                default:
                    return 0;
            }
            break;
        case TCP_CLOSE_WAIT://fin+ack ack
            switch (flags) {
                case TH_ACK:
                    futurSndState = TCP_CLOSE_WAIT;
                    futurRecvState = TCP_FIN_WAIT2;
                    ackChallenge = 1;
                    break;
                case TH_FIN + TH_ACK:
                    if (*rec_state == TCP_FIN_WAIT1) {
                        futurSndState = futurRecvState = TCP_CLOSING;
                        break;
                    } else {
                        futurSndState = TCP_LAST_ACK;
                        futurRecvState = TCP_TIME_WAIT;
                        break;
                    }
                case TH_ACK + TH_RST:
                    futurSndState = futurRecvState = TCP_CLOSE;
                    break;
                default:
                    return 0;
            }
            break;
        case TCP_FIN_WAIT1: //ack
        case TCP_FIN_WAIT2: // ack
            if (flags == TH_ACK) {
                futurSndState = *snd_state;
                futurRecvState = *rec_state;
                break;
            }
        case TCP_TIME_WAIT: //ack
            if (flags == TH_ACK) {
                futurSndState = futurRecvState = TCP_CLOSE;
                break;
            }
        case TCP_CLOSING:   //ack
            if ((tcph->tcp_flags & (TH_ACK + TH_FIN + TH_SYN)) == TH_ACK) {
                futurSndState = TCP_CLOSE;
                if (tcph->tcp_flags & TH_RST)
                    futurRecvState = TCP_CLOSE;
                else
                    futurRecvState = *rec_state;
                break;
            }
        case TCP_SYN_SENT:
        case TCP_LAST_ACK:
        default:
            return 0;
    }


#if DEBUGGING > 1
    sprintf(tmp, "Old Server State %"PRIu8"\nOld Client State %"PRIu8"\n", conState->srv_state, conState->cli_state);
    strcat(debug, tmp);
    sprintf(tmp, "Server:  %"PRIu32" Client: %"PRIu32"\n", conState->srv_seq, conState->cli_seq);
    strcat(debug, tmp);
#endif
    //check seq nums
    seq = rte_be_to_cpu_32(tcph->sent_seq);
    ack_seq = rte_be_to_cpu_32(tcph->recv_ack);
    uint16_t tcp_window_size = rte_be_to_cpu_16(tcph->rx_win);

    total_iplength = rte_be_to_cpu_16(iph->total_length);
    ip_hdr_length = iph->version_ihl & RTE_IPV4_HDR_IHL_MASK;
    tcp_hdr_length = (tcph->data_off >> 4);

    if (iph->src_addr < iph->dst_addr) {//=> server = sender  s_ip < c_ip
        // added 1 packet (max ipV4 payload size) tolerance
        if ((SEQ_LT(seq, conState->srv_seq) || SEQ_GEQ(seq, conState->srv_seq + conState->srv_window)) && !(tcph->tcp_flags & TH_SYN)) {
#if DEBUGGING > 3
            sprintf(tmp, "wrong seq num \n");
            strcat(debug, tmp);
#endif
            return 0;
        }

        if (SEQ_LT(ack_seq, conState->cli_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
#if DEBUGGING > 3
            sprintf(tmp, "ACK belongs to previous packet\n");
            strcat(debug, tmp);
#endif
            return 1;
        }
        //fin ack -> fin ack -> ack valide depending on ack seq
        if (futurSndState == TCP_CLOSING && futurRecvState == TCP_CLOSING && SEQ_GT(ack_seq, conState->cli_seq)) {
            futurSndState = TCP_CLOSE;
        }
        conState->cli_seq = ack_seq;
        conState->cli_window = tcp_window_size * TCP_WINDOW_SCALING;
        conState->srv_state = futurSndState;
        conState->cli_state = futurRecvState;

    } else { //=> client = sender
        //added 1 packet tolerance
        if ((SEQ_LT(seq, conState->cli_seq) || SEQ_GEQ(seq, conState->cli_seq + conState->cli_window)) && !(tcph->tcp_flags & TH_SYN))  {
#if DEBUGGING > 3
            sprintf(tmp, "wrong seq num \n");
            strcat(debug, tmp);
#endif
            return 0;
        }

        if (SEQ_LT(ack_seq, conState->srv_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
#if DEBUGGING > 3
            sprintf(tmp, "ACK belongs to previous packet\n");
            strcat(debug, tmp);
#endif
            return 1;
        }

        if (futurSndState == TCP_CLOSING && futurRecvState == TCP_CLOSING && SEQ_GT(ack_seq, conState->srv_seq)) {
            futurSndState = TCP_CLOSE;
        }

        conState->srv_seq = ack_seq;
        conState->srv_window = tcp_window_size * TCP_WINDOW_SCALING;
        conState->cli_state = futurSndState;
        conState->srv_state = futurRecvState;
    }


    if ((tcph->tcp_flags & TH_RST) || (futurSndState == TCP_CLOSE && futurRecvState == TCP_CLOSE)) {
        conState->cli_seq = 0;
        conState->srv_seq = 0;
    }

#if DEBUGGING > 1
    sprintf(tmp, "New Server State %i\nNew Client State %i\n", conState->srv_state, conState->cli_state);
    strcat(debug, tmp);
    sprintf(tmp, "Server:  %"PRIu32" Client: %"PRIu32"\n", conState->srv_seq, conState->cli_seq);
    strcat(debug, tmp);
#endif

    return 1;

}


int packetInspector(void* arg){
    const int *queuenum = arg;



    int running = 1;
    struct packetQueueElement *toBeInspected = malloc(sizeof(struct packetQueueElement));
    struct packetQueueElement *old;
    toBeInspected->port = 0;
    toBeInspected->id = 0;
    toBeInspected->pid = -1;



    while (running){

        old = toBeInspected;
        do{
            toBeInspected = getFromQueue(flowQueues[*queuenum], toBeInspected);

        }while (toBeInspected == old);

        if(inspectPacket(toBeInspected->packet, &toBeInspected->id)){
            addToQueue(forwardQueues[toBeInspected->port], toBeInspected);

        }
        else{
#if DEBUGGING > 4
            sprintf(tmp, "pkt %i blocked\n", toBeInspected->pid);
            strcat(debug, tmp);
#endif
            destruct(toBeInspected);

        }
    }

}


void decideAndForward(struct packetQueueElement *buffer) {

    int *queue, id;
    struct rte_ether_hdr *eth_hdr;
    struct rte_ipv4_hdr *ip_hdr;
    struct rte_tcp_hdr *tcp_hdr;
    struct rte_udp_hdr *udp_hdr;
    uint32_t ip_dst;
    struct rte_mbuf help = *(buffer->packet);
    struct rte_mbuf *toBeJudged = &help;

    eth_hdr = rte_pktmbuf_mtod(toBeJudged, struct rte_ether_hdr *);


    switch (rte_cpu_to_be_16(eth_hdr->ether_type)) {
        case RTE_ETHER_TYPE_IPV4:
            ip_hdr = rte_pktmbuf_mtod_offset(toBeJudged, struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));
            switch (ip_hdr->next_proto_id) {
                case IPPROTO_TCP:


                    tcp_hdr = rte_pktmbuf_mtod_offset(toBeJudged, struct rte_tcp_hdr *, sizeof(struct rte_ether_hdr)+sizeof(struct rte_ipv4_hdr));
#if DEBUGGING > 2
                    sprintf(tmp, "ID: %"PRIu32":%05d->%"PRIu32":%05d\n", rte_be_to_cpu_32(ip_hdr->src_addr), rte_be_to_cpu_16(tcp_hdr->src_port),
                            rte_be_to_cpu_32(ip_hdr->dst_addr), rte_be_to_cpu_16(tcp_hdr->dst_port));
                    strcat(debug, tmp);
                    sprintf(tmp, "Flags:  %i \n", tcp_hdr->tcp_flags);
                    strcat(debug, tmp);
                    sprintf(tmp, "Seq:  %"PRIu32" Ack_seq: %"PRIu32" \n", rte_be_to_cpu_32(tcp_hdr->sent_seq),
                            rte_be_to_cpu_32(tcp_hdr->recv_ack));
                    strcat(debug, tmp);
#endif
                    id = hash(&(ip_hdr->next_proto_id), (const unsigned long *) &ip_hdr->src_addr, &tcp_hdr->src_port,
                              (const unsigned long *) &ip_hdr->dst_addr, &tcp_hdr->dst_port);
                    buffer->id = id;
                    queue = getConnection(&id);
                    if(queue != NULL){
                        addToQueue(flowQueues[*queue], buffer);
                    } else {

                    }
                    break;
                case IPPROTO_UDP :
		{
		    uint8_t l4_type = (uint8_t) toBeJudged->l4_type;
                    udp_hdr = rte_pktmbuf_mtod_offset(toBeJudged, struct rte_udp_hdr *, sizeof(struct rte_ether_hdr)+sizeof(struct rte_ipv4_hdr));
                    id = hash(&l4_type, (const unsigned long *) &(ip_hdr->src_addr), &(udp_hdr->src_port),
                              (const unsigned long *) &(ip_hdr->dst_addr), &(udp_hdr->dst_port));
                    if(getConnection(&id) != NULL){
                        addToQueue(forwardQueues[buffer->port], buffer);
                        break;
                    }
		}
                default:
#if DEBUGGING > 4
                    sprintf(tmp, "pkt %i blocked\n", buffer->pid);
                    strcat(debug, tmp);
#endif
                    destruct(buffer);
            }
            break;

        case RTE_ETHER_TYPE_ARP:
            addToQueue(forwardQueues[buffer->port], buffer);
            break;
        default:
#if DEBUGGING > 4
            sprintf(tmp, "pkt %i blocked\n", buffer->pid);
            strcat(debug, tmp);
#endif
            destruct(buffer);
    }
}


static __attribute__((noreturn)) int
lcore_main(void *args) {

    struct packetQueueElement *buf = malloc(sizeof(struct packetQueueElement));
    struct packetQueueElement *old;
    buf->packet = malloc(sizeof(struct rte_mbuf));
    buf->port = 0;
    buf->id = 0;
    buf->pid = -1;

    // Run until the application is quit or killed.
    while (1) {
        old = buf;

        do{
            buf = getFromQueue(decideQueue, buf);
        }while(old == buf);


        decideAndForward(buf);


#if DEBUGGING > 0
        sprintf(tmp, "\n---------------------------------------------------\n");
        strcat(debug, tmp);
        printf("%s\n", debug);
        fflush(stdout);
        memset(debug, 0, strlen(debug));
#endif

    }
}

/*
 * The main function, which does initialization and calls the per-lcore
 * functions.
 */
int
main(int argc, char *argv[]) {
    struct rte_mempool *mbuf_pool;
    unsigned lcore_id = rte_lcore_id();
    int args[NUMQUEUES];
    // Initialize the Environment Abstraction Layer (EAL).
    int ret = rte_eal_init(argc, argv);
    if (ret < 0)

        rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");
    argc -= ret;
    argv += ret;

    if (rte_eth_dev_get_port_by_name(INTERFACE_ID_1, &portids[0]) != 0)
        rte_exit(EXIT_FAILURE, "Cannot find device %s \n",
                 INTERFACE_ID_1);


    if (rte_eth_dev_get_port_by_name(INTERFACE_ID_2, &portids[1]) != 0)
        rte_exit(EXIT_FAILURE, "Cannot find device %s \n",
                 INTERFACE_ID_2);

    // Creates a new mempool in memory to hold the mbufs.
    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * 2,
                                        MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");
    // Initialize all ports.
    if (port_init(portids[0], mbuf_pool) != 0)
        rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu8 "\n",
                 portids[0]);
    if (port_init(portids[1], mbuf_pool) != 0)
        rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu8 "\n",
                 portids[1]);


    readRules("../rules.csv", NUMQUEUES);
    initQueue(&decideQueue);
    forwardQueues = calloc(2, sizeof(packetQueue));
    for (int i = 0; i < 2; ++i) {
        initQueue(&forwardQueues[i]);
    }
    flowQueues = calloc(NUMQUEUES, sizeof(packetQueue));
    for (int i = 0; i < NUMQUEUES; ++i) {
        initQueue(&flowQueues[i]);
        args[i] = i;
    }

    lcore_id = rte_get_next_lcore(lcore_id,1,0);
    if(rte_eal_remote_launch(forwardWrapper, &args[0], lcore_id)<0){
        printf("failed to init Thread\n");
    }
    lcore_id = rte_get_next_lcore(lcore_id,1,0);
    if(rte_eal_remote_launch(forwardWrapper, &args[1], lcore_id)<0){
        printf("failed to init Thread\n");
    }
    for (int j = 0; j < NUMQUEUES; j = j+1) {
        lcore_id = rte_get_next_lcore(lcore_id,1,0);
        if(rte_eal_remote_launch(packetInspector, &args[j], lcore_id)<0){
            printf("failed to init Thread\n");
        }
    }
    lcore_id = rte_get_next_lcore(lcore_id,1,0);
    if(rte_eal_remote_launch(recieveWrapper, &args[0], lcore_id)<0){
        printf("failed to init Thread\n");
    }
    lcore_id = rte_get_next_lcore(lcore_id,1,0);
    if(rte_eal_remote_launch(recieveWrapper, &args[1], lcore_id)<0){
        printf("failed to init Thread\n");
    }
    lcore_main(NULL);


    return 0;
}
