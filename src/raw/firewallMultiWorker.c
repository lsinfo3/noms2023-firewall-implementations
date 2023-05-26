#define _GNU_SOURCE //access makros for thread affinity

#include <sys/socket.h> //socket calls
#include <linux/if_packet.h> //socket addressen
#include <net/if.h> //if_tonametoindex
#include <net/ethernet.h> //ethernet header
#include <linux/ip.h> //ip header
#include <netinet/tcp.h> //tcp header
#include <netinet/udp.h> //udp header
#include <arpa/inet.h> //inet_ntop
#include <stdio.h> //print, ntohs
#include <sys/ioctl.h> //ioctl for promiscuous mode
#include <pthread.h> //thread affinity
#include <errno.h> //error codes
#include <string.h> //debug und fail ausgabe

#include <inttypes.h> //debug: print uint32_t
#include "../includes/klib/khash.h" //hash tabel

// 0=none, 1=notify each rcv pkt, 2=track state changes, 3= show tcp flags, 4= show retran. blocked ,
#define DEBUGGING 0

#define BUF_LENGTH 1500 + sizeof(struct ether_header)
#define IP_PROTO_UDP 17
#define IP_PROTO_TCP 6

#define MAX_TCP_PKT_SIZE 1448
#define TCP_WINDOW_SCALING 1024 //(this is a Window Scale option value of 10)

#define SEQ_GT(a,b) ((int)((a)-(b)) > 0)
#define SEQ_LT(a,b) ((int)((a)-(b)) < 0)
#define SEQ_GEQ(a,b) ((int)((a)-(b)) >= 0)
#define SEQ_LEQ(a,b) ((int)((a)-(b)) <= 0)

#define QUEUE_LENGTH 1024
#define NUMQUEUES 2


#if DEBUGGING > 0
char debug[4096];
char tmp[60];
pthread_mutex_t debugMutex;
#endif

int pnum = 1;

struct packetQueueElement {
    uint8_t *packet;
    size_t *len;
    int socket;
    int pid;
    int id;
};

typedef struct {
    struct packetQueueElement **queue;
    pthread_mutex_t *mutex;
    int head;
    int tail;
} packetQueue;

typedef struct { //s_ip < c_ip
    tcp_seq srv_seq;
    tcp_seq cli_seq;
    uint8_t srv_state;
    uint8_t cli_state;
    uint32_t srv_window;
    uint32_t cli_window;
    uint queue;
} tcpState;

KHASH_MAP_INIT_INT(rules, int)

KHASH_MAP_INIT_INT(states, tcpState)

kh_rules_t *connections = NULL;
kh_states_t *states = NULL;

int sockets[2];

packetQueue *decideQueue = NULL;
packetQueue **flowQueues = NULL;//[NUMQUEUES];
packetQueue **forwardQueues;

static inline struct packetQueueElement * addToQueue(packetQueue *queue, struct packetQueueElement *toBeAdded) {
    struct packetQueueElement *swap;
    pthread_mutex_lock(queue->mutex);
    swap = queue->queue[queue->tail];
    queue->queue[queue->tail] = toBeAdded;
    //toBeAdded = swap;
    queue->tail = queue->tail + 1;
    if(queue->tail >= QUEUE_LENGTH){
        queue->tail = 0;
    }
    pthread_mutex_unlock(queue->mutex);
    return swap;
}

static inline struct packetQueueElement * addToDecideQueue(struct packetQueueElement *toBeAdded) {
    struct packetQueueElement *swap;
    pthread_mutex_lock(decideQueue->mutex);
    toBeAdded->pid = pnum;
    swap = decideQueue->queue[decideQueue->tail];
    decideQueue->queue[decideQueue->tail] = toBeAdded;
    //toBeAdded = swap;
    decideQueue->tail = decideQueue->tail + 1;
    if (decideQueue->tail >= QUEUE_LENGTH) {
        decideQueue->tail = 0;
    }
    pnum = pnum + 1;
    pthread_mutex_unlock(decideQueue->mutex);

#if DEBUGGING > 4
    pthread_mutex_lock(&debugMutex);
    sprintf(tmp, "Received %i (%i bytes) from %i\n", toBeAdded->pid, *(toBeAdded->len), toBeAdded->socket);
    strcat(debug, tmp);
    pthread_mutex_unlock(&debugMutex);
#endif
    return swap;
}

