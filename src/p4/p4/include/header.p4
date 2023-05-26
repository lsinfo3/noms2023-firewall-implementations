/* Ethernet header */
header_type ethernet_t {
    fields {
        dstAddr   : 48;
        srcAddr   : 48;
        etherType : 16;
    }
}

/* IPv4 header */
header_type ipv4_t {
    fields {
        version        : 4;
        ihl            : 4;
        diffserv       : 8;
        totalLen       : 16;
        identification : 16;
        flags          : 3;
        fragOffset     : 13;
        ttl            : 8;
        protocol       : 8;
        hdrChecksum    : 16;
        srcAddr        : 32;
        dstAddr        : 32;
    }
}

/* Combined TCP/UDP header (first 32 bit) */ 
header_type tcp_udp_t {
    fields {
        srcPort         : 16;
        dstPort         : 16;
    }
}

/* TCP header */
header_type tcp_t {
    fields {
        seqNo           : 32;
        ackNo           : 32;
        dataOffset      : 4;
        res             : 3;
        ecn             : 3;
        urg             : 1;
        ack             : 1;
        psh             : 1;
        rst             : 1;
        syn             : 1;
        fin             : 1;
        window          : 16;
        checksum        : 16;
        urgentPtr       : 16;
    }
}

/* UDP header */
header_type udp_t {
    fields {
        udpLength       : 16;   //length is keyword in P4
        checksum        : 16;
    }
}

/* ICMP header */
header_type icmp_t {
    fields {
        icmpType        : 8;
        icmpCode        : 8;
        checksum        : 16;
        /* up to 32 bit may follow, ignore */
    }
}

header ethernet_t       ethernet;
header ipv4_t           ipv4;
header tcp_udp_t        tcp_udp;
header tcp_t            tcp;
header udp_t            udp;
header icmp_t           icmp;