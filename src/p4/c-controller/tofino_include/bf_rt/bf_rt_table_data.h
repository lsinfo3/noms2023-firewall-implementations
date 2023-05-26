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
#ifndef _BF_RT_TABLE_DATA_H
#define _BF_RT_TABLE_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_common.h>
#include <bf_rt/bf_rt_table_data.h>

#ifdef __cplusplus
}
#endif

/* Data field setters/getter */
EXTERNC bf_status_t bf_rt_data_field_set_value(bf_rt_table_data_hdl *data_hdl,
                                               const bf_rt_id_t field_id,
                                               const uint64_t val);

EXTERNC bf_status_t bf_rt_data_field_set_float(bf_rt_table_data_hdl *data_hdl,
                                               const bf_rt_id_t field_id,
                                               const float val);

EXTERNC bf_status_t
bf_rt_data_field_set_value_ptr(bf_rt_table_data_hdl *data_hdl,
                               const bf_rt_id_t field_id,
                               const uint8_t *val,
                               const size_t s);

EXTERNC bf_status_t
bf_rt_data_field_set_value_array(bf_rt_table_data_hdl *data_hdl,
                                 const bf_rt_id_t field_id,
                                 const uint32_t *val,
                                 const uint32_t num_array);

EXTERNC bf_status_t
bf_rt_data_field_set_value_bool_array(bf_rt_table_data_hdl *data_hdl,
                                      const bf_rt_id_t field_id,
                                      const bool *val,
                                      const uint32_t num_array);

EXTERNC bf_status_t bf_rt_data_field_set_bool(bf_rt_table_data_hdl *data_hdl,
                                              const bf_rt_id_t field_id,
                                              const bool val);

EXTERNC bf_status_t bf_rt_data_field_set_string(bf_rt_table_data_hdl *data_hdl,
                                                const bf_rt_id_t field_id,
                                                const char *val);

EXTERNC void bf_rt_data_field_get_value(const bf_rt_table_data_hdl *data_hdl,
                                        const bf_rt_id_t field_id,
                                        uint64_t *val);

EXTERNC void bf_rt_data_field_get_value_ptr(
    const bf_rt_table_data_hdl *data_hdl,
    const bf_rt_id_t field_id,
    const size_t size,
    uint8_t *val);

EXTERNC bf_status_t
bf_rt_data_field_get_value_array_size(const bf_rt_table_data_hdl *data_hdl,
                                      const bf_rt_id_t field_id,
                                      uint32_t *array_size);

EXTERNC bf_status_t
bf_rt_data_field_get_value_array(const bf_rt_table_data_hdl *data_hdl,
                                 const bf_rt_id_t field_id,
                                 uint32_t *val);

EXTERNC bf_status_t
bf_rt_data_field_get_value_bool_array_size(const bf_rt_table_data_hdl *data_hdl,
                                           const bf_rt_id_t field_id,
                                           uint32_t *array_size);

EXTERNC bf_status_t
bf_rt_data_field_get_value_bool_array(const bf_rt_table_data_hdl *data_hdl,
                                      const bf_rt_id_t field_id,
                                      bool *val);

EXTERNC void bf_rt_data_field_get_float(const bf_rt_table_data_hdl *data_hdl,
                                        const bf_rt_id_t field_id,
                                        float *val);

EXTERNC void bf_rt_data_field_get_bool(const bf_rt_table_data_hdl *data_hdl,
                                       const bf_rt_id_t field_id,
                                       bool *val);

EXTERNC bf_status_t
bf_rt_data_field_get_string_size(const bf_rt_table_data_hdl *data_hdl,
                                 const bf_rt_id_t field_id,
                                 uint32_t *str_size);

EXTERNC bf_status_t
bf_rt_data_field_get_string(const bf_rt_table_data_hdl *data_hdl,
                            const bf_rt_id_t field_id,
                            char *val);

EXTERNC bf_status_t
bf_rt_data_field_get_value_u64_array(const bf_rt_table_data_hdl *data_hdl,
                                     const bf_rt_id_t field_id,
                                     uint64_t *val);

EXTERNC bf_status_t
bf_rt_data_field_get_value_u64_array_size(const bf_rt_table_data_hdl *data_hdl,
                                          const bf_rt_id_t field_id,
                                          uint32_t *array_size);

EXTERNC bf_status_t
bf_rt_data_action_id_get(const bf_rt_table_data_hdl *data_hdl,
                         uint32_t *action_id);

#endif  // _BF_RT_TABLE_DATA_H
