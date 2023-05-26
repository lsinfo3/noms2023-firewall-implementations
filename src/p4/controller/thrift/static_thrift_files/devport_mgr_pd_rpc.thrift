include "res.thrift"

namespace py devport_mgr_pd_rpc
namespace cpp devport_mgr_pd_rpc
namespace c_glib devport_mgr_pd_rpc

exception InvalidDevportMgrOperation {
  1:i32 code
}

enum dev_init_mode {
  DEV_INIT_COLD,
  // Device incurs complete reset
  DEV_WARM_INIT_FAST_RECFG,
  // Device incurs a fast-reconfig reset with minimal traffic disruption
  DEV_WARM_INIT_HITLESS,
  // Device incurs a hitless warm init
  DEV_WARM_INIT_FAST_RECFG_QUICK,
  // Device incurs a fast-reconfig reset with minimal traffic disruption
  // bf-drivers pushes all the cached config back to the asic, there is no
  // config replay
}

enum dev_serdes_upgrade_mode {
  DEV_SERDES_UPD_NONE,
  // No serdes update needed
  DEV_SERDES_UPD_FORCED_PORT_RECFG,
  // Update serdes by flapping ports immediately
  DEV_SERDES_UPD_DEFERRED_PORT_RECFG
  // Defer the serdes update until a port flap occurs
} 

enum dev_port_corrective_action {
  HA_CA_PORT_NONE = 0,
  HA_CA_PORT_ADD,
  HA_CA_PORT_ENABLE,
  HA_CA_PORT_ADD_THEN_ENABLE,
  HA_CA_PORT_FLAP,
  HA_CA_PORT_DISABLE,
  HA_CA_PORT_DELETE_THEN_ADD,
  HA_CA_PORT_DELETE_THEN_ADD_THEN_ENABLE,
  HA_CA_PORT_DELETE,
  HA_CA_PORT_MAX
} 

