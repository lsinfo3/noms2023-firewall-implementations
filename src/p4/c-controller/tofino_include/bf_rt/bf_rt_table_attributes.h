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
#ifndef _BF_RT_TABLE_ATTRIBUTES_H
#define _BF_RT_TABLE_ATTRIBUTES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_common.h>
#include <bf_types/bf_types.h>

#ifdef __cplusplus
}
#endif

typedef enum attributes_idle_table_mode {
  BFRT_POLL_MODE,
  BFRT_NOTIFY_MODE
} bf_rt_attributes_idle_table_mode_t;

// not used for now. TODO: refactor entry scope APIs
typedef enum table_entry_scope {
  ENTRY_SCOPE_ALL_PIPELINES = 0,
  ENTRY_SCOPE_SINGLE_PIPELINE = 1,
  ENTRY_SCOPE_USER_DEFINED = 2  // this mode is not used in C API for now
} bf_rt_table_entry_scope_t;

typedef bf_status_t (*bf_rt_idle_tmo_expiry_cb)(bf_rt_target_t *,
                                                bf_rt_table_key_hdl *,
                                                void *);

typedef bf_status_t (*bf_rt_port_status_chg_cb)(bf_rt_target_t *,
                                                bf_rt_table_key_hdl *,
                                                bool *,
                                                void *);

typedef void (*bf_rt_selector_table_update_cb)(const bf_rt_session_hdl *session,
                                               const bf_rt_target_t *target,
                                               const void *cookie,
                                               const bf_rt_id_t sel_grp_id,
                                               const bf_rt_id_t act_mbr_id,
                                               const int logical_table_index,
                                               const bool is_add);

EXTERNC bf_status_t
bf_rt_attributes_idle_table_poll_mode_set(bf_rt_table_attributes_hdl *tbl_attr,
                                          const bool enable);

EXTERNC bf_status_t bf_rt_attributes_entry_scope_symmetric_mode_set(
    bf_rt_table_attributes_hdl *tbl_attr, const bool symmetric_mode);

EXTERNC bf_status_t bf_rt_attributes_entry_scope_symmetric_mode_get(
    bf_rt_table_attributes_hdl *tbl_attr, bool *is_symmetric_mode);

EXTERNC bf_status_t bf_rt_attributes_idle_table_notify_mode_set(
    bf_rt_table_attributes_hdl *tbl_attr,
    const bool enable,
    const bf_rt_idle_tmo_expiry_cb callback,
    const uint32_t ttl_query_interval,
    const uint32_t max_ttl,
    const uint32_t min_ttl,
    const void *cookie);

EXTERNC bf_status_t
bf_rt_attributes_port_status_notify_set(bf_rt_table_attributes_hdl *tbl_attr,
                                        const bool enable,
                                        const bf_rt_port_status_chg_cb callback,
                                        const void *cookie);

EXTERNC bf_status_t bf_rt_attributes_port_status_notify_get(
    const bf_rt_table_attributes_hdl *tbl_attr,
    bool *enable,
    bf_rt_port_status_chg_cb *callback,
    void **cookie);

EXTERNC bf_status_t
bf_rt_attributes_idle_table_get(const bf_rt_table_attributes_hdl *tbl_attr,
                                bf_rt_attributes_idle_table_mode_t *mode,
                                bool *enable,
                                bf_rt_idle_tmo_expiry_cb *callback,
                                uint32_t *ttl_query_interval,
                                uint32_t *max_ttl,
                                uint32_t *min_ttl,
                                void **cookie);

EXTERNC bf_status_t bf_rt_attributes_selector_table_update_cb_set(
    bf_rt_table_attributes_hdl *tbl_attr,
    const bool enable,
    const bf_rt_session_hdl *session,
    const bf_rt_selector_table_update_cb callback,
    const void *cookie);

EXTERNC bf_status_t bf_rt_attributes_selector_table_update_cb_get(
    const bf_rt_table_attributes_hdl *tbl_attr,
    bool *enable,
    bf_rt_session_hdl **session,
    bf_rt_selector_table_update_cb *callback,
    void **cookie);

#endif  // _BF_RT_TABLE_ATTRIBUTES_H
