#define MAX_IP4_FLOWS 131072
/*
 * Forwarding to correct port
 */
action to_controller_action() {
    modify_field(ig_intr_md_for_tm.copy_to_cpu, 1);
    drop();
}
ACTION2TABLE(to_controller)

action forward_hit(port) {
    modify_field(ig_intr_md_for_tm.ucast_egress_port, port);
}

action forward_miss() {
    drop();
}

table forward_table {
    reads { ig_intr_md.ingress_port: exact; }
    actions {
        forward_hit;
        forward_miss;
    }
    default_action: forward_miss();
    size: 64;
}

action forward_ip_hit(port) {
    modify_field(ig_intr_md_for_tm.ucast_egress_port, port);
}

action forward_ip_miss() {
    drop();
}

table forward_table_by_dst_ip {
    reads { ipv4.dstAddr: exact; }
    actions {
        forward_ip_hit;
        forward_ip_miss;
    }
    default_action: forward_ip_miss();
    size: 128;
}

/*
 * Tcp state checking
 */

action state_check_allow_action() {
}

action state_check_to_controller_action() {
    modify_field(ig_intr_md_for_tm.copy_to_cpu, 1);
}

action state_check_drop_action() {
    drop();
}

table state_check_table {
    reads {
        ipv4.srcAddr: exact;
        ipv4.dstAddr: exact;
        tcp_udp.srcPort: exact;
        tcp_udp.dstPort: exact;
        tcp.ack: exact;
        tcp.rst: exact;
        tcp.syn: exact;
        tcp.fin: exact;
    }
    actions {
        state_check_allow_action;
        state_check_to_controller_action;
        state_check_drop_action;
    }
    default_action: state_check_drop_action();
    size: MAX_IP4_FLOWS;
}

/*
 * Simple firewall rule checking
 */

action firewall_allow_action() {
    //apply(state_check_table);
}

action firewall_drop_action() {
    drop();
}

table firewall_table {
    reads {
        ipv4.srcAddr: exact;
        ipv4.dstAddr: exact;
        tcp_udp.srcPort: exact;
        tcp_udp.dstPort: exact;
    }
    actions {
        firewall_allow_action;
        firewall_drop_action;
    }
    default_action: firewall_drop_action();
    size: MAX_IP4_FLOWS;
}
