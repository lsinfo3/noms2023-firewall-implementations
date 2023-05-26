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
#ifndef _BF_RT_TABLE_OPERATIONS_H
#define _BF_RT_TABLE_OPERATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_common.h>
#include <bf_types/bf_types.h>

#ifdef __cplusplus
}
#endif

typedef enum table_operations_mode {
  BFRT_COUNTER_SYNC = 0,
  BFRT_REGISTER_SYNC = 1,
  BFRT_HIT_STATUS_UPDATE = 2,
  BFRT_INVALID
} bf_rt_table_operations_mode_t;

typedef void (*bf_rt_register_sync_cb)(bf_rt_target_t *, void *);

typedef void (*bf_rt_counter_sync_cb)(bf_rt_target_t *, void *);

typedef void (*bf_rt_hit_state_update_cb)(bf_rt_target_t *, void *);

EXTERNC bf_status_t
bf_rt_operations_register_sync_set(bf_rt_table_operations_hdl *tbl_ops,
                                   const bf_rt_session_hdl *session,
                                   const bf_rt_target_t *dev_tgt,
                                   const bf_rt_register_sync_cb callback,
                                   const void *cookie);

EXTERNC bf_status_t
bf_rt_operations_counter_sync_set(bf_rt_table_operations_hdl *tbl_ops,
                                  const bf_rt_session_hdl *session,
                                  const bf_rt_target_t *dev_tgt,
                                  const bf_rt_counter_sync_cb callback,
                                  const void *cookie);

EXTERNC bf_status_t
bf_rt_operations_hit_state_update_set(bf_rt_table_operations_hdl *tbl_ops,
                                      const bf_rt_session_hdl *session,
                                      const bf_rt_target_t *dev_tgt,
                                      const bf_rt_hit_state_update_cb callback,
                                      const void *cookie);

#endif  // _BF_RT_TABLE_OPERATIONS_H
