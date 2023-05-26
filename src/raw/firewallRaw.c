#define _GNU_SOURCE //access makros for thread affinity
#include <sys/socket.h> //socket calls
#include <linux/if_packet.h> //socket addressen
#include <net/if.h> //if_tonametoindex
#include <net/ethernet.h> //ethernet header
#include <linux/ip.h> //ip header
#include <netinet/tcp.h> //tcp header
#include <netinet/udp.h> //udp header
#include <arpa/inet.h> //inet_ntop
#include <stdio.h> //print,

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

#if DEBUGGING > 0
char debug[4096];
char tmp[128];
#endif

//stupid uint sequence math
#define SEQ_GT(a,b) ((int)((a)-(b)) > 0)
#define SEQ_LT(a,b) ((int)((a)-(b)) < 0)
#define SEQ_GEQ(a,b) ((int)((a)-(b)) >= 0)
#define SEQ_LEQ(a,b) ((int)((a)-(b)) <= 0)

typedef struct { //s_ip < c_ip
    tcp_seq srv_seq;
    tcp_seq cli_seq;
    uint8_t srv_state;
    uint8_t cli_state;
    uint32_t srv_window;
    uint32_t cli_window;
} tcpState;

int hash(const __u8 *proto, const unsigned long *s_addr, const u_int16_t *s_port, const unsigned long *c_addr,
         const uint16_t *c_port) {
    int erg = (int) ((*s_addr ^ *s_port) ^ (*c_addr ^ *c_port) ^ *proto);
    return erg;
}

KHASH_MAP_INIT_INT(rules, tcpState)

kh_rules_t *connections;

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
        printf("bind error :%s, %i\n", strerror(errno), errno);
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


int receive(const int * socket, uint8_t buffer[]) {
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
#if DEBUGGING > 4
    sprintf(tmp, "Received %i bytes\n", numb);
    strcat(debug, tmp);
#endif
    return numb;
}

void forward(const int* socket, uint8_t buf[], const int *numbytes) {
    if (send(*socket, buf, *numbytes, 0) < 0) {
        printf("Send error %s\n", strerror(errno));
    }
#if DEBUGGING > 4
    else {
        sprintf(tmp, "Sent %i bytes \n",  *numbytes);
        strcat(debug, tmp);
    }
#endif
}