enum bf_error_sev_level {
  BF_ERR_SEV_CORRECTABLE = 0,
  BF_ERR_SEV_NON_CORRECTABLE = 1,
  BF_ERR_SEV_FATAL = 2
}
enum bf_error_type {
  BF_ERR_TYPE_GENERIC = 0,
  BF_ERR_TYPE_SINGLE_BIT_ECC,
  BF_ERR_TYPE_MULTI_BIT_ECC,
  BF_ERR_TYPE_PARITY,
  BF_ERR_TYPE_OVERFLOW,
  BF_ERR_TYPE_UNDERFLOW,
}
enum bf_error_block {
  BF_ERR_BLK_NONE = 0,
  BF_ERR_BLK_MAU,
  BF_ERR_BLK_TCAM,
  BF_ERR_BLK_SRAM,
  BF_ERR_BLK_MAP_RAM,
  BF_ERR_BLK_STATS,
  BF_ERR_BLK_METERS,
  BF_ERR_BLK_SYNTH2PORT,
  BF_ERR_BLK_SELECTOR_ALU,
  BF_ERR_BLK_IMEM,
  BF_ERR_BLK_MIRROR,
  BF_ERR_BLK_TM_PRE,
  BF_ERR_BLK_TM_WAC,
  BF_ERR_BLK_TM_QAC,
  BF_ERR_BLK_TM_CLC,
  BF_ERR_BLK_TM_PEX,
  BF_ERR_BLK_TM_QLC,
  BF_ERR_BLK_TM_PRC,
  BF_ERR_BLK_TM_PSC,
  BF_ERR_BLK_TM_CAA,
  BF_ERR_BLK_TM_SCH,
  BF_ERR_BLK_PRSR,
  BF_ERR_BLK_DEPRSR,
  BF_ERR_BLK_PKTGEN,
  BF_ERR_BLK_GFM,
  BF_ERR_BLK_DMA,
}
enum bf_error_block_location {
  BF_ERR_LOC_NONE = 0,
  BF_ERR_LOC_MAU_IDLETIME,
  BF_ERR_LOC_MAU_STATEFUL_LOG,
  BF_ERR_LOC_SELECTOR_ALU_ST_MINMAX,
  BF_ERR_LOC_SELECTOR_ALU_DEV_BY0,
  BF_ERR_LOC_SELECTOR_ALU_SALU_PRED,
  BF_ERR_LOC_MIRR_POINTER_FIFO,
  BF_ERR_LOC_MIRR_IG,
  BF_ERR_LOC_MIRR_EG,
  BF_ERR_LOC_MIRR_OUT_DESC,
  BF_ERR_LOC_MIRR_DATA_BUFFER,
  BF_ERR_LOC_MIRR_DROP_NEG,
  BF_ERR_LOC_MIRR_DROP_COAL,
  BF_ERR_LOC_MIRR_IG_DIS_SESS,
  BF_ERR_LOC_MIRR_EG_DIS_SESS,
  BF_ERR_LOC_MIRR_OUT,
  BF_ERR_LOC_MIRR_CRC12,
  BF_ERR_LOC_MIRR_SESSION,
  BF_ERR_LOC_MIRR_S2P_CREDIT,
  BF_ERR_LOC_MIRR_IDPRSR_SOPEOP_MISMATCH,
  BF_ERR_LOC_MIRR_EDPRSR_SOPEOP_MISMATCH,
  BF_ERR_LOC_MIRR_DATA_MEM,
  BF_ERR_LOC_TM_PRE_FIFO,
  BF_ERR_LOC_TM_PRE_MIT,
  BF_ERR_LOC_TM_PRE_LIT0_BM,
  BF_ERR_LOC_TM_PRE_LIT1_BM,
  BF_ERR_LOC_TM_PRE_LIT0_NP,
  BF_ERR_LOC_TM_PRE_LIT1_NP,
  BF_ERR_LOC_TM_PRE_PMT0,
  BF_ERR_LOC_TM_PRE_PMT1,
  BF_ERR_LOC_TM_PRE_RDM,
  BF_ERR_LOC_TM_PRE_BANKID_MEM,
  BF_ERR_LOC_TM_WAC_PPG_MAP,
  BF_ERR_LOC_TM_WAC_DROP_CNT,
  BF_ERR_LOC_TM_WAC_PFC_VIS,
  BF_ERR_LOC_TM_WAC_SCH_FCR,
  BF_ERR_LOC_TM_WAC_QID_MAP,
  BF_ERR_LOC_TM_WAC_WAC2QAC,
  BF_ERR_LOC_TM_QAC_QUE_DROP,
  BF_ERR_LOC_TM_QAC_PORT_DROP,
  BF_ERR_LOC_TM_QAC_QID_MAP,
  BF_ERR_LOC_TM_QAC_QAC2PRC,
  BF_ERR_LOC_TM_QAC_PRC2PSC,
  BF_ERR_LOC_TM_CLC_ENQ_FIFO,
  BF_ERR_LOC_TM_CLC_QAC_FIFO,
  BF_ERR_LOC_TM_CLC_PH_FIFO,
  BF_ERR_LOC_TM_CLC_QAC_PH_FIFO,
  BF_ERR_LOC_TM_PEX_CLM,
  BF_ERR_LOC_TM_PEX_PH_FIFO,
  BF_ERR_LOC_TM_PEX_META_FIFO,
  BF_ERR_LOC_TM_PEX_PH_AFIFO,
  BF_ERR_LOC_TM_PEX_DISCARD_FIFO,
  BF_ERR_LOC_TM_QLC_QLM,
  BF_ERR_LOC_TM_QLC_SCHDEQ,
  BF_ERR_LOC_TM_QLC_PH_FIFO,
  BF_ERR_LOC_TM_PRC_T3,
  BF_ERR_LOC_TM_PSC_PSM,
  BF_ERR_LOC_TM_PSC_COMM,
  BF_ERR_LOC_TM_CAA,
  BF_ERR_LOC_TM_SCH_TDM,
  BF_ERR_LOC_TM_SCH_UPD_WAC,
  BF_ERR_LOC_TM_SCH_UPD_EDPRSR_ADVFC,
  BF_ERR_LOC_TM_SCH_Q_MINRATE,
  BF_ERR_LOC_TM_SCH_Q_EXCRATE,
  BF_ERR_LOC_TM_SCH_Q_MAXRATE,
  BF_ERR_LOC_TM_SCH_L1_MINRATE,
  BF_ERR_LOC_TM_SCH_L1_EXCRATE,
  BF_ERR_LOC_TM_SCH_L1_MAXRATE,
  BF_ERR_LOC_TM_SCH_P_MAXRATE,
  BF_ERR_LOC_TM_SCH_UPD_PEX,
  BF_ERR_LOC_TM_SCH_UPD_EDPRSR,
  BF_ERR_LOC_TM_SCH_PEX_CREDIT,
  BF_ERR_LOC_TM_SCH_PEX_MAC_CREDIT,
  BF_ERR_LOC_TM_SCH_Q_WATCHDOG,
  BF_ERR_LOC_PRSR_ACT_RAM,
  BF_ERR_LOC_PRSR_INP_BUFF,
  BF_ERR_LOC_PRSR_OUT_FIFO,
  BF_ERR_LOC_PRSR_TCAM_PARITY,
  BF_ERR_LOC_PRSR_CSUM,
  BF_ERR_LOC_DEPRSR_PIPE_VEC_TBL0,
  BF_ERR_LOC_DEPRSR_PIPE_VEC_TBL1,
  BF_ERR_LOC_DEPRSR_MIRRTBL,
  BF_ERR_LOC_DEPRSR_IPKT_MAC,
  BF_ERR_LOC_DEPRSR_CMD_FIFO,
  BF_ERR_LOC_DEPRSR_CRED_ERR,
  BF_ERR_LOC_DEPRSR_PKTST,
  BF_ERR_LOC_DEPRSR_META_FIFO,
  BF_ERR_LOC_DEPRSR_PKTHDR,
  BF_ERR_LOC_DEPRSR_MIRRHDR,
  BF_ERR_LOC_DEPRSR_DATAST,
  BF_ERR_LOC_DEPRSR_PKTDATA,
  BF_ERR_LOC_DEPRSR_TMSCH,
  BF_ERR_LOC_DEPRSR_ARB_FIFO,
  BF_ERR_LOC_DEPRSR_CTL_CHAN,
  BF_ERR_LOC_PKTGEN_BUFFER,
  BF_ERR_LOC_PKTGEN_PFC,
  BF_ERR_LOC_PKTGEN_TBC_FIFO,
  BF_ERR_LOC_PKTGEN_ETH_CPU_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P0_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P1_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P2_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P3_FIFO,
  BF_ERR_LOC_PKTGEN_APP_EVT,
  BF_ERR_LOC_PKTGEN_IPB_CHNL_SEQ,
  BF_ERR_LOC_PKTGEN_ETH_CPU_TBC_SAMECHNL,
  BF_ERR_LOC_PKTGEN_ETH_PORT_FIFO,
  BF_ERR_LOC_PKTGEN_PHASE0,
  BF_ERR_LOC_GFM_INGRESS,
  BF_ERR_LOC_GFM_EGRESS,
  BF_ERR_LOC_DMA_PBC,
  BF_ERR_LOC_DMA_CBC,
  BF_ERR_LOC_DMA_MBC,
}
struct error_event_record {
  1: required bf_error_sev_level sev;
  2: required i32 dev_id;
  3: required i32 pipe;
  4: required byte stage;
  5: required i64 address;
  6: required bf_error_type err_type;
  7: required bf_error_block err_blk;
  8: required bf_error_block_location err_loc;
  9: required string err_string;
}

struct clock_speed {
  1: i64 bps_clock_speed;
  2: i64 pps_clock_speed;
}

enum bf_port_speeds {
  BF_PORT_SPEED_NONE = 0,
  BF_PORT_SPEED_1G = 1,
  BF_PORT_SPEED_10G = 2,
  BF_PORT_SPEED_25G = 4,
  BF_PORT_SPEED_40G = 8,
  BF_PORT_SPEED_40G_NB = 16,
  BF_PORT_SPEED_50G = 32,
  BF_PORT_SPEED_100G = 64,
  BF_PORT_SPEED_200G = 128,
  BF_PORT_SPEED_400G = 256
}
enum bf_fec_types {
  BF_FEC_TYP_NONE = 0,
  BF_FEC_TYP_FIRECODE = 1,
  BF_FEC_TYP_FC = 1,
  BF_FEC_TYP_REED_SOLOMON = 2,
  BF_FEC_TYP_RS = 2
}

service devport_mgr {
    # Device Port APIs.
    void devport_mgr_add_port(1: i32 dev_id, 2: i32 port_id, 
                              3: i32 port_speeds, 4: i32 port_fec_types) throws (1:InvalidDevportMgrOperation ouch);
    void devport_mgr_add_port_with_lanes(1: i32 dev_id, 2: i32 port_id, 3: i32 port_speeds,
                              4: i32 port_lanes, 5: i32 port_fec_types) throws (1:InvalidDevportMgrOperation ouch);
    void devport_mgr_remove_port (1: i32 dev_id, 2: i32 port_id) throws (1:InvalidDevportMgrOperation ouch);
    i32 devport_mgr_port_ca_get(1: i32 dev_id, 2: i32 port_id) throws (1:InvalidDevportMgrOperation ouch);
    i32 devport_mgr_serdes_ca_get(1: i32 dev_id, 2: i32 port_id) throws (1:InvalidDevportMgrOperation ouch);
    void devport_mgr_set_copy_to_cpu (1: i32 dev_id, 2: byte enable, 3: i16 pport) throws (1:InvalidDevportMgrOperation ouch);
    i32 devport_mgr_pcie_cpu_port_get (1: i32 dev_id) throws (1:InvalidDevportMgrOperation ouch);
    i32 devport_mgr_eth_cpu_port_get (1: i32 dev_id) throws (1:InvalidDevportMgrOperation ouch);
    void devport_mgr_warm_init_begin (1: i32 dev_id, 2: dev_init_mode warm_init_mode, 3: dev_serdes_upgrade_mode serdes_upgrade_mode, 4:bool upgrade_agents) throws (1:InvalidDevportMgrOperation ouch);
    void devport_mgr_warm_init_end (1: i32 dev_id) throws (1:InvalidDevportMgrOperation ouch);
    i32 devport_mgr_get_parser_id(1: i32 dev_id, 2: i32 port_id) throws (1: InvalidDevportMgrOperation ouch);
    i32 devport_mgr_get_pipe_id(1: i32 dev_id, 2: i32 port_id) throws (1: InvalidDevportMgrOperation ouch);
    void devport_mgr_set_virtual_dev_slave_mode(1 : i32 dev_id) throws (1:InvalidDevportMgrOperation ouch);
    clock_speed devport_mgr_get_clock_speed(1: i32 dev_id) throws (1: InvalidDevportMgrOperation ouch);
    void devport_mgr_lrt_dr_timeout_set(1: i32 dev_id, 2: i32 timeout_ms) throws (1: InvalidDevportMgrOperation ouch);
    i32 devport_mgr_lrt_dr_timeout_get(1: i32 dev_id) throws (1: InvalidDevportMgrOperation ouch);
    void devport_mgr_register_for_error_events(1: i32 dev_id) throws (1: InvalidDevportMgrOperation ouch);
    list<error_event_record> devport_mgr_get_error_events(1: i32 dev_id)
}
