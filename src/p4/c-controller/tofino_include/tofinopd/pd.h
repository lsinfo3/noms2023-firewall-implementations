#ifndef _PD_MAIN_PD_H
#define _PD_MAIN_PD_H

#include <stdint.h>

#include <tofino/pdfixed/pd_common.h>
#include <pipe_mgr/pipe_mgr_intf.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN_
#define LITTLE_ENDIAN_CALLER 1
#endif


/* MATCH STRUCTS */

typedef struct p4_pd_main_firewall_table_match_spec {
  uint32_t ipv4_srcAddr;
  uint32_t ipv4_dstAddr;
  uint16_t tcp_udp_srcPort;
  uint16_t tcp_udp_dstPort;
} p4_pd_main_firewall_table_match_spec_t;

typedef struct p4_pd_main_forward_table_match_spec {
  uint16_t ig_intr_md_ingress_port;
} p4_pd_main_forward_table_match_spec_t;

typedef struct p4_pd_main_forward_table_by_dst_ip_match_spec {
  uint32_t ipv4_dstAddr;
} p4_pd_main_forward_table_by_dst_ip_match_spec_t;

typedef struct p4_pd_main_state_check_table_match_spec {
  uint32_t ipv4_srcAddr;
  uint32_t ipv4_dstAddr;
  uint16_t tcp_udp_srcPort;
  uint16_t tcp_udp_dstPort;
  uint8_t tcp_ack;
  uint8_t tcp_rst;
  uint8_t tcp_syn;
  uint8_t tcp_fin;
} p4_pd_main_state_check_table_match_spec_t;



/* Dynamic Exm Table Key Mask */

/* firewall_table has no dynamic key masks */

/* forward_table has no dynamic key masks */

/* forward_table_by_dst_ip has no dynamic key masks */

/* state_check_table has no dynamic key masks */



/* ACTION STRUCTS */

/* Enum of all action names. */
typedef enum p4_pd_main_action_names {
  p4_pd_main_firewall_allow_action,
  p4_pd_main_firewall_drop_action,
  p4_pd_main_forward_hit,
  p4_pd_main_forward_miss,
  p4_pd_main_forward_ip_hit,
  p4_pd_main_forward_ip_miss,
  p4_pd_main_state_check_allow_action,
  p4_pd_main_state_check_to_controller_action,
  p4_pd_main_state_check_drop_action,
  p4_pd_main_action_names_t_invalid
} p4_pd_main_action_names_t;

const char* p4_pd_main_action_enum_to_string(p4_pd_main_action_names_t e);

p4_pd_main_action_names_t p4_pd_main_action_string_to_enum(const char* s);

  /* firewall_allow_action has no parameters */

  /* firewall_drop_action has no parameters */

typedef struct p4_pd_main_forward_hit_action_spec {
  uint16_t action_port;
} p4_pd_main_forward_hit_action_spec_t;

  /* forward_miss has no parameters */

typedef struct p4_pd_main_forward_ip_hit_action_spec {
  uint16_t action_port;
} p4_pd_main_forward_ip_hit_action_spec_t;

  /* forward_ip_miss has no parameters */

  /* state_check_allow_action has no parameters */

  /* state_check_to_controller_action has no parameters */

  /* state_check_drop_action has no parameters */


typedef struct p4_pd_main_action_specs_t {
  p4_pd_main_action_names_t name;
  union {
  /* firewall_allow_action has no parameters */
  /* firewall_drop_action has no parameters */
    struct p4_pd_main_forward_hit_action_spec p4_pd_main_forward_hit;
  /* forward_miss has no parameters */
    struct p4_pd_main_forward_ip_hit_action_spec p4_pd_main_forward_ip_hit;
  /* forward_ip_miss has no parameters */
  /* state_check_allow_action has no parameters */
  /* state_check_to_controller_action has no parameters */
  /* state_check_drop_action has no parameters */
  } u;
} p4_pd_main_action_specs_t;

void p4_pd_main_init(void);

/* HA TESTING INFRASTRUCTURE */

/* REGISTER VALUES */


/* IDLE TIME CONFIG */


p4_pd_status_t
p4_pd_main_firewall_table_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_firewall_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_forward_table_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_state_check_table_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);



/* Dynamic Exm Table Key Mask */


/* ADD ENTRIES */

