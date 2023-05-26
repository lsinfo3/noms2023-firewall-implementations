#include "dp_api.h"

#include <stdio.h>
#include <stdlib.h>
#include "../tcp.h"

#include <tofino/bf_pal/bf_pal_port_intf.h>
#include <arpa/inet.h>
#include "../port_config.h"

bool already_inserted_forwarding_ip_rule = false;

pipe_sess_hdl_t sess_hdl;

p4_pd_dev_target_t ALL_PIPES = {
		.device_id = 0,
		.dev_pipe_id = PD_DEV_PIPE_ALL
};

/*
 * Initialize the switch client and retrieve a session id
 */
int switch_connect() {
	sess_hdl = 0;
	pipe_status_t status;
	if ((status = pipe_mgr_init())) {
		printf("Could not init pipe_mgr, status: %s\n", pipe_str_err(status));
		return ERR_CONNECT;
	}
	if ((status = pipe_mgr_client_init(&sess_hdl))) {
		printf("Could not get sess_hdl, status: %s\n", pipe_str_err(status));
		return ERR_CONNECT;
	}
	return SUCCESS;
}

/*
 * Convert TCP-State to match_spec for the data plane API
 */
static void inline
apply_flags_to_match_spec(tcp_flags_t flags,
						  p4_pd_main_state_check_table_match_spec_t *match_spec) {
	match_spec->tcp_ack = 0;
	match_spec->tcp_syn = 0;
	match_spec->tcp_fin = 0;
	match_spec->tcp_rst = 0;
	switch (flags) {
		case SYN_SET:
			match_spec->tcp_syn = 1;
			break;
		case SYNACK_SET:
			match_spec->tcp_ack = 1;
			match_spec->tcp_syn = 1;
			break;
		case FIN_SET:
			match_spec->tcp_fin = 1;
			break;
		case ACK_SET:
			match_spec->tcp_ack = 1;
			break;
		case RST_SET:
			match_spec->tcp_rst = 1;
			break;
		case FINACK_SET:
			match_spec->tcp_fin = 1;
			match_spec->tcp_ack = 1;
			break;
		default:
			break;
	}
}

static void print_five_tuple(five_tuple_t five_tuple, char *buf) {
	char src[INET_ADDRSTRLEN], dst[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &five_tuple.src_ipv4, src, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &five_tuple.dst_ipv4, dst, INET_ADDRSTRLEN);
	sprintf(buf, "%s:%d -> %s:%d", src, five_tuple.src_port, dst, five_tuple.dst_port);
}

static void apply_remove_rules(five_tuple_t five_tuple, tcp_state_t state, direction_t direction) {
	p4_pd_main_state_check_table_match_spec_t match_spec = {
			.ipv4_srcAddr = SWAP_ENDIAN_32(five_tuple.src_ipv4),
			.ipv4_dstAddr = SWAP_ENDIAN_32(five_tuple.dst_ipv4),
			.tcp_udp_srcPort = five_tuple.src_port,
			.tcp_udp_dstPort = five_tuple.dst_port,
	};

	p4_pd_status_t status;
	tcp_state_t new_state;

	if (state == INVALID || state == IGNORE) {
		return;
	}
	for (tcp_flags_t flag = 0; flag < NUM_FLAGS; flag++) {
		new_state = transitions[direction][flag][state];
		apply_flags_to_match_spec(flag, &match_spec);
		if (new_state == state || new_state == IGNORE) {
			if ((status = p4_pd_main_state_check_table_table_delete_by_match_spec(
					sess_hdl,
					ALL_PIPES,
					&match_spec)) != 0) {
				ERROR_LOG("Error inserting into data plane: %s\n", pipe_str_err(status))
			}
		}
		else if (new_state != INVALID) {
			if ((status = p4_pd_main_state_check_table_table_delete_by_match_spec(
					sess_hdl,
					ALL_PIPES,
					&match_spec)) != 0) {
				ERROR_LOG("Error inserting into data plane: %s\n", pipe_str_err(status))
			}
		}
	}
}

