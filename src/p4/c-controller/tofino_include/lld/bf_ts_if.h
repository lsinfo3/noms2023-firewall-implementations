
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
 *  @file bf_ts_if.h
 *  @date
 *
 */

#ifndef __BF_TS_IF_H_
#define __BF_TS_IF_H_

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

#define TS_MBC_MBUS_REG_OFFSET(reg) \
  (offsetof(Tofino, device_select.mbc.mbc_mbus.reg))

bf_status_t bf_ts_global_ts_state_set(bf_dev_id_t dev_id, bool enable);
bf_status_t bf_ts_global_ts_value_set(bf_dev_id_t dev_id,
                                      uint64_t global_ts_ns);

bf_status_t bf_ts_global_ts_increment_one_time_set(
    bf_dev_id_t dev_id, uint64_t global_ts_inc_time_ns);
bf_status_t bf_ts_global_ts_offset_set(bf_dev_id_t dev_id,
                                       uint64_t global_ts_offset_ns);
bf_status_t bf_ts_global_baresync_ts_get(bf_dev_id_t dev_id,
                                         uint64_t *global_ts_ns,
                                         uint64_t *baresync_ts_ns);
bf_status_t bf_ts_global_ts_periodic_distribution_timer_set(bf_dev_id_t dev_id,
                                                            uint32_t timer_ns);
bf_status_t bf_ts_baresync_state_set(bf_dev_id_t dev_id,
                                     uint32_t reset_count_threshold,
                                     uint32_t debounce_count,
                                     bool enable);
bf_status_t bf_ts_baresync_reset_value_set(bf_dev_id_t dev_id,
                                           uint64_t baresync_time_ns);
bf_status_t bf_ts_baresync_increment_set(bf_dev_id_t dev_id,
                                         uint32_t baresync_inc_time_ns,
                                         uint32_t baresync_inc_time_fract_ns);

#ifdef __cplusplus
}
#endif /* C++ */

#endif
