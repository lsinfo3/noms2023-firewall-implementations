/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2019 Barefoot Networks, Inc.

 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of
 * Barefoot Networks, Inc. and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Barefoot Networks,
 * Inc.
 * and its suppliers and may be covered by U.S. and Foreign Patents, patents in
 * process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material is
 * strictly forbidden unless prior written permission is obtained from
 * Barefoot Networks, Inc.
 *
 * No warranty, explicit or implicit is provided, unless granted under a
 * written agreement with Barefoot Networks, Inc.
 *
 * $Id: $
 *
 ******************************************************************************/
/*!
 * @file pipe_mgr_intf.h
 * @date
 *
 * Definitions for interfaces to pipeline manager
 */

#ifndef _PIPE_MGR_INTF_H
#define _PIPE_MGR_INTF_H

/* Standard includes */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Module header files */
#include <bf_types/bf_types.h>
#include <pipe_mgr/pipe_mgr_err.h>

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum pipe_hdl_type {
  /* API session handles */
  PIPE_HDL_TYPE_SESSION = 0x00,

  /* Handles for logical table objects */
  PIPE_HDL_TYPE_MAT_TBL = 0x01,   /* Match action table */
  PIPE_HDL_TYPE_ADT_TBL = 0x02,   /* Action data table */
  PIPE_HDL_TYPE_SEL_TBL = 0x03,   /* Selection table */
  PIPE_HDL_TYPE_STAT_TBL = 0x04,  /* Statistics table */
  PIPE_HDL_TYPE_METER_TBL = 0x05, /* Meter, LPF and WRED table */
  PIPE_HDL_TYPE_STFUL_TBL = 0x06, /* Stateful table */
  PIPE_HDL_TYPE_COND_TBL = 0x07,  /* Gateway table */

  /* Handles for logical table entry objects */
  PIPE_HDL_TYPE_MAT_ENT = 0x10,  /* Match action table entry */
  PIPE_HDL_TYPE_ADT_ENT = 0x11,  /* Action data table entry */
  PIPE_HDL_TYPE_SEL_GRP = 0x12,  /* Selection table group entry */
  PIPE_HDL_TYPE_STAT_ENT = 0x13, /* Statistics table entry */
  PIPE_HDL_TYPE_MET_ENT = 0x14,  /* Meter table entry */
  PIPE_HDL_TYPE_SFUL_ENT = 0x15, /* Stateful memory table entry */

  /* Handles for other P4 level objects */
  PIPE_HDL_TYPE_ACTION_FN = 0x20, /* P4 action function */
  PIPE_HDL_TYPE_FIELD_LST = 0x21, /* P4 field list */
  PIPE_HDL_TYPE_CALC_ALGO = 0x22, /* P4 calculation algorithm */

  /* Handle for Poor-mans selection table */
  PIPE_HDL_TYPE_POOR_MANS_SEL_TBL = 0x23,

  /* Reserve one type for invalid type */
  PIPE_HDL_TYPE_INVALID = 0x3F /* Reserved to indicate invalid handle */
} pipe_hdl_type_t;

#define PIPE_SET_HDL_TYPE(hdl, type) (((type) << 24) | (hdl))
#define PIPE_GET_HDL_TYPE(hdl) (((hdl) >> 24) & 0x3F)
#define PIPE_SET_HDL_PIPE(hdl, pipe) (((pipe) << 30) | (hdl))
#define PIPE_GET_HDL_PIPE(hdl) (((hdl) >> 30) & 0x3)
#define PIPE_GET_HDL_VAL(hdl) ((hdl)&0x00FFFFFF)

typedef enum pipe_mgr_tbl_prop_type_ {
  PIPE_MGR_TABLE_PROP_NONE = 0,
  PIPE_MGR_TABLE_ENTRY_SCOPE,
  PIPE_MGR_TERN_TABLE_ENTRY_PLACEMENT,
  PIPE_MGR_DUPLICATE_ENTRY_CHECK,
  PIPE_MGR_IDLETIME_REPEATED_NOTIFICATION,
} pipe_mgr_tbl_prop_type_t;

typedef enum pipe_mgr_tbl_prop_scope_value {
  PIPE_MGR_ENTRY_SCOPE_ALL_PIPELINES = 0,
  PIPE_MGR_ENTRY_SCOPE_SINGLE_PIPELINE = 1,
  PIPE_MGR_ENTRY_SCOPE_USER_DEFINED = 2,
} pipe_mgr_tbl_prop_scope_value_t;

typedef enum pipe_mgr_tbl_prop_tern_placement_value {
  PIPE_MGR_TERN_ENTRY_PLACEMENT_DRV_MANAGED = 0,
  PIPE_MGR_TERN_ENTRY_PLACEMENT_APP_MANAGED = 1,
} pipe_mgr_tbl_prop_tern_placement_value_t;

typedef enum pipe_mgr_tbl_prop_duplicate_entry_check_value {
  PIPE_MGR_DUPLICATE_ENTRY_CHECK_DISABLE = 0,
  PIPE_MGR_DUPLICATE_ENTRY_CHECK_ENABLE = 1,
} pipe_mgr_tbl_prop_duplicate_entry_check_value_t;

typedef enum pipe_mgr_tbl_prop_idletime_repeated_notification_enable_value {
  PIPE_MGR_IDLETIME_REPEATED_NOTIFICATION_DISABLE = 0,
  PIPE_MGR_IDLETIME_REPEATED_NOTIFICATION_ENABLE = 1,
} pipe_mgr_tbl_prop_idletime_repeated_notification_enable_value_t;

typedef union pipe_mgr_tbl_prop_value {
  uint32_t value;
  pipe_mgr_tbl_prop_scope_value_t scope;
  pipe_mgr_tbl_prop_tern_placement_value_t tern_placement;
  pipe_mgr_tbl_prop_duplicate_entry_check_value_t duplicate_check;
  pipe_mgr_tbl_prop_idletime_repeated_notification_enable_value_t
      repeated_notify;
} pipe_mgr_tbl_prop_value_t;

#define PIPE_MGR_MAX_USER_DEFINED_SCOPES 4
typedef uint8_t scope_pipes_t;
typedef union pipe_mgr_tbl_prop_args {
  uint32_t value;
  scope_pipes_t user_defined_entry_scope[PIPE_MGR_MAX_USER_DEFINED_SCOPES];
} pipe_mgr_tbl_prop_args_t;

typedef enum {
  /* keep enums in sync with p4_pd_pvs_parser_scope_en */
  PIPE_MGR_PVS_SCOPE_ALL_PARSERS_IN_PIPE = 0,
  PIPE_MGR_PVS_SCOPE_SINGLE_PARSER = 1
} pipe_mgr_pvs_parser_scope_en;

typedef enum {
  /* keep enums in sync with p4_pd_pvs_gress_scope_en */
  PIPE_MGR_PVS_SCOPE_ALL_GRESS = 0,
  PIPE_MGR_PVS_SCOPE_SINGLE_GRESS = 1
} pipe_mgr_pvs_gress_scope_en;

typedef enum {
  /* keep enums in sync with p4_pd_pvs_pipe_scope_en */
  PIPE_MGR_PVS_SCOPE_ALL_PIPELINES = 0,
  PIPE_MGR_PVS_SCOPE_SINGLE_PIPELINE = 1,
  PIPE_MGR_PVS_SCOPE_USER_DEFINED = 2
} pipe_mgr_pvs_pipe_scope_en;

typedef enum {
  /* keep enums in sync with p4_pd_pvs_gress_en */
  PIPE_MGR_PVS_GRESS_INGRESS = 0,
  PIPE_MGR_PVS_GRESS_EGRESS = 1,
  PIPE_MGR_PVS_GRESS_ALL = 0xFF /* Wildcard when you want to specify all
                                 * gress*/
} pipe_mgr_pvs_gress_en;

typedef enum pipe_mgr_pvs_prop_type_ {
  /* keep enum in sync with p4_pd_pvs_prop_type_t */
  PIPE_MGR_PVS_PROP_NONE = 0,
  PIPE_MGR_PVS_GRESS_SCOPE,
  PIPE_MGR_PVS_PIPE_SCOPE,
  PIPE_MGR_PVS_PARSER_SCOPE
} pipe_mgr_pvs_prop_type_t;

typedef union pipe_mgr_pvs_prop_value {
  /* keep enum in sync with p4_pd_pvs_prop_value_t */
  uint32_t value;
  pipe_mgr_pvs_gress_scope_en gress_scope;
  pipe_mgr_pvs_pipe_scope_en pipe_scope;
  pipe_mgr_pvs_parser_scope_en parser_scope;
} pipe_mgr_pvs_prop_value_t;

typedef struct pipe_mgr_pvs_prop_user_defined_args_ {
  pipe_mgr_pvs_gress_en gress;
  scope_pipes_t user_defined_scope[PIPE_MGR_MAX_USER_DEFINED_SCOPES];
} pipe_mgr_pvs_prop_user_defined_args_t;

typedef union pipe_mgr_pvs_prop_args {
  /* keep enum in sync with p4_pd_pvs_prop_args_t */
  uint32_t value;
  pipe_mgr_pvs_gress_en gress;
  pipe_mgr_pvs_prop_user_defined_args_t user_defined;
} pipe_mgr_pvs_prop_args_t;

// Wildcard when you want to specify all parsers
// keep in sync with PD_DEV_PIPE_PARSER_ALL
#define PIPE_MGR_PVS_PARSER_ALL 0xff

/*!
 * Typedefs for pipeline object handles
 */
typedef uint32_t pipe_sess_hdl_t;

typedef uint32_t pipe_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_mat_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_adt_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_sel_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_stat_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_meter_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_lpf_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_wred_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_stful_tbl_hdl_t;
typedef pipe_tbl_hdl_t pipe_ind_res_hdl_t;
typedef pipe_tbl_hdl_t pipe_res_hdl_t;

typedef uint32_t pipe_ent_hdl_t;
typedef pipe_ent_hdl_t pipe_mat_ent_hdl_t;
typedef pipe_ent_hdl_t pipe_adt_ent_hdl_t;
typedef pipe_ent_hdl_t pipe_sel_grp_hdl_t;
typedef pipe_ent_hdl_t pipe_stat_ent_idx_t;
typedef pipe_ent_hdl_t pipe_meter_idx_t;
typedef pipe_ent_hdl_t pipe_lpf_idx_t;
typedef pipe_ent_hdl_t pipe_wred_idx_t;
typedef pipe_ent_hdl_t pipe_stful_mem_idx_t;
typedef pipe_ent_hdl_t pipe_ind_res_idx_t;
typedef pipe_ent_hdl_t pipe_res_idx_t;
typedef pipe_ent_hdl_t pipe_pvs_hdl_t;

typedef uint32_t pipe_act_fn_hdl_t;
typedef uint32_t pipe_fld_lst_hdl_t;
typedef uint32_t pipe_hash_alg_hdl_t;
typedef uint32_t pipe_snapshot_hdl_t;
typedef uint8_t dev_stage_t;
typedef int profile_id_t;
typedef uint32_t pipe_idx_t;
typedef uint8_t pipe_parser_id_t;
typedef uint32_t pipe_hash_calc_hdl_t;

/* Seed value for a hash calculation */
typedef uint64_t pipe_hash_seed_t;

/* Structure definition for a hash value computed by the device */
typedef struct pipe_exm_hash_ {
  uint32_t num_bits; /* Number of bits of hash */
  uint64_t hash_value;

} pipe_exm_hash_t;

typedef void (*pipe_mgr_stat_ent_sync_cback_fn)(bf_dev_id_t device_id,
                                                void *cookie);
typedef void (*pipe_mgr_stat_tbl_sync_cback_fn)(bf_dev_id_t device_id,
                                                void *cookie);
typedef void (*pipe_stful_ent_sync_cback_fn)(bf_dev_id_t device_id,
                                             void *cookie);
typedef void (*pipe_stful_tbl_sync_cback_fn)(bf_dev_id_t device_id,
                                             void *cookie);
/*!
 * Flags that can be used in conjunction with API calls
 */
/*! Flag to make hardware synchronous API requests */
#define PIPE_FLAG_SYNC_REQ (1 << 0)

/* Not to be used */
#define PIPE_FLAG_INTERNAL (1 << 1)

/*!
 * Data types used with this library
 */

/*! Definitions used to identify the target of an API request */
#define DEV_PIPE_ALL BF_DEV_PIPE_ALL
typedef bf_dev_target_t dev_target_t;

/*!
 * Generalized match specification for any lookup table entry
 */
typedef struct pipe_tbl_match_spec {
  uint32_t partition_index;      /*!< The partition index for this entry */
  uint16_t num_valid_match_bits; /*!< Number of match bits valid */
  uint16_t num_match_bytes;      /*!< Size of padded match_value_bits */
  uint8_t *match_value_bits;     /*!< Value of match bits */
  uint8_t *match_mask_bits;
  /*!< Mask for matching. Valid only for ternary tables */
  uint16_t num_match_validity_fields;
  /*!< Number of match fields that require have validity qual */
  uint16_t match_field_validity;
  /*!< Ordered list of match field validity values */
  uint16_t match_field_validity_mask;
  /*!< Mask for matching. Valid only for ternary tables */
  uint32_t priority;
  /*!< Priority dictates the position of a ternary table
   * entry in relation to other entries in the table
   */
} pipe_tbl_match_spec_t;

typedef struct pipe_tbl_ha_reconc_report {
  /*!< Number of entries that were added after delta compute */
  uint32_t num_entries_added;
  /*!< Number of entries that were deleted after delta compute */
  uint32_t num_entries_deleted;
  /*!< Number of entries that were modified after delta compute */
  uint32_t num_entries_modified;
} pipe_tbl_ha_reconc_report_t;