static void apply_insert_rules(five_tuple_t five_tuple, tcp_state_t state, direction_t direction) {
	p4_pd_main_state_check_table_match_spec_t match_spec = {
			.ipv4_srcAddr = SWAP_ENDIAN_32(five_tuple.src_ipv4),
			.ipv4_dstAddr = SWAP_ENDIAN_32(five_tuple.dst_ipv4),
			.tcp_udp_srcPort = five_tuple.src_port,
			.tcp_udp_dstPort = five_tuple.dst_port,
	};

	tcp_state_t new_state;
	p4_pd_entry_hdl_t entry_hdl;
	p4_pd_status_t status;

	if (state == INVALID || state == IGNORE) {
		return;
	}
	for (tcp_flags_t flag = 0; flag < NUM_FLAGS; flag++) {
		new_state = transitions[direction][flag][state];
		apply_flags_to_match_spec(flag, &match_spec);
		if (new_state == state || new_state == IGNORE) {
			if ((status = p4_pd_main_state_check_table_table_add_with_state_check_allow_action(
					sess_hdl,
					ALL_PIPES,
					&match_spec,
					&entry_hdl)) != 0) {
				char buf[256];
				print_five_tuple(five_tuple, buf);
				ERROR_LOG("Error inserting into data plane: %s\n", pipe_str_err(status))
				ERROR_LOG("Writing %s, SYN:%d, FIN:%d, ACK:%d, RST:%d", buf, match_spec.tcp_syn, match_spec.tcp_fin, match_spec.tcp_ack, match_spec.tcp_rst)
			}
		}
		else if (new_state != INVALID) {
			if ((status = p4_pd_main_state_check_table_table_add_with_state_check_to_controller_action(
					sess_hdl,
					ALL_PIPES,
					&match_spec,
					&entry_hdl)) != 0) {
				char buf[256];
				print_five_tuple(five_tuple, buf);
				ERROR_LOG("Error inserting into data plane: %s\n", pipe_str_err(status))
				ERROR_LOG("Writing %s, SYN:%d, FIN:%d, ACK:%d, RST:%d", buf, match_spec.tcp_syn, match_spec.tcp_fin, match_spec.tcp_ack, match_spec.tcp_rst)
			}
		}
	}
}

void remove_rules(five_tuple_t five_tuple, tcp_state_t old_state) {
	apply_remove_rules(five_tuple, old_state, get_direction(five_tuple));

	five_tuple = reverse_five_tuple(five_tuple);

	apply_remove_rules(five_tuple, old_state, get_direction(five_tuple));
}

void add_rules(five_tuple_t five_tuple, tcp_state_t new_state) {
	apply_insert_rules(five_tuple, new_state, get_direction(five_tuple));

	five_tuple = reverse_five_tuple(five_tuple);

	apply_insert_rules(five_tuple, new_state, get_direction(five_tuple));
}

void add_firewall_rule(five_tuple_t five_tuple) {
	p4_pd_main_firewall_table_match_spec_t match_spec = {
			.ipv4_srcAddr = SWAP_ENDIAN_32(five_tuple.src_ipv4),
			.ipv4_dstAddr = SWAP_ENDIAN_32(five_tuple.dst_ipv4),
			.tcp_udp_srcPort = five_tuple.src_port,
			.tcp_udp_dstPort = five_tuple.dst_port,
	};
	p4_pd_entry_hdl_t entry_hdl;
	p4_pd_main_firewall_table_table_add_with_firewall_allow_action(
			sess_hdl, ALL_PIPES,
			&match_spec, &entry_hdl
	);
}


#define DP_EXIT_ON_ERROR(call, errstring) {                 \
    p4_pd_status_t status;                                  \
    status = call;                                          \
    if (status != 0) {                                      \
        ERROR_LOG(errstring " %s\n", pipe_str_err(status))  \
        exit(1);                                            \
    }                                                       \
}

