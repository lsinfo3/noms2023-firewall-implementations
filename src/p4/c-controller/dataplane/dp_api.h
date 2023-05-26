#ifndef LOW_LEVEL_LIB_DP_API_H
#define LOW_LEVEL_LIB_DP_API_H

#include <pipe_mgr/pipe_mgr_intf.h>
#include <tofinopd/pd.h>

#include "../datastructures/structs.h"
#include "../config.h"


#define SUCCESS 0
#define ERR_CONNECT 1

extern pipe_sess_hdl_t sess_hdl;

extern p4_pd_dev_target_t ALL_PIPES;

extern bool already_inserted_forwarding_ip_rule;

/*
 * Initialize the switch client and retrieve a session id
 */
int switch_connect();

/*
 * Remove state matching rules for this particular 5-tuple - state combination
 * from the dataplane
 */
void remove_rules(five_tuple_t five_tuple, tcp_state_t old_state);

/*
 * Add state matching rules for this particular 5-tuple - state combination
 * to the dataplane
 */
void add_rules(five_tuple_t five_tuple, tcp_state_t new_state);

/*
 * Add a basic firewall rule for this 5-tuple. All other flows will be dropped
 */
void add_firewall_rule(five_tuple_t five_tuple);

/*
 * Insert the forwarding rules configured in port_config.h
 */
void insert_forwarding_rules();

/*
 * Insert the forwarding rules for packets from the controller
 */
void insert_forwarding_rules_ip(five_tuple_t five_tuple);

/*
 * Internal function to insert the forwarding rule for packets from the controller
 */
void _insert_forwarding_rule_ip(bf_dev_port_t port, uint32_t dst_ip);


#endif //LOW_LEVEL_LIB_DP_API_H