/* Profile of number groups sizes of a certain size in a selection table */
typedef struct pipe_sel_grp_profile {
  uint16_t grp_size; /* Max members in a grp <2..4K> */
  uint16_t num_grps; /* Number of groups of this <grp_size> */
} pipe_sel_grp_profile_t;

typedef struct pipe_sel_tbl_profile {
  uint16_t num_grp_profiles;
  pipe_sel_grp_profile_t *grp_profile_list; /* array */
} pipe_sel_tbl_profile_t;

/*! Flow learn notification entry format. This is interpreted
 * in terms of P4 fields by entry decoder routines
 */

/*! Flow learn notification message format
 */
typedef struct pipe_lrn_digest_msg {
  dev_target_t dev_tgt;
  /*< Device that is the originator of the learn notification */
  uint16_t num_entries;
  /*< number of learn notifications in this message */
  void *entries;
  /*< array of <num_entries> of
    pd_<program_name>_<lrn_digest_field_list_name>_digest_entry_t;*/
  pipe_fld_lst_hdl_t flow_lrn_fld_lst_hdl;
} pipe_flow_lrn_msg_t;

/* Prototype for flow learn notification handler */
typedef pipe_status_t (*pipe_flow_lrn_notify_cb)(
    pipe_sess_hdl_t sess_hdl,
    pipe_flow_lrn_msg_t *pipe_flow_lrn_msg,
    void *callback_fn_cookie);

/*!
 * Enum to define meter rate unit types
 */
typedef enum pipe_meter_type {
  METER_TYPE_COLOR_AWARE,   /*< Color aware meter */
  METER_TYPE_COLOR_UNAWARE, /*< Color unaware meter */
} pipe_meter_type_e;

typedef enum pipe_meter_rate_type {
  METER_RATE_TYPE_KBPS, /*< Type to measure rate in kilobits per sec */
  METER_RATE_TYPE_PPS,  /*< Type to measure rate in pkts per sec */
} pipe_meter_rate_type_e;

/*!
 * Structure for meter specification
 */
typedef struct pipe_meter_rate {
  pipe_meter_rate_type_e type; /*< Type of rate specified */
  union {
    uint64_t kbps; /*< Rate in units of kilobits per second  */
    uint64_t pps;  /*< Rate units of pkts per second */
  } value;
} pipe_meter_rate_t;

/*! Structure for meter specification
 */
typedef struct pipe_meter_spec {
  pipe_meter_type_e meter_type;
  /*< Meter type */
  pipe_meter_rate_t cir;
  /*< Meter committed information rate */
  uint64_t cburst;
  /*< Meter committed burst size */
  pipe_meter_rate_t pir;
  /*< Meter peak information rate */
  uint64_t pburst;
  /*< Meter peak burst size */
} pipe_meter_spec_t;

/*!
 * Enum to define lpf type
 */
typedef enum pipe_lpf_type_ {
  LPF_TYPE_RATE,   /*< Rate LPF */
  LPF_TYPE_SAMPLE, /*< Sample LPF */
} pipe_lpf_type_e;

/*! Structure for a LPF specification
 */
typedef struct pipe_lpf_spec {
  pipe_lpf_type_e lpf_type;
  /*< Enum indicating the type of lpf */
  bool gain_decay_separate_time_constant;
  /*< A flag indicating if a separate rise/fall time constant is desired */
  float gain_time_constant;
  /*< Rise time constant, in nanoseconds, valid only if the above flag is set */
  float decay_time_constant;
  /*< Fall time constant, in nanoseconds valid only if
   * rise_fall_separate_time_constant
   *  flag is set
   */
  float time_constant;
  /*< A common time constant, in nanoseconds valid only if the
   *  rise_fall_separate_time_constant is not set
   */
  uint32_t output_scale_down_factor;
  /*< An integer indicating the scale down factor, right-shifted by these
   *  many bits. Values range from 0 to 31
   */

} pipe_lpf_spec_t;

/*! Structure for a WRED specification
 */
typedef struct pipe_wred_spec {
  float time_constant;
  /*< Time constant, in nanoseconds*/
  uint32_t red_min_threshold;
  /*< Queue threshold above which the probabilistic dropping starts in units
   *  of packet buffer cells
   */
  uint32_t red_max_threshold;
  /*< Queue threshold above which all packets are dropped in units cells*/
  float max_probability;
  /*< Maximum probability desired for marking the packet, with range from 0.0 to
   * 1.0 */

} pipe_wred_spec_t;

/*! Idle Timers
 */
/*!
 * Enum for Idle timer hit state
 */
typedef enum pipe_idle_time_hit_state_ {
  ENTRY_IDLE,
  ENTRY_ACTIVE
} pipe_idle_time_hit_state_e;

/* Prototype for idle timer expiry notification handler */
typedef void (*pipe_idle_tmo_expiry_cb)(bf_dev_id_t dev_id,
                                        pipe_mat_ent_hdl_t mat_ent_hdl,
                                        void *client_data);

/* Prototype for idle time update complete callback handler */
typedef void (*pipe_idle_tmo_update_complete_cb)(bf_dev_id_t dev_id,
                                                 void *cb_data);

typedef enum pipe_idle_time_mode_ {
  POLL_MODE,
  NOTIFY_MODE,
  INVALID_MODE
} pipe_idle_time_mode_e;
static inline const char *idle_time_mode_to_str(pipe_idle_time_mode_e mode) {
  switch (mode) {
    case POLL_MODE:
      return "poll";
    case NOTIFY_MODE:
      return "notify";
    case INVALID_MODE:
      return "disabled";
  }
  return "unknown";
}

typedef struct pipe_idle_time_params_ {
  pipe_idle_time_mode_e mode;
  union {
    struct {
      uint32_t ttl_query_interval;
      /*< Minimum query interval with which the application will call
       *  pipe_mgr_idle_time_get_ttl to get the TTL of an entry.
       * If the API is called sooner than the query interval, then
       * the value received will be same
       */
      uint32_t max_ttl;
      /*< Max TTL any entry in this table can have in msecs */
      uint32_t min_ttl;
      /*< Min TTL any entry in this table can have in msecs */
      pipe_idle_tmo_expiry_cb callback_fn;
      /*< Callback function to call in case of notification mode */
      void *client_data;
      /*< Client data for the callback function */
    } notify;
  } u;
} pipe_idle_time_params_t;

typedef union pipe_stful_mem_spec_t {
  bool bit;
  uint8_t byte;
  uint16_t half;
  uint32_t word;
  uint64_t dbl;
  struct {
    uint8_t hi;
    uint8_t lo;
  } dbl_byte;
  struct {
    uint16_t hi;
    uint16_t lo;
  } dbl_half;
  struct {
    uint32_t hi;
    uint32_t lo;
  } dbl_word;
  struct {
    uint64_t hi;
    uint64_t lo;
  } dbl_dbl;
} pipe_stful_mem_spec_t;

typedef struct pipe_stful_mem_query_t {
  int pipe_count;  // Number of valid indices in the "data" array
  pipe_stful_mem_spec_t *data;
} pipe_stful_mem_query_t;

/*! Statstics state data
 */
typedef struct pipe_stat_data {
  uint64_t bytes;   /*< Byte statistics */
  uint64_t packets; /*< Packet statistics */
} pipe_stat_data_t;

/*! Meter state data
 */
typedef struct pipe_meter_data {
  uint64_t comm_conformed_units;
  /*< bytes or packets that conformed to meter committed rate */
  uint64_t comm_exceeded_units;
  /*< bytes or packets that exceeded meter committed rate */
  uint64_t peak_exceeded_units;
  /*< bytes or packets that exceeded meter peak rate */
} pipe_meter_data_t;

/*! Stateful memory data
 */
enum pipe_res_action_tag {
  PIPE_RES_ACTION_TAG_NO_CHANGE,
  PIPE_RES_ACTION_TAG_ATTACHED,
  PIPE_RES_ACTION_TAG_DETACHED
};
typedef union pipe_res_data_spec_t {
  pipe_stful_mem_spec_t stful;
  pipe_meter_spec_t meter;
  pipe_lpf_spec_t lpf;
  pipe_wred_spec_t red;
  pipe_stat_data_t counter;
} pipe_res_data_spec_t;
typedef struct pipe_res_spec_t {
  pipe_res_hdl_t tbl_hdl;  // Use PIPE_GET_HDL_TYPE to decode
  pipe_res_idx_t tbl_idx;
  pipe_res_data_spec_t data;
  enum pipe_res_action_tag tag;
} pipe_res_spec_t;

/*!
 * Action data specification
 */
typedef struct pipe_action_data_spec {
  uint16_t num_valid_action_data_bits;
  uint16_t num_action_data_bytes;
  /*!< Number of action data bits valid */
  uint8_t *action_data_bits;
  /*!< Action data */
} pipe_action_data_spec_t;

/* Types of action data for a match-action table entry */
#define PIPE_ACTION_DATA_TYPE (1 << 0)
#define PIPE_ACTION_DATA_HDL_TYPE (1 << 1)
#define PIPE_SEL_GRP_HDL_TYPE (1 << 2)
/*!
 * Generalized action specification that encodes all types of action data refs
 */
typedef struct pipe_action_spec {
  uint8_t pipe_action_datatype_bmap;
  /* bitmap of action datatypes */
  pipe_action_data_spec_t act_data;
  pipe_adt_ent_hdl_t adt_ent_hdl;
  pipe_sel_grp_hdl_t sel_grp_hdl;
#define PIPE_NUM_TBL_RESOURCES 4
  pipe_res_spec_t resources[PIPE_NUM_TBL_RESOURCES];
  int resource_count;
} pipe_action_spec_t;

#define IS_ACTION_SPEC_ACT_DATA(act_spec) \
  ((act_spec)->pipe_action_datatype_bmap & PIPE_ACTION_DATA_TYPE)
#define IS_ACTION_SPEC_ACT_DATA_HDL(act_spec) \
  ((act_spec)->pipe_action_datatype_bmap & PIPE_ACTION_DATA_HDL_TYPE)
#define IS_ACTION_SPEC_SEL_GRP(act_spec) \
  ((act_spec)->pipe_action_datatype_bmap & PIPE_SEL_GRP_HDL_TYPE)

typedef enum bf_tbl_dbg_counter_type_e {
  BF_TBL_DBG_CNTR_DISABLED = 0,
  BF_TBL_DBG_CNTR_LOG_TBL_MISS = 1,
  BF_TBL_DBG_CNTR_LOG_TBL_HIT = 2,
  BF_TBL_DBG_CNTR_GW_TBL_MISS = 3,
  BF_TBL_DBG_CNTR_GW_TBL_HIT = 4,
  BF_TBL_DBG_CNTR_GW_TBL_INHIBIT = 5,
  BF_TBL_DBG_CNTR_MAX
} bf_tbl_dbg_counter_type_t;
static inline const char *bf_tbl_dbg_counter_type_to_str(
    bf_tbl_dbg_counter_type_t t) {
  switch (t) {
    case BF_TBL_DBG_CNTR_DISABLED:
      return "BF_TBL_DBG_CNTR_DISABLED";
    case BF_TBL_DBG_CNTR_LOG_TBL_MISS:
      return "BF_TBL_DBG_CNTR_LOG_TBL_MISS";
    case BF_TBL_DBG_CNTR_LOG_TBL_HIT:
      return "BF_TBL_DBG_CNTR_LOG_TBL_HIT";
    case BF_TBL_DBG_CNTR_GW_TBL_MISS:
      return "BF_TBL_DBG_CNTR_GW_TBL_MISS";
    case BF_TBL_DBG_CNTR_GW_TBL_HIT:
      return "BF_TBL_DBG_CNTR_GW_TBL_HIT";
    case BF_TBL_DBG_CNTR_GW_TBL_INHIBIT:
      return "BF_TBL_DBG_CNTR_GW_TBL_INHIBIT";
    case BF_TBL_DBG_CNTR_MAX:
      return "BF_TBL_DBG_CNTR_MAX";
  }
  return "Unknown";
}
/* Snapshot enable/disable state */
typedef enum bf_snapshot_state_e {
  BF_SNAPSHOT_ST_DISABLED = 0,
  BF_SNAPSHOT_ST_ENABLED
} bf_snapshot_state_t;

/* Snapshot direction */
typedef enum {
  BF_SNAPSHOT_DIR_INGRESS = 0,
  BF_SNAPSHOT_DIR_EGRESS = 1
} bf_snapshot_dir_t;

#define BF_TBL_NAME_LEN 200
#define BF_MAX_LOG_TBLS 16
#define BF_MAX_SNAPSHOT_CAPTURES 20
typedef struct bf_snapshot_tables_info {
  char table_name[BF_TBL_NAME_LEN];
  uint32_t table_handle;
  uint32_t match_hit_address;
  uint32_t hit_entry_handle;
  bool table_hit;
  bool table_inhibited;
  bool table_executed;
  bool table_type_tcam;
  char gbl_exec_out_tbl_name[BF_TBL_NAME_LEN];
  char mpr_gbl_exec_out_tbl_name[BF_TBL_NAME_LEN];
} bf_snapshot_tables_info_t;

typedef struct bf_snapshot_meter_alu_info {
  uint32_t table_handle;
  char *ctrl_info_p;
} bf_snapshot_meter_alu_info_t;

typedef struct bf_snapshot_capture_ctrl_info {
  uint8_t stage_id;
  bool valid;
  bool prev_stage_trigger;
  bool timer_trigger;
  bool local_stage_trigger;
  bf_snapshot_tables_info_t tables_info[BF_MAX_LOG_TBLS];
  char next_table[BF_TBL_NAME_LEN];
  char mpr_next_table[BF_TBL_NAME_LEN];
  bool ingr_dp_error;
  bool egr_dp_error;
  bf_snapshot_meter_alu_info_t meter_alu_info[4];
} bf_snapshot_capture_ctrl_info_t;

