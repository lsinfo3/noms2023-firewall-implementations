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
#ifndef _BF_RT_SESSION_H
#define _BF_RT_SESSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_session.h>
#include <bf_rt/bf_rt_common.h>
#include <bf_types/bf_types.h>

#ifdef __cplusplus
}
#endif

EXTERNC bf_status_t bf_rt_session_create(bf_rt_session_hdl **session);

EXTERNC bf_status_t bf_rt_session_destroy(bf_rt_session_hdl *const session);

EXTERNC bf_rt_id_t
bf_rt_sess_handle_get(const bf_rt_session_hdl *const session);

EXTERNC bf_rt_id_t
bf_rt_pre_sess_handle_get(const bf_rt_session_hdl *const session);

EXTERNC bool bf_rt_session_is_valid(const bf_rt_session_hdl *const session);

EXTERNC bf_status_t
bf_rt_session_complete_operations(const bf_rt_session_hdl *const session);

// Batching functions
EXTERNC bf_status_t bf_rt_begin_batch(bf_rt_session_hdl *const session);

EXTERNC bf_status_t bf_rt_flush_batch(bf_rt_session_hdl *const session);

EXTERNC bf_status_t
bf_rt_end_batch(bf_rt_session_hdl *const session, bool hwSynchronous);

// Transaction functions
EXTERNC bf_status_t
bf_rt_begin_transaction(bf_rt_session_hdl *const session, bool isAtomic);

EXTERNC bf_status_t bf_rt_verify_transaction(bf_rt_session_hdl *const session);

EXTERNC bf_status_t
bf_rt_commit_transaction(bf_rt_session_hdl *const session, bool hwSynchronous);

EXTERNC bf_status_t bf_rt_abort_transaction(bf_rt_session_hdl *const session);

#endif  // _BF_RT_SESSION_H
