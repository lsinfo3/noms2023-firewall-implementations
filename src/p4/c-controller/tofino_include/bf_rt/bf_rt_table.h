/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2017-2018 Barefoot Networks, Inc.

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
#ifndef _BF_RT_TABLE_H
#define _BF_RT_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_common.h>
#include <bf_rt/bf_rt_table_attributes.h>
#include <bf_rt/bf_rt_table_operations.h>
#include <bf_types/bf_types.h>

#ifdef __cplusplus
}
#endif

typedef enum bf_rt_key_field_type_ {
  INVALID = 0,
  EXACT = 1,
  TERNARY = 2,
  RANGE = 3,
  LPM = 4,
} bf_rt_key_field_type_t;

typedef enum bf_rt_data_field_type_ {
  INT_ARR = 0,
  BOOL_ARR = 1,
  UINT64 = 2,
  BYTE_STREAM = 3,
  FLOAT = 4,
  CONTAINER = 5,
  STRING = 6,
  BOOL = 7,
} bf_rt_data_type_t;

typedef struct bf_rt_annotation_ {
  const char *name;
  const char *value;
} bf_rt_annotation_t;

typedef enum bf_rt_entry_read_flag_ {
  ENTRY_READ_FROM_SW = 0,
  ENTRY_READ_FOM_HW = 1
} bf_rt_entry_read_flag_e;

typedef enum bf_rt_entry_mod_inc_flag_ {
  MOD_INC_ADD = 0,   /** Flag to add the given data incrementally to the
                         existing table entry */
  MOD_INC_DELETE = 1 /** Flag to delete the given data from the
                         existing table entry */
} bf_rt_entry_mod_inc_flag_e;

typedef enum bf_rt_table_type_ {
  MATCH_DIRECT = 0,            /** Match action table*/
  MATCH_INDIRECT = 1,          /** Match action table with actions of the
                                  table implemented using an
                                  "ActionProfile" */
  MATCH_INDIRECT_SELECTOR = 2, /** Match action table with actions of the
                                  table implemented using an
                                  "ActionSelector"*/
  ACTION_PROFILE = 3,          /** Action Profile table*/
  SELECTOR = 4,                /** Action Selector table*/
  COUNTER = 5,                 /** Counter table*/
  METER = 6,                   /** Meter table*/
  REGISTER = 7,                /** Register table*/
  LPF = 8,                     /** LPF table*/
  WRED = 9,                    /** WRED table*/
  PVS = 10, /** Parser Value Set table. This table contains only Keys and no
              Data*/
  PORT_METADATA = 11, /** Port Metadata table.*/
  DYN_HASH_CFG = 12,  /** Dynamic Hashing configuration table*/
  PORT_CFG = 15,      /** Port Configuration */
  PORT_STAT = 16,     /** Port Stats */
  PORT_HDL_INFO = 17, /** Port Hdl to Dev_port Conversion table */
  PORT_FRONT_PANEL_IDX_INFO =
      18,                    /** Front panel Idx to Dev_port Conversion table */
  PORT_STR_INFO = 19,        /** Port Str to Dev_port Conversion table */
  PKTGEN_PORT_CFG = 20,      /** Pktgen Port Configuration table */
  PKTGEN_APP_CFG = 21,       /** Pktgen Application Configuration table */
  PKTGEN_PKT_BUFF_CFG = 22,  /** Pktgen Packet Buffer Configuration table */
  PKTGEN_PORT_MASK_CFG = 23, /** Pktgen Port Mask Configuration table */
  PKTGEN_PORT_DOWN_REPLAY_CFG =
      24,         /** Pktgen Port Down Replay Configuration table*/
  PRE_MGID = 25,  /** PRE MGID table */
  PRE_NODE = 26,  /** PRE Node table */
  PRE_ECMP = 27,  /** PRE ECMP table */
  PRE_LAG = 28,   /** PRE LAG table */
  PRE_PRUNE = 29, /** PRE Prune (L2 XID) table */
  INVLD = 30,
} bf_rt_table_type_t;

