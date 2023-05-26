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
/*
        pltfm_pm thrift file
*/

namespace py pltfm_pm_rpc
namespace cpp pltfm_pm_rpc

typedef i32 pltfm_pm_status_t
typedef i32 pltfm_pm_dev_port_t
typedef byte pltfm_pm_device_t

exception InvalidPltfmPmOperation {
  1:i32 code
}

enum pltfm_pm_board_type_t {
  BF_PLTFM_BD_ID_MAVERICKS_P0A = 0x0234,
  BF_PLTFM_BD_ID_MAVERICKS_P0B = 0x1234,
  BF_PLTFM_BD_ID_MAVERICKS_P0C = 0x5234,
  BF_PLTFM_BD_ID_MONTARA_P0A = 0x2234,
  BF_PLTFM_BD_ID_MONTARA_P0B = 0x3234,
  BF_PLTFM_BD_ID_MAVERICKS_P0B_EMU = 0x4234,
  BF_PLTFM_BD_ID_UNKNOWN = 0XFFFF
}

service pltfm_pm_rpc {
    /* init */
    pltfm_pm_board_type_t pltfm_pm_board_type_get() throws (1:InvalidPltfmPmOperation ouch);
}