/* Array of snapshot control info captures if start and en stage are different*/
typedef struct bf_snapshot_capture_ctrl_info_arr {
  bf_snapshot_capture_ctrl_info_t ctrl[BF_MAX_SNAPSHOT_CAPTURES];
} bf_snapshot_capture_ctrl_info_arr_t;

typedef enum { INPUT_FIELD_ATTR_TYPE_MASK = 0 } pipe_input_field_attr_type_t;

typedef enum {
  INPUT_FIELD_EXCLUDED = 0,
  INPUT_FIELD_INCLUDED
} pipe_input_field_attr_value_mask_t;

typedef struct pipe_hash_calc_input_field_attribute {
  uint32_t input_field;
  pipe_input_field_attr_type_t type;
  union {
    pipe_input_field_attr_value_mask_t mask;
    uint32_t val;
  } value;
} pipe_hash_calc_input_field_attribute_t;

/******************************************************************************
 *
 * MAT Placement Callbacks
 *
 *****************************************************************************/
enum pipe_mat_update_type {
  PIPE_MAT_UPDATE_ADD,
  PIPE_MAT_UPDATE_ADD_MULTI, /* An add to multiple logical indices. */
  PIPE_MAT_UPDATE_SET_DFLT,  /* Set the table's default action. */
  PIPE_MAT_UPDATE_CLR_DFLT,  /* Clear the table's default action. */
  PIPE_MAT_UPDATE_DEL,
  PIPE_MAT_UPDATE_MOD,
  PIPE_MAT_UPDATE_MOV,
  PIPE_MAT_UPDATE_MOV_MULTI, /* A move involving mulitple logical indices. */
  PIPE_MAT_UPDATE_MOV_MOD,
  PIPE_MAT_UPDATE_MOV_MULTI_MOD,
  PIPE_MAT_UPDATE_ADD_IDLE
};
struct pipe_mat_update_set_dflt_params {
  pipe_mat_ent_hdl_t ent_hdl;
  pipe_adt_ent_hdl_t action_profile_mbr;
  pipe_idx_t indirect_action_index;
  bool action_profile_mbr_exists;
  pipe_sel_grp_hdl_t sel_grp_hdl;
  pipe_idx_t indirect_selection_index;
  uint32_t num_selector_words;
  bool sel_grp_exists;
  void *data;
};
struct pipe_mat_update_clr_dflt_params {
  pipe_mat_ent_hdl_t ent_hdl;
};
struct pipe_mat_update_add_params {
  pipe_mat_ent_hdl_t ent_hdl;
  uint32_t priority; /* TCAM priority, only valid for TCAM tables. */
  pipe_idx_t logical_index;
  pipe_adt_ent_hdl_t action_profile_mbr;
  pipe_idx_t indirect_action_index;
  bool action_profile_mbr_exists;
  pipe_sel_grp_hdl_t sel_grp_hdl;
  pipe_idx_t indirect_selection_index;
  uint32_t num_selector_words;
  bool sel_grp_exists;
  void *data;
};
struct pipe_mat_update_del_params {
  pipe_mat_ent_hdl_t ent_hdl;
};
struct pipe_mat_update_mod_params {
  pipe_mat_ent_hdl_t ent_hdl;
  pipe_adt_ent_hdl_t action_profile_mbr;
  pipe_idx_t indirect_action_index;
  bool action_profile_mbr_exists;
  pipe_sel_grp_hdl_t sel_grp_hdl;
  pipe_idx_t indirect_selection_index;
  uint32_t num_selector_words;
  bool sel_grp_exists;
  void *data;
};
struct pipe_mat_update_mov_params {
  pipe_mat_ent_hdl_t ent_hdl;
  pipe_idx_t logical_index;
  pipe_adt_ent_hdl_t action_profile_mbr;
  pipe_idx_t indirect_action_index;
  bool action_profile_mbr_exists;
  pipe_sel_grp_hdl_t sel_grp_hdl;
  pipe_idx_t indirect_selection_index;
  uint32_t num_selector_words;
  bool sel_grp_exists;
  void *data;
};
struct pipe_multi_index {
  /* Base logical index. */
  pipe_idx_t logical_index_base;
  /* Count of consecutive indexes (a minimum of one). */
  uint8_t logical_index_count;
};
/* Represents an add to multiple logical indices.  There are
 * logical_index_array_length number of base indices, specified in
 * logical_index_base_array.  Associated with each base index is a count,
 * specified in logical_index_count_array, saying how many consecutive indices
 * are used.  For example, given:
 *   logical_index_array_length = 3
 *   location_array = [ [250,2], [200,1], [300,6] ]
 * The following nine logical indices would be used: 250-251, 200, and 300-305.
 */
struct pipe_mat_update_add_multi_params {
  pipe_mat_ent_hdl_t ent_hdl;
  uint32_t priority; /* TCAM priority, only valid for TCAM tables. */
  pipe_adt_ent_hdl_t action_profile_mbr;
  pipe_idx_t indirect_action_index;
  bool action_profile_mbr_exists;
  pipe_sel_grp_hdl_t sel_grp_hdl;
  pipe_idx_t indirect_selection_index;
  uint32_t num_selector_words;
  bool sel_grp_exists;
  int logical_index_array_length;
  struct pipe_multi_index *location_array;
  void *data;
};
/* Represents a move of an entry occupying multiple logical indices.  Similar
 * to struct pipe_mat_update_add_multi_params, logical_index_array_length
 * specifies how many sets of logical indices are moving.  The location_array
 * provides the new logical indexes of the entry specified as a series of base
 * and count pairs representing count number of logical indexes starting at and
 * includeing the base.  For example, given:
 *   logical_index_array_length = 2
 *   location_array = [[50,3], [100,1]]
 * The entry now occupies logical indices 50-52 and 100. */
struct pipe_mat_update_mov_multi_params {
  pipe_mat_ent_hdl_t ent_hdl;
  pipe_adt_ent_hdl_t action_profile_mbr;
  pipe_idx_t indirect_action_index;
  bool action_profile_mbr_exists;
  pipe_sel_grp_hdl_t sel_grp_hdl;
  pipe_idx_t indirect_selection_index;
  uint32_t num_selector_words;
  bool sel_grp_exists;
  int logical_index_array_length;
  struct pipe_multi_index *location_array;
  void *data;
};
/* A union representing all the possible parameters to a MAT update. */
union pipe_mat_update_params {
  struct pipe_mat_update_set_dflt_params set_dflt;
  struct pipe_mat_update_clr_dflt_params clr_dflt;
  struct pipe_mat_update_add_params add;
  struct pipe_mat_update_del_params del;
  struct pipe_mat_update_mod_params mod;
  struct pipe_mat_update_mov_params mov;
  struct pipe_mat_update_add_multi_params add_multi;
  struct pipe_mat_update_mov_multi_params mov_multi;
};
typedef void (*pipe_mat_update_cb)(bf_dev_target_t dev_tgt,
                                   pipe_tbl_hdl_t tbl_hdl,
                                   enum pipe_mat_update_type update_type,
                                   union pipe_mat_update_params *update_params,
                                   void *cookie);
bf_status_t pipe_register_mat_update_cb(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t device_id,
                                        pipe_mat_tbl_hdl_t tbl_hdl,
                                        pipe_mat_update_cb cb,
                                        void *cb_cookie);

/******************************************************************************
 *
 * ADT Placement Callbacks
 *
 *****************************************************************************/
enum pipe_adt_update_type {
  PIPE_ADT_UPDATE_ADD,
  PIPE_ADT_UPDATE_DEL,
  PIPE_ADT_UPDATE_MOD
};
struct pipe_adt_update_add_params {
  pipe_adt_ent_hdl_t ent_hdl;
  void *data;
};
struct pipe_adt_update_del_params {
  pipe_adt_ent_hdl_t ent_hdl;
};
struct pipe_adt_update_mod_params {
  pipe_adt_ent_hdl_t ent_hdl;
  void *data;
};
union pipe_adt_update_params {
  struct pipe_adt_update_add_params add;
  struct pipe_adt_update_del_params del;
  struct pipe_adt_update_mod_params mod;
};
typedef void (*pipe_adt_update_cb)(bf_dev_target_t dev_tgt,
                                   pipe_tbl_hdl_t tbl_hdl,
                                   enum pipe_adt_update_type update_type,
                                   union pipe_adt_update_params *update_params,
                                   void *cookie);
bf_status_t pipe_register_adt_update_cb(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t device_id,
                                        pipe_adt_tbl_hdl_t tbl_hdl,
                                        pipe_adt_update_cb cb,
                                        void *cb_cookie);

/******************************************************************************
 *
 * SEL Placement Callbacks
 *
 *****************************************************************************/
enum pipe_sel_update_type {
  PIPE_SEL_UPDATE_GROUP_CREATE,
  PIPE_SEL_UPDATE_GROUP_DESTROY,
  PIPE_SEL_UPDATE_ADD,
  PIPE_SEL_UPDATE_DEL,
  PIPE_SEL_UPDATE_ACTIVATE,
  PIPE_SEL_UPDATE_DEACTIVATE,
  PIPE_SEL_UPDATE_SET_FALLBACK,
  PIPE_SEL_UPDATE_CLR_FALLBACK
};
struct pipe_sel_update_group_create_params {
  pipe_sel_grp_hdl_t grp_hdl;
  uint32_t max_members;
  uint32_t num_indexes;
  pipe_idx_t base_logical_index;
  int logical_adt_index_array_length;
  struct pipe_multi_index *logical_adt_indexes;
};
struct pipe_sel_update_group_destroy_params {
  pipe_sel_grp_hdl_t grp_hdl;
};
struct pipe_sel_update_add_params {
  pipe_sel_grp_hdl_t grp_hdl;
  pipe_adt_ent_hdl_t ent_hdl;
  pipe_idx_t logical_index;
  pipe_idx_t logical_subindex;
  void *data;
};
struct pipe_sel_update_del_params {
  pipe_sel_grp_hdl_t grp_hdl;
  pipe_adt_ent_hdl_t ent_hdl;
  pipe_idx_t logical_index;
  pipe_idx_t logical_subindex;
};
struct pipe_sel_update_activate_params {
  pipe_sel_grp_hdl_t grp_hdl;
  pipe_adt_ent_hdl_t ent_hdl;
  pipe_idx_t logical_index;
  pipe_idx_t logical_subindex;
};
struct pipe_sel_update_deactivate_params {
  pipe_sel_grp_hdl_t grp_hdl;
  pipe_adt_ent_hdl_t ent_hdl;
  pipe_idx_t logical_index;
  pipe_idx_t logical_subindex;
};
struct pipe_sel_set_fallback_params {
  pipe_adt_ent_hdl_t ent_hdl;
  void *data;
};
union pipe_sel_update_params {
  struct pipe_sel_update_group_create_params grp_create;
  struct pipe_sel_update_group_destroy_params grp_destroy;
  struct pipe_sel_update_add_params add;
  struct pipe_sel_update_del_params del;
  struct pipe_sel_update_activate_params activate;
  struct pipe_sel_update_deactivate_params deactivate;
  struct pipe_sel_set_fallback_params set_fallback;
};
typedef void (*pipe_sel_update_cb)(bf_dev_target_t dev_tgt,
                                   pipe_tbl_hdl_t tbl_hdl,
                                   enum pipe_sel_update_type update_type,
                                   union pipe_sel_update_params *update_params,
                                   void *cookie);
bf_status_t pipe_register_sel_update_cb(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t device_id,
                                        pipe_sel_tbl_hdl_t tbl_hdl,
                                        pipe_sel_update_cb cb,
                                        void *cb_cookie);

/****************************************
 * ParDe EBUF cut-through APIs
 ****************************************/
/*
 * NOTE:
 *     These APIs shouldn't be called directly and should be called only
 *     through BF_PAL APIs
 */
bf_status_t bf_pipe_mgr_port_ebuf_enable_cut_through(bf_dev_id_t dev_id,
                                                     bf_dev_port_t port_id);

bf_status_t bf_pipe_mgr_port_ebuf_disable_cut_through(bf_dev_id_t dev_id,
                                                      bf_dev_port_t port_id);

/****************************************
 * ParDe IBUF drop threshold API
 ****************************************/
/*
 * This API can be used to set ibuf high and low drop thresholds
 * for a specific port.
 *
 * Note:
 *   This API is not intended to be used by application as changing
 *   defaults would cause over-carving or under-carving of IBUF. This
 *   should be used for debugging purpose or for internal use.
 *
 * Related APIs: bf_pipe_mgr_port_ibuf_set_afull_threshold()
 *
 * @param dev_id              ASIC device identifier.
 * @param port_id             Port Identifier
 * @param drop_hi_thrd        Drop high threshold value in bytes
 * @param drop_low_thrd       Drop low threshold value in bytes
 * @return                    Status of API call.
 */
bf_status_t bf_pipe_mgr_port_ibuf_set_drop_threshold(bf_dev_id_t dev_id,
                                                     bf_dev_port_t port_id,
                                                     uint32_t drop_hi_thrd,
                                                     uint32_t drop_low_thrd);

/****************************************
 * ParDe IBUF almost full threshold API
 ****************************************/
/*
 * This API can be used to set ibuf high and low almost full thresholds
 * for a specific port.
 *
 * Note:
 *   This API is not intended to be used by application as changing
 *   defaults would cause over-carving or under-carving of IBUF. This
 *   should be used for debugging purpose or for internal use.
 *
 * Related APIs: bf_pipe_mgr_port_ibuf_set_drop_threshold()
 *
 * @param dev_id              ASIC device identifier.
 * @param port_id             Port Identifier
 * @param afull_hi_thrd       Afull high threshold value in bytes
 * @param afull_low_thrd      Afull low threshold value in bytes
 * @return                    Status of API call.
 */