/**
 * @brief p4_pd_main_firewall_table_table_add_with_firewall_allow_action
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_add_with_firewall_allow_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_firewall_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_firewall_table_table_add_with_firewall_drop_action
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_add_with_firewall_drop_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_firewall_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_table_add_with_forward_hit
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_table_add_with_forward_hit
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_match_spec_t *match_spec,
 p4_pd_main_forward_hit_action_spec_t *action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_table_add_with_forward_miss
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_table_add_with_forward_miss
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_add_with_forward_ip_hit
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_add_with_forward_ip_hit
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec,
 p4_pd_main_forward_ip_hit_action_spec_t *action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_add_with_forward_ip_miss
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_add_with_forward_ip_miss
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_add_with_state_check_allow_action
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_add_with_state_check_allow_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_add_with_state_check_to_controller_action
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_add_with_state_check_to_controller_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_add_with_state_check_drop_action
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_add_with_state_check_drop_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);


/* DELETE ENTRIES */

/**
 * @brief p4_pd_main_firewall_table_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_firewall_table_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_firewall_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_forward_table_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_state_check_table_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec
);


/* Get default entry handle */

p4_pd_status_t
p4_pd_main_firewall_table_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_firewall_table_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t *action_spec
);

p4_pd_status_t
p4_pd_main_forward_table_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_forward_table_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t *action_spec
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t *action_spec
);

p4_pd_status_t
p4_pd_main_state_check_table_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_state_check_table_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t *action_spec
);


/* Clear default entry */

p4_pd_status_t
p4_pd_main_firewall_table_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_forward_table_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_state_check_table_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);


/* MODIFY TABLE PROPERTIES */

p4_pd_status_t
p4_pd_main_firewall_table_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_firewall_table_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_forward_table_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_forward_table_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_state_check_table_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_state_check_table_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);


/* MODIFY ENTRIES */

/**
 * @brief p4_pd_main_firewall_table_table_modify_with_firewall_allow_action
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_modify_with_firewall_allow_action
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_firewall_table_table_modify_with_firewall_allow_action_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_modify_with_firewall_allow_action_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_firewall_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_firewall_table_table_modify_with_firewall_drop_action
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_modify_with_firewall_drop_action
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_firewall_table_table_modify_with_firewall_drop_action_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_firewall_table_table_modify_with_firewall_drop_action_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_firewall_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_forward_table_table_modify_with_forward_hit
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_table_modify_with_forward_hit
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 p4_pd_main_forward_hit_action_spec_t *action_spec
);

/**
 * @brief p4_pd_main_forward_table_table_modify_with_forward_hit_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_table_modify_with_forward_hit_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_match_spec_t *match_spec,
 p4_pd_main_forward_hit_action_spec_t *action_spec
);

/**
 * @brief p4_pd_main_forward_table_table_modify_with_forward_miss
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_table_modify_with_forward_miss
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_forward_table_table_modify_with_forward_miss_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_table_modify_with_forward_miss_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_hit
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_hit
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 p4_pd_main_forward_ip_hit_action_spec_t *action_spec
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_hit_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_hit_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec,
 p4_pd_main_forward_ip_hit_action_spec_t *action_spec
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_miss
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_miss
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_miss_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_table_modify_with_forward_ip_miss_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_state_check_table_table_modify_with_state_check_allow_action
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_modify_with_state_check_allow_action
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_modify_with_state_check_allow_action_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_modify_with_state_check_allow_action_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_state_check_table_table_modify_with_state_check_to_controller_action
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_modify_with_state_check_to_controller_action
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_modify_with_state_check_to_controller_action_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_modify_with_state_check_to_controller_action_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec
);

/**
 * @brief p4_pd_main_state_check_table_table_modify_with_state_check_drop_action
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_modify_with_state_check_drop_action
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_state_check_table_table_modify_with_state_check_drop_action_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_state_check_table_table_modify_with_state_check_drop_action_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_state_check_table_match_spec_t *match_spec
);



/* SET DEFAULT_ACTION */

/**
 * @brief p4_pd_main_firewall_table_set_default_action_firewall_drop_action
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_firewall_table_set_default_action_firewall_drop_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_set_default_action_forward_miss
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_set_default_action_forward_miss
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_forward_table_by_dst_ip_set_default_action_forward_ip_miss
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_set_default_action_forward_ip_miss
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_state_check_table_set_default_action_state_check_drop_action
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_state_check_table_set_default_action_state_check_drop_action
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);



/* INDIRECT ACTION DATA AND MATCH SELECT */






p4_pd_status_t
p4_pd_main_firewall_table_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_forward_table_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_state_check_table_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);



p4_pd_status_t
p4_pd_main_firewall_table_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int *index
);

p4_pd_status_t
p4_pd_main_firewall_table_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 int *next_entry_handles
);

