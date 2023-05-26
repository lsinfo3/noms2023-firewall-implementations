#include <stdio.h>

#include <tofinopd/pd.h>
#include <pipe_mgr/pipe_mgr_intf.h>
#include <tofino/pdfixed/pd_tm.h>
#include <tofino/bf_pal/bf_pal_port_intf.h>


#include "controller.h"
#include "../config.h"

int main() {
	low_level_controller();
}

#define ARG_UNUSED __attribute__((unused))

#define print(str) VERBOSE_LOG(str)

pipe_status_t pipe_mgr_init(void) {
	print("INIT");
	return 0;
}

pipe_status_t pipe_mgr_client_init(pipe_sess_hdl_t *sess_hdl) {
	*sess_hdl = 0;
	print("CLIENT_INIT");

	return 0;
}

p4_pd_status_t
p4_pd_main_state_check_table_table_add_with_state_check_allow_action
		(
				p4_pd_sess_hdl_t sess_hdl,
				p4_pd_dev_target_t dev_tgt,
				p4_pd_main_state_check_table_match_spec_t *match_spec,
				p4_pd_entry_hdl_t *entry_hdl
		) {}

p4_pd_status_t
p4_pd_main_state_check_table_table_add_with_state_check_to_controller_action
		(
				p4_pd_sess_hdl_t sess_hdl,
				p4_pd_dev_target_t dev_tgt,
				p4_pd_main_state_check_table_match_spec_t *match_spec,
				p4_pd_entry_hdl_t *entry_hdl
		) {}

p4_pd_status_t
p4_pd_main_state_check_table_table_delete_by_match_spec
		(
				p4_pd_sess_hdl_t sess_hdl,
				p4_pd_dev_target_t dev_tgt,
				p4_pd_main_state_check_table_match_spec_t *match_spec
		) {}

p4_pd_status_t
p4_pd_main_firewall_table_table_add_with_firewall_allow_action
		(
				p4_pd_sess_hdl_t sess_hdl,
				p4_pd_dev_target_t dev_tgt,
				p4_pd_main_firewall_table_match_spec_t *match_spec,
				p4_pd_entry_hdl_t *entry_hdl
		) {}

bf_status_t bf_pal_port_add(bf_dev_id_t dev_id,
							bf_dev_port_t dev_port,
							bf_port_speed_t speed,
							bf_fec_type_t fec_type) {return 0;}

bf_status_t bf_pal_port_enable(bf_dev_id_t dev_id, bf_dev_port_t dev_port) {return 0;}

p4_pd_status_t p4_pd_main_forward_table_table_add_with_forward_hit
		(
				p4_pd_sess_hdl_t sess_hdl,
				p4_pd_dev_target_t dev_tgt,
				p4_pd_main_forward_table_match_spec_t *match_spec,
				p4_pd_main_forward_hit_action_spec_t *action_spec,
				p4_pd_entry_hdl_t *entry_hdl
		){return 0;}

p4_pd_status_t p4_pd_main_forward_table_by_dst_ip_table_add_with_forward_ip_hit
        (
                p4_pd_sess_hdl_t sess_hdl,
                p4_pd_dev_target_t dev_tgt,
                p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec,
                p4_pd_main_forward_ip_hit_action_spec_t *action_spec,
                p4_pd_entry_hdl_t *entry_hdl
        ){return 0;}

bf_status_t bf_pal_is_port_internal(bf_dev_id_t dev_id,
									bf_dev_port_t dev_port,
									bool *is_internal) {*is_internal = false;return 0;}

p4_pd_status_t p4_pd_tm_set_cpuport(p4_pd_tm_dev_t dev, p4_pd_tm_port_t port) {return 0;}
bf_status_t bf_pal_front_port_to_dev_port_get(
		bf_dev_id_t dev_id,
		bf_pal_front_port_handle_t *port_hdl,
		bf_dev_port_t *dev_port) {return 0;}