//#ifdef __TARGET_TOFINO__
#include <tofino/constants.p4>
#include <tofino/intrinsic_metadata.p4>
#include <tofino/primitives.p4>
#include <tofino/stateful_alu_blackbox.p4>
/*#else
#error This program is intended to compile for Tofino P4 architecture only
#endif*/

#define CPU_PORT 320

action noop() {}

#include "include/macros.p4"
#include "include/header.p4"
#include "include/parser.p4"
#include "include/firewall_rules.p4"

control ingress {
    // packets from controller (320) don't need to go through firewall
    if (ig_intr_md.ingress_port == CPU_PORT) {
        apply(forward_table_by_dst_ip);
    }
    else {
        if (valid(ipv4)) {
            if (valid(tcp)) {
                apply(firewall_table) {
                    firewall_allow_action {
                        apply(state_check_table);
                    }
                }
            }
        }
        apply(forward_table);
    }
}