p4_pd_status_t
p4_pd_main_firewall_table_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_firewall_table_match_spec_t *match_spec,
 p4_pd_main_action_specs_t *action_spec
);

p4_pd_status_t
p4_pd_main_forward_table_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int *index
);

p4_pd_status_t
p4_pd_main_forward_table_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 int *next_entry_handles
);

p4_pd_status_t
p4_pd_main_forward_table_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_forward_table_match_spec_t *match_spec,
 p4_pd_main_action_specs_t *action_spec
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int *index
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 int *next_entry_handles
);

p4_pd_status_t
p4_pd_main_forward_table_by_dst_ip_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_forward_table_by_dst_ip_match_spec_t *match_spec,
 p4_pd_main_action_specs_t *action_spec
);

p4_pd_status_t
p4_pd_main_state_check_table_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int *index
);

p4_pd_status_t
p4_pd_main_state_check_table_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 int *next_entry_handles
);

p4_pd_status_t
p4_pd_main_state_check_table_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 uint8_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_state_check_table_match_spec_t *match_spec,
 p4_pd_main_action_specs_t *action_spec
);






p4_pd_status_t
p4_pd_main_set_learning_timeout(p4_pd_sess_hdl_t shdl,
                                    uint8_t          device_id,
                                    uint32_t         usecs);

/* COUNTERS */




// REGISTERS



/* METERS */


/* LPF */


/* WRED */



typedef struct __attribute__((__packed__)) p4_pd_main_ig_snapshot_trig_spec {
  uint8_t ig_intr_md_resubmit_flag;
  uint8_t ig_intr_md__pad1;
  uint8_t ig_intr_md__pad2;
  uint8_t ig_intr_md__pad3;
  uint16_t ig_intr_md_ingress_port;
  uint16_t ig_intr_md_for_tm_ucast_egress_port;
  uint8_t ig_intr_md_for_tm_drop_ctl;
  uint8_t ig_intr_md_for_tm_copy_to_cpu;
  uint8_t ethernet_dstAddr[6];
  uint8_t ethernet_srcAddr[6];
  uint16_t ethernet_etherType;
  uint8_t ipv4_version;
  uint8_t ipv4_ihl;
  uint8_t ipv4_diffserv;
  uint16_t ipv4_totalLen;
  uint16_t ipv4_identification;
  uint8_t ipv4_flags;
  uint16_t ipv4_fragOffset;
  uint8_t ipv4_ttl;
  uint8_t ipv4_protocol;
  uint16_t ipv4_hdrChecksum;
  uint32_t ipv4_srcAddr;
  uint32_t ipv4_dstAddr;
  uint16_t tcp_udp_srcPort;
  uint16_t tcp_udp_dstPort;
  uint32_t tcp_seqNo;
  uint32_t tcp_ackNo;
  uint8_t tcp_dataOffset;
  uint8_t tcp_res;
  uint8_t tcp_ecn;
  uint8_t tcp_urg;
  uint8_t tcp_ack;
  uint8_t tcp_psh;
  uint8_t tcp_rst;
  uint8_t tcp_syn;
  uint8_t tcp_fin;
  uint16_t tcp_window;
  uint16_t tcp_checksum;
  uint16_t tcp_urgentPtr;
  uint16_t udp_udpLength;
  uint16_t udp_checksum;
  uint8_t icmp_icmpType;
  uint8_t icmp_icmpCode;
  uint16_t icmp_checksum;
  uint32_t _selector_CLONE_I2E_DIGEST_RCVR;
  /* POV fields */
  uint8_t ethernet_valid;
  uint8_t ipv4_valid;
  uint8_t tcp_udp_valid;
  uint8_t tcp_valid;
  uint8_t udp_valid;
  uint8_t icmp_valid;

} p4_pd_main_ig_snapshot_trig_spec_t;


