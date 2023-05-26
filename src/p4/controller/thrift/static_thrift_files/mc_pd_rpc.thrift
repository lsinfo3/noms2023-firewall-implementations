include "res.thrift"

namespace py mc_pd_rpc
namespace cpp mc_pd_rpc
namespace c_glib mc_pd_rpc

typedef i32 McHandle_t

exception InvalidMcOperation {
  1:i32 code
}

struct mc_node_assoc_attr {
  1: bool is_associated,
  2: McHandle_t mgrp_hdl,
  3: byte xid_valid,
  4: i16 xid,
}

struct mc_node_attr {
  1: i16 rid,
  2: binary port_map,
  3: binary lag_map,
}

struct mc_node_is_member {
  1:  bool is_ecmp_mbr,
  2:  McHandle_t ecmp_hdl,
}

struct mc_ecmp_assoc_attr {
  1: byte xid_valid,
  2: i16 xid,
}

struct mc_mgrp_attr {
  1: i16 mgid,
}

struct mc_mgrp_node_mbr {
  1: McHandle_t node_hdl,
  2: byte xid_valid,
  3: i16 xid
}

struct mc_mgrp_ecmp_mbr {
  1: McHandle_t ecmp_hdl,
  2: byte xid_valid,
  3: i16 xid
}

struct mc_ecmp_mbr {
  1: McHandle_t node_hdl,
  2: bool is_pruned,
}

struct mc_lag_mbr {
  1: i32 port,
  2: bool is_pruned,
}