static inline struct packetQueueElement *getFromQueue(packetQueue *queue, struct packetQueueElement *ret) {
    struct packetQueueElement *element;
    pthread_mutex_lock(queue->mutex);
    if (queue->head == queue->tail){
        pthread_mutex_unlock(queue->mutex);
        return ret;
    }

    element = queue->queue[queue->head];
    queue->queue[queue->head] = ret;
    ret = element;
    queue->head = queue->head + 1;
    if (queue->head >= QUEUE_LENGTH) {
        queue->head = 0;
    }
    pthread_mutex_unlock(queue->mutex);

    return ret;
}

static inline void initQueue(packetQueue **toBeInitialized) {
    packetQueue *queue;
    queue = malloc(sizeof(packetQueue));
    queue->queue = calloc(QUEUE_LENGTH, sizeof(struct packetQueueElement *));
    queue->mutex = malloc(sizeof(pthread_mutex_t));

    queue->tail = 0;
    queue->head = 0;
    pthread_mutex_init(queue->mutex, NULL);
    for(int i = 0; i < QUEUE_LENGTH; i = i+1){
        queue->queue[i] = malloc(sizeof(struct packetQueueElement));
        queue->queue[i]->packet = calloc(BUF_LENGTH, sizeof(uint8_t));
        queue->queue[i]->len = malloc(sizeof(size_t));
        queue->queue[i]->socket = -1;
        queue->queue[i]->pid = -1;
        queue->queue[i]->id = -1;

    }
    *toBeInitialized = queue;
}

int hash(const __u8 *proto, const unsigned long *s_addr, const u_int16_t *s_port, const unsigned long *c_addr,
         const uint16_t *c_port) {
    int erg = (int) ((*s_addr ^ *s_port) ^ (*c_addr ^ *c_port) ^ *proto);
    return erg;
}

void addConnection(const int *key, const int *num) {
    int ret;
    khint_t k;
    k = kh_put_rules(connections, (khint32_t) *key, &ret);
    if (!ret) {
        kh_del_rules(connections, k);
    }
    kh_value(connections, k) = *num;
}

int *getConnection(const int *key) {
    khint_t k;
    int *s;
    k = kh_get_rules(connections, (khint32_t) *key);
    if (k == kh_end(connections)) {
        return NULL;
    }
    s = &kh_value(connections, k);
    return s;
}

void addState(const int *key, const tcpState *s) {
    int ret;
    khint_t k;
    k = kh_put_states(states, (khint32_t) *key, &ret);
    if (!ret) {
        kh_del_states(states, k);
    }
    kh_value(states, k) = *s;
}

tcpState *getState(const int *key) {
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
    int i, j, rulehash, queuenum, numRules;
    uint16_t port1, port2;
    uint8_t proto;
    unsigned long netip1, netip2;
    struct in_addr inp;
    FILE *fp;

    tcpState s;
    connections = kh_init_rules();
    states = kh_init_states();

    s.cli_state = TCP_CLOSE;
    s.cli_seq = 0;
    s.cli_window = 0;
    s.srv_seq = 0;
    s.srv_window = 0;
    s.srv_state = TCP_CLOSE;

    numRules = 0;

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
            addConnection(&rulehash, &queuenum);
            if (proto == IP_PROTO_TCP) {
                addState(&rulehash, &s);
            }
            numRules++;
        }
    }
}

static inline void print_sys_error(const char *msg) {
    printf("%s;%s(%i)\n", msg, strerror(errno), errno);
    fflush(stdout);
}

int inititialise_socket(int ifidx) {
    int sock = 0;
    int erfolg;
    struct sockaddr_ll sll;
    socklen_t sll_len = sizeof(sll);
    unsigned short domain = AF_PACKET;
    __be16 protocol = htons(ETH_P_ALL);
    struct ifreq ethreq;
    //create socket
    sock = socket(domain, SOCK_RAW, protocol);
    if (sock < 0) {
        printf("Raw socket error :%s\n", strerror(errno));
        return -1;
    }
    //bind socket to given interface
    bzero(&sll, sll_len);
    sll.sll_family = domain;
    sll.sll_ifindex = ifidx;
    sll.sll_protocol = protocol;
    erfolg = bind(sock, (struct sockaddr *) &sll, sll_len);
    if (erfolg < 0) {
        printf("bind error :%s\n", strerror(errno));
        return -1;
    }
    //set to promiscuous mode (receive everything passing the interface)
    ethreq.ifr_ifindex = ifidx;
    erfolg = ioctl(sock, SIOCGIFFLAGS, &ethreq);
    if (erfolg < 0) {
        printf("Promisc 1 error :%s, %i\n", strerror(errno), errno);
        return -1;
    }
    ethreq.ifr_flags |= IFF_PROMISC;
    erfolg = ioctl(sock, SIOCSIFFLAGS, &ethreq);
    if (erfolg < 0) {
        printf("Promisc 2 error :%s\n", strerror(errno));
        return -1;
    }
    return sock;
}