typedef struct __attribute__((__packed__)) p4_pd_main_eg_snapshot_trig_spec {
  uint8_t ethernet_dstAddr[6];
  uint8_t ethernet_srcAddr[6];
  uint16_t ethernet_etherType;
  uint8_t ipv4_version;
  uint8_t ipv4_ihl;
  uint8_t ipv4_diffserv;
  uint16_t ipv4_totalLen;
  uint16_t ipv4_identification;
  uint8_t ipv4_flags;
  uint16_t ipv4_fragOffset;
  uint8_t ipv4_ttl;
  uint8_t ipv4_protocol;
  uint16_t ipv4_hdrChecksum;
  uint32_t ipv4_srcAddr;
  uint32_t ipv4_dstAddr;
  uint8_t icmp_icmpType;
  uint8_t icmp_icmpCode;
  uint16_t icmp_checksum;
  uint16_t tcp_udp_srcPort;
  uint16_t tcp_udp_dstPort;
  uint32_t tcp_seqNo;
  uint32_t tcp_ackNo;
  uint8_t tcp_dataOffset;
  uint8_t tcp_res;
  uint8_t tcp_ecn;
  uint8_t tcp_urg;
  uint8_t tcp_ack;
  uint8_t tcp_psh;
  uint8_t tcp_rst;
  uint8_t tcp_syn;
  uint8_t tcp_fin;
  uint16_t tcp_window;
  uint16_t tcp_checksum;
  uint16_t tcp_urgentPtr;
  uint16_t udp_udpLength;
  uint16_t udp_checksum;
  uint8_t eg_intr_md__pad0;
  uint16_t eg_intr_md_egress_port;
  uint8_t eg_intr_md__pad7;
  uint8_t eg_intr_md_egress_cos;
  /* POV fields */
  uint8_t ethernet_valid;
  uint8_t ipv4_valid;
  uint8_t icmp_valid;
  uint8_t tcp_udp_valid;
  uint8_t tcp_valid;
  uint8_t udp_valid;

} p4_pd_main_eg_snapshot_trig_spec_t;


typedef struct __attribute__((__packed__)) p4_pd_main_snapshot_trig_spec {
    union {
        p4_pd_main_ig_snapshot_trig_spec_t ig;
        p4_pd_main_eg_snapshot_trig_spec_t eg;
    } u;
}  p4_pd_main_snapshot_trig_spec_t;


typedef p4_pd_main_ig_snapshot_trig_spec_t p4_pd_main_ig_snapshot_capture_data_t;
typedef p4_pd_main_eg_snapshot_trig_spec_t p4_pd_main_eg_snapshot_capture_data_t;


typedef struct __attribute__ ((__packed__)) p4_pd_main_snapshot_capture {
     union {
         p4_pd_main_ig_snapshot_capture_data_t ig;
         p4_pd_main_eg_snapshot_capture_data_t eg;
     } u;
} p4_pd_main_snapshot_capture_t;

/* Array of snapshot captures if start and en stage are different */
typedef struct p4_pd_main_snapshot_capture_arr {
    p4_pd_main_snapshot_capture_t captures[BF_MAX_SNAPSHOT_CAPTURES];
} p4_pd_main_snapshot_capture_arr_t;


/**
 * @brief Set snapshot trigger.
 * @param hdl Snapshot handle.
 * @param trig_spec Trigger spec.
 * @param trig_mask Trigger mask.
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_capture_trigger_set(
              pipe_snapshot_hdl_t hdl,
              p4_pd_main_snapshot_trig_spec_t *trig_spec,
              p4_pd_main_snapshot_trig_spec_t *trig_mask);

/**
 * @brief Get snapshot capture data.
 * @param hdl Snapshot handle.
 * @param pipe Pipe.
 * @param capture Captured data
 * @param num_captures Num of captures
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_capture_data_get(
              pipe_snapshot_hdl_t hdl,
              uint16_t dev_pipe_id,
              p4_pd_main_snapshot_capture_arr_t *capture,
              bf_snapshot_capture_ctrl_info_arr_t *capture_ctrl_arr,
              int *num_captures);

/**
 * @brief Create a snapshot.
 * @param dev_tgt Device information.
 * @param start_stage_id Start stage.
 * @param end_stage_id End stage.
 * @param direction Ingress or egress
 * @param hdl Snapshot handle.
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_create(
            p4_pd_dev_target_t dev_tgt,
            uint8_t start_stage_id, uint8_t end_stage_id,
            bf_snapshot_dir_t direction,
            pipe_snapshot_hdl_t *hdl);

/**
 * @brief Delete snapshot.
 * @param hdl Snapshot handle.
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_delete(
            pipe_snapshot_hdl_t hdl);






typedef enum p4_pd_main_input_field_attr_type {
  P4_PD_INPUT_FIELD_ATTR_TYPE_MASK = 0,
  P4_PD_INPUT_FIELD_ATTR_TYPE_VALUE,
} p4_pd_main_input_field_attr_type_t;

typedef enum p4_pd_main_input_field_attr_value_mask {
  P4_PD_INPUT_FIELD_EXCLUDED = 0,
  P4_PD_INPUT_FIELD_INCLUDED
} p4_pd_main_input_field_attr_value_mask_t;


#endif
