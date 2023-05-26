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
/*
        pal thrift file
*/

include "res.thrift"

namespace py pal_rpc
namespace cpp pal_rpc
namespace c_glib pal_rpc

typedef i32 pal_status_t
typedef i32 pal_dev_port_t
typedef byte pal_device_t
typedef i32 pal_front_port_t
typedef i32 pal_front_chnl_t

exception InvalidPalOperation {
  1:i32 code
}

enum pal_port_speed_t {
  BF_SPEED_NONE = 0,
  BF_SPEED_1G = 1,
  BF_SPEED_10G = 2,
  BF_SPEED_25G = 3,
  BF_SPEED_40G = 4,
  BF_SPEED_40G_NB = 5,
  BF_SPEED_50G = 6,
  BF_SPEED_100G = 7,
  BF_SPEED_40G_NON_BREAKABLE = 8
  BF_SPEED_200G = 9,
  BF_SPEED_400G = 10,
}

enum pal_fec_type_t {
  BF_FEC_TYP_NONE = 0,
  BF_FEC_TYP_FIRECODE = 1,
  BF_FEC_TYP_REED_SOLOMON = 2
}

enum pal_oper_status_t {
  BF_PORT_DOWN = 0,
  BF_PORT_UP = 1
}

enum pal_autoneg_policy_t {
  BF_AN_DEFAULT = 0,
  BF_AN_FORCE_ENABLE = 1,
  BF_AN_FORCE_DISABLE = 2
}

enum pal_loopback_mod_t {
  BF_LPBK_NONE = 0,
  BF_LPBK_MAC_NEAR = 1,
  BF_LPBK_MAC_FAR = 2,
  BF_LPBK_PCS_NEAR = 3,
  BF_LPBK_SERDES_NEAR = 4,
  BF_LPBK_SERDES_FAR = 5
}