static bf_dev_port_t front_panel_to_devport(uint8_t port, uint8_t lane) {
	bf_pal_front_port_handle_t front_port_handle = {
			.conn_id = port,
			.chnl_id = lane,
	};
	bf_dev_port_t dev_port;
	DP_EXIT_ON_ERROR(bf_pal_front_port_to_dev_port_get(0, &front_port_handle, &dev_port),
					 "when converting front panel to dev port");
	return dev_port;
}

void insert_forwarding_rules() {
	p4_pd_entry_hdl_t entry_hdl;

	/*
	 * Add and enable all configured ports (see port_config.h)
	 */
	for (int i = 0; i < sizeof(port_entries) / sizeof(port_entry_t); i++) {
		bf_dev_port_t dev_port = front_panel_to_devport(port_entries[i].port, port_entries[i].lane);

		bool is_internal;
		DP_EXIT_ON_ERROR(bf_pal_is_port_internal(0, dev_port, &is_internal),
						 "when checking whether port is internal");
		if (is_internal) {
			ERROR_LOG("Can not configure port %d:%d as it is internal",
					  port_entries[i].port, port_entries[i].lane)
			exit(1);
		}

		DP_EXIT_ON_ERROR(bf_pal_port_add(0, dev_port, port_entries[i].speed, port_entries[i].fec),
						 "when adding port")
		DP_EXIT_ON_ERROR(bf_pal_port_enable(0, dev_port), "when enabling port")
	}

	/*
	 * Insert forward rules for each configured forward entry (see port_config.h)
	 */
	for (int i = 0; i < sizeof(forward_entries) / sizeof(forward_entry_t); i++) {
		bf_dev_port_t from_port = front_panel_to_devport(forward_entries[i].from_port,
														 forward_entries[i].from_lane);
		bf_dev_port_t to_port = front_panel_to_devport(forward_entries[i].to_port,
													   forward_entries[i].to_lane);

		p4_pd_main_forward_table_match_spec_t match_spec = {
				.ig_intr_md_ingress_port = from_port
		};
		p4_pd_main_forward_hit_action_spec_t action_spec = {
				.action_port = to_port
		};

		DP_EXIT_ON_ERROR(p4_pd_main_forward_table_table_add_with_forward_hit(
				sess_hdl, ALL_PIPES,
				&match_spec,
				&action_spec, &entry_hdl),
						 "when adding forward entry"
		);
	}
}

void insert_forwarding_rules_ip(five_tuple_t five_tuple) {
    // CAREFUL: this is a dirty hack because we only have one connection from one ip to another
    if (already_inserted_forwarding_ip_rule)
        return;

    bf_dev_port_t dir1_dst_port = front_panel_to_devport(forward_entries[1].from_port,
                                                     forward_entries[1].from_lane);
    bf_dev_port_t dir2_dst_port = front_panel_to_devport(forward_entries[0].from_port,
                                                   forward_entries[0].from_lane);

    _insert_forwarding_rule_ip(dir1_dst_port, five_tuple.src_ipv4);
    _insert_forwarding_rule_ip(dir2_dst_port, five_tuple.dst_ipv4);

    already_inserted_forwarding_ip_rule = true;
}

void _insert_forwarding_rule_ip(bf_dev_port_t port, uint32_t dst_ip) {
    p4_pd_entry_hdl_t entry_hdl;

    p4_pd_main_forward_table_by_dst_ip_match_spec_t match_spec = {
            .ipv4_dstAddr = SWAP_ENDIAN_32(dst_ip)
    };
    p4_pd_main_forward_ip_hit_action_spec_t action_spec = {
            .action_port = port
    };

    DP_EXIT_ON_ERROR(p4_pd_main_forward_table_by_dst_ip_table_add_with_forward_ip_hit(
            sess_hdl, ALL_PIPES, &match_spec, &action_spec, &entry_hdl),
    "when adding forward by ip entry"
    );
}