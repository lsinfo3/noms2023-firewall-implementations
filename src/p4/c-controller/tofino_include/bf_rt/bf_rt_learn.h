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
#ifndef _BF_RT_LEARN_H
#define _BF_RT_LEARN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_common.h>
#include <bf_types/bf_types.h>
#include <pipe_mgr/pipe_mgr_intf.h>

#ifdef __cplusplus
}
#endif

typedef pipe_status_t (*bf_rt_cb_function)(const bf_rt_target_t *,
                                           const bf_rt_session_hdl *,
                                           bf_rt_learn_data_hdl **,
                                           uint32_t,
                                           bf_rt_learn_msg_hdl *const,
                                           const void *);

EXTERNC bf_status_t
bf_rt_num_learns_get(const bf_rt_info_hdl *bf_rt, int *num_learns);

EXTERNC bf_status_t
bf_rt_learns_get(const bf_rt_info_hdl *bf_rt,
                 const bf_rt_learn_hdl **bf_rt_learn_hdl_ret);

EXTERNC bf_status_t
bf_rt_learn_from_name_get(const bf_rt_info_hdl *bf_rt,
                          const char *learn_name,
                          const bf_rt_learn_hdl **bf_rt_learn_hdl_ret);

EXTERNC bf_status_t
bf_rt_learn_from_id_get(const bf_rt_info_hdl *bf_rt,
                        bf_rt_id_t id,
                        const bf_rt_learn_hdl **bf_rt_learn_hdl_ret);

EXTERNC bf_status_t bf_rt_learn_name_to_id(const bf_rt_info_hdl *bf_rt,
                                           const char *learn_name,
                                           bf_rt_id_t *id_ret);

// learn obj apis

EXTERNC bf_status_t
bf_rt_learn_callback_register(const bf_rt_learn_hdl *learn,
                              const bf_rt_session_hdl *session,
                              const bf_rt_target_t *dev_tgt,
                              const bf_rt_cb_function callback_fn,
                              const void *cookie);

EXTERNC bf_status_t
bf_rt_learn_callback_deregister(const bf_rt_learn_hdl *learn,
                                const bf_rt_session_hdl *session,
                                const bf_rt_target_t *dev_tgt);

EXTERNC bf_status_t
bf_rt_learn_notify_ack(const bf_rt_learn_hdl *learn,
                       const bf_rt_session_hdl *session,
                       bf_rt_learn_msg_hdl *const learn_msg_hdl);

EXTERNC bf_status_t
bf_rt_learn_id_get(const bf_rt_learn_hdl *learn, bf_rt_id_t *learn_id);

EXTERNC bf_status_t
bf_rt_learn_name_get(const bf_rt_learn_hdl *learn, const char **learn_name_ret);

EXTERNC bf_status_t
bf_rt_learn_field_id_list_size_get(const bf_rt_learn_hdl *learn, uint32_t *num);

EXTERNC bf_status_t bf_rt_learn_field_id_list_get(const bf_rt_learn_hdl *learn,
                                                  bf_rt_id_t *field_id_list);

EXTERNC bf_status_t bf_rt_learn_field_id_get(const bf_rt_learn_hdl *learn,
                                             char *name,
                                             bf_rt_id_t *field_id);

EXTERNC bf_status_t bf_rt_learn_field_size_get(const bf_rt_learn_hdl *learn,
                                               const bf_rt_id_t field_id,
                                               size_t *size);

EXTERNC bf_status_t bf_rt_learn_field_is_ptr_get(const bf_rt_learn_hdl *learn,
                                                 const bf_rt_id_t field_id,
                                                 bool *is_ptr);

EXTERNC bf_status_t bf_rt_learn_field_name_get(const bf_rt_learn_hdl *learn,
                                               const bf_rt_id_t field_id,
                                               const char **field_name_ret);

#endif  // _BF_RT_LEARN_H