bf_status_t bf_pipe_mgr_port_ibuf_set_afull_threshold(bf_dev_id_t dev_id,
                                                      bf_dev_port_t port_id,
                                                      uint32_t afull_hi_thrd,
                                                      uint32_t afull_low_thrd);

/******************************************************************************
 *
 * Placement Data Management
 *   Functions and types used to manage the "void *data" pointer in the
 *   placement update param structures.
 *
 *****************************************************************************/
/* Register the allocation and deallocation functions the driver should use to
 * obtain and release memory required for driver specific placement data.  Note
 * that the registered functions will be used across all devices and therefore
 * only need to be registered once.  If no functions are registered then
 * bf_sys_malloc and bf_sys_free will be used. */
typedef void *(*pipe_plcmnt_alloc)(size_t size);
typedef void (*pipe_plcmnt_free)(void *data);
bf_status_t pipe_register_plcmnt_mem_fns(pipe_plcmnt_alloc alloc_fn,
                                         pipe_plcmnt_free free_fn);
/* Returns the size of the memory pointed to by data.  This can be used to know
 * how much memory to allocate when copying data. */
bf_status_t bf_drv_plcmt_data_size(void *data, size_t *size);
/* Copies the data at src to dst.  Dst should be pre-allocated and of adequate
 * size. src and dst must not overlap. */
bf_status_t bf_drv_plcmt_copy(void *src, void *dst);
/* Allocates memory and then copys the data at src into it.  The memory will be
 * allocated using the registered alloc_fn if set.  The address of the copied
 * data will be returned in *copy. */
bf_status_t bf_drv_plcmt_duplicate(void *src, void **copy);
/* Frees placement data previously allocated by the driver which is no longer
 * needed.  This should be used to free the data returned by a delete callback
 * or the old data returned by a modify callback. */
bf_status_t bf_drv_plcmt_free(void *data);

/******************************************************************************
 *
 * Placement Data Decode
 *
 *****************************************************************************/
pipe_status_t pipe_mgr_plcmt_mat_data_get_entry(
    void *mat_data,
    pipe_tbl_match_spec_t *pipe_match_spec,
    pipe_action_spec_t *pipe_action_spec,
    pipe_act_fn_hdl_t *act_fn_hdl);
pipe_status_t pipe_mgr_plcmt_adt_data_get_entry(
    void *adt_data,
    pipe_action_data_spec_t *pipe_action_data_spec,
    pipe_act_fn_hdl_t *act_fn_hdl);

/******************************************************************************
 *
 * Placement Operations
 *
 *****************************************************************************/

/* Structure representing an ordered group of placement information on the same
 * table.
 * This structure must be created with the pipe_create_plcmt_info function.
 * This structure must be freed with the pipe_destroy_plcmt_info function.
 * The various table operations should be added to the structure using the
 * pipe_set_one_plcmt_op_XXX functions.*/
struct pipe_plcmt_info;
struct pipe_plcmt_info *pipe_create_plcmt_info();
void pipe_destroy_plcmt_info(struct pipe_plcmt_info *info);

/* To populate one operation in a pipe_placement_info structure for MAT entries.
 */