static inline void destruct(struct packetQueueElement *pElement){
    pElement->packet[0] =  '\0';
    *(pElement->len) = 0;
    pElement->socket = -1;
    pElement->pid = -1;
    pElement->id = -1;
}

int receive(const int *socket, uint8_t buffer[]) {
    int numb = -1;
    numb = (int) recv(*socket, buffer, BUF_LENGTH, MSG_DONTWAIT);
    if (numb < 0) {
        if (errno == EAGAIN && errno == EWOULDBLOCK) {
            numb = 0;
        } else {
            printf("Read error :%s\n", strerror(errno));
            return -1;
        }
    }
    return numb;
}

void forward(const int *socket, uint8_t buf[], const size_t *numbytes) {
    if (send(*socket, buf, *numbytes, 0) <= 0) {
        print_sys_error("Send error");
    }
}

void *receiveWrapper(void *arg) {
    const int *from = arg;
    uint8_t *buffer;
    int numb;
    int running = 1;
    struct packetQueueElement *add;
    add = malloc(sizeof(struct packetQueueElement));
    add->packet = calloc(BUF_LENGTH, sizeof(uint8_t));
    add->len = malloc(sizeof(size_t));
    add->socket = -1;
    add->pid = -1;
    add->id = -1;

    while (running) {
        buffer = add->packet;
        numb = -1;
        while (numb <= 0) {
            numb = receive(&sockets[*from], buffer);
            if (numb < 0 && errno != ETIME) {
                print_sys_error("Read error:");
            }
        }
        add->socket = (*from + 1) % 2;
        *(add->len) = (size_t) numb;


        add = addToDecideQueue(add);
    }
}

void *forwardWrapper(void *arg) {
    uint8_t *buf;
    const int *socket = arg;
    size_t *numbytes;
    struct packetQueueElement *toSend;
    struct packetQueueElement *old;
    toSend = malloc(sizeof(struct packetQueueElement));
    toSend->packet = calloc(BUF_LENGTH, sizeof(uint8_t));
    toSend->len = malloc(sizeof(size_t));
    toSend->socket = -1;
    toSend->pid = -1;
    toSend->id = -1;


    int running = 1;
    while (running) {
        old = toSend;
        do{
            toSend = getFromQueue(forwardQueues[*socket], toSend);
        }while (toSend == old);
        buf = toSend->packet;
        numbytes = toSend->len;
        forward(&sockets[*socket], buf, (const size_t *) numbytes);
#if DEBUGGING > 4

        pthread_mutex_lock(&debugMutex);
        sprintf(tmp, "Sent %i (%li bytes) to %i \n",   toSend->pid, *numbytes, *socket);
        strcat(debug, tmp);
        pthread_mutex_unlock(&debugMutex);

#endif
        destruct(toSend);
    }
}

