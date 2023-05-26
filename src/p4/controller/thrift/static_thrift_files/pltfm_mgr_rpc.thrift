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
        pltfm_mgr thrift file
*/

namespace py pltfm_mgr_rpc
namespace cpp pltfm_mgr_rpc

typedef i32 pltfm_mgr_status_t
typedef byte pltfm_mgr_device_t
typedef i16 pltfm_mgr_ps_num_t
typedef i32 pltfm_mgr_fan_pct_t
typedef i32 pltfm_mgr_fan_num_t
typedef i32 pltfm_mgr_max_port_t

struct pltfm_mgr_sys_tmp_t {
  1 : double tmp1,
  2 : double tmp2,
  3 : double tmp3,
  4 : double tmp4,
  5 : double tmp5,
  6 : double tmp6,
  7 : double tmp7,
  8 : double tmp8,
  9 : double tmp9,
  10 : double tmp10,
}

struct pltfm_mgr_eeprom_t {
  1 : i16 version,
  2 : string prod_name,
  3 : string prod_part_num,
  4 : string sys_asm_part_num,
  5 : string bfn_pcba_part_num,
  6 : string bfn_pcbb_part_num,
  7 : string odm_pcba_part_num,
  8 : string odm_pcba_ser_num,
  9 : i16 prod_state,
  10 : i16 prod_ver,
  11 : i16 prod_sub_ver,
  12 : string prod_ser_num,
  13 : string prod_ast_tag,
  14 : string sys_mfger,
  15 : string sys_mfg_date,
  16 : string pcb_mfger,
  17 : string assembled_at,
  18 : string loc_mac_addr,
  19 : string ext_mac_addr,
  20 : i32 ext_mac_addr_size,
  21 : string location,
  22 : i16 crc8,
}

struct pltfm_mgr_pwr_supply_info_t {
  1 : i32 vin,
  2 : i32 vout,
  3 : i32 iout,
  4 : i32 pwr_out,
  5 : i32 fspeed,
  6 : bool ffault,
  7 : bool load_sharing,
  8 : string model,
  9 : string serial,
  10 : string rev,
}

struct pltfm_mgr_pwr_rail_info_t {
  1 : i32 vrail1,
  2 : i32 vrail2,
  3 : i32 vrail3,
  4 : i32 vrail4,
  5 : i32 vrail5,
  6 : i32 vrail6,
  7 : i32 vrail7,
  8 : i32 vrail8,
  9 : i32 vrail9,
  10 : i32 vrail10,
  11 : i32 vrail11,
  12 : i32 vrail12,
  13 : i32 vrail13,
  14 : i32 vrail14,
  15 : i32 vrail15,
  16 : i32 vrail16,
}

struct pltfm_mgr_fan_info_t {
  1 : i32 fan_num,
  2 : i32 front_rpm,
  3 : i32 rear_rpm,
  4 : i32 percent,
}

typedef i32 pltfm_mgr_fan_num
typedef i32 pltfm_mgr_fan_percent

exception InvalidPltfmMgrOperation {
  1 : i32 code
}


service pltfm_mgr_rpc {
    /* init */
    pltfm_mgr_status_t pltfm_mgr_dummy(1:pltfm_mgr_device_t device);
    pltfm_mgr_sys_tmp_t pltfm_mgr_sys_tmp_get() throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_eeprom_t pltfm_mgr_sys_eeprom_get() throws (1:InvalidPltfmMgrOperation ouch);
    bool pltfm_mgr_pwr_supply_present_get(1:pltfm_mgr_ps_num_t ps_num) throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_pwr_supply_info_t pltfm_mgr_pwr_supply_info_get(1:pltfm_mgr_ps_num_t ps_num) throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_pwr_rail_info_t pltfm_mgr_pwr_rail_info_get(1:pltfm_mgr_ps_num_t ps_num) throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_status_t pltfm_mgr_fan_speed_set(1:pltfm_mgr_fan_num fan_num 2:pltfm_mgr_fan_percent percent) throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_fan_info_t pltfm_mgr_fan_info_get(1:pltfm_mgr_fan_num_t fan_num) throws (1:InvalidPltfmMgrOperation ouch);
    bool pltfm_mgr_qsfp_presence_get(1:i32 port_num) throws (1:InvalidPltfmMgrOperation ouch);
    string pltfm_mgr_qsfp_info_get(1:i32 port_num) throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_max_port_t pltfm_mgr_qsfp_get_max_port() throws (1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_status_t pltfm_mgr_qsfp_reset(1:i32 port_num 2:bool reset) throws (1:InvalidPltfmMgrOperation ouch);
    bool pltfm_mgr_qsfp_lpmode_get(1:i32 port_num) throws(1:InvalidPltfmMgrOperation ouch);
    pltfm_mgr_status_t pltfm_mgr_qsfp_lpmode_set(1:i32 port_num 2:bool lpmode) throws(1:InvalidPltfmMgrOperation ouch);
    string pltfm_mgr_sensor_info_get() throws(1:InvalidPltfmMgrOperation ouch);
}