pipe_status_t pipe_set_one_plcmt_op_mat_add(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl,
                                            bf_dev_pipe_t pipe,
                                            pipe_idx_t ent_idx,
                                            pipe_idx_t indirect_selection_idx,
                                            pipe_idx_t indirect_action_idx,
                                            void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_mat_mov(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl,
                                            pipe_idx_t ent_idx,
                                            pipe_idx_t indirect_selection_index,
                                            pipe_idx_t indirect_action_index,
                                            void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_mat_mod(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl,
                                            pipe_idx_t indirect_selection_index,
                                            pipe_idx_t indirect_action_index,
                                            void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_mat_del(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl);
pipe_status_t pipe_set_one_plcmt_op_mat_set_dflt(
    struct pipe_plcmt_info *info,
    pipe_ent_hdl_t ent_hdl,
    bf_dev_pipe_t pipe,
    pipe_idx_t indirect_selection_idx,
    pipe_idx_t logical_action_idx,
    void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_mat_clr_dflt(struct pipe_plcmt_info *info,
                                                 pipe_ent_hdl_t ent_hdl,
                                                 bf_dev_pipe_t pipe);
pipe_status_t pipe_set_one_plcmt_op_mat_add_multi(
    struct pipe_plcmt_info *info,
    pipe_ent_hdl_t ent_hdl,
    bf_dev_pipe_t pipe,
    pipe_idx_t indirect_selection_idx,
    pipe_idx_t indirect_action_idx,
    int array_length,
    struct pipe_multi_index *location_array,
    void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_mat_mov_multi(
    struct pipe_plcmt_info *info,
    pipe_ent_hdl_t ent_hdl,
    pipe_idx_t indirect_selection_idx,
    pipe_idx_t indirect_action_idx,
    int array_length,
    struct pipe_multi_index *location_array,
    void *ent_data);

/* To populate one operation in a pipe_plcmt_info structure for ADT entries.
 */
pipe_status_t pipe_set_one_plcmt_op_adt_add(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl,
                                            bf_dev_pipe_t pipe,
                                            void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_adt_mod(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl,
                                            void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_adt_del(struct pipe_plcmt_info *info,
                                            pipe_ent_hdl_t ent_hdl);

/* To populate one operation in a pipe_plcmt_info structure for Selection
 * entries.
 */
pipe_status_t pipe_set_one_plcmt_op_sel_grp_create(
    struct pipe_plcmt_info *info,
    pipe_sel_grp_hdl_t grp_hdl,
    bf_dev_pipe_t pipe,
    uint32_t num_indexes,
    uint32_t max_members,
    pipe_idx_t base_logical_index,
    int array_length,
    struct pipe_multi_index *location_array);
pipe_status_t pipe_set_one_plcmt_op_sel_grp_destroy(
    struct pipe_plcmt_info *info,
    pipe_sel_grp_hdl_t grp_hdl,
    bf_dev_pipe_t pipe);
pipe_status_t pipe_set_one_plcmt_op_sel_add(struct pipe_plcmt_info *info,
                                            pipe_sel_grp_hdl_t grp_hdl,
                                            pipe_ent_hdl_t ent_hdl,
                                            bf_dev_pipe_t pipe,
                                            pipe_idx_t ent_idx,
                                            pipe_idx_t ent_subidx,
                                            void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_sel_del(struct pipe_plcmt_info *info,
                                            pipe_sel_grp_hdl_t grp_hdl,
                                            pipe_ent_hdl_t ent_hdl,
                                            bf_dev_pipe_t pipe,
                                            pipe_idx_t ent_idx,
                                            pipe_idx_t ent_subidx);
pipe_status_t pipe_set_one_plcmt_op_sel_activate(struct pipe_plcmt_info *info,
                                                 pipe_sel_grp_hdl_t grp_hdl,
                                                 pipe_ent_hdl_t ent_hdl,
                                                 bf_dev_pipe_t pipe,
                                                 pipe_idx_t ent_idx,
                                                 pipe_idx_t ent_subidx);
pipe_status_t pipe_set_one_plcmt_op_sel_deactivate(struct pipe_plcmt_info *info,
                                                   pipe_sel_grp_hdl_t grp_hdl,
                                                   pipe_ent_hdl_t ent_hdl,
                                                   bf_dev_pipe_t pipe,
                                                   pipe_idx_t ent_idx,
                                                   pipe_idx_t ent_subidx);
pipe_status_t pipe_set_one_plcmt_op_sel_set_fallback(
    struct pipe_plcmt_info *info,
    pipe_ent_hdl_t ent_hdl,
    bf_dev_pipe_t pipe,
    void *ent_data);
pipe_status_t pipe_set_one_plcmt_op_sel_clr_fallback(
    struct pipe_plcmt_info *info, bf_dev_pipe_t pipe);

/* A function to process the placement info contained in a pipe_plcmt_info
 * structure. */
pipe_status_t pipe_process_plcmt_info(pipe_sess_hdl_t sess_hdl,
                                      bf_dev_id_t dev_id,
                                      pipe_tbl_hdl_t tbl_hdl,
                                      struct pipe_plcmt_info *info,
                                      uint32_t pipe_api_flags,
                                      uint32_t *processed);

/********************************************
 * Library init/cleanup API
 ********************************************/

/* API to invoke pipe_mgr initialization */
pipe_status_t pipe_mgr_init(void);

void pipe_mgr_cleanup(void);

/********************************************
 * CLIENT API
 ********************************************/

/* API to invoke client library registration */
pipe_status_t pipe_mgr_client_init(pipe_sess_hdl_t *sess_hdl);

/* API to invoke client library de-registration */
pipe_status_t pipe_mgr_client_cleanup(pipe_sess_hdl_t def_sess_hdl);

/********************************************
 * Transaction related API */
/*!
 * Begin a transaction on a session. Only one transaction can be in progress
 * on any given session
 *
 * @param shdl Handle to an active session
 * @param isAtomic If @c true, upon committing the transaction, all changes
 *        will be applied atomically such that a packet being processed will
 *        see either all of the changes or none of the changes.
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_begin_txn(pipe_sess_hdl_t shdl, bool isAtomic);

/*!
 * Verify if all the API requests against the transaction in progress have
 * resources to be committed. This also ends the transaction implicitly
 *
 * @param Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_verify_txn(pipe_sess_hdl_t shdl);

/*!
 * Abort and rollback all API requests against the transaction in progress
 * This also ends the transaction implicitly
 *
 * @param Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_abort_txn(pipe_sess_hdl_t shdl);

/*!
 * Abort and rollback all API requests against the transaction in progress
 * This also ends the transaction implicitly
 *
 * @param Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_commit_txn(pipe_sess_hdl_t shdl, bool hwSynchronous);

/********************************************
 * Batch related API */
/*!
 * Begin a batch on a session. Only one batch can be in progress
 * on any given session.  Updates to the hardware will be batch together
 * and delayed until the batch is ended.
 *
 * @param shdl Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_begin_batch(pipe_sess_hdl_t shdl);

/*!
 * Flush a batch on a session pushing all pending updates to hardware.
 *
 * @param shdl Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_flush_batch(pipe_sess_hdl_t shdl);

/*!
 * End a batch on a session and push all batched updated to hardware.
 *
 * @param shdl Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_end_batch(pipe_sess_hdl_t shdl, bool hwSynchronous);

/*!
 * Helper function for of-tests. Return after all the pending operations
 * for the given session have been completed.
 *
 * @param Handle to an active session
 * @return Status of the API call
 */
pipe_status_t pipe_mgr_complete_operations(pipe_sess_hdl_t shdl);

/*!
 * API to get a match entry handle for the given match spec
 */
pipe_status_t pipe_mgr_match_spec_to_ent_hdl(pipe_sess_hdl_t sess_hdl,
                                             dev_target_t dev_tgt,
                                             pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                             pipe_tbl_match_spec_t *match_spec,
                                             pipe_mat_ent_hdl_t *mat_ent_hdl);

/*!
 * API to apply match key mask on a dynamic key mask table
 */
pipe_status_t pipe_mgr_match_key_mask_spec_set(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_tbl_match_spec_t *match_spec);

pipe_status_t pipe_mgr_match_key_mask_spec_reset(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_mat_tbl_hdl_t mat_tbl_hdl);

pipe_status_t pipe_mgr_match_key_mask_spec_get(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_tbl_match_spec_t *match_spec);

/*!
 * API to install an entry into a match action table
 */
pipe_status_t pipe_mgr_mat_ent_add(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_tbl_match_spec_t *match_spec,
    pipe_act_fn_hdl_t act_fn_hdl,
    pipe_action_spec_t *act_data_spec,
    uint32_t ttl, /*< TTL value in msecs, 0 for disable */
    uint32_t pipe_api_flags,
    pipe_mat_ent_hdl_t *ent_hdl_p);

/*!
 * API to install default (miss) entry for a match action table
 */
pipe_status_t pipe_mgr_mat_default_entry_set(pipe_sess_hdl_t sess_hdl,
                                             dev_target_t dev_tgt,
                                             pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                             pipe_act_fn_hdl_t act_fn_hdl,
                                             pipe_action_spec_t *act_spec,
                                             uint32_t pipe_api_flags,
                                             pipe_mat_ent_hdl_t *ent_hdl_p);

/*!
 * API to get default (miss) entry handle for a match action table
 */
pipe_status_t pipe_mgr_table_get_default_entry_handle(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_mat_ent_hdl_t *ent_hdl_p);

pipe_status_t pipe_mgr_table_get_default_entry(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_action_spec_t *pipe_action_spec,
    pipe_act_fn_hdl_t *act_fn_hdl,
    bool from_hw);

/*!
 * API function to delete an entry from a match action table using an ent hdl
 */
pipe_status_t pipe_mgr_mat_ent_del(pipe_sess_hdl_t sess_hdl,
                                   bf_dev_id_t device_id,
                                   pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                   pipe_mat_ent_hdl_t mat_ent_hdl,
                                   uint32_t pipe_api_flags);

/*!
 * API function to delete an entry from a match action table using a match spec
 */
pipe_status_t pipe_mgr_mat_ent_del_by_match_spec(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_tbl_match_spec_t *match_spec,
    uint32_t pipe_api_flags);

/*!
 * API function to clear the default entry installed.
 */
pipe_status_t pipe_mgr_mat_tbl_default_entry_reset(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    uint32_t pipe_api_flags);

/*!
 * API function to modify action for a match action table entry using an ent hdl
 */
pipe_status_t pipe_mgr_mat_ent_set_action(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t device_id,
                                          pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                          pipe_mat_ent_hdl_t mat_ent_hdl,
                                          pipe_act_fn_hdl_t act_fn_hdl,
                                          pipe_action_spec_t *act_spec,
                                          uint32_t pipe_api_flags);

/*!
 * API function to modify action for a match action table entry using match spec
 */
pipe_status_t pipe_mgr_mat_ent_set_action_by_match_spec(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_tbl_match_spec_t *match_spec,
    pipe_act_fn_hdl_t act_fn_hdl,
    pipe_action_spec_t *act_spec,
    uint32_t pipe_api_flags);

pipe_status_t pipe_mgr_mat_ent_set_resource(pipe_sess_hdl_t sess_hdl,
                                            bf_dev_id_t device_id,
                                            pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                            pipe_mat_ent_hdl_t mat_ent_hdl,
                                            pipe_res_spec_t *resources,
                                            int resource_count,
                                            uint32_t pipe_api_flags);

/********************************************
 * API FOR ACTION DATA TABLE MANIPULATION   *
 ********************************************/

/*!
 * API function to create an action data entry in an action data table
 */
pipe_status_t pipe_mgr_adt_ent_add(pipe_sess_hdl_t sess_hdl,
                                   dev_target_t dev_tgt,
                                   pipe_adt_tbl_hdl_t adt_tbl_hdl,
                                   pipe_act_fn_hdl_t act_fn_hdl,
                                   pipe_action_spec_t *action_spec,
                                   pipe_adt_ent_hdl_t *adt_ent_hdl_p,
                                   uint32_t pipe_api_flags);

/* API function to free an action data entry */
pipe_status_t pipe_mgr_adt_ent_del(pipe_sess_hdl_t sess_hdl,
                                   bf_dev_id_t device_id,
                                   pipe_adt_tbl_hdl_t adt_tbl_hdl,
                                   pipe_adt_ent_hdl_t adt_ent_hdl,
                                   uint32_t pipe_api_flags);

/* API function to update an action data entry */
pipe_status_t pipe_mgr_adt_ent_set(pipe_sess_hdl_t sess_hdl,
                                   bf_dev_id_t device_id,
                                   pipe_adt_tbl_hdl_t adt_tbl_hdl,
                                   pipe_adt_ent_hdl_t adt_ent_hdl,
                                   pipe_act_fn_hdl_t act_fn_hdl,
                                   pipe_action_spec_t *action_spec,
                                   uint32_t pipe_api_flags);

/*********************************************
 * API FOR SELECTOR TABLE MANIPULATION *
 ********************************************/

/*!
 * Callback function prototype to track updates within a stateful selection
 * table.
 */
typedef pipe_status_t (*pipe_mgr_sel_tbl_update_callback)(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    void *cookie,
    pipe_sel_grp_hdl_t sel_grp_hdl,
    pipe_adt_ent_hdl_t adt_ent_hdl,
    int logical_table_index,
    bool is_add);

/*!
 * API function to register a callback function to track updates to groups in
 * the selection table.
 */
pipe_status_t pipe_mgr_sel_tbl_register_cb(pipe_sess_hdl_t sess_hdl,
                                           bf_dev_id_t device_id,
                                           pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                           pipe_mgr_sel_tbl_update_callback cb,
                                           void *cb_cookie);

/*!
 * API function to set the group profile for a selection table
 */
pipe_status_t pipe_mgr_sel_tbl_profile_set(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_sel_tbl_hdl_t sel_tbl_hdl,
    pipe_sel_tbl_profile_t *sel_tbl_profile);

/*!
 * API function to add a new group into a selection table
 */
pipe_status_t pipe_mgr_sel_grp_add(pipe_sess_hdl_t sess_hdl,
                                   dev_target_t dev_tgt,
                                   pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                   uint32_t max_grp_size,
                                   pipe_sel_grp_hdl_t *sel_grp_hdl_p,
                                   uint32_t pipe_api_flags);

/*!
 * API function to delete a group from a selection table
 */
pipe_status_t pipe_mgr_sel_grp_del(pipe_sess_hdl_t sess_hdl,
                                   bf_dev_id_t device_id,
                                   pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                   pipe_sel_grp_hdl_t sel_grp_hdl,
                                   uint32_t pipe_api_flags);

/*!
 * API function to add a member to a group of a selection table
 */
pipe_status_t pipe_mgr_sel_grp_mbr_add(pipe_sess_hdl_t sess_hdl,
                                       bf_dev_id_t device_id,
                                       pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                       pipe_sel_grp_hdl_t sel_grp_hdl,
                                       pipe_act_fn_hdl_t act_fn_hdl,
                                       pipe_adt_ent_hdl_t adt_ent_hdl,
                                       uint32_t pipe_api_flags);

/*!
 * API function to delete a member from a group of a selection table
 */
pipe_status_t pipe_mgr_sel_grp_mbr_del(pipe_sess_hdl_t sess_hdl,
                                       bf_dev_id_t device_id,
                                       pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                       pipe_sel_grp_hdl_t sel_grp_hdl,
                                       pipe_adt_ent_hdl_t adt_ent_hdl,
                                       uint32_t pipe_api_flags);

/*!
 * API function to set membership of a group
 */
pipe_status_t pipe_mgr_sel_grp_mbrs_set(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t device_id,
                                        pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                        pipe_sel_grp_hdl_t sel_grp_hdl,
                                        uint32_t num_mbrs,
                                        pipe_adt_ent_hdl_t *mbrs,
                                        bool *enable,
                                        uint32_t pipe_api_flags);

/*!
 * API function to get membership of a group
 */
pipe_status_t pipe_mgr_sel_grp_mbrs_get(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t device_id,
                                        pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                        pipe_sel_grp_hdl_t sel_grp_hdl,
                                        uint32_t mbrs_size,
                                        pipe_adt_ent_hdl_t *mbrs,
                                        bool *enable,
                                        uint32_t *mbrs_populated);

enum pipe_mgr_grp_mbr_state_e {
  PIPE_MGR_GRP_MBR_STATE_ACTIVE = 0,
  PIPE_MGR_GRP_MBR_STATE_INACTIVE = 1
};

/* API function to disable a group member of a selection table */
pipe_status_t pipe_mgr_sel_grp_mbr_disable(pipe_sess_hdl_t sess_hdl,
                                           bf_dev_id_t device_id,
                                           pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                           pipe_sel_grp_hdl_t sel_grp_hdl,
                                           pipe_adt_ent_hdl_t adt_ent_hdl,
                                           uint32_t pipe_api_flags);

/* API function to re-enable a group member of a selection table */
pipe_status_t pipe_mgr_sel_grp_mbr_enable(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t device_id,
                                          pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                          pipe_sel_grp_hdl_t sel_grp_hdl,
                                          pipe_adt_ent_hdl_t adt_ent_hdl,
                                          uint32_t pipe_api_flags);

/* API function to get the current state of a selection member */
pipe_status_t pipe_mgr_sel_grp_mbr_state_get(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_sel_tbl_hdl_t sel_tbl_hdl,
    pipe_sel_grp_hdl_t sel_grp_hdl,
    pipe_adt_ent_hdl_t adt_ent_hdl,
    enum pipe_mgr_grp_mbr_state_e *mbr_state_p);

/* API function to get the member handle given a hash value */
pipe_status_t pipe_mgr_sel_grp_mbr_get_from_hash(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t dev_id,
    pipe_sel_tbl_hdl_t sel_tbl_hdl,
    pipe_sel_grp_hdl_t grp_hdl,
    uint8_t *hash,
    uint32_t hash_len,
    pipe_adt_ent_hdl_t *adt_ent_hdl_p);

/* API function to set the fallback member */
pipe_status_t pipe_mgr_sel_fallback_mbr_set(pipe_sess_hdl_t sess_hdl,
                                            dev_target_t dev_tgt,
                                            pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                            pipe_adt_ent_hdl_t adt_ent_hdl,
                                            uint32_t pipe_api_flags);

/* API function to reset the fallback member */
pipe_status_t pipe_mgr_sel_fallback_mbr_reset(pipe_sess_hdl_t sess_hdl,
                                              dev_target_t dev_tgt,
                                              pipe_sel_tbl_hdl_t sel_tbl_hdl,
                                              uint32_t pipe_api_flags);

/***************************************
 * API FOR FLOW LEARNING NOTIFICATIONS *
 ***************************************/
/* Flow learn notify registration */
pipe_status_t pipe_mgr_lrn_digest_notification_register(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_fld_lst_hdl_t flow_lrn_fld_lst_hdl,
    pipe_flow_lrn_notify_cb callback_fn,
    void *callback_fn_cookie);

/* Flow learn notify de-registration */
pipe_status_t pipe_mgr_lrn_digest_notification_deregister(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_fld_lst_hdl_t flow_lrn_fld_lst_hdl);

/* Flow learn notification processing completion acknowledgment */
pipe_status_t pipe_mgr_flow_lrn_notify_ack(
    pipe_sess_hdl_t sess_hdl,
    pipe_fld_lst_hdl_t flow_lrn_fld_lst_hdl,
    pipe_flow_lrn_msg_t *pipe_flow_lrn_msg);

/* Flow learn notification set timeout */
pipe_status_t pipe_mgr_flow_lrn_set_timeout(pipe_sess_hdl_t sess_hdl,
                                            bf_dev_id_t device_id,
                                            uint32_t usecs);

pipe_status_t pipe_mgr_flow_lrn_set_network_order_digest(bf_dev_id_t device_id,
                                                         bool network_order);

/*****************************************
 * API FOR STATISTICS TABLE MANIPULATION *
 *****************************************/

/* API function to query a direct stats entry */
pipe_status_t pipe_mgr_mat_ent_direct_stat_query(pipe_sess_hdl_t sess_hdl,
                                                 bf_dev_id_t device_id,
                                                 pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                                 pipe_mat_ent_hdl_t mat_ent_hdl,
                                                 pipe_stat_data_t *stat_data);

/* API function to set/clear a direct stats entry */
pipe_status_t pipe_mgr_mat_ent_direct_stat_set(pipe_sess_hdl_t sess_hdl,
                                               bf_dev_id_t device_id,
                                               pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                               pipe_mat_ent_hdl_t mat_ent_hdl,
                                               pipe_stat_data_t *stat_data);

/* API function to load a direct stats entry */
pipe_status_t pipe_mgr_mat_ent_direct_stat_load(pipe_sess_hdl_t sess_hdl,
                                                bf_dev_id_t device_id,
                                                pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                                pipe_mat_ent_hdl_t mat_ent_hdl,
                                                pipe_stat_data_t *stat_data);

/* API function to query a stats entry */
pipe_status_t pipe_mgr_stat_ent_query(pipe_sess_hdl_t sess_hdl,
                                      dev_target_t dev_target,
                                      pipe_stat_tbl_hdl_t stat_tbl_hdl,
                                      pipe_stat_ent_idx_t stat_ent_idx,
                                      pipe_stat_data_t *stat_data);

/* API function to set/clear a stats entry */
pipe_status_t pipe_mgr_stat_ent_set(pipe_sess_hdl_t sess_hdl,
                                    dev_target_t dev_tgt,
                                    pipe_stat_tbl_hdl_t stat_tbl_hdl,
                                    pipe_stat_ent_idx_t stat_ent_idx,
                                    pipe_stat_data_t *stat_data);

/* API function to load a stats entry (in Hardware) */
pipe_status_t pipe_mgr_stat_ent_load(pipe_sess_hdl_t sess_hdl,
                                     dev_target_t dev_tgt,
                                     pipe_stat_tbl_hdl_t stat_tbl_hdl,
                                     pipe_stat_ent_idx_t stat_idx,
                                     pipe_stat_data_t *stat_data);

/* API to trigger a stats database sync on the indirectly referenced
 * stats table.
 */
pipe_status_t pipe_mgr_stat_database_sync(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_stat_tbl_hdl_t stat_tbl_hdl,
    pipe_mgr_stat_tbl_sync_cback_fn cback_fn,
    void *cookie);

/* API to trigger a stats database sync on the directly referenced
 * stats table.
 */
pipe_status_t pipe_mgr_direct_stat_database_sync(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_mgr_stat_tbl_sync_cback_fn cback_fn,
    void *cookie);

/* API to trigger a stats entry database sync for an indirectly
 * addressed stat table.
 */
pipe_status_t pipe_mgr_stat_ent_database_sync(pipe_sess_hdl_t sess_hdl,
                                              dev_target_t dev_tgt,
                                              pipe_stat_tbl_hdl_t stat_tbl_hdl,
                                              pipe_stat_ent_idx_t stat_ent_idx);

/* API to trigger a stats entry database sync for a directly
 * addressed stat table.
 */
pipe_status_t pipe_mgr_direct_stat_ent_database_sync(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_mat_ent_hdl_t mat_ent_hdl);

/*************************************
 * API FOR METER TABLE MANIPULATION  *
 *************************************/

/* API to update a meter entry specification */
pipe_status_t pipe_mgr_meter_ent_set(pipe_sess_hdl_t sess_hdl,
                                     dev_target_t dev_tgt,
                                     pipe_meter_tbl_hdl_t meter_tbl_hdl,
                                     pipe_meter_idx_t meter_idx,
                                     pipe_meter_spec_t *meter_spec,
                                     uint32_t pipe_api_flags);

/* API to set a meter table bytecount adjust */
pipe_status_t pipe_mgr_meter_set_bytecount_adjust(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_meter_tbl_hdl_t meter_tbl_hdl,
    int bytecount);

/* API to get a meter table bytecount adjust */
pipe_status_t pipe_mgr_meter_get_bytecount_adjust(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_meter_tbl_hdl_t meter_tbl_hdl,
    int *bytecount);

/*************************************
 * API FOR LPF MANIPULATION  *
 *************************************/
pipe_status_t pipe_mgr_lpf_ent_set(pipe_sess_hdl_t sess_hdl,
                                   dev_target_t dev_tgt,
                                   pipe_meter_tbl_hdl_t meter_tbl_hdl,
                                   pipe_lpf_idx_t lpf_idx,
                                   pipe_lpf_spec_t *lpf_spec,
                                   uint32_t pipe_api_flags);

/*************************************
 * API FOR WRED MANIPULATION  *
 *************************************/
pipe_status_t pipe_mgr_wred_ent_set(pipe_sess_hdl_t sess_hdl,
                                    dev_target_t dev_tgt,
                                    pipe_meter_tbl_hdl_t meter_tbl_hdl,
                                    pipe_wred_idx_t red_idx,
                                    pipe_wred_spec_t *wred_spec,
                                    uint32_t pipe_api_flags);

/* API to set the time that the model sees, purely for testing purposes. */
pipe_status_t pipe_mgr_model_time_advance(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t device_id,
                                          uint64_t tick_time);

pipe_status_t pipe_mgr_meter_read_entry(pipe_sess_hdl_t sess_hdl,
                                        dev_target_t dev_tgt,
                                        pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                        pipe_mat_ent_hdl_t mat_ent_hdl,
                                        pipe_meter_spec_t *meter_spec);

pipe_status_t pipe_mgr_meter_read_entry_idx(pipe_sess_hdl_t sess_hdl,
                                            dev_target_t dev_tgt,
                                            pipe_meter_tbl_hdl_t meter_tbl_hdl,
                                            pipe_meter_idx_t index,
                                            pipe_meter_spec_t *meter_spec);

pipe_status_t pipe_mgr_lpf_read_entry(pipe_sess_hdl_t sess_hdl,
                                      dev_target_t dev_tgt,
                                      pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                      pipe_mat_ent_hdl_t mat_ent_hdl,
                                      pipe_lpf_spec_t *lpf_spec);

pipe_status_t pipe_mgr_lpf_read_entry_idx(pipe_sess_hdl_t sess_hdl,
                                          dev_target_t dev_tgt,
                                          pipe_meter_tbl_hdl_t meter_tbl_hdl,
                                          pipe_lpf_idx_t index,
                                          pipe_lpf_spec_t *lpf_spec);

pipe_status_t pipe_mgr_wred_read_entry(pipe_sess_hdl_t sess_hdl,
                                       dev_target_t dev_tgt,
                                       pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                       pipe_mat_ent_hdl_t mat_ent_hdl,
                                       pipe_wred_spec_t *wred_spec);

pipe_status_t pipe_mgr_wred_read_entry_idx(pipe_sess_hdl_t sess_hdl,
                                           dev_target_t dev_tgt,
                                           pipe_meter_tbl_hdl_t meter_tbl_hdl,
                                           pipe_wred_idx_t index,
                                           pipe_wred_spec_t *wred_spec);

pipe_status_t pipe_mgr_exm_entry_activate(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t device_id,
                                          pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                          pipe_mat_ent_hdl_t mat_ent_hdl);

pipe_status_t pipe_mgr_exm_entry_deactivate(pipe_sess_hdl_t sess_hdl,
                                            bf_dev_id_t device_id,
                                            pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                            pipe_mat_ent_hdl_t mat_ent_hdl);

/* Set the Idle timeout TTL for a given match entry */
pipe_status_t pipe_mgr_mat_ent_set_idle_ttl(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_mat_ent_hdl_t mat_ent_hdl,
    uint32_t ttl, /*< TTL value in msecs */
    uint32_t pipe_api_flags);

pipe_status_t pipe_mgr_mat_ent_reset_idle_ttl(pipe_sess_hdl_t sess_hdl,
                                              bf_dev_id_t device_id,
                                              pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                              pipe_mat_ent_hdl_t mat_ent_hdl);

/***************************
 * API FOR IDLE-TMEOUT MGMT*
 ***************************/

/* Configure idle timeout at table level */
pipe_status_t pipe_mgr_idle_params_get(pipe_sess_hdl_t sess_hdl,
                                       bf_dev_id_t device_id,
                                       pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                       pipe_idle_time_params_t *params);

pipe_status_t pipe_mgr_idle_tmo_enable(pipe_sess_hdl_t sess_hdl,
                                       bf_dev_id_t device_id,
                                       pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                       pipe_idle_time_params_t params);

pipe_status_t pipe_mgr_idle_register_tmo_cb(pipe_sess_hdl_t sess_hdl,
                                            bf_dev_id_t device_id,
                                            pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                            pipe_idle_tmo_expiry_cb cb,
                                            void *client_data);

pipe_status_t pipe_mgr_idle_tmo_disable(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t device_id,
                                        pipe_mat_tbl_hdl_t mat_tbl_hdl);

/* The below APIs are used for Poll mode operation only */

/* API function to poll idle timeout data for a table entry */
pipe_status_t pipe_mgr_idle_time_get_hit_state(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_mat_ent_hdl_t mat_ent_hdl,
    pipe_idle_time_hit_state_e *idle_time_data);

/* API function that should be called
 *  periodically or on-demand prior to querying for the hit state
 * The function completes asynchronously and the client will
 * be notified of it's completion via the provided callback function
 */
pipe_status_t pipe_mgr_idle_time_update_hit_state(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t device_id,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_idle_tmo_update_complete_cb callback_fn,
    void *cb_data);

/* The below APIs are used in notify mode */
/* API function to get the current TTL value of the table entry */
pipe_status_t pipe_mgr_mat_ent_get_idle_ttl(pipe_sess_hdl_t sess_hdl,
                                            bf_dev_id_t device_id,
                                            pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                            pipe_mat_ent_hdl_t mat_ent_hdl,
                                            uint32_t *ttl);

/***********************************************
 * API FOR STATEFUL MEMORY TABLE MANIPULATION  *
 ***********************************************/
pipe_status_t pipe_stful_ent_set(pipe_sess_hdl_t sess_hdl,
                                 dev_target_t dev_target,
                                 pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                 pipe_stful_mem_idx_t stful_ent_idx,
                                 pipe_stful_mem_spec_t *stful_spec,
                                 uint32_t pipe_api_flags);

pipe_status_t pipe_stful_database_sync(pipe_sess_hdl_t sess_hdl,
                                       dev_target_t dev_tgt,
                                       pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                       pipe_stful_tbl_sync_cback_fn cback_fn,
                                       void *cookie);

pipe_status_t pipe_stful_direct_database_sync(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_stful_tbl_sync_cback_fn cback_fn,
    void *cookie);

pipe_status_t pipe_stful_query_get_sizes(pipe_sess_hdl_t sess_hdl,
                                         bf_dev_id_t device_id,
                                         pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                         int *num_pipes);

pipe_status_t pipe_stful_direct_query_get_sizes(pipe_sess_hdl_t sess_hdl,
                                                bf_dev_id_t device_id,
                                                pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                                int *num_pipes);

pipe_status_t pipe_stful_ent_query(pipe_sess_hdl_t sess_hdl,
                                   dev_target_t dev_tgt,
                                   pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                   pipe_stful_mem_idx_t stful_ent_idx,
                                   pipe_stful_mem_query_t *stful_query,
                                   uint32_t pipe_api_flags);

pipe_status_t pipe_stful_direct_ent_query(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t device_id,
                                          pipe_mat_tbl_hdl_t mat_tbl_hdl,
                                          pipe_mat_ent_hdl_t mat_ent_hdl,
                                          pipe_stful_mem_query_t *stful_query,
                                          uint32_t pipe_api_flags);

pipe_status_t pipe_stful_table_reset(pipe_sess_hdl_t sess_hdl,
                                     dev_target_t dev_tgt,
                                     pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                     pipe_stful_mem_spec_t *stful_spec);

pipe_status_t pipe_stful_table_reset_range(pipe_sess_hdl_t sess_hdl,
                                           dev_target_t dev_tgt,
                                           pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                           pipe_stful_mem_idx_t stful_ent_idx,
                                           uint32_t num_indices,
                                           pipe_stful_mem_spec_t *stful_spec);
pipe_status_t pipe_stful_fifo_occupancy(pipe_sess_hdl_t sess_hdl,
                                        dev_target_t dev_tgt,
                                        pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                        int *occupancy);
pipe_status_t pipe_stful_fifo_reset(pipe_sess_hdl_t sess_hdl,
                                    dev_target_t dev_tgt,
                                    pipe_stful_tbl_hdl_t stful_tbl_hdl);
pipe_status_t pipe_stful_fifo_dequeue(pipe_sess_hdl_t sess_hdl,
                                      dev_target_t dev_tgt,
                                      pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                      int num_to_dequeue,
                                      pipe_stful_mem_spec_t *values,
                                      int *num_dequeued);
pipe_status_t pipe_stful_fifo_enqueue(pipe_sess_hdl_t sess_hdl,
                                      dev_target_t dev_tgt,
                                      pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                      int num_to_enqueue,
                                      pipe_stful_mem_spec_t *values);

pipe_status_t pipe_stful_ent_query_range(pipe_sess_hdl_t sess_hdl,
                                         dev_target_t dev_tgt,
                                         pipe_stful_tbl_hdl_t stful_tbl_hdl,
                                         pipe_stful_mem_idx_t stful_ent_idx,
                                         uint32_t num_indices_to_read,
                                         pipe_stful_mem_query_t *stful_query,
                                         uint32_t *num_indices_read,
                                         uint32_t pipe_api_flags);

/**
 * Service the instruction list completion DR
 * @param dev_id Device id
 * @return Returns @c PIPE_LLD_FAILED if the servicing fails
 *         Returns @c PIPE_SUCCESS on success.
 */
pipe_status_t bf_dma_service_pipe_ilist_completion(bf_dev_id_t dev_id);

/**
 * Service the learn DR
 * @param dev_id Device id
 * @return Returns @c PIPE_LLD_FAILED if the servicing fails
 *         Returns @c PIPE_SUCCESS on success.
 */
pipe_status_t bf_dma_service_pipe_learning(bf_dev_id_t dev_id);

/**
 * Service the idle time DR
 * @param dev_id Device id
 * @return Returns @c PIPE_LLD_FAILED if the servicing fails
 *         Returns @c PIPE_SUCCESS on success.
 */
pipe_status_t bf_dma_service_pipe_idle_time(bf_dev_id_t dev_id);

/**
 * Service the stats (lr(t)) DR
 * @param dev_id Device id
 * @return Returns @c PIPE_LLD_FAILED if the servicing fails
 *         Returns @c PIPE_SUCCESS on success.
 */
pipe_status_t bf_dma_service_pipe_stats(bf_dev_id_t dev_id);

/**
 * Service the read block completion DR
 * @param dev_id Device id
 * @return Returns @c PIPE_LLD_FAILED if the servicing fails
 *         Returns @c PIPE_SUCCESS on success.
 */
pipe_status_t bf_dma_service_pipe_read_block_completion(bf_dev_id_t dev_id);

/**
 * Service the write block completion DR
 * @param dev_id Device id
 * @return Returns @c PIPE_LLD_FAILED if the servicing fails
 *         Returns @c PIPE_SUCCESS on success.
 */
pipe_status_t bf_dma_service_pipe_write_block_completion(bf_dev_id_t dev_id);

/**
 * Get pipe-id for a particular port
 *
 * @param  dev_port_id           Port-id.
 * @return                       Pipe
 */
uint16_t dev_port_to_pipe_id(uint16_t dev_port_id);

/**
 * Get first entry handle
 *
 * @param  sess_hdl              Session handle
 * @param  tbl_hdl               Table handle.
 * @param  dev_tgt               Device target.
 * @param  entry_handle          Entry handle.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_first_entry_handle(pipe_sess_hdl_t sess_hdl,
                                              pipe_mat_tbl_hdl_t tbl_hdl,
                                              dev_target_t dev_tgt,
                                              int *entry_handle);

/**
 * Get next entry handles
 *
 * @param  sess_hdl              Session handle
 * @param  tbl_hdl               Table handle.
 * @param  dev_tgt               Device target.
 * @param  entry_handle          Entry handle.
 * @param  n                     Num of handles
 * @param  next_entry_handles    Next Entry handles.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_next_entry_handles(pipe_sess_hdl_t sess_hdl,
                                              pipe_mat_tbl_hdl_t tbl_hdl,
                                              dev_target_t dev_tgt,
                                              pipe_mat_ent_hdl_t entry_handle,
                                              int n,
                                              int *next_entry_handles);

/**
 * Get first group member
 *
 * @param  sess_hdl              Session handle
 * @param  tbl_hdl               Table handle.
 * @param  dev_id                Device ID.
 * @param  sel_grp_hdl           Group handle
 * @param  mbr_hdl               Pointer to the member handle
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_first_group_member(pipe_sess_hdl_t sess_hdl,
                                              pipe_tbl_hdl_t tbl_hdl,
                                              bf_dev_id_t dev_id,
                                              pipe_sel_grp_hdl_t sel_grp_hdl,
                                              pipe_adt_ent_hdl_t *mbr_hdl);

/**
 * Get next group members
 *
 * @param  sess_hdl              Session handle.
 * @param  tbl_hdl               Table handle.
 * @param  dev_id                Device ID.
 * @param  sel_grp_hdl           Group handle
 * @param  mbr_hdl               Member handle
 * @param  n                     Number of group member handles requested
 * @param  next_mbr_hdls         Array big enough to hold n member handles
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_next_group_members(
    pipe_sess_hdl_t sess_hdl,
    pipe_tbl_hdl_t tbl_hdl,
    bf_dev_id_t dev_id,
    pipe_sel_grp_hdl_t sel_grp_hdl,
    pipe_adt_ent_hdl_t mbr_hdl,
    int n,
    pipe_adt_ent_hdl_t *next_mbr_hdls);

pipe_status_t pipe_mgr_get_word_llp_active_member_count(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_sel_tbl_hdl_t tbl_hdl,
    uint32_t word_index,
    uint32_t *count);

pipe_status_t pipe_mgr_get_word_llp_active_members(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_sel_tbl_hdl_t tbl_hdl,
    uint32_t word_index,
    uint32_t count,
    pipe_adt_ent_hdl_t *mbr_hdls);

/**
 * Get entry count for the given table
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_tgt               Device target.
 * @param  tbl_hdl               Table handle.
 * @param  count                 Pointer to the entry count
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_entry_count(pipe_sess_hdl_t sess_hdl,
                                       dev_target_t dev_tgt,
                                       pipe_mat_tbl_hdl_t tbl_hdl,
                                       bool read_from_hw,
                                       uint32_t *count);

/**
 * Get member count for the given selector group
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device id.
 * @param  tbl_hdl               Selector table handle.
 * @param  grp_hdl               Selector group handle.
 * @param  count                 Pointer to the member count.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_sel_grp_mbr_count(pipe_sess_hdl_t sess_hdl,
                                             bf_dev_id_t dev_id,
                                             pipe_sel_tbl_hdl_t tbl_hdl,
                                             pipe_sel_grp_hdl_t grp_hdl,
                                             uint32_t *count);

/**
 * Get entry information
 *
 * @param  sess_hdl              Session handle
 * @param  tbl_hdl               Table handle.
 * @param  dev_id                Device ID.
 * @param  pipe_match_spec       Match spec.
 * @param  pipe_action_spec      Action data spec.
 * @param  act_fn_hdl            Action function handle.
 * @param  from_hw               Read from HW.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_entry(pipe_sess_hdl_t sess_hdl,
                                 pipe_mat_tbl_hdl_t tbl_hdl,
                                 bf_dev_id_t dev_id,
                                 pipe_mat_ent_hdl_t entry_hdl,
                                 pipe_tbl_match_spec_t *pipe_match_spec,
                                 pipe_action_spec_t *pipe_action_spec,
                                 pipe_act_fn_hdl_t *act_fn_hdl,
                                 bool from_hw);

/**
 * Get action data entry
 *
 * @param  tbl_hdl               Table handle.
 * @param  dev_id                Device ID.
 * @param  pipe_action_data_spec Action data spec.
 * @param  act_fn_hdl            Action function handle.
 * @param  from_hw               Read from HW.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_get_action_data_entry(
    pipe_adt_tbl_hdl_t tbl_hdl,
    bf_dev_id_t dev_id,
    pipe_adt_ent_hdl_t entry_hdl,
    pipe_action_data_spec_t *pipe_action_data_spec,
    pipe_act_fn_hdl_t *act_fn_hdl,
    bool from_hw);

/**
 * Set the table property
 *
 * @param  sess_hdl              Session handle.
 * @param  tbl_hdl               Table handle.
 * @param  property              Property Type.
 * @param  value                 Value.
 * @param  args                  Scope args.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_tbl_set_property(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t dev_id,
                                        pipe_mat_tbl_hdl_t tbl_hdl,
                                        pipe_mgr_tbl_prop_type_t property,
                                        pipe_mgr_tbl_prop_value_t value,
                                        pipe_mgr_tbl_prop_args_t args);

/**
 * Get the table property
 *
 * @param  sess_hdl              Session handle.
 * @param  tbl_hdl               Table handle.
 * @param  property              Property Type.
 * @param  value                 Value.
 * @param  args                  Scope args.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_tbl_get_property(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t dev_id,
                                        pipe_mat_tbl_hdl_t tbl_hdl,
                                        pipe_mgr_tbl_prop_type_t property,
                                        pipe_mgr_tbl_prop_value_t *value,
                                        pipe_mgr_tbl_prop_args_t *args);

/**
 * Get parser engine id associated with pipe, port.
 *
 * @param  dev_id                Device ID.
 * @param  port                  port with in pipe
 * @param  parser_id             Parser engine id associated with port in the
 *pipe.
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_parser_id_get(bf_dev_id_t devid,
                                     bf_dev_port_t port,
                                     pipe_parser_id_t *parser_id);

/**
 * Set property of PVS instance. This can be use to set the gress scope
 * of the pvs instance as well as the pipe and the parser scope of the
 * pvs instance within the gresses
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  property 		 PVS property which can be gress or pipe or
 * 				 parser scope
 * @param  value		 PVS property value
 * @param  args 		 PVS property args which are used to specify
 *				 the gress instance in which the pipe or
 *				 parser scope property is to be set. This
 * 				 parameter is unusued when setting gress scope
 *				 property
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_set_property(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t dev_id,
                                        pipe_pvs_hdl_t pvs_handle,
                                        pipe_mgr_pvs_prop_type_t property,
                                        pipe_mgr_pvs_prop_value_t value,
                                        pipe_mgr_pvs_prop_args_t args);

/**
 * Get property of PVS instance. This can be use to get the gress scope
 * of the pvs instance as well as the pipe and the parser scope of the
 * pvs instance within the gresses
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  property 		 PVS property which can be gress or pipe or
 * 				 parser scope
 * @param  value		 PVS property value
 * @param  args 		 PVS property args which are used to specify
 *				 the gress instance in which the pipe or
 *				 parser scope property is to be fetched from.
 * 				 This parameter is unusued when getting gress
 *				 scope property
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_get_property(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t dev_id,
                                        pipe_pvs_hdl_t pvs_handle,
                                        pipe_mgr_pvs_prop_type_t property,
                                        pipe_mgr_pvs_prop_value_t *value,
                                        pipe_mgr_pvs_prop_args_t args);

/**
 * Set/Add parser value in parser tcam
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  gress		 Gress ID or all Gress
 * @param  pipeid                Pipe ID or all Pipes.
 * @param  parser_id		 Parser ID or all Parsers
 * @param  parser_value          parser value that packet parser need to match
 *                               This value is programmed into parser ML tcam.
 * @param  parser_mask           parser mask to be applied on parser value
 * @param  pvs_entry_handle      A new entry handle is allocated for the newly
 *added pvs entry
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_entry_add(pipe_sess_hdl_t sess_hdl,
                                     bf_dev_id_t devid,
                                     pipe_pvs_hdl_t pvs_handle,
                                     pipe_mgr_pvs_gress_en gress,
                                     bf_dev_pipe_t pipeid,
                                     uint8_t parser_id,
                                     uint32_t parser_value,
                                     uint32_t parser_value_mask,
                                     pipe_pvs_hdl_t *pvs_entry_handle);

/**
 * Modify existing parser tcam entry parser value to new value.
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  pvs_entry_handle      Entry Handle allocated at the time of adding
 *pvs entry
 * @param  parser_value          parser value that packet parser need to match
 *                               This value is programmed into parser ML tcam.
 * @param  parser_mask           parser mask to be applied on parser value
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_entry_modify(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t devid,
                                        pipe_pvs_hdl_t pvs_handle,
                                        pipe_pvs_hdl_t pvs_entry_handle,
                                        uint32_t parser_value,
                                        uint32_t parser_value_mask);

/**
 * Delete parser value entry in parser tcam.
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  pvs_entry_handle      Entry Handle allocated at the time of adding
 *pvs entry
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_entry_delete(pipe_sess_hdl_t sess_hdl,
                                        bf_dev_id_t devid,
                                        pipe_pvs_hdl_t pvs_handle,
                                        pipe_pvs_hdl_t pvs_entry_handle);

/**
 * Get parser value entry in parser tcam.
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  pvs_entry_handle      Entry Handle allocated at the time of adding
 *pvs entry
 * @param parser_value           parser value return
 * @param parser_value_mask      parser value mask return
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_entry_get(pipe_sess_hdl_t sess_hdl,
                                     bf_dev_id_t devid,
                                     pipe_pvs_hdl_t pvs_handle,
                                     pipe_pvs_hdl_t pvs_entry_handle,
                                     uint32_t *parser_value,
                                     uint32_t *parser_value_mask);

/**
 * Get parser value entry in parser tcam.
 *
 * @param  sess_hdl              Session handle.
 * @param  dev_id                Device ID.
 * @param  pvs_handle            Handle that identifies PVS instance.
 * @param  gress                 Gress ID or all Gress
 * @param  pipeid                Pipe ID or all Pipes.
 * @param  parser_id             Parser ID or all Parsers
 * @param  parser_value          parser value that packet parser need to match
 *                               This value is programmed into parser ML tcam.
 * @param  parser_mask           parser mask to be applied on parser value
 * @param  pvs_entry_handle      A existing entry handle is return.
 *added pvs entry
 * @return                       Status of the API call
 */
pipe_status_t pipe_mgr_pvs_entry_handle_get(pipe_sess_hdl_t sess_hdl,
                                            bf_dev_id_t devid,
                                            pipe_pvs_hdl_t pvs_handle,
                                            pipe_mgr_pvs_gress_en gress,
                                            bf_dev_pipe_t pipeid,
                                            uint8_t parser_id,
                                            uint32_t parser_value,
                                            uint32_t parser_value_mask,
                                            pipe_pvs_hdl_t *pvs_entry_handle);

/* Hash Calculation APIs */
pipe_status_t pipe_mgr_hash_calc_input_set(pipe_sess_hdl_t sess_hdl,
                                           bf_dev_id_t dev_id,
                                           pipe_hash_calc_hdl_t handle,
                                           pipe_fld_lst_hdl_t fl_handle);

pipe_status_t pipe_mgr_hash_calc_input_get(pipe_sess_hdl_t sess_hdl,
                                           bf_dev_id_t dev_id,
                                           pipe_hash_calc_hdl_t handle,
                                           pipe_fld_lst_hdl_t *fl_handle);

pipe_status_t pipe_mgr_hash_calc_input_field_attribute_set(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t dev_id,
    pipe_hash_calc_hdl_t handle,
    pipe_fld_lst_hdl_t fl_handle,
    uint32_t attr_count,
    pipe_hash_calc_input_field_attribute_t *attr_list);

pipe_status_t pipe_mgr_hash_calc_input_field_attribute_get(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t dev_id,
    pipe_hash_calc_hdl_t handle,
    pipe_fld_lst_hdl_t fl_handle,
    uint32_t max_attr_count,
    pipe_hash_calc_input_field_attribute_t *attr_list,
    uint32_t *num_attr_filled);

pipe_status_t pipe_mgr_hash_calc_input_field_attribute_count_get(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t dev_id,
    pipe_hash_calc_hdl_t handle,
    pipe_fld_lst_hdl_t fl_handle,
    uint32_t *attr_count);

pipe_status_t pipe_mgr_hash_calc_algorithm_set(pipe_sess_hdl_t sess_hdl,
                                               bf_dev_id_t dev_id,
                                               pipe_hash_calc_hdl_t handle,
                                               pipe_hash_alg_hdl_t al_handle);

pipe_status_t pipe_mgr_hash_calc_algorithm_get(pipe_sess_hdl_t sess_hdl,
                                               bf_dev_id_t dev_id,
                                               pipe_hash_calc_hdl_t handle,
                                               pipe_hash_alg_hdl_t *al_handle);

pipe_status_t pipe_mgr_hash_calc_seed_set(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t dev_id,
                                          pipe_hash_calc_hdl_t handle,
                                          pipe_hash_seed_t seed);

pipe_status_t pipe_mgr_hash_calc_seed_get(pipe_sess_hdl_t sess_hdl,
                                          bf_dev_id_t dev_id,
                                          pipe_hash_calc_hdl_t handle,
                                          pipe_hash_seed_t *seed);

pipe_status_t pipe_mgr_hash_calc_calculate_hash_value(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t dev_id,
    pipe_hash_calc_hdl_t handle,
    uint8_t *stream,
    uint32_t stream_len,
    uint8_t *hash,
    uint32_t hash_len);

/*  ---- Table debug counter APIs start  ---- */

/**
 * The function be used to set the counter type for table
   debug counter.
 *
 * @param  dev_tgt               ASIC Device information.
 * @param  tbl_name              Table name.
 * @param  type                  Type.
 * @return                       Status of the API call
 */
pipe_status_t bf_tbl_dbg_counter_type_set(dev_target_t dev_tgt,
                                          char *tbl_name,
                                          bf_tbl_dbg_counter_type_t type);

/**
 * The function be used to get the counter value for table
   debug counter.
 *
 * @param  dev_tgt               ASIC Device information.
 * @param  tbl_name              Table name.
 * @param  type                  Type.
 * @param  value                 Value.
 * @return                       Status of the API call
 */
pipe_status_t bf_tbl_dbg_counter_get(dev_target_t dev_tgt,
                                     char *tbl_name,
                                     bf_tbl_dbg_counter_type_t *type,
                                     uint32_t *value);

/**
 * The function be used to clear the counter value for table
   debug counter.
 *
 * @param  dev_tgt               ASIC Device information.
 * @param  tbl_name              Table name.
 * @return                       Status of the API call
 */
pipe_status_t bf_tbl_dbg_counter_clear(dev_target_t dev_tgt, char *tbl_name);

/**
 * The function be used to set the debug counter type for all tables
   in a stage
 *
 * @param  dev_tgt               ASIC Device information.
 * @param  stage_id              Stage.
 * @param  type                  Counter type.
 * @return                       Status of the API call
 */
pipe_status_t bf_tbl_dbg_counter_type_stage_set(dev_target_t dev_tgt,
                                                dev_stage_t stage_id,
                                                bf_tbl_dbg_counter_type_t type);

/**
 * The function be used to get the debug counter value for all tables
   in a stage
 *
 * @param  dev_tgt               ASIC Device information.
 * @param  stage_id              Stage.
 * @param  type_arr              List of counter types.
 * @param  value_arr             List of counter values.
 * @param  tbl_name              List of table names.
 * @param  num_counters          Number of counters.
 * @return                       Status of the API call
 */
#define PIPE_MGR_TBL_NAME_LEN 200
pipe_status_t bf_tbl_dbg_counter_stage_get(
    dev_target_t dev_tgt,
    dev_stage_t stage_id,
    bf_tbl_dbg_counter_type_t *type_arr,
    uint32_t *value_arr,
    char tbl_name[][PIPE_MGR_TBL_NAME_LEN],
    int *num_counters);

/**
 * The function be used to clear the debug counter value for all tables
   in a stage
 *
 * @param  dev_tgt               ASIC Device information.
 * @param  stage_id              Stage.
 * @return                       Status of the API call
 */
pipe_status_t bf_tbl_dbg_counter_stage_clear(dev_target_t dev_tgt,
                                             dev_stage_t stage_id);

/*  ---- Table debug counter APIs end  ---- */

/*  ---- Snapshot APIs start  ---- */

typedef bf_status_t (*bf_snapshot_triggered_cb)(bf_dev_id_t dev_id,
                                                bf_dev_pipe_t pipe_id,
                                                pipe_snapshot_hdl_t hdl);
/**
 * The function be used to set the monitoring mode for snapshot
   Also, register callback function for snapshot
 *
 * @param  dev_id                ASIC device identifier
 * @param  interrupt_or_polling  True for interrupt, false for polling
 * @param  trig_cb               Callback API
 * @return                       Status of the API call
 */
bf_status_t bf_snapshot_monitoring_mode(bf_dev_id_t dev_id,
                                        bool interrupt_or_polling,
                                        bf_snapshot_triggered_cb trig_cb);

/**
 * The function be used to poll the snapshots
 * Callback is given if a snapshot has been triggered
 *
 * @param  dev_id                ASIC device identifier
 * @return                       Status of the API call
 */
bf_status_t bf_snapshot_do_polling(bf_dev_id_t dev);

/**
 * The function be used to create the snapshot
 *
 * @param  dev                ASIC device identifier
 * @param  pipe               Pipe
 * @param  start_stage        Snapshot start stage
 * @param  end_stage          Snapshot end stage
 * @param  dir                Direction (ingress/egress)
 * @param  hdl                Snapshot handle
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_create(bf_dev_id_t dev,
                               bf_dev_pipe_t pipe,
                               dev_stage_t start_stage,
                               dev_stage_t end_stage,
                               bf_snapshot_dir_t dir,
                               pipe_snapshot_hdl_t *hdl);

/**
 * The function be used to get the snapshot handle
 *
 * @param  dev                ASIC device identifier
 * @param  pipe               Pipe
 * @param  start_stage        Snapshot start stage
 * @param  end_stage          Snapshot end stage
 * @param  dir                Direction (ingress/egress)
 * @param  hdl                Snapshot handle
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_handle_get(bf_dev_id_t dev,
                                   bf_dev_pipe_t pipe,
                                   dev_stage_t start_stage,
                                   dev_stage_t end_stage,
                                   bf_snapshot_dir_t dir,
                                   pipe_snapshot_hdl_t *hdl);

/**
 * The function be used to delete the snapshot
 *
 * @param  hdl                Snapshot handle
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_delete(pipe_snapshot_hdl_t hdl);

/**
 * The function be used to set all required fields
    for capture trigger
 *
 * @param  hdl                Snapshot handle
 * @param  trig_spec          Trig Spec
 * @param  trig_mask          Trig Mask
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_capture_trigger_set(pipe_snapshot_hdl_t hdl,
                                            void *trig_spec,
                                            void *trig_mask);

/**
 * The function be used to add one snapshot capture trigger
    field to the trigger list
 *
 * @param  hdl                Snapshot handle
 * @param  field_name         Name of field
 * @param  value              Field value
 * @param  mask               Field mask
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_capture_trigger_field_add(pipe_snapshot_hdl_t hdl,
                                                  char *field_name,
                                                  uint64_t value,
                                                  uint64_t mask);

/**
 * The function be used to clear all snapshot capture trigger
   fields
 *
 * @param  hdl                Snapshot handle
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_capture_trigger_fields_clr(pipe_snapshot_hdl_t hdl);

/**
 * The function be used to get the size of the capture data that needs to
 * be allocated
 *
 * @param  hdl                Snapshot handle
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_capture_phv_fields_dict_size(pipe_snapshot_hdl_t hdl,
                                                     uint32_t *total_size,
                                                     uint32_t *per_stage_size);

/**
 * The function be used to get the snapshot capture
 *
 * @param  hdl                Snapshot handle
 * @param  pipe               Pipe
 * @param  capture            Captures for all stages in snapshot
 * @param  num_captures       Num of Captures
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_capture_get(
    pipe_snapshot_hdl_t hdl,
    bf_dev_pipe_t pipe,
    uint8_t *capture,
    bf_snapshot_capture_ctrl_info_arr_t *capture_ctrl_arr,
    int *num_captures);

/**
 * The function be used to decode the snapshot capture and get the value of a
 *field
 *
 * @param  hdl                Snapshot handle
 * @param  pipe               Pipe
 * @param  stage              Stage
 * @param  capture            Captures for all stages in snapshot
 * @param  num_captures       Num of Captures
 * @param  field_name         Name of field
 * @param  field_value        Value of field
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_capture_decode_field_value(pipe_snapshot_hdl_t hdl,
                                                   bf_dev_pipe_t pipe,
                                                   dev_stage_t stage,
                                                   uint8_t *capture,
                                                   int num_captures,
                                                   char *field_name,
                                                   uint64_t *field_value);
/**
 * The function be used to set the snapshot state
 *
 * @param  hdl                Snapshot handle
 * @param  state              Snapshot state (enable/disable)
 * @param  usec               Timeout in micro-sec
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_state_set(pipe_snapshot_hdl_t hdl,
                                  bf_snapshot_state_t state,
                                  uint32_t usec);

/**
 * The function be used to get the snapshot state
 *
 * @param  hdl                Snapshot handle
 * @param  pipe               Pipe
 * @param  state              Snapshot state (enable/disable)
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_state_get(pipe_snapshot_hdl_t hdl,
                                  bf_dev_pipe_t pipe,
                                  int *state);

/**
 * The function be used to enable the snapshot timer
 *
 * @param  hdl                Snapshot handle
 * @param  disable            timer state (enable/disable)
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_timer_enable(pipe_snapshot_hdl_t hdl, bool disable);

/**
 * The function be used to check if a field is in scope
   in a particular stage
 *
 * @param  dev                ASIC device identifier
 * @param  pipe               Pipe
 * @param  stage              Snapshot start stage
 * @param  dir                Direction (ingress/egress)
 * @param  field_name         Field name
 * @param  exists[out]        Field exists
 * @return                    Status of the API call
 */
bf_status_t bf_snapshot_field_in_scope(bf_dev_id_t dev,
                                       bf_dev_pipe_t pipe,
                                       dev_stage_t stage,
                                       bf_snapshot_dir_t dir,
                                       char *field_name,
                                       bool *exists);

/*  ---- Snapshot APIs end  ---- */

/************ IBUF, EBUF, PARB APIs **************/
/**
 * The function be used to enable buffer full notification to parser when ibuf
 * usage is above low_wm_bytes
 *
 * @param  dev_id             ASIC device identifier
 * @param  port_id            Port identifier
 * @param  low_wm_bytes       Threshold level in bytes above which notification
 *                            sent.
 * @param  hi_wm_bytes        Threshold level in bytes above which drop
 *                            occurs.
 * @return                    Status of the API call
 */
pipe_status_t bf_pipe_enable_ibuf_congestion_notif_to_parser(
    bf_dev_id_t dev_id,
    bf_dev_port_t port_id,
    uint16_t low_wm_bytes,
    uint16_t hi_wm_bytes);
/**
 * The function be used to enable buffer full notification to mac when ibuf
 * usage is above low_wm_bytes
 *
 * @param  dev_id             ASIC device identifier
 * @param  port_id            Port identifier
 * @param  low_wm_bytes       Threshold level in bytes above which notification
 *                            sent.
 * @param  hi_wm_bytes        Threshold level in bytes above which drop
 *                            occurs.
 * @return                    Status of the API call
 */
pipe_status_t bf_pipe_parb_enable_flow_control_to_mac(bf_dev_id_t dev_id,
                                                      bf_dev_port_t port_id,
                                                      uint16_t low_wm_bytes,
                                                      uint16_t hi_wm_bytes);

/**
 * The function be used to disable buffer full notification to parser
 *
 * @param  dev_id             ASIC device identifier
 * @param  port_id            Port identifier
 * @return                    Status of the API call
 */
pipe_status_t bf_pipe_disable_ibuf_congestion_notif_to_parser(
    bf_dev_id_t dev_id, bf_dev_port_t port_id);

/*
 * The function be used to disable buffer full notification to mac
 *
 * @param  dev_id             ASIC device identifier
 * @param  port_id            Port identifier
 * @return                    Status of the API call
 */
pipe_status_t bf_pipe_parb_disable_flow_control_to_mac(bf_dev_id_t dev_id,
                                                       bf_dev_port_t port_id);

/*
 * The function be used to set high priority port arbitration.
 * Setting arbitration priority high helps to avoid port starvation.
 * Recommended to use this setting only on CPU bound port.
 *
 * @param  dev_id             ASIC device identifier
 * @param  port_id            Port identifier
 * @return                    Status of the API call
 */
pipe_status_t bf_pipe_enable_port_arb_priority_high(bf_dev_id_t dev_id,
                                                    bf_dev_port_t port_id);

/*
 * The function be used to set normal priority port arbitration.
 * Recommended to use this setting on all ports expect CPU bound port.
 * Default setting arbitrates port at normal priority. Hence no need
 * to invoke this function for default behaviour.
 *
 * @param  dev_id             ASIC device identifier
 * @param  port_id            Port identifier
 * @return                    Status of the API call
 */
pipe_status_t bf_pipe_enable_port_arb_priority_normal(bf_dev_id_t dev_id,
                                                      bf_dev_port_t port_id);

/************ Hitless HA State restore APIs **************/
typedef struct adt_data_resources_ {
  pipe_res_hdl_t tbl_hdl;
  pipe_res_idx_t tbl_idx;
} adt_data_resources_t;

typedef void (*pd_ha_restore_cb_1)(pipe_sess_hdl_t sess_hdl,
                                   bf_dev_id_t dev_id,
                                   pipe_adt_tbl_hdl_t adt_tbl_hdl,
                                   pipe_act_fn_hdl_t act_hdl,
                                   pipe_sel_grp_hdl_t grp_hdl,
                                   pipe_adt_ent_hdl_t mbr_hdl,
                                   int num_resources,
                                   adt_data_resources_t *resources);

/*
 * This function is used to restore the software state at the virtual
 * device.
 */
pipe_status_t pipe_mgr_hitless_ha_restore_virtual_dev_state(
    pipe_sess_hdl_t sess_hdl,
    bf_dev_id_t dev_id,
    pipe_tbl_hdl_t tbl_hdl,
    struct pipe_plcmt_info *info,
    uint32_t *processed,
    pd_ha_restore_cb_1 cb1);

pipe_status_t pipe_set_adt_ent_hdl_in_mat_data(void *data,
                                               pipe_adt_ent_hdl_t adt_ent_hdl);

pipe_status_t pipe_set_sel_grp_hdl_in_mat_data(void *data,
                                               pipe_adt_ent_hdl_t sel_grp_hdl);

pipe_status_t pipe_set_ttl_in_mat_data(void *data, uint32_t ttl);

/* Set Tcam scrub timer in msec */
pipe_status_t pipe_mgr_tcam_scrub_timer_set(bf_dev_id_t dev,
                                            uint32_t msec_timer);
/* Get Tcam scrub timer in msec */
uint32_t pipe_mgr_tcam_scrub_timer_get(bf_dev_id_t dev);

/* Given the dev port, get the corresponding pipe id to which this port belongs
 */
pipe_status_t pipe_mgr_pipe_id_get(bf_dev_id_t dev_id,
                                   bf_dev_port_t dev_port,
                                   bf_dev_pipe_t *pipe_id);

/************ Hitless HA testing APIs ******************/
pipe_status_t pipe_mgr_enable_callbacks_for_hitless_ha(pipe_sess_hdl_t sess_hdl,
                                                       bf_dev_id_t device_id);

/*
 * This function is used to get a report of the total number of entries that
 * were added/deleted/modified after HA reconcile.
 *
 * @param  sess_hdl	        Session handle
 * @param  dev_tgt 	        Device target (device id, pipe id)
 * @param  mat_tbl_hdl          Table handle of the match table
 * @param  ha_report	        Structure containing all the entry add/delete/
 *				modify count during HA reconcile
 * @return 		        Status of the API call
 */
pipe_status_t pipe_mgr_mat_ha_reconciliation_report_get(
    pipe_sess_hdl_t sess_hdl,
    dev_target_t dev_tgt,
    pipe_mat_tbl_hdl_t mat_tbl_hdl,
    pipe_tbl_ha_reconc_report_t *ha_report);

/*
 * This function is used to get the pipe val to be Or'ed with the handle
 * from context.json
 *
 * @param  dev_id 	        Device ID
 * @param  prog_name	        Program name
 * @param  pipe_mask (out)	Pipe mask
 * @return 		        Status of the API call
 */
bf_status_t pipe_mgr_tbl_hdl_pipe_mask_get(bf_dev_id_t dev_id,
                                           const char *prog_name,
                                           uint32_t *pipe_mask);

/*
 * This function is used to get the number of active pipelines
 *
 * @param  dev_id 	        Device ID
 * @param  num_pipes (out)	Number of pipes
 * @return 		        Status of the API call
 */
pipe_status_t pipe_mgr_get_num_pipelines(bf_dev_id_t dev_id,
                                         uint32_t *num_pipes);

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _PIPE_MGR_INTF_H */