enum pal_rmon_counter_t {
  pal_mac_stat_FramesReceivedOK = 0,
  pal_mac_stat_FramesReceivedAll = 1,
  pal_mac_stat_FramesReceivedwithFCSError = 2,
  pal_mac_stat_FrameswithanyError = 3,
  pal_mac_stat_OctetsReceivedinGoodFrames = 4,
  pal_mac_stat_OctetsReceived = 5,
  pal_mac_stat_FramesReceivedwithUnicastAddresses = 6,
  pal_mac_stat_FramesReceivedwithMulticastAddresses = 7,
  pal_mac_stat_FramesReceivedwithBroadcastAddresses = 8,
  pal_mac_stat_FramesReceivedoftypePAUSE = 9,
  pal_mac_stat_FramesReceivedwithLengthError = 10,
  pal_mac_stat_FramesReceivedUndersized = 11,
  pal_mac_stat_FramesReceivedOversized = 12,
  pal_mac_stat_FragmentsReceived = 13,
  pal_mac_stat_JabberReceived = 14,
  pal_mac_stat_PriorityPauseFrames = 15,
  pal_mac_stat_CRCErrorStomped = 16,
  pal_mac_stat_FrameTooLong = 17,
  pal_mac_stat_RxVLANFramesGood = 18,
  pal_mac_stat_FramesDroppedBufferFull = 19,
  pal_mac_stat_FramesReceivedLength_lt_64 = 20,
  pal_mac_stat_FramesReceivedLength_eq_64 = 21,
  pal_mac_stat_FramesReceivedLength_65_127 = 22,
  pal_mac_stat_FramesReceivedLength_128_255 = 23,
  pal_mac_stat_FramesReceivedLength_256_511 = 24,
  pal_mac_stat_FramesReceivedLength_512_1023 = 25,
  pal_mac_stat_FramesReceivedLength_1024_1518 = 26,
  pal_mac_stat_FramesReceivedLength_1519_2047 = 27,
  pal_mac_stat_FramesReceivedLength_2048_4095 = 28,
  pal_mac_stat_FramesReceivedLength_4096_8191 = 29,
  pal_mac_stat_FramesReceivedLength_8192_9215 = 30,
  pal_mac_stat_FramesReceivedLength_9216 = 31,
  pal_mac_stat_FramesTransmittedOK = 32,
  pal_mac_stat_FramesTransmittedAll = 33,
  pal_mac_stat_FramesTransmittedwithError = 34,
  pal_mac_stat_OctetsTransmittedwithouterror = 35,
  pal_mac_stat_OctetsTransmittedTotal = 36,
  pal_mac_stat_FramesTransmittedUnicast = 37,
  pal_mac_stat_FramesTransmittedMulticast = 38,
  pal_mac_stat_FramesTransmittedBroadcast = 39,
  pal_mac_stat_FramesTransmittedPause = 40,
  pal_mac_stat_FramesTransmittedPriPause = 41,
  pal_mac_stat_FramesTransmittedVLAN = 42,
  pal_mac_stat_FramesTransmittedLength_lt_64 = 43,
  pal_mac_stat_FramesTransmittedLength_eq_64 = 44,
  pal_mac_stat_FramesTransmittedLength_65_127 = 45,
  pal_mac_stat_FramesTransmittedLength_128_255 = 46,
  pal_mac_stat_FramesTransmittedLength_256_511 = 47,
  pal_mac_stat_FramesTransmittedLength_512_1023 = 48,
  pal_mac_stat_FramesTransmittedLength_1024_1518 = 49,
  pal_mac_stat_FramesTransmittedLength_1519_2047 = 50,
  pal_mac_stat_FramesTransmittedLength_2048_4095 = 51,
  pal_mac_stat_FramesTransmittedLength_4096_8191 = 52,
  pal_mac_stat_FramesTransmittedLength_8192_9215 = 53,
  pal_mac_stat_FramesTransmittedLength_9216 = 54,
  pal_mac_stat_Pri0FramesTransmitted = 55,
  pal_mac_stat_Pri1FramesTransmitted = 56,
  pal_mac_stat_Pri2FramesTransmitted = 57,
  pal_mac_stat_Pri3FramesTransmitted = 58,
  pal_mac_stat_Pri4FramesTransmitted = 59,
  pal_mac_stat_Pri5FramesTransmitted = 60,
  pal_mac_stat_Pri6FramesTransmitted = 61,
  pal_mac_stat_Pri7FramesTransmitted = 62,
  pal_mac_stat_Pri0FramesReceived = 63,
  pal_mac_stat_Pri1FramesReceived = 64,
  pal_mac_stat_Pri2FramesReceived = 65,
  pal_mac_stat_Pri3FramesReceived = 66,
  pal_mac_stat_Pri4FramesReceived = 67,
  pal_mac_stat_Pri5FramesReceived = 68,
  pal_mac_stat_Pri6FramesReceived = 69,
  pal_mac_stat_Pri7FramesReceived = 70,
  pal_mac_stat_TransmitPri0Pause1USCount = 71,
  pal_mac_stat_TransmitPri1Pause1USCount = 72,
  pal_mac_stat_TransmitPri2Pause1USCount = 73,
  pal_mac_stat_TransmitPri3Pause1USCount = 74,
  pal_mac_stat_TransmitPri4Pause1USCount = 75,
  pal_mac_stat_TransmitPri5Pause1USCount = 76,
  pal_mac_stat_TransmitPri6Pause1USCount = 77,
  pal_mac_stat_TransmitPri7Pause1USCount = 78,
  pal_mac_stat_ReceivePri0Pause1USCount = 79,
  pal_mac_stat_ReceivePri1Pause1USCount = 80,
  pal_mac_stat_ReceivePri2Pause1USCount = 81,
  pal_mac_stat_ReceivePri3Pause1USCount = 82,
  pal_mac_stat_ReceivePri4Pause1USCount = 83,
  pal_mac_stat_ReceivePri5Pause1USCount = 84,
  pal_mac_stat_ReceivePri6Pause1USCount = 85,
  pal_mac_stat_ReceivePri7Pause1USCount = 86,
  pal_mac_stat_ReceiveStandardPause1USCount = 87,
  pal_mac_stat_FramesTruncated = 88,
  PAL_NUM_RMON_COUNTERS = 89
}

enum pal_media_type_t {
  BF_MEDIA_TYPE_COPPER = 0,
  BF_MEDIA_TYPE_OPTICAL = 1,
  BF_MEDIA_TYPE_UNKNOWN = 2
}

struct pal_stats_t {
  1:list<i64> entry;
  2:i32 entry_count;
  3:pal_status_t status;
}

struct pal_rmon_counters_array_t {
  1:list<pal_rmon_counter_t> array;
  2:i32 array_count;
}

struct pal_stats_with_ts_t {
  1:list<i64> entry;
  2:i32 entry_count;
  3:i64 timestamp_s;
  4:i64 timestamp_ns;
  5:pal_status_t status;
}

struct pal_mtu_t {
  1:i32 tx_mtu;
  2:i32 rx_mtu;
  3:pal_status_t status;
}

struct pal_pfc_t {
  1:i32 tx_en_map;
  2:i32 rx_en_map;
  3:pal_status_t status;
}

