/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2016 Barefoot Networks, Inc.
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
#ifndef _BF_PLTFM_TYPES_H
#define _BF_PLTFM_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bfsys/bf_sal/bf_sys_intf.h>
#include <libusb-1.0/libusb.h>

#define LOG_ERROR(...) \
  bf_sys_log_and_trace(BF_MOD_PLTFM, BF_LOG_ERR, __VA_ARGS__)
#define LOG_DEBUG(...) \
  bf_sys_log_and_trace(BF_MOD_PLTFM, BF_LOG_DBG, __VA_ARGS__)

#define MAX_CONNECTORS \
  66  // connectors are numbered starting from 1, Hence total connectors = 1
      // unused + 64 + 1 CPU

/*
 * Identifies the type of the board
 */
typedef enum bf_pltfm_board_id_e {
  BF_PLTFM_BD_ID_MAVERICKS_P0A = 0x0234,
  BF_PLTFM_BD_ID_MAVERICKS_P0B = 0x1234,
  BF_PLTFM_BD_ID_MAVERICKS_P0C = 0x5234,
  BF_PLTFM_BD_ID_MONTARA_P0A = 0x2234,
  BF_PLTFM_BD_ID_MONTARA_P0B = 0x3234,
  BF_PLTFM_BD_ID_AG9064V1_P0A = 0x5678,
  BF_PLTFM_BD_ID_MAVERICKS_P0B_EMU = 0x4234,
  BF_PLTFM_BD_ID_UNKNOWN = 0XFFFF
} bf_pltfm_board_id_t;

/*
 * Identifies the type of the QSFP connected
 */
typedef enum bf_pltfm_qsfp_type_t {

  BF_PLTFM_QSFP_CU_0_5_M = 0,
  BF_PLTFM_QSFP_CU_1_M = 1,
  BF_PLTFM_QSFP_CU_2_M = 2,
  BF_PLTFM_QSFP_CU_3_M = 3,
  BF_PLTFM_QSFP_CU_LOOP = 4,
  BF_PLTFM_QSFP_OPT = 5,
  BF_PLTFM_QSFP_UNKNOWN = 6
} bf_pltfm_qsfp_type_t;

/*
 * Holds the entire context of a CP2112 device
 */
typedef struct bf_pltfm_cp2112_device_ctx_t {
  libusb_device *usb_device;
  libusb_device_handle *usb_device_handle;
  libusb_context *usb_context;
  int selected_port;
  int selected_repeater;
  bool bus_good;
  uint16_t usb_bus_num;
} bf_pltfm_cp2112_device_ctx_t;

/*
 * Holds the information about a platform
 */
typedef struct bf_pltfm_board_info_t {
  bf_pltfm_board_id_t bd_id;
  bf_pltfm_cp2112_device_ctx_t *cp2112_dev_arr;
} bf_pltfm_board_info_t;

/*
 * Encapsulates the information of a port on the board
 */
typedef struct bf_pltfm_port_info_t {
  uint32_t conn_id;
  uint32_t chnl_id;
} bf_pltfm_port_info_t;

/*
 * Identifies an error code
 */
typedef int bf_pltfm_status_t;

#define BF_PLTFM_STATUS_VALUES                                         \
  BF_PLTFM_STATUS_(BF_PLTFM_SUCCESS, "Success"),                       \
      BF_PLTFM_STATUS_(BF_PLTFM_INVALID_ARG, "Invalid Arguments"),     \
      BF_PLTFM_STATUS_(BF_PLTFM_OBJECT_NOT_FOUND, "Object Not Found"), \
      BF_PLTFM_STATUS_(BF_PLTFM_COMM_FAILED,                           \
                       "Communication Failed with Hardware"),          \
      BF_PLTFM_STATUS_(BF_PLTFM_OBJECT_ALREADY_EXISTS,                 \
                       "Object Already Exists"),                       \
      BF_PLTFM_STATUS_(BF_PLTFM_OTHER, "Other")

enum bf_pltfm_status_enum {
#define BF_PLTFM_STATUS_(x, y) x
  BF_PLTFM_STATUS_VALUES,
  BF_PLTFM_STS_MAX
#undef BF_PLTFM_STATUS_
};

static const char *bf_pltfm_err_strings[BF_PLTFM_STS_MAX + 1] = {
#define BF_PLTFM_STATUS_(x, y) y
    BF_PLTFM_STATUS_VALUES, "Unknown error"
#undef BF_PLTFM_STATUS_
};

static inline const char *bf_pltfm_err_str(bf_pltfm_status_t sts) {
  if (BF_PLTFM_STS_MAX <= sts || 0 > sts) {
    return bf_pltfm_err_strings[BF_PLTFM_STS_MAX];
  } else {
    return bf_pltfm_err_strings[sts];
  }
}

#endif