static inline int inspectPacket(const uint8_t *buffer, int *id) {
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
#if DEBUGGING > 3
        sprintf(tmp, "s:%"PRIu32"  != %"PRIu32" + %"PRIu32" \n", seq, conState->srv_seq, conState->srv_seq);
        strcat(debug, tmp);
#endif
        if ((SEQ_LT(seq, conState->srv_seq) || SEQ_GEQ(seq, conState->srv_seq + conState->srv_window)) && !(tcph->th_flags & TH_SYN)) {
#if DEBUGGING > 3
            sprintf(tmp, "srv wrong seq num \n");
            strcat(debug, tmp);
#endif
            return 0;
        }
        if (SEQ_LT(ack_seq, conState->cli_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
#if DEBUGGING > 3
            //conState->srv_seq = seq;
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
#if DEBUGGING > 3
        sprintf(tmp, "c:%"PRIu32"  != %"PRIu32" + %"PRIu32" \n", seq, conState->cli_seq, conState->cli_seq);
        strcat(debug, tmp);
#endif
        if ((SEQ_LT(seq, conState->cli_seq) || SEQ_GEQ(seq, conState->cli_seq + conState->cli_window)) && !(tcph->th_flags & TH_SYN)) {
#if DEBUGGING > 3
            sprintf(tmp, "cli wrong seq num \n");
            strcat(debug, tmp);
            sprintf(tmp, "expected inside:(%"PRIu32", %"PRIu32") but has:%"PRIu32"", conState->cli_seq, conState->cli_seq + conState->cli_window , seq);
            strcat(debug, tmp);
#endif
            return 0;
        }
        if (SEQ_LT(ack_seq, (conState->srv_seq)) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
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

int main(int argc, char *argv[]) {
    if (argc != 1 && argc != 3) {
        printf("Wrong amount of arguments\n");
        return -1;
    }

    // variable declaration
    int src_idx, allowed, id, numbytes;
    int sockets[2];
    uint8_t buf[BUF_LENGTH];

    pthread_t main;
    cpu_set_t mainSet;

    char interface0[IFNAMSIZ], interface1[IFNAMSIZ];

    struct ether_header *eh = (struct ether_header *) buf;
    struct iphdr *iph = (struct iphdr *) (buf + (sizeof(struct ether_header)));
    struct tcphdr *tcph = (struct tcphdr *) (buf + sizeof(struct iphdr) + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr *) (buf + sizeof(struct iphdr) + sizeof(struct ether_header));
    //initiiren
    if (argc == 3) {
        sprintf(interface0, "%s", argv[1]);
        sprintf(interface1, "%s", argv[2]);
    } else {
        sprintf(interface0, "%s", "h3-eth0");
        sprintf(interface1, "%s", "h3-eth1");
    }

    readRules("../rules.csv");

#if DEBUGGING > 0
    //Debug initiation
    printf("Debuglevel: %i\n", DEBUGGING);
    int packetcounter = 0;
    char sender[INET_ADDRSTRLEN], recepient[INET_ADDRSTRLEN];
    memset(debug, 0, strlen(debug));
#endif

    sockets[0] = inititialise_socket(if_nametoindex(interface0));
    sockets[1] = inititialise_socket(if_nametoindex(interface1));

    if (sockets[0] < 0 || sockets[1] < 0) {
        return -1;
    }

    main = pthread_self();
    CPU_ZERO(&mainSet);
    CPU_SET(0,&mainSet);
    if(pthread_setaffinity_np(main, sizeof(cpu_set_t), &mainSet)!= 0) {
        printf("Error set thread affinity");
        return -1;
    }

    while (1) {
        for (src_idx = 0; src_idx < 2; src_idx = src_idx + 1) {
            numbytes = receive(&sockets[src_idx], buf);
            if (numbytes < 0) {
                return -1;
            } else if (numbytes > 0) {
                switch (ntohs(eh->ether_type)) {
                    case ETHERTYPE_IP:
                        switch (iph->protocol) {
                            case IP_PROTO_TCP:
#if DEBUGGING > 2
                                inet_ntop(AF_INET, &iph->saddr, sender, INET_ADDRSTRLEN);
                                inet_ntop(AF_INET, &iph->daddr, recepient, INET_ADDRSTRLEN);
                                sprintf(tmp, "ID: %s:%05d->%s:%05d\n", sender, ntohs(tcph->source), recepient,
                                        ntohs(tcph->dest));
                                strcat(debug, tmp);
                                sprintf(tmp, "Syn:  %i Ack: %i Fin: %i Rst: %i Psh: %i\n", tcph->syn, tcph->ack,
                                        tcph->fin,
                                        tcph->rst, tcph->psh);
                                strcat(debug, tmp);
                                sprintf(tmp, "Seq:  %"PRIu32" Ack_seq: %"PRIu32"\n", ntohl(tcph->seq),
                                        ntohl(tcph->ack_seq));
                                strcat(debug, tmp);
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
                        if (allowed)
                            sprintf(tmp, "Allowed\n");
                        else
                            sprintf(tmp, "Blocked\n");
                        strcat(debug, tmp);
#endif
                        if (!allowed) {
                            break;
                        }

                    case ETHERTYPE_ARP:
                        forward(&sockets[src_idx^1], buf, &numbytes);
                }
#if DEBUGGING > 0
                packetcounter = packetcounter + 1;
                sprintf(tmp, "\nPC %i\n---------------------------------------------------\n", packetcounter);
                strcat(debug, tmp);
                fprintf(stdout, "%s\n", debug);
                fflush(stdout);
                memset(debug, 0, strlen(debug));
#endif
            }
        }
    }

    return 0;
}
