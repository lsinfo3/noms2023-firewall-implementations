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

#define BUF_LENGTH 1500 + sizeof(struct ether_header)

int inititialise_socket(int ifidx) {
    int sock = 0;
    int erfolg = -1;
    struct sockaddr_ll sll;
    int sll_len = sizeof(sll);
    int domain = AF_PACKET;
    int protocol = htons(ETH_P_ALL);
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

void forward(const int *socket, uint8_t buf[], const int *numbytes) {
    if (send(*socket, buf, *numbytes, 0) < 0) {
        printf("Send error %s\n", strerror(errno));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 1 && argc != 3) {
        printf("Wrong amount of arguments\n");
        return -1;
    }
    // variable declaration
    int numbytes, erfolg, reorder, i;
    int sockets[2];
    uint8_t buf[BUF_LENGTH];
    pthread_t main;
    cpu_set_t mainSet;

    char interface0[IFNAMSIZ], interface1[IFNAMSIZ];
    if (argc == 3) {
        sprintf(interface0, "%s", argv[1]);
        sprintf(interface1, "%s", argv[2]);
    } else {
        sprintf(interface0, "%s", "h3-eth0");
        sprintf(interface1, "%s", "h3-eth1");
    }

    sockets[0] = inititialise_socket(if_nametoindex(interface0));
    sockets[1] = inititialise_socket(if_nametoindex(interface1));

    main = pthread_self();
    CPU_ZERO(&mainSet);
    CPU_SET(0, &mainSet);
    if (pthread_setaffinity_np(main, sizeof(cpu_set_t), &mainSet) != 0) {
        printf("Error set thread affinity");
        return -1;
    }

    while (1) {
        for (i = 0; i < 2; i = i + 1) {
            numbytes = receive(&sockets[i], buf);
            if (numbytes < 0) {
                return -1;
            }
            if (numbytes > 0) {
                forward(&sockets[i ^ 1], buf, &numbytes);
            }
        }
    }

    return 0;
}
