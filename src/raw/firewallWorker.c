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

// 0=none, 1=notify each rcv pkt, 2=track state changes, 3= show tcp flags, 4= show retran. blocked , 5= rcv snt packet sizes
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

#define QUEUE_LENGTH  1024

#if DEBUGGING > 0
char debug[2048];
char tmp[60];
pthread_mutex_t debugMutex;
#endif

int pnum = 1;

struct packetQueueElement {
    uint8_t *packet;
    size_t *len;
    int socket;
    int id;
    int pid;
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
} tcpState;


packetQueue *decideQueue;
packetQueue **forwardQueues;

static inline struct packetQueueElement * addToQueue(packetQueue *queue, struct packetQueueElement *toBeAdded) {
    struct packetQueueElement *swap;
    pthread_mutex_lock(queue->mutex);
    swap = queue->queue[queue->tail];
    queue->queue[queue->tail] = toBeAdded;
    queue->tail = queue->tail + 1;
    if (queue->tail >= QUEUE_LENGTH) {
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

    decideQueue->tail = decideQueue->tail + 1;
    if (decideQueue->tail >= QUEUE_LENGTH) {
        decideQueue->tail = 0;
    }
    pnum = pnum + 1;
    pthread_mutex_unlock(decideQueue->mutex);

#if DEBUGGING > 4
    pthread_mutex_lock(&debugMutex);
    sprintf(tmp, "Received %i (%li bytes) from %i\n", toBeAdded->pid, *(toBeAdded->len), (toBeAdded->socket+1)%2);
    strcat(debug, tmp);
    pthread_mutex_unlock(&debugMutex);
#endif
    return swap;
}

static inline struct packetQueueElement *getFromQueue(packetQueue *queue, struct packetQueueElement *ret) {
    struct packetQueueElement *element;
    while (queue->head == queue->tail);

    pthread_mutex_lock(queue->mutex);
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

KHASH_MAP_INIT_INT(rules, tcpState)

kh_rules_t *connections;

int sockets[2];

void addConnection(const int *key, const tcpState *s) {
    int ret;
    khint_t k;
    k = kh_put_rules(connections, (khint32_t) *key, &ret);
    if (!ret) {
        kh_del_rules(connections, k);
    }
    kh_value(connections, k) = *s;
}

tcpState *getConnection(const int *key) {
    khint_t k;
    tcpState *s;
    k = kh_get_rules(connections, (khint32_t) *key);         // query the hash table
    if (k == kh_end(connections)) {
        return NULL;
    }
    s = &kh_value(connections, k);
    return s;
}

void readRules(const char *file) {
    char buffer[1024], ip1[INET_ADDRSTRLEN], ip2[INET_ADDRSTRLEN];
    int i, j, rulehash;
    uint16_t port1, port2;
    uint8_t proto;
    unsigned long netip1, netip2;
    struct in_addr inp;
    FILE *fp;
    connections = kh_init_rules();
    tcpState s;
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

            s.cli_state = TCP_CLOSE;
            s.cli_seq = 0;
            s.cli_window = 0;
            s.srv_seq = 0;
            s.srv_window = 0;
            s.srv_state = TCP_CLOSE;

            rulehash = hash(&proto, &netip1, &port1, &netip2, &port2);
            addConnection(&rulehash, &s);
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


int receive(const int *socket, uint8_t *buffer) {
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


void forward(const int *socket, uint8_t *buf, const size_t *numbytes) {
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
        *(add->len) = (size_t) numb;
        add->socket = (*from + 1) % 2;
        add = addToDecideQueue(add);
    }
}


void *forwardWrapper(void *arg) {
    uint8_t *buf;
    const int *socket = arg;
    size_t *numbytes;
    struct packetQueueElement *toSend;
    toSend = malloc(sizeof(struct packetQueueElement));
    toSend->packet = calloc(BUF_LENGTH, sizeof(uint8_t));
    toSend->len = malloc(sizeof(size_t));
    toSend->socket = -1;
    toSend->pid = -1;
    toSend->id = -1;




    int running = 1;
    while (running) {
        toSend = getFromQueue(forwardQueues[*socket], toSend);
        buf = toSend->packet;
        numbytes = toSend->len;
        forward(&sockets[*socket], buf, (const size_t *) numbytes);

#if DEBUGGING > 4
        pthread_mutex_lock(&debugMutex);
        sprintf(tmp, "Sent %i (%li bytes) to %i \n", toSend->pid,  *(toSend->len), *socket);
        strcat(debug, tmp);
        pthread_mutex_unlock(&debugMutex);
#endif
        destruct(toSend);
    }
}

static inline int inspectPacket(const uint8_t *buffer, int *id) {
    //struct ether_header *eh = (struct ether_header *) buffer;
    struct iphdr *iph = (struct iphdr *) (buffer + (sizeof(struct ether_header)));
    struct tcphdr *tcph = (struct tcphdr *) (buffer + sizeof(struct iphdr) + sizeof(struct ether_header));
    uint8_t *snd_state, *rec_state;
    uint8_t futurSndState, futurRecvState;
    tcp_seq seq, ack_seq;
    int ackChallenge = 0;
    tcpState *conState = getConnection(id);
    if (conState == NULL) {
        return 0;
    }

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
    sprintf(tmp, "Old Server State %"PRIu8"\nOld Client State %"PRIu8"\n", conState->srv_state, conState->cli_state);
    strcat(debug, tmp);
    sprintf(tmp, "Server:  %"PRIu32" Client: %"PRIu32"\n", conState->srv_seq, conState->cli_seq);
    strcat(debug, tmp);
#endif
    //check seq nums
    seq = ntohl(tcph->th_seq);
    ack_seq = ntohl(tcph->th_ack);
    uint16_t tcp_window_size = ntohs(tcph->th_win);

    if (iph->saddr < iph->daddr) {//=> server = sender  s_ip < c_ip
        if ((SEQ_LT(seq, conState->srv_seq) || SEQ_GEQ(seq, conState->srv_seq + conState->srv_window)) && !(tcph->th_flags & TH_SYN)) {
#if DEBUGGING > 3
            sprintf(tmp, "wrong seq num  1 \n");
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


    } else {
        if ((SEQ_LT(seq, conState->cli_seq) || SEQ_GEQ(seq, conState->cli_seq + conState->cli_window)) && !(tcph->th_flags & TH_SYN)) {
#if DEBUGGING > 3
            sprintf(tmp, "wrong seq num 2 \n");
            strcat(debug, tmp);
            sprintf(tmp, "%i  \n", tcph->th_flags);
            strcat(debug, tmp);
            sprintf(tmp, "%i  \n", seq - conState->cli_seq);
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


    if ((tcph->th_flags & TH_RST) || (futurSndState == TCP_CLOSE && futurRecvState == TCP_CLOSE)) {
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

void *decideAndForward() {
    int allowed, id;
    uint8_t *buf;
    struct ether_header *eh;
    struct iphdr *iph;
    struct tcphdr *tcph;
    struct udphdr *udph;

    struct packetQueueElement *toBeJudged;

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
        toBeJudged = getFromQueue(decideQueue, toBeJudged);
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
                        sprintf(tmp, "PID: %i\n",toBeJudged->pid);
                        strcat(debug, tmp);
                        sprintf(tmp, "ID: %s:%05d->%s:%05d\n", sender, ntohs(tcph->source), recepient,
                                ntohs(tcph->dest));
                        strcat(debug, tmp);
                        sprintf(tmp, "Syn:  %i Ack: %i Fin: %i Rst: %i Psh: %i\n", tcph->syn, tcph->ack, tcph->fin,
                                tcph->rst, tcph->psh);
                        strcat(debug, tmp);
                        sprintf(tmp, "Seq:  %"PRIu32" Ack_seq: %"PRIu32"\n", ntohl(tcph->seq),
                                ntohl(tcph->ack_seq));
                        strcat(debug, tmp);
                        pthread_mutex_unlock(&debugMutex);
#endif
                        id = hash(&(iph->protocol), (const unsigned long *) &iph->saddr, &tcph->source,
                                  (const unsigned long *) &iph->daddr, &tcph->dest);
                        allowed = inspectPacket(buf, &id);
                        break;
                    case IP_PROTO_UDP:
                        id = hash(&(iph->protocol), (const unsigned long *) &(iph->saddr), &(udph->source),
                                  (const unsigned long *) &(iph->daddr), &(udph->dest));
                        allowed = (getConnection(&id) != NULL);
                        break;
                    default:
                        allowed = 0;

                }
#if DEBUGGING > 3
            pthread_mutex_lock(&debugMutex);
            if (allowed)
                sprintf(tmp, "Allowed\n");
            else
                sprintf(tmp, "Blocked\n");
            strcat(debug, tmp);
            pthread_mutex_unlock(&debugMutex);
#endif

                if (!allowed) {
                    destruct(toBeJudged);
                    break;
                }

            case ETHERTYPE_ARP:
                toBeJudged = addToQueue(forwardQueues[toBeJudged->socket],toBeJudged);
                break;
            default:
                destruct(toBeJudged);

        }

#if DEBUGGING > 0
        pthread_mutex_lock(&debugMutex);
        sprintf(tmp, "\n---------------------------------------------------\n");
        strcat(debug, tmp);
        printf("%s\n", debug);
        fflush(stdout);
        memset(debug, 0, strlen(debug));
        pthread_mutex_unlock(&debugMutex);
#endif
    }


}


int main(int argc, char *argv[]) {
#if DEBUGGING > 0
    printf("DEBUGGING level %i\n", DEBUGGING);
    fflush(stdout);
#endif
    // variable declaration
    char interface1[IFNAMSIZ], interface2[IFNAMSIZ];
    pthread_t read0, read1, decide, write0, write1;
    int arg0, arg1;
    cpu_set_t read_set0, read_set1, decide_set, write_set0, write_set1;

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

    readRules("../rules.csv");

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

#if DEBUGGING > 0
    pthread_mutex_init (&debugMutex, NULL);
    memset(debug, 0, strlen(debug));
#endif

    arg0 = 0;
    arg1 = 1;
    //schreiben 0
    if (pthread_create(&write0, NULL, forwardWrapper, &arg0) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&write_set0);
    CPU_SET(4, &write_set0);
    if (pthread_setaffinity_np(write0, sizeof(cpu_set_t), &write_set0) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    //schreiben 1
    if (pthread_create(&write1, NULL, forwardWrapper, &arg1) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&write_set1);
    CPU_SET(6, &write_set1);
    if (pthread_setaffinity_np(write1, sizeof(cpu_set_t), &write_set1) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    //lesen 0
    if (pthread_create(&read0, NULL, receiveWrapper, &arg0) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&read_set0);
    CPU_SET(0, &read_set0);
    if (pthread_setaffinity_np(read0, sizeof(cpu_set_t), &read_set0) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    //lesen 1
    if (pthread_create(&read1, NULL, receiveWrapper, &arg1) != 0) {
        printf("Error pthread_create");
        return -1;
    }
    CPU_ZERO(&read_set1);
    CPU_SET(2, &read_set1);
    if (pthread_setaffinity_np(read1, sizeof(cpu_set_t), &read_set1) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    //entscheiden
    decide = pthread_self();
    CPU_ZERO(&decide_set);
    CPU_SET(1, &decide_set);
    if (pthread_setaffinity_np(decide, sizeof(cpu_set_t), &decide_set) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    decideAndForward();

    return 0;
}
