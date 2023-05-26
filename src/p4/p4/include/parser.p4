/* parse Ethernet header, continue if IPv4 packet, else throw parser exception */
parser start {
    extract(ethernet);
    return select(ethernet.etherType) {
        0x0800 : parse_ipv4;
        default: parse_error p4_pe_default;
    }
}

/* parse IPv4 header, continue if no option headers are present, else throw parser exception */
parser parse_ipv4 {
    extract(ipv4);
    return select(ipv4.ihl) {
       5 : parse_layer4;
       default: parse_error p4_pe_default; 
    }
}

/* parse layer 4 protocol, continue if ICMP/TCP/UDP, else throw parser exception */
parser parse_layer4 {
    return select(ipv4.protocol) {
        1  : parse_icmp;
        6  : parse_tcp_udp;
        17 : parse_tcp_udp;
        default: parse_error p4_pe_default;
    }
}

/* parse ICMP, provide fake path for UDP meta header, finish */
parser parse_icmp {
    extract(icmp);
    return ingress;
}

/* parse first two fields of TCP/UDP packet, continue with right protocol */
parser parse_tcp_udp {
    extract(tcp_udp);
    return select(ipv4.protocol) {
        6  : parse_tcp;
        17 : parse_udp;
        253 : ingress;
        default: parse_error p4_pe_default;
    }
}

/* parse TCP, provide fake path for UDP meta header, finish */
parser parse_tcp {
    extract(tcp);
    return ingress;
}

/* parse UDP, provide fake path for UDP meta header, finish */
parser parse_udp {
    extract(udp);
    return ingress;
}

/* handle parser exception, drop packet */
parser_exception p4_pe_default {
    parser_drop;
}