include "res.thrift"

namespace py mirror_pd_rpc
namespace cpp mirror_pd_rpc
namespace c_glib mirror_pd_rpc

enum MirrorType_e {
  PD_MIRROR_TYPE_NORM = 0,
  PD_MIRROR_TYPE_COAL,
  PD_MIRROR_TYPE_MAX
}

enum Direction_e {
  PD_DIR_NONE = 0,
  PD_DIR_INGRESS,
  PD_DIR_EGRESS,
  PD_DIR_BOTH
}

enum MetaFlag_e {
  PD_HASH_CFG = 0,
  PD_HASH_CFG_P,
  PD_ICOS_CFG,
  PD_DOD_CFG,
  PD_C2C_CFG,
  PD_MC_CFG,
  PD_EPIPE_CFG  
}

typedef i16 MirrorId_t

exception InvalidPipeMgrOperation {
  1:i32 code
}

struct MirrorSessionInfo_t {
  1: MirrorType_e mir_type;
  2: Direction_e direction;
  3: MirrorId_t mir_id;
  4: i16 egr_port;
  5: bool egr_port_v;
  6: i16 egr_port_queue;
  7: i16 packet_color;
  8: i16 mcast_grp_a;
  9: bool mcast_grp_a_v;
  10: i16 mcast_grp_b;
  11: bool mcast_grp_b_v;
  12: i16 max_pkt_len;
  13: i32 level1_mcast_hash;
  14: i32 level2_mcast_hash;
  15: i16 mcast_l1_xid;
  16: i16 mcast_l2_xid;
  17: i16 mcast_rid;
  18: byte cos;
  19: bool c2c;
  20: i16 extract_len;
  21: i32 timeout_usec;
  22: list<i32> int_hdr;
  23: byte int_hdr_len;
}

struct MirrorSessionGetResult_t {
  1: MirrorSessionInfo_t info
  2: i16 pipe_id
}

service mirror {
    # Mirror APIs.
    
    void mirror_session_create (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorSessionInfo_t mirr_sess_info) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_update (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorSessionInfo_t mirr_sess_info, 4: bool enable) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_delete (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t mir_id) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_disable (1: res.SessionHandle_t sess_hdl, 2: Direction_e direction, 3: res.DevTarget_t dev_tgt, 4: MirrorId_t mir_id) throws (1: InvalidPipeMgrOperation ouch);   

    void mirror_session_enable (1: res.SessionHandle_t sess_hdl, 2: Direction_e direction, 3: res.DevTarget_t dev_tgt, 4: MirrorId_t mir_id) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_pipe_vec_set (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t mir_id, 4: i32 pipe_vec) throws (1: InvalidPipeMgrOperation ouch);

    i32 mirror_session_pipe_vec_get (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t mir_id) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_meta_flag_update (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t mir_id, 4: MetaFlag_e flag, 5: bool value) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_priority_update (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t mir_id, 4: bool value) throws (1: InvalidPipeMgrOperation ouch);

    void mirror_session_coal_mode_update (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t mir_id, 4: bool value) throws (1: InvalidPipeMgrOperation ouch);

    MirrorSessionGetResult_t mirror_session_get_first (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt) throws (1: InvalidPipeMgrOperation ouch);

    MirrorSessionGetResult_t mirror_session_get_next (1: res.SessionHandle_t sess_hdl, 2: res.DevTarget_t dev_tgt, 3: MirrorId_t id, 4: i16 pipe_id) throws (1: InvalidPipeMgrOperation ouch);

    MirrorId_t mirror_session_get_max_session_id (1: res.SessionHandle_t sess_hdl, 2: i32 dev, 3: MirrorType_e mir_type) throws (1: InvalidPipeMgrOperation ouch);

    MirrorId_t mirror_session_get_base_session_id (1: res.SessionHandle_t sess_hdl, 2: i32 dev, 3: MirrorType_e mir_type) throws (1: InvalidPipeMgrOperation ouch);
}
