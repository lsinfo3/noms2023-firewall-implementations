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
 * $Id: $ *
 ******************************************************************************/
#ifndef _BF_RT_TABLE_KEY_H
#define _BF_RT_TABLE_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_table_key.h>
#include <bf_rt/bf_rt_common.h>

#ifdef __cplusplus
}
#endif

/** Set */
/* Exact */
EXTERNC bf_status_t bf_rt_key_field_set_value(bf_rt_table_key_hdl *key_hdl,
                                              const bf_rt_id_t field_id,
                                              uint64_t value);

EXTERNC bf_status_t bf_rt_key_field_set_value_ptr(bf_rt_table_key_hdl *key_hdl,
                                                  const bf_rt_id_t field_id,
                                                  const uint8_t *value,
                                                  const size_t size);

EXTERNC bf_status_t
bf_rt_key_field_set_value_string(bf_rt_table_key_hdl *key_hdl,
                                 const bf_rt_id_t field_id,
                                 const char *value);

/* Ternary */
EXTERNC bf_status_t
bf_rt_key_field_set_value_and_mask(bf_rt_table_key_hdl *key_hdl,
                                   const bf_rt_id_t field_id,
                                   uint64_t value,
                                   uint64_t mask);

EXTERNC bf_status_t
bf_rt_key_field_set_value_and_mask_ptr(bf_rt_table_key_hdl *key_hdl,
                                       const bf_rt_id_t field_id,
                                       const uint8_t *value1,
                                       const uint8_t *mask,
                                       const size_t size);

/* Range */
EXTERNC bf_status_t
bf_rt_key_field_set_value_range(bf_rt_table_key_hdl *key_hdl,
                                const bf_rt_id_t field_id,
                                const uint64_t start,
                                const uint64_t end);

EXTERNC bf_status_t
bf_rt_key_field_set_value_range_ptr(bf_rt_table_key_hdl *key_hdl,
                                    const bf_rt_id_t field_id,
                                    const uint8_t *start,
                                    const uint8_t *end,
                                    const size_t size);

/* LPM */
EXTERNC bf_status_t bf_rt_key_field_set_value_lpm(bf_rt_table_key_hdl *key_hdl,
                                                  const bf_rt_id_t field_id,
                                                  const uint64_t value1,
                                                  const uint16_t p_length);

EXTERNC bf_status_t
bf_rt_key_field_set_value_lpm_ptr(bf_rt_table_key_hdl *key_hdl,
                                  const bf_rt_id_t field_id,
                                  const uint8_t *value1,
                                  const uint16_t p_length,
                                  const size_t size);

/** Get */
/* Exact */
EXTERNC bf_status_t
bf_rt_key_field_get_value(const bf_rt_table_key_hdl *key_hdl,
                          const bf_rt_id_t field_id,
                          uint64_t *value);

EXTERNC bf_status_t
bf_rt_key_field_get_value_ptr(const bf_rt_table_key_hdl *key_hdl,
                              const bf_rt_id_t field_id,
                              const size_t size,
                              uint8_t *value);

EXTERNC bf_status_t
bf_rt_key_field_get_value_string(const bf_rt_table_key_hdl *key_hdl,
                                 const bf_rt_id_t field_id,
                                 char *value);

/* Ternary */
EXTERNC bf_status_t
bf_rt_key_field_get_value_and_mask(const bf_rt_table_key_hdl *key_hdl,
                                   const bf_rt_id_t field_id,
                                   uint64_t *value1,
                                   uint64_t *value2);

EXTERNC bf_status_t
bf_rt_key_field_get_value_and_mask_ptr(const bf_rt_table_key_hdl *key_hdl,
                                       const bf_rt_id_t field_id,
                                       const size_t size,
                                       uint8_t *value1,
                                       uint8_t *value2);

/* Range */
EXTERNC bf_status_t
bf_rt_key_field_get_value_range(const bf_rt_table_key_hdl *key_hdl,
                                const bf_rt_id_t field_id,
                                uint64_t *start,
                                uint64_t *end);

EXTERNC bf_status_t
bf_rt_key_field_get_value_range_ptr(const bf_rt_table_key_hdl *key_hdl,
                                    const bf_rt_id_t field_id,
                                    const size_t size,
                                    uint8_t *start,
                                    uint8_t *end);

/* LPM */
EXTERNC bf_status_t
bf_rt_key_field_get_value_lpm(const bf_rt_table_key_hdl *key_hdl,
                              const bf_rt_id_t field_id,
                              uint64_t *start,
                              uint16_t *p_length);

EXTERNC bf_status_t
bf_rt_key_field_get_value_lpm_ptr(const bf_rt_table_key_hdl *key_hdl,
                                  const bf_rt_id_t field_id,
                                  const size_t size,
                                  uint8_t *value1,
                                  uint16_t *p_length);

#endif  // _BF_RT_TABLE_KEY_H
