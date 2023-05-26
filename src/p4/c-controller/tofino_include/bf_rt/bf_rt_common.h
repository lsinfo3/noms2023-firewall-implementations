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
/** @file bf_rt_common.h
 *
 *  @brief Contains Common data types used in BF-RT
 */
#ifndef _BF_RT_COMMON_H
#define _BF_RT_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <bf_types/bf_types.h>
#include <pipe_mgr/pipe_mgr_intf.h>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/**
 * @brief 32-bit ID for all BF-RT entities
 */
typedef uint32_t bf_rt_id_t;

/**
 * @brief For sake of strict typechecking, instead of typedef-ing
 * \n void to our handle, we make a small struct with one element.
 */
#define DECLARE_HANDLE(name) \
  struct name##__ {          \
    int unused;              \
  };                         \
  typedef struct name##__ name

// C frontend typedefs
DECLARE_HANDLE(bf_rt_info_hdl);
DECLARE_HANDLE(bf_rt_session_hdl);
DECLARE_HANDLE(bf_rt_table_hdl);
DECLARE_HANDLE(bf_rt_table_key_hdl);
DECLARE_HANDLE(bf_rt_table_data_hdl);
DECLARE_HANDLE(bf_rt_table_attributes_hdl);
DECLARE_HANDLE(bf_rt_entry_scope_arguments_hdl);
DECLARE_HANDLE(bf_rt_learn_hdl);
DECLARE_HANDLE(bf_rt_table_operations_hdl);
/**
 * @brief learn_data_hdl and table_data_hdl are the same,
 *  \n hence simple typedef like BfRtLearnData in
 *  \n include/bf_rt_learn.hpp
 */
typedef bf_rt_table_data_hdl bf_rt_learn_data_hdl;

// C and C++ void typedefs
DECLARE_HANDLE(bf_rt_learn_msg_hdl);

/**
 * @brief Structure definition for configuration target
 */
typedef struct bf_rt_target_ {
  /** Device ID */
  bf_dev_id_t dev_id;
  /** Pipe ID */
  bf_dev_pipe_t pipe_id;
  /** Gress direction In/Eg */
  pipe_mgr_pvs_gress_en direction;
  /** Parser ID */
  uint8_t prsr_id;
} bf_rt_target_t;

// non-inline version of err string function for use in ctypes FFI
void bf_rt_cli_err_str(bf_status_t sts, const char **err_str);

#endif