typedef enum bf_rt_table_attributes_type_ {
  ENTRY_SCOPE = 0,
  DYNAMIC_KEY_MASK = 1,
  IDLE_TABLE_RUNTIME = 2,
  DYNAMIC_HASH_ALG_SEED = 3,
  METER_BYTE_COUNT_ADJ = 4,
  PORT_STATUS_NOTIF = 5,
  PORT_STAT_POLL_INTVL_MS = 6
} bf_rt_table_attributes_type_t;

typedef enum bf_rt_table_operations_type_ {
  COUNTER_SYNC = 0,
  REGISTER_SYNC = 1,
  HIT_STATUS_UPDATE = 2,
  INVALID_OPERATION = 3
} bf_rt_table_operations_type_t;

EXTERNC bf_status_t
bf_rt_info_create(const char *bf_rt_info_path,
                  const char *context_json_path,
                  const bf_rt_info_hdl **bf_rt_info_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_from_name_get(const bf_rt_info_hdl *bf_rt,
                          const char *table_name,
                          const bf_rt_table_hdl **bf_rt_table_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_from_id_get(const bf_rt_info_hdl *bf_rt,
                        bf_rt_id_t id,
                        const bf_rt_table_hdl **bf_rt_table_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_id_from_handle_get(const bf_rt_table_hdl *table_hdl,
                               bf_rt_id_t *id);

EXTERNC bf_status_t
bf_rt_num_tables_get(const bf_rt_info_hdl *bf_rt, int *num_tables);

EXTERNC bf_status_t
bf_rt_tables_get(const bf_rt_info_hdl *bf_rt,
                 const bf_rt_table_hdl **bf_rt_table_hdl_ret);

EXTERNC bf_status_t bf_rt_table_name_to_id(const bf_rt_info_hdl *bf_rt,
                                           const char *table_name,
                                           bf_rt_id_t *id_ret);

//// Table Object APIs
// Table APIs
EXTERNC bf_status_t bf_rt_table_name_get(const bf_rt_table_hdl *table_hdl,
                                         const char **table_name_ret);

EXTERNC bf_status_t bf_rt_table_entry_add(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_session_hdl *session,
                                          const bf_rt_target_t *dev_tgt,
                                          const bf_rt_table_key_hdl *key,
                                          const bf_rt_table_data_hdl *data);

EXTERNC bf_status_t bf_rt_table_entry_mod(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_session_hdl *session,
                                          const bf_rt_target_t *dev_tgt,
                                          const bf_rt_table_key_hdl *key,
                                          const bf_rt_table_data_hdl *data);

EXTERNC bf_status_t
bf_rt_table_entry_mod_inc(const bf_rt_table_hdl *table_hdl,
                          const bf_rt_session_hdl *session,
                          const bf_rt_target_t *dev_tgt,
                          const bf_rt_table_key_hdl *key,
                          const bf_rt_table_data_hdl *data,
                          const bf_rt_entry_mod_inc_flag_e flag);

EXTERNC bf_status_t bf_rt_table_entry_del(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_session_hdl *session,
                                          const bf_rt_target_t *dev_tgt,
                                          const bf_rt_table_key_hdl *key);

EXTERNC bf_status_t bf_rt_table_entry_get(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_session_hdl *session,
                                          const bf_rt_target_t *dev_tgt,
                                          const bf_rt_table_key_hdl *key,
                                          bf_rt_table_data_hdl *data,
                                          bf_rt_entry_read_flag_e flag);

EXTERNC bf_status_t
bf_rt_table_entry_get_first(const bf_rt_table_hdl *table_hdl,
                            const bf_rt_session_hdl *session,
                            const bf_rt_target_t *dev_tgt,
                            bf_rt_table_key_hdl *key,
                            bf_rt_table_data_hdl *data,
                            bf_rt_entry_read_flag_e flag);

EXTERNC bf_status_t
bf_rt_table_entry_get_next_n(const bf_rt_table_hdl *table_hdl,
                             const bf_rt_session_hdl *session,
                             const bf_rt_target_t *dev_tgt,
                             const bf_rt_table_key_hdl *key,
                             bf_rt_table_key_hdl **output_keys,
                             bf_rt_table_data_hdl **output_data,
                             uint32_t n,
                             uint32_t *num_returned,
                             bf_rt_entry_read_flag_e flag);

EXTERNC bf_status_t bf_rt_table_type_get(const bf_rt_table_hdl *table_hdl,
                                         bf_rt_table_type_t *table_type);

EXTERNC bf_status_t bf_rt_table_usage_get(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_session_hdl *session,
                                          const bf_rt_target_t *dev_tgt,
                                          uint32_t *count,
                                          bf_rt_entry_read_flag_e flag);

EXTERNC bf_status_t
bf_rt_table_has_const_default_action(const bf_rt_table_hdl *table_hdl,
                                     bool *has_const_default_action);

EXTERNC bf_status_t
bf_rt_table_num_annotations_get(const bf_rt_table_hdl *table_hdl,
                                uint32_t *num_annotations);
EXTERNC bf_status_t
bf_rt_table_annotations_get(const bf_rt_table_hdl *table_hdl,
                            bf_rt_annotation_t *annotations_c);
EXTERNC bf_status_t
bf_rt_table_size_get(const bf_rt_table_hdl *table_hdl, size_t *count);

EXTERNC bf_status_t
bf_rt_table_default_entry_set(const bf_rt_table_hdl *table_hdl,
                              const bf_rt_session_hdl *session,
                              const bf_rt_target_t *dev_tgt,
                              const bf_rt_table_data_hdl *data);

EXTERNC
bf_status_t bf_rt_table_default_entry_get(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_session_hdl *session,
                                          const bf_rt_target_t *dev_tgt,
                                          bf_rt_table_data_hdl *data,
                                          const bf_rt_entry_read_flag_e flag);

EXTERNC
bf_status_t bf_rt_table_default_entry_reset(const bf_rt_table_hdl *table_hdl,
                                            const bf_rt_session_hdl *session,
                                            const bf_rt_target_t *dev_tgt);

// Allocate APIs
EXTERNC bf_status_t bf_rt_table_key_allocate(const bf_rt_table_hdl *table_hdl,
                                             bf_rt_table_key_hdl **key_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_data_allocate(const bf_rt_table_hdl *table_hdl,
                          bf_rt_table_data_hdl **data_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_action_data_allocate(const bf_rt_table_hdl *table_hdl,
                                 const bf_rt_id_t action_id,
                                 bf_rt_table_data_hdl **data_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_data_allocate_with_fields(const bf_rt_table_hdl *table_hdl,
                                      const bf_rt_id_t *fields,
                                      const uint32_t num_array,
                                      bf_rt_table_data_hdl **data_hdl_ret);

EXTERNC bf_status_t bf_rt_table_action_data_allocate_with_fields(
    const bf_rt_table_hdl *table_hdl,
    const bf_rt_id_t action_id,
    const bf_rt_id_t *fields,
    const uint32_t num_array,
    bf_rt_table_data_hdl **data_hdl_ret);

EXTERNC bf_status_t bf_rt_table_entry_scope_attributes_allocate(
    const bf_rt_table_hdl *table_hdl,
    bf_rt_table_attributes_hdl **tbl_attr_hdl_ret);

EXTERNC bf_status_t bf_rt_table_idle_table_attributes_allocate(
    const bf_rt_table_hdl *table_hdl,
    const bf_rt_attributes_idle_table_mode_t idle_mode,
    bf_rt_table_attributes_hdl **tbl_attr_hdl_ret);

EXTERNC bf_status_t
bf_rt_table_operations_allocate(const bf_rt_table_hdl *table_hdl,
                                const bf_rt_table_operations_mode_t op_type,
                                bf_rt_table_operations_hdl **tbl_ops);

// De-allocate APIs
EXTERNC bf_status_t bf_rt_table_key_deallocate(bf_rt_table_key_hdl *key_hdl);

EXTERNC bf_status_t bf_rt_table_data_deallocate(bf_rt_table_data_hdl *data_hdl);

EXTERNC bf_status_t
bf_rt_table_attributes_deallocate(bf_rt_table_attributes_hdl *tbl_attr_hdl);

EXTERNC bf_status_t
bf_rt_table_operations_deallocate(bf_rt_table_operations_hdl *tbl_op_hdl);

// KeyField APIs
EXTERNC bf_status_t
bf_rt_key_field_id_list_size_get(const bf_rt_table_hdl *table_hdl,
                                 uint32_t *num);

EXTERNC bf_status_t
bf_rt_key_field_id_list_get(const bf_rt_table_hdl *table_hdl,
                            bf_rt_id_t *id_vec_ret);

EXTERNC bf_status_t
bf_rt_key_field_type_get(const bf_rt_table_hdl *table_hdl,
                         const bf_rt_id_t field_id,
                         bf_rt_key_field_type_t *field_type_ret);

EXTERNC bf_status_t
bf_rt_key_field_data_type_get(const bf_rt_table_hdl *table_hdl,
                              const bf_rt_id_t field_id,
                              bf_rt_data_type_t *field_type_ret);

EXTERNC bf_status_t bf_rt_key_field_id_get(const bf_rt_table_hdl *table_hdl,
                                           const char *key_field_name,
                                           bf_rt_id_t *field_id_ret);

EXTERNC bf_status_t bf_rt_key_field_size_get(const bf_rt_table_hdl *table_hdl,
                                             const bf_rt_id_t field_id,
                                             size_t *field_size_ret);

EXTERNC bf_status_t bf_rt_key_field_is_ptr_get(const bf_rt_table_hdl *table_hdl,
                                               const bf_rt_id_t field_id,
                                               bool *is_ptr_ret);

EXTERNC bf_status_t bf_rt_key_field_name_get(const bf_rt_table_hdl *table_hdl,
                                             const bf_rt_id_t field_id,
                                             const char **name_ret);

EXTERNC bf_status_t
bf_rt_key_field_num_allowed_choices_get(const bf_rt_table_hdl *table_hdl,
                                        const bf_rt_id_t field_id,
                                        uint32_t *num_choices);

EXTERNC bf_status_t
bf_rt_key_field_allowed_choices_get(const bf_rt_table_hdl *table_hdl,
                                    const bf_rt_id_t field_id,
                                    const char *choices[]);

// DataField APIs
EXTERNC bf_status_t
bf_rt_data_field_id_list_size_get(const bf_rt_table_hdl *table_hdl,
                                  uint32_t *num);
EXTERNC bf_status_t
bf_rt_data_field_id_list_size_with_action_get(const bf_rt_table_hdl *table_hdl,
                                              const bf_rt_id_t action_id,
                                              uint32_t *num);

EXTERNC bf_status_t bf_rt_data_field_list_get(const bf_rt_table_hdl *table_hdl,
                                              bf_rt_id_t *id_vec_ret);

EXTERNC bf_status_t
bf_rt_container_data_field_list_get(const bf_rt_table_hdl *table_hdl,
                                    bf_rt_id_t container_field_id,
                                    bf_rt_id_t *id_vec_ret);

EXTERNC bf_status_t
bf_rt_container_data_field_list_size_get(const bf_rt_table_hdl *table_hdl,
                                         bf_rt_id_t container_field_id,
                                         size_t *field_list_size_ret);

EXTERNC bf_status_t
bf_rt_data_field_list_with_action_get(const bf_rt_table_hdl *table_hdl,
                                      const bf_rt_id_t action_id,
                                      bf_rt_id_t *id_vec_ret);

EXTERNC bf_status_t bf_rt_data_field_id_get(const bf_rt_table_hdl *table_hdl,
                                            const char *data_field_name,
                                            bf_rt_id_t *field_id_ret);
EXTERNC bf_status_t
bf_rt_data_field_id_with_action_get(const bf_rt_table_hdl *table_hdl,
                                    const char *data_field_name,
                                    const bf_rt_id_t action_id,
                                    bf_rt_id_t *field_id_ret);

EXTERNC bf_status_t bf_rt_data_field_size_get(const bf_rt_table_hdl *table_hdl,
                                              const bf_rt_id_t field_id,
                                              size_t *field_size_ret);
EXTERNC bf_status_t
bf_rt_data_field_size_with_action_get(const bf_rt_table_hdl *table_hdl,
                                      const bf_rt_id_t field_id,
                                      const bf_rt_id_t action_id,
                                      size_t *field_size_ret);

EXTERNC bf_status_t
bf_rt_data_field_is_ptr_get(const bf_rt_table_hdl *table_hdl,
                            const bf_rt_id_t field_id,
                            bool *is_ptr_ret);
EXTERNC bf_status_t
bf_rt_data_field_is_ptr_with_action_get(const bf_rt_table_hdl *table_hdl,
                                        const bf_rt_id_t field_id,
                                        const bf_rt_id_t action_id,
                                        bool *is_ptr_ret);

EXTERNC bf_status_t
bf_rt_data_field_is_mandatory_get(const bf_rt_table_hdl *table_hdl,
                                  const bf_rt_id_t field_id,
                                  bool *is_mandatory_ret);

EXTERNC bf_status_t
bf_rt_data_field_is_mandatory_with_action_get(const bf_rt_table_hdl *table_hdl,
                                              const bf_rt_id_t field_id,
                                              const bf_rt_id_t action_id,
                                              bool *is_mandatory_ret);

EXTERNC bf_status_t
bf_rt_data_field_is_read_only_get(const bf_rt_table_hdl *table_hdl,
                                  const bf_rt_id_t field_id,
                                  bool *is_read_only_ret);

EXTERNC bf_status_t
bf_rt_data_field_is_read_only_with_action_get(const bf_rt_table_hdl *table_hdl,
                                              const bf_rt_id_t field_id,
                                              const bf_rt_id_t action_id,
                                              bool *is_read_only_ret);

EXTERNC bf_status_t bf_rt_data_field_name_get(const bf_rt_table_hdl *table_hdl,
                                              const bf_rt_id_t field_id,
                                              const char **name_ret);
EXTERNC bf_status_t
bf_rt_data_field_name_with_action_get(const bf_rt_table_hdl *table_hdl,
                                      const bf_rt_id_t field_id,
                                      const bf_rt_id_t action_id,
                                      const char **name_ret);

EXTERNC bf_status_t
bf_rt_data_field_type_get(const bf_rt_table_hdl *table_hdl,
                          const bf_rt_id_t field_id,
                          bf_rt_data_type_t *field_type_ret);

EXTERNC bf_status_t
bf_rt_data_field_type_with_action_get(const bf_rt_table_hdl *table_hdl,
                                      const bf_rt_id_t field_id,
                                      const bf_rt_id_t action_id,
                                      bf_rt_data_type_t *field_type_ret);

EXTERNC bf_status_t
bf_rt_data_field_num_allowed_choices_get(const bf_rt_table_hdl *table_hdl,
                                         const bf_rt_id_t field_id,
                                         uint32_t *num_choices);

EXTERNC bf_status_t
bf_rt_data_field_allowed_choices_get(const bf_rt_table_hdl *table_hdl,
                                     const bf_rt_id_t field_id,
                                     const char *choices[]);

EXTERNC bf_status_t bf_rt_data_field_num_allowed_choices_with_action_get(
    const bf_rt_table_hdl *table_hdl,
    const bf_rt_id_t field_id,
    const bf_rt_id_t action_id,
    uint32_t *num_choices);

EXTERNC bf_status_t bf_rt_data_field_allowed_choices_with_action_get(
    const bf_rt_table_hdl *table_hdl,
    const bf_rt_id_t field_id,
    const bf_rt_id_t action_id,
    const char *choices[]);

EXTERNC bf_status_t
bf_rt_data_field_num_annotations_get(const bf_rt_table_hdl *table_hdl,
                                     const bf_rt_id_t field_id,
                                     uint32_t *num_annotations);
EXTERNC bf_status_t
bf_rt_data_field_annotations_get(const bf_rt_table_hdl *table_hdl,
                                 const bf_rt_id_t field_id,
                                 bf_rt_annotation_t *annotations_c);
EXTERNC bf_status_t bf_rt_data_field_num_annotations_with_action_get(
    const bf_rt_table_hdl *table_hdl,
    const bf_rt_id_t field_id,
    const bf_rt_id_t action_id,
    uint32_t *num_annotations);
EXTERNC bf_status_t
bf_rt_data_field_annotations_with_action_get(const bf_rt_table_hdl *table_hdl,
                                             const bf_rt_id_t field_id,
                                             const bf_rt_id_t action_id,
                                             bf_rt_annotation_t *annotations_c);

// Action APIs
EXTERNC bf_status_t
bf_rt_action_id_list_size_get(const bf_rt_table_hdl *table_hdl, uint32_t *num);

EXTERNC bf_status_t bf_rt_action_id_list_get(const bf_rt_table_hdl *table_hdl,
                                             bf_rt_id_t *id_vec_ret);

EXTERNC bf_status_t bf_rt_action_name_get(const bf_rt_table_hdl *table_hdl,
                                          const bf_rt_id_t action_id,
                                          const char **name_ret);

EXTERNC bf_status_t bf_rt_action_name_to_id(const bf_rt_table_hdl *table_hdl,
                                            const char *action_name,
                                            bf_rt_id_t *action_id_ret);

EXTERNC bf_status_t
bf_rt_action_id_applicable(const bf_rt_table_hdl *table_hdl, bool *ret_val);

EXTERNC bf_status_t
bf_rt_action_num_annotations_get(const bf_rt_table_hdl *table_hdl,
                                 const bf_rt_id_t action_id,
                                 uint32_t *num_annotations);
EXTERNC bf_status_t
bf_rt_action_annotations_get(const bf_rt_table_hdl *table_hdl,
                             const bf_rt_id_t action_id,
                             bf_rt_annotation_t *annotations_c);

// Attribute APIs
EXTERNC bf_status_t
bf_rt_table_attributes_set(const bf_rt_table_hdl *table_hdl,
                           const bf_rt_session_hdl *session,
                           const bf_rt_target_t *dev_tgt,
                           const bf_rt_table_attributes_hdl *tbl_attr);

EXTERNC bf_status_t
bf_rt_table_attributes_get(const bf_rt_table_hdl *table_hdl,
                           const bf_rt_session_hdl *session,
                           const bf_rt_target_t *dev_tgt,
                           bf_rt_table_attributes_hdl *tbl_attr);

EXTERNC bf_status_t
bf_rt_table_num_attributes_supported(const bf_rt_table_hdl *table_hdl,
                                     uint32_t *num_attributes);

EXTERNC bf_status_t
bf_rt_table_attributes_supported(const bf_rt_table_hdl *table_hdl,
                                 bf_rt_table_attributes_type_t *attributes,
                                 uint32_t *num_returned);

// Operations APIs
EXTERNC bf_status_t
bf_rt_table_operations_execute(const bf_rt_table_hdl *table_hdl,
                               const bf_rt_table_operations_hdl *tbl_ops);

EXTERNC bf_status_t
bf_rt_table_num_operations_supported(const bf_rt_table_hdl *table_hdl,
                                     uint32_t *num_operations);

EXTERNC bf_status_t
bf_rt_table_operations_supported(const bf_rt_table_hdl *table_hdl,
                                 bf_rt_table_operations_type_t *operations,
                                 uint32_t *num_returned);

#endif  //_BF_RT_TABLE_H