static inline int inspectPacket(const uint8_t *buffer, int *id) {
    struct iphdr *iph = (struct iphdr *) (buffer + (sizeof(struct ether_header)));
    struct tcphdr *tcph = (struct tcphdr *) (buffer + sizeof(struct iphdr) + sizeof(struct ether_header));
    uint8_t *snd_state, *rec_state;
    uint8_t futurSndState, futurRecvState;
    tcp_seq seq, ack_seq;
    int ackChallenge = 0;
    tcpState *conState = getState(id);

    if (iph->saddr < iph->daddr) {//s_ip < c_ip
        snd_state = &(conState->srv_state);
        rec_state = &(conState->cli_state);
    } else {
        snd_state = &(conState->cli_state);
        rec_state = &(conState->srv_state);
    }

    const int flags = tcph->th_flags & ((TH_ACK + TH_FIN) + (TH_SYN + TH_RST));
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
            if ((tcph->th_flags & (TH_ACK + TH_FIN + TH_SYN)) == TH_ACK) {
                futurSndState = TCP_CLOSE;
                if (tcph->th_flags & TH_RST)
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
    pthread_mutex_lock(&debugMutex);
    sprintf(tmp, "Old Server State %"PRIu8"\nOld Client State %"PRIu8"\n", conState->srv_state, conState->cli_state);
    strncat(debug, tmp, 60);
    sprintf(tmp, "Server:  %"PRIu32" Client: %"PRIu32"\n", conState->srv_seq, conState->cli_seq);
    strncat(debug, tmp, 60);
    pthread_mutex_unlock(&debugMutex);
#endif
    //check seq nums
    seq = ntohl(tcph->th_seq);
    ack_seq = ntohl(tcph->th_ack);
    uint16_t tcp_window_size = ntohs(tcph->th_win);

    if (iph->saddr < iph->daddr) {//=> server = sender  s_ip < c_ip
        if ((SEQ_LT(seq, conState->srv_seq) || SEQ_GEQ(seq, conState->srv_seq + conState->srv_window)) && !(tcph->th_flags & TH_SYN)) {
#if DEBUGGING > 3
            pthread_mutex_lock(&debugMutex);
            sprintf(tmp, "wrong seq num \n");
            strncat(debug, tmp, 60);
            pthread_mutex_unlock(&debugMutex);
#endif
            return 0;
        }
        if (SEQ_LT(ack_seq, conState->cli_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
#if DEBUGGING > 3
            pthread_mutex_lock(&debugMutex);
            sprintf(tmp, "ACK belongs to previous packet\n");
            strncat(debug, tmp, 60);
            pthread_mutex_unlock(&debugMutex);
#endif
            return 1;
        }
        //fin ack -> fin ack -> ack valide depending on ack seq
        if (futurSndState == TCP_CLOSING && futurRecvState == TCP_CLOSING && ack_seq == conState->cli_seq) {
            futurSndState = TCP_CLOSE;
        }
        conState->cli_seq = ack_seq;
        conState->cli_window = tcp_window_size * TCP_WINDOW_SCALING;
        conState->srv_state = futurSndState;
        conState->cli_state = futurRecvState;
    } else {
        if ((SEQ_LT(seq, conState->cli_seq) || SEQ_GEQ(seq, conState->cli_seq + conState->cli_window)) && !(tcph->th_flags & TH_SYN)) {
#if DEBUGGING > 3
            pthread_mutex_lock(&debugMutex);
            sprintf(tmp, "wrong seq num \n");
            strncat(debug, tmp, 60);
            pthread_mutex_unlock(&debugMutex);
#endif
            return 0;
        }
        if (SEQ_LT(ack_seq, conState->srv_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
#if DEBUGGING > 3
            pthread_mutex_lock(&debugMutex);
            sprintf(tmp, "ACK belongs to previous packet\n");
            strncat(debug, tmp, 60);
            pthread_mutex_unlock(&debugMutex);
#endif
            return 1;
        }
        if (futurSndState == TCP_CLOSING && futurRecvState == TCP_CLOSING && ack_seq > conState->srv_seq) {
            futurSndState = TCP_CLOSE;
        }
        conState->srv_seq = ack_seq;
        conState->srv_window = tcp_window_size * TCP_WINDOW_SCALING;
        conState->cli_state = futurSndState;
        conState->srv_state = futurRecvState;
    }

    if ((tcph->th_flags & TH_RST) || (futurSndState == TCP_CLOSE && futurRecvState == TCP_CLOSE)) {
        conState->cli_seq = 0;
        conState->srv_seq = 0;
    }
#if DEBUGGING > 1
    pthread_mutex_lock(&debugMutex);
    sprintf(tmp, "New Server State %i\nNew Client State %i\n", conState->srv_state, conState->cli_state);
    strncat(debug, tmp, 60);
    sprintf(tmp, "Server:  %"PRIu32" Client: %"PRIu32"\n", conState->srv_seq, conState->cli_seq);
    strncat(debug, tmp, 60);
    pthread_mutex_unlock(&debugMutex);
#endif
    return 1;
}

void *decideAndForward() {
    int id;
    uint8_t *buf;
    struct ether_header *eh;
    struct iphdr *iph;
    struct tcphdr *tcph;
    struct udphdr *udph;
    int *queue;
    struct packetQueueElement *toBeJudged;
    struct packetQueueElement *old;
    toBeJudged = malloc(sizeof(struct packetQueueElement));
    toBeJudged->packet = calloc(BUF_LENGTH, sizeof(uint8_t));
    toBeJudged->len = malloc(sizeof(size_t));
    toBeJudged->socket = -1;
    toBeJudged->pid = -1;
    toBeJudged->id = -1;

#if DEBUGGING > 2
    char sender[INET_ADDRSTRLEN], recepient[INET_ADDRSTRLEN];
#endif
    int running = 1;
    while (running) {
        old = toBeJudged;
        do{
            toBeJudged = getFromQueue(decideQueue, toBeJudged);
        }while (toBeJudged == old);
        buf = toBeJudged->packet;
        eh = (struct ether_header *) buf;
        iph = (struct iphdr *) (buf + (sizeof(struct ether_header)));
        tcph = (struct tcphdr *) (buf + sizeof(struct iphdr) + sizeof(struct ether_header));
        udph = (struct udphdr *) (buf + sizeof(struct iphdr) + sizeof(struct ether_header));

        switch (ntohs(eh->ether_type)) {
            case ETHERTYPE_IP:
                switch (iph->protocol) {
                    case IP_PROTO_TCP:
#if DEBUGGING > 2
                        pthread_mutex_lock(&debugMutex);
                        inet_ntop(AF_INET, &iph->saddr, sender, INET_ADDRSTRLEN);
                        inet_ntop(AF_INET, &iph->daddr, recepient, INET_ADDRSTRLEN);
                        sprintf(tmp, "PID: %i\n", toBeJudged->pid);
                        strncat(debug, tmp, 60);
                        sprintf(tmp, "ID: %s:%05d->%s:%05d\n", sender, ntohs(tcph->source), recepient,
                                ntohs(tcph->dest));
                        strncat(debug, tmp, 60);
                        sprintf(tmp, "Syn:  %i Ack: %i Fin: %i Rst: %i Psh: %i\n", tcph->syn, tcph->ack, tcph->fin,
                                tcph->rst, tcph->psh);
                        strncat(debug, tmp, 60);
                        sprintf(tmp, "Seq:  %"PRIu32" Ack_seq: %"PRIu32"\n", ntohl(tcph->seq),
                                ntohl(tcph->ack_seq));
                        strncat(debug, tmp, 60);
                        pthread_mutex_unlock(&debugMutex);
#endif
                        id = hash(&(iph->protocol), (const unsigned long *) &iph->saddr, &tcph->source,
                                  (const unsigned long *) &iph->daddr, &tcph->dest);
                        queue = getConnection(&id);
                        toBeJudged->id = id;
                        if (queue != NULL) {
                            toBeJudged = addToQueue(flowQueues[*queue], toBeJudged);
#if DEBUGGING > 3
                            pthread_mutex_lock(&debugMutex);
                            sprintf(tmp, "To Be Further Investigated\n");
                            strncat(debug, tmp, 60);
                            pthread_mutex_unlock(&debugMutex);
#endif
                        } else{
                            destruct(toBeJudged);
                        }
                        break;
                    case IP_PROTO_UDP:
                        id = hash(&(iph->protocol), (const unsigned long *) &(iph->saddr), &(udph->source),
                                  (const unsigned long *) &(iph->daddr), &(udph->dest));
                        if (getConnection(&id) != NULL) {
                            toBeJudged = addToQueue(forwardQueues[toBeJudged->socket], toBeJudged);
#if DEBUGGING > 3
                            pthread_mutex_lock(&debugMutex);
                            sprintf(tmp, "Allowed\n");
                            strncat(debug, tmp, 60);
                            pthread_mutex_unlock(&debugMutex);
#endif
                            break;
                        }
                    default:
                        destruct(toBeJudged);
#if DEBUGGING > 3
                    pthread_mutex_lock(&debugMutex);
                    sprintf(tmp, "Blocked\n");
                    strncat(debug, tmp, 60);
                    pthread_mutex_unlock(&debugMutex);
#endif
                }
                break;
            case ETHERTYPE_ARP:
                toBeJudged = addToQueue(forwardQueues[toBeJudged->socket], toBeJudged);
                break;
            default:
                destruct(toBeJudged);
        }
#if DEBUGGING > 0
        pthread_mutex_lock(&debugMutex);
        sprintf(tmp, "\n---------------------------------------------------\n");
        strncat(debug, tmp, 60);
        printf("%s\n", debug);
        //printf("Decide Q h %i t %i \n", decideQueue->head, decideQueue->tail);
        //printf("Flow Q0 h %i t %i Flow Q1 h %i t %i\n", flowQueues[0]->head, flowQueues[0]->tail, flowQueues[1]->head, flowQueues[1]->tail);
        //printf("Fwd Q0 h %i t %i Fwd Q1 h %i t %i\n", forwardQueues[0]->head, forwardQueues[0]->tail, forwardQueues[1]->head, forwardQueues[1]->tail);
        fflush(stdout);
        memset(debug, 0, strlen(debug));
        pthread_mutex_unlock(&debugMutex);
#endif
    }
}

void *packetInspector(void *arg) {
    const int *queuenum = arg;
    int running = 1;
    struct packetQueueElement *toBeInspected;
    struct packetQueueElement *old;
    toBeInspected = malloc(sizeof(struct packetQueueElement));
    toBeInspected->packet = calloc(BUF_LENGTH, sizeof(uint8_t));
    toBeInspected->len = malloc(sizeof(size_t));
    toBeInspected->socket = -1;
    toBeInspected->pid = -1;
    toBeInspected->id = -1;


    while (running) {
        old = toBeInspected;
        do{
            toBeInspected = getFromQueue(flowQueues[*queuenum], toBeInspected);
        }while(toBeInspected == old);
        if (inspectPacket(toBeInspected->packet, &toBeInspected->id) ) {
#if DEBUGGING > 1
            pthread_mutex_lock(&debugMutex);
            sprintf(tmp, "PID %i\n", toBeInspected->pid);
            strncat(debug, tmp, 60);
            pthread_mutex_unlock(&debugMutex);
#endif
            toBeInspected = addToQueue(forwardQueues[toBeInspected->socket], toBeInspected);
        } else {
            destruct(toBeInspected);
        }
    }
}

int main(int argc, char *argv[]) {
#if DEBUGGING > 0
    printf("DEBUGGING level %i\n", DEBUGGING);
    fflush(stdout);
#endif
    // variable declaration
    char interface1[IFNAMSIZ], interface2[IFNAMSIZ];
    pthread_t read0, read1, decide[NUMQUEUES], write0, write1, main;
    cpu_set_t readSet0, readSet1, decideSet[NUMQUEUES], write0Set, write1Set, mainSet;
    int arg0, arg1, args[NUMQUEUES];
    //initiiren
    if (argc != 1 && argc != 3) {
        printf("Wrong amount of arguments\n");
        return -1;
    }
    if (argc == 3) {
        sprintf(interface1, "%s", argv[1]);
        sprintf(interface2, "%s", argv[2]);
    } else {
        sprintf(interface1, "%s", "h3-eth0");
        sprintf(interface2, "%s", "h3-eth1");
    }
    readRules("../rules.csv", NUMQUEUES);


    sockets[0] = inititialise_socket(if_nametoindex(interface1));
    sockets[1] = inititialise_socket(if_nametoindex(interface2));
    if (sockets[0] < 0 || sockets[1] < 0) {
        printf("socket initiation failed\n");
        return -1;
    }

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
#if DEBUGGING > 0
    pthread_mutex_init(&debugMutex, NULL);
    memset(debug, 0, strlen(debug));
#endif
    arg0 = 0;
    arg1 = 1;


    if (pthread_create(&write0, NULL, forwardWrapper, &arg0) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&write0Set);
    CPU_SET(4, &write0Set);
    if (pthread_setaffinity_np(write0, sizeof(cpu_set_t), &write0Set) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    if (pthread_create(&write1, NULL, forwardWrapper, &arg1) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&write1Set);
    CPU_SET(3, &write1Set);
    if (pthread_setaffinity_np(write1, sizeof(cpu_set_t), &write1Set) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    for (int i = 0; i < NUMQUEUES; ++i) {
        if (pthread_create(&decide[i], NULL, packetInspector, &args[i]) != 0) {
            printf("Error pthread_create");
            return -1;
        }
        CPU_ZERO(&decideSet[i]);
        CPU_SET(5 + i, &decideSet[i]);
        if (pthread_setaffinity_np(decide[i], sizeof(cpu_set_t), &decideSet[i]) != 0) {
            printf("Error set thread affinity");
            return -1;
        }
    }

    if (pthread_create(&read0, NULL, receiveWrapper, &arg0) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&readSet0);
    CPU_SET(0, &readSet0);
    if (pthread_setaffinity_np(read0, sizeof(cpu_set_t), &readSet0) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    if (pthread_create(&read1, NULL, receiveWrapper, &arg1) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&readSet1);
    CPU_SET(2, &readSet1);
    if (pthread_setaffinity_np(read1, sizeof(cpu_set_t), &readSet1) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    main = pthread_self();
    CPU_ZERO(&mainSet);
    CPU_SET(1, &mainSet);
    if (pthread_setaffinity_np(main, sizeof(cpu_set_t), &mainSet) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    decideAndForward();
    return 0;
}