struct pal_link_pause_t {
  1:bool tx_en;
  2:bool rx_en;
  3:pal_status_t status;
}

struct pal_string_t {
  1:list<byte> entry;
  2:i32 entry_count;
  3:pal_status_t status;
}

struct pal_recirc_ports_t {
  1:i32 start_recirc_port;
  2:i32 end_recirc_port;
  3:pal_status_t status;
}

struct pal_front_panel_port_t {
  1: pal_front_port_t pal_front_port,
  2: pal_front_chnl_t pal_front_chnl,
}

service pal {
    #BF PAL APIs

    pal_status_t pal_port_add(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:pal_port_speed_t ps, 4:pal_fec_type_t fec) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_add_all(1:pal_device_t device, 2:pal_port_speed_t ps, 3:pal_fec_type_t fec) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_del(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_del_all(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_enable(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_enable_all(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_dis(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_oper_status_t pal_port_oper_status_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    bool pal_port_is_valid(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_autoneg_policy_t pal_port_an_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_an_set(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:pal_autoneg_policy_t an) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_an_set_all(1:pal_device_t device, 2:pal_autoneg_policy_t an) throws (1:InvalidPalOperation ouch);
    pal_dev_port_t pal_port_get_first(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    pal_dev_port_t pal_port_get_next(1:pal_device_t device, 2:pal_dev_port_t curr_dev_port) throws (1:InvalidPalOperation ouch);
    pal_stats_t pal_port_stats_direct_get(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:pal_rmon_counters_array_t ctr_type) throws (1:InvalidPalOperation ouch);
    pal_stats_t pal_port_all_stats_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_stats_with_ts_t pal_port_all_stats_get_with_ts(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    i64 pal_port_this_stat_get(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:pal_rmon_counter_t ctr_type) throws (1:InvalidPalOperation ouch);
    pal_string_t pal_port_this_stat_id_to_str(1:pal_rmon_counter_t ctr_type) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_this_stat_clear(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:pal_rmon_counter_t ctr_type) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_all_stats_clear(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    i32 pal_port_stats_poll_intvl_get(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_stats_poll_intvl_set(1:pal_device_t device, 2:i32 poll_intvl_ms) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_all_stats_update(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    i32 pal_port_num_lanes_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_mtu_t pal_port_mtu_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_mtu_set(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:i32 tx_mtu, 4:i32 rx_mtu) throws (1:InvalidPalOperation ouch);
    pal_pfc_t pal_port_flow_control_pfc_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_flow_control_pfc_set(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:i32 tx_en_map, 4:i32 rx_en_map) throws (1:InvalidPalOperation ouch);
    pal_link_pause_t pal_port_flow_control_link_pause_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_flow_control_link_pause_set(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:bool tx_en, 4:bool rx_en) throws (1:InvalidPalOperation ouch);
    pal_fec_type_t pal_port_fec_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_fec_set(1:pal_device_t device, 2:pal_dev_port_t dev_port, 3:pal_fec_type_t fec) throws (1:InvalidPalOperation ouch);
    pal_media_type_t pal_port_media_type_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_cut_through_enable(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_cut_through_disable(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    bool pal_port_cut_through_enable_status_get(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    i32 pal_num_pipes_get(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    pal_loopback_mod_t pal_port_loopback_mode_get(1:pal_device_t dev, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    pal_status_t pal_port_loopback_mode_set(1:pal_device_t dev, 2:pal_dev_port_t dev_port, 3:pal_loopback_mod_t mode) throws (1:InvalidPalOperation ouch);
    pal_dev_port_t pal_port_front_panel_port_to_dev_port_get(1:pal_device_t dev, 2:pal_front_port_t front_port, 3:pal_front_chnl_t front_chnl) throws (1:InvalidPalOperation ouch);
    pal_front_panel_port_t pal_port_dev_port_to_front_panel_port_get(1:pal_device_t dev, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
    i32 pal_max_ports_get(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    pal_dev_port_t pal_fp_idx_to_dev_port_map(1:pal_device_t device, 2:i32 fp_idx) throws (1:InvalidPalOperation ouch);
    pal_dev_port_t pal_recirc_port_to_dev_port_map(1:pal_device_t device, 2:i32 recirc_port) throws (1:InvalidPalOperation ouch);
    pal_recirc_ports_t pal_recirc_port_range_get(1:pal_device_t device) throws (1:InvalidPalOperation ouch);
    bool pal_is_port_internal(1:pal_device_t device, 2:pal_dev_port_t dev_port) throws (1:InvalidPalOperation ouch);
}
