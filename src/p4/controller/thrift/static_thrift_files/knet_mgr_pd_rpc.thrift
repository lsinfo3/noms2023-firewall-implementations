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
        knet_mgr thrift file
*/

namespace py knet_mgr_pd_rpc 
namespace cpp knet_mgr_pd_rpc 
namespace c_glib knet_mgr_pd_rpc

typedef i32 status_t 
typedef i64 knet_cpuif_t 
typedef i64 knet_hostif_t 
typedef i64 knet_filter_t 
typedef i32 knet_priority_t 
typedef i16 knet_action_count_t 
typedef i16 knet_data_offset_t 
typedef byte knet_data_size_t 
typedef i16 knet_count_t

enum knet_filter_dest_t {
  BF_KNET_FILTER_DESTINATION_CPUIF = 0,
  BF_KNET_FILTER_DESTINATION_HOSTIF = 1,
  BF_KNET_FILTER_DESTINATION_NULL = 2,
}

enum knet_mutation_type_t {
  BF_KNET_RX_MUT_NONE = 0,
  BF_KNET_RX_MUT_INSERT = 1,
  BF_KNET_RX_MUT_STRIP = 2,
}

struct knet_cpuif_res_t {
  1 : status_t status,
  2 : knet_cpuif_t knet_cpuif_id,
  3 : string name,
}

struct knet_hostif_kndev_res_t {
  1 : status_t status,
  2 : knet_hostif_t knet_hostif_id,
}

struct knet_filter_res_t {
  1 : status_t status,
  2 : knet_filter_t filter_id,
}

struct knet_rx_filter_spec_t {
  1 : knet_filter_t filter_id,
  2 : knet_priority_t priority,
  3 : binary filter,
  4 : binary mask,
  5 : i16 filter_size,
}

struct knet_packet_mutation_t {
  1 : knet_mutation_type_t mutation_type,
  2 : knet_data_offset_t offset,
  3 : knet_data_size_t len,
  4 : binary data,
}

struct knet_rx_filter_action_t {
  1 : knet_filter_dest_t dest_type,
  2 : knet_hostif_t knet_hostif_id,
  3 : i32 dest_proto,
  4 : knet_action_count_t count,
  5 : list<knet_packet_mutation_t> pkt_mutation,
}

struct knet_rx_filter_t {
  1 : knet_rx_filter_spec_t spec,
  2 : knet_rx_filter_action_t action,
}

struct knet_rx_filter_res_t {
  1 : status_t status,
  2 : knet_rx_filter_t rx_filter,
}

struct knet_count_res_t {
  1 : status_t status,
  2 : knet_count_t obj_count,
} 

struct knet_tx_action_t {
  1 : knet_action_count_t count,
  2 : list<knet_packet_mutation_t> pkt_mutation,
}

struct knet_filter_list_res_t {
  1 : status_t status,
  2 : knet_count_t filter_count,
  3 : list<knet_filter_t> filter_list,
}

struct knet_cpuif_list_t {
  1 : knet_cpuif_t id,
  2 : string name,
}

struct knet_cpuif_list_res_t {
  1 : status_t status,
  2 : knet_count_t cpuif_count,
  3 : list<knet_cpuif_list_t> cpuif_list,
}

struct knet_hostif_list_t {
  1 : knet_hostif_t id,
  2 : string name,
}

struct knet_hostif_list_res_t {
  1 : status_t status,
  2 : knet_count_t hostif_count,
  3 : list<knet_hostif_list_t> hostif_list,
}

struct knet_tx_action_res_t {
  1 : status_t status,
  2 : knet_tx_action_t tx_action,
}

exception InvalidKnetOperation {
  1 : i32 code
}

service knet_mgr {
  #BF KNET APIs

  knet_cpuif_res_t knet_cpuif_ndev_add(1: string cpuif_netdev_name) throws(1: InvalidKnetOperation ouch);

  status_t knet_cpuif_ndev_delete(1: knet_cpuif_t knet_cpuif_id) throws(1: InvalidKnetOperation ouch);

  knet_hostif_kndev_res_t knet_hostif_kndev_add(1: knet_cpuif_t knet_cpuif_id, 2: string hostif_name)
      throws(1: InvalidKnetOperation ouch);

  status_t knet_hostif_kndev_delete(1: knet_cpuif_t knet_cpuif_id, 2: knet_hostif_t knet_hostif_id)
      throws(1: InvalidKnetOperation ouch);

  knet_filter_res_t knet_rx_filter_add(1: knet_cpuif_t knet_cpuif_id, 2: knet_rx_filter_t rx_filter)
      throws(1: InvalidKnetOperation ouch);

  status_t knet_rx_filter_delete(1: knet_cpuif_t knet_cpuif_id, 2: knet_filter_t filter_id)
      throws(1: InvalidKnetOperation ouch);

  knet_rx_filter_res_t knet_rx_filter_get(1: knet_cpuif_t knet_cpuif_id, 2: knet_filter_t filter_id, 3: knet_count_t rx_mutation_count)
      throws(1: InvalidKnetOperation ouch);

  status_t knet_tx_action_add(1: knet_cpuif_t knet_cpuif_id, 2: knet_hostif_t knet_hostif_id, 3: knet_tx_action_t tx_action)
      throws(1: InvalidKnetOperation ouch);

  status_t knet_tx_action_delete(1: knet_cpuif_t knet_cpuif_id, 2: knet_hostif_t knet_hostif_id)
      throws(1: InvalidKnetOperation ouch);

  knet_count_res_t knet_get_cpuif_cnt() throws(1 : InvalidKnetOperation ouch);

  knet_count_res_t knet_get_hostif_cnt(1: knet_cpuif_t knet_cpuif_id)
      throws(1: InvalidKnetOperation ouch);

  knet_count_res_t knet_get_rx_filter_cnt(1: knet_cpuif_t knet_cpuif_id)
      throws(1: InvalidKnetOperation ouch);

  knet_count_res_t knet_get_rx_mutation_cnt(1: knet_cpuif_t knet_cpuif_id, 2: knet_filter_t filter_id)
      throws(1: InvalidKnetOperation ouch);

  knet_count_res_t knet_get_tx_mutation_cnt(1: knet_cpuif_t knet_cpuif_id, 2: knet_hostif_t hostif_id)
      throws(1: InvalidKnetOperation ouch);

  knet_filter_list_res_t knet_rx_filter_list_get(1: knet_cpuif_t knet_cpuif_id, 2: knet_count_t filter_count)
      throws(1: InvalidKnetOperation ouch);

  knet_cpuif_list_res_t knet_cpuif_list_get(1: knet_count_t cpuif_count)
      throws(1: InvalidKnetOperation ouch);

  knet_hostif_list_res_t knet_hostif_list_get(1: knet_cpuif_t knet_cpuif_id, 2: knet_count_t hostif_count)
      throws(1: InvalidKnetOperation ouch);

  knet_tx_action_res_t knet_tx_action_get(1: knet_cpuif_t knet_cpuif_id, 2: knet_hostif_t knet_hostif_id, 3: knet_count_t tx_mutation_count)
      throws(1: InvalidKnetOperation ouch);

  bool knet_module_is_inited();
}