service mc {
    # Multicast APIs.
    void            mc_init () throws (1:InvalidMcOperation ouch);
    res.SessionHandle_t mc_create_session    () throws (1:InvalidMcOperation ouch);
    void            mc_destroy_session    (1: res.SessionHandle_t sess_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_complete_operations(1: res.SessionHandle_t sess_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_begin_batch        (1:res.SessionHandle_t sess_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_flush_batch        (1:res.SessionHandle_t sess_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_end_batch          (1:res.SessionHandle_t sess_hdl, 2:bool hwSynchronous) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_mgrp_create    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 mgid) throws (1:InvalidMcOperation ouch);
    mc_mgrp_attr    mc_mgrp_get_attr    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_mgrp_destroy   (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t grp_hdl) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_mgrp_get_first (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    i32             mc_mgrp_get_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    list<McHandle_t> mc_mgrp_get_next_i (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl, 4: i32 n) throws (1:InvalidMcOperation ouch);
    mc_mgrp_node_mbr       mc_mgrp_get_first_node_mbr (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl) throws (1:InvalidMcOperation ouch);
    i32                    mc_mgrp_get_node_mbr_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl) throws (1:InvalidMcOperation ouch);
    list<mc_mgrp_node_mbr> mc_mgrp_get_next_i_node_mbr(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl, 4:McHandle_t node_hdl, 5: i32 n) throws (1:InvalidMcOperation ouch);
    mc_mgrp_ecmp_mbr       mc_mgrp_get_first_ecmp_mbr (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl) throws (1:InvalidMcOperation ouch);
    i32                    mc_mgrp_get_ecmp_mbr_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl) throws (1:InvalidMcOperation ouch);
    list<mc_mgrp_ecmp_mbr> mc_mgrp_get_next_i_ecmp_mbr(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl, 4:McHandle_t ecmp_hdl, 5: i32 n) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_node_create    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 rid, 4: binary port_map, 5: binary lag_map) throws (1:InvalidMcOperation ouch);
    mc_node_attr    mc_node_get_attr    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_node_update    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t l1_hdl, 4: binary port_map, 5: binary lag_map) throws (1:InvalidMcOperation ouch);
    void            mc_node_destroy   (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t l1_hdl) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_node_get_first (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    i32             mc_node_get_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    list<McHandle_t> mc_node_get_next_i (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t node_hdl, 4: i32 n) throws (1:InvalidMcOperation ouch);
    mc_ecmp_mbr     mc_ecmp_get_mbr_from_hash (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t mgrp_hdl, 4: McHandle_t ecmp_hdl, 5: i16 level1_mcast_hash, i16 pkt_xid) throws (1:InvalidMcOperation ouch);
    mc_node_assoc_attr mc_node_get_association (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t node_hdl) throws (1:InvalidMcOperation ouch);
    mc_node_is_member mc_node_is_mbr (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t node_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_associate_node (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t grp_hdl, 4: McHandle_t l1_hdl, 5: i16 xid, 6: byte xid_valid) throws (1:InvalidMcOperation ouch);
    void            mc_dissociate_node(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t grp_hdl, 4: McHandle_t l1_hdl) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_ecmp_create    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    void            mc_ecmp_destroy   (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_ecmp_get_first (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    i32             mc_ecmp_get_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    list<McHandle_t> mc_ecmp_get_next_i (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl, 4: i32 n) throws (1:InvalidMcOperation ouch);
    void            mc_ecmp_mbr_add   (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl, 4: McHandle_t l1_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_ecmp_mbr_rem   (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl, 4: McHandle_t l1_hdl) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_ecmp_get_first_mbr (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    i32             mc_ecmp_get_mbr_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    list<McHandle_t> mc_ecmp_get_next_i_mbr (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl, 4: McHandle_t node_hdl, 5: i32 n) throws (1:InvalidMcOperation ouch);
    void            mc_associate_ecmp (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t grp_hdl, 4: McHandle_t ecmp_hdl, 5: i16 xid, 6: byte xid_valid) throws (1:InvalidMcOperation ouch);
    mc_ecmp_assoc_attr   mc_ecmp_get_assoc_attr (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t grp_hdl, 4: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    void            mc_dissociate_ecmp(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t grp_hdl, 4: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    McHandle_t      mc_ecmp_get_first_assoc (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    i32             mc_ecmp_get_assoc_count (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl) throws (1:InvalidMcOperation ouch);
    list<McHandle_t> mc_ecmp_get_next_i_assoc (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t ecmp_hdl, 4: McHandle_t mgrp_hdl, 5: i32 n) throws (1:InvalidMcOperation ouch);
    void            mc_set_lag_membership(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: byte lag_index, 4: binary port_map) throws (1:InvalidMcOperation ouch);
    binary          mc_get_lag_membership(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: byte lag_index) throws (1:InvalidMcOperation ouch);
    mc_lag_mbr      mc_get_lag_member_from_hash(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: McHandle_t l1_hdl, 4: byte lag_index, 5: i16 level2_mcast_hash, 6: i16 pkt_xid, 7: i16 pkt_yid, 8: i16 pkt_rid) throws (1:InvalidMcOperation ouch);
    void            mc_set_remote_lag_member_count(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: byte lag_index, 4: i32 left, 5: i32 right) throws (1:InvalidMcOperation ouch);
    void            mc_update_port_prune_table(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 yid, 4: binary port_map) throws (1:InvalidMcOperation ouch);
    binary          mc_get_port_prune_table(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 yid, 4:bool from_hw) throws (1:InvalidMcOperation ouch);
    void            mc_set_global_rid    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 rid) throws (1:InvalidMcOperation ouch);
    void            mc_set_port_mc_fwd_state (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 port, 4: byte is_active) throws (1:InvalidMcOperation ouch);
    void            mc_enable_port_ff    (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    void            mc_disable_port_ff   (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    void            mc_clr_port_ff_state (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 port) throws (1:InvalidMcOperation ouch);
    void            mc_enable_port_protection  (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    void            mc_disable_port_protection (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id) throws (1:InvalidMcOperation ouch);
    void            mc_set_port_protection (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 pport, 4: i16 bport) throws (1:InvalidMcOperation ouch);
    void            mc_clear_port_protection (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 pport) throws (1:InvalidMcOperation ouch);
    void            mc_set_max_nodes_before_yield (1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i32 count) throws (1:InvalidMcOperation ouch);
    void            mc_set_max_node_threshold(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i32 node_count, 4: i32 lag_count) throws (1:InvalidMcOperation ouch);
    i32             mc_get_pipe_vec(1: res.SessionHandle_t sess_hdl, 2: i32 dev_id, 3: i16 mgid) throws (1:InvalidMcOperation ouch);
}
