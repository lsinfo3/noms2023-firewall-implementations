
namespace py tm_api_rpc
namespace cpp tm_api_rpc
namespace c_glib tm_api_rpc

typedef i32 tm_dev_t
typedef i32 tm_pipe_t
typedef i32 tm_bf_status_t
typedef i32 tm_bf_dev_id_t
typedef i32 tm_cells_t
typedef i32 tm_limit_t
typedef i32 tm_q_t
typedef i32 tm_l1_node_t
typedef i32 tm_color_t
typedef i32 tm_pool_t
typedef i32 tm_ppg_baf_t
typedef i32 tm_q_baf_t
typedef i32 tm_q_color_limit_t
typedef i32 tm_flow_ctrl_t
typedef i32 tm_sched_prio_t
typedef i16 tm_icos_t
typedef i16 tm_pfc_prio_t
typedef i32 tm_ppg_t
typedef i32 tm_port_t
typedef i32 tm_port_speed_t




exception InvalidTmOperation {
  1:i32 code
}

struct tm_pfc_cos_map_t {
  1:  i32 CoS0_to_iCos,
  2:  i32 CoS1_to_iCos,
  3:  i32 CoS2_to_iCos,
  4:  i32 CoS3_to_iCos,
  5:  i32 CoS4_to_iCos,
  6:  i32 CoS5_to_iCos,
  7:  i32 CoS6_to_iCos,
  8:  i32 CoS7_to_iCos,
}

struct tm_q_map_t {
  1:  i32 md_qid0_to_tm_q,
  2:  i32 md_qid1_to_tm_q,
  3:  i32 md_qid2_to_tm_q,
  4:  i32 md_qid3_to_tm_q,
  5:  i32 md_qid4_to_tm_q,
  6:  i32 md_qid5_to_tm_q,
  7:  i32 md_qid6_to_tm_q,
  8:  i32 md_qid7_to_tm_q,
  9:  i32 md_qid8_to_tm_q,
  10:  i32 md_qid9_to_tm_q,
  11:  i32 md_qid10_to_tm_q,
  12:  i32 md_qid11_to_tm_q,
  13:  i32 md_qid12_to_tm_q,
  14:  i32 md_qid13_to_tm_q,
  15:  i32 md_qid14_to_tm_q,
  16:  i32 md_qid15_to_tm_q,
  17:  i32 md_qid16_to_tm_q,
  18:  i32 md_qid17_to_tm_q,
  19:  i32 md_qid18_to_tm_q,
  20:  i32 md_qid19_to_tm_q,
  21:  i32 md_qid20_to_tm_q,
  22:  i32 md_qid21_to_tm_q,
  23:  i32 md_qid22_to_tm_q,
  24:  i32 md_qid23_to_tm_q,
  25:  i32 md_qid24_to_tm_q,
  26:  i32 md_qid25_to_tm_q,
  27:  i32 md_qid26_to_tm_q,
  28:  i32 md_qid27_to_tm_q,
  29:  i32 md_qid28_to_tm_q,
  30:  i32 md_qid29_to_tm_q,
  31:  i32 md_qid30_to_tm_q,
  32:  i32 md_qid31_to_tm_q,
  33:  i32 q_count
}

struct tm_shaper_rate_t {
  1:  bool pps,
  2:  i32  burst_size,
  3:  i32  rate,
}

struct tm_pool_usage_t {
  1:  tm_pool_t  pool,
  2:  tm_limit_t base_use_limit,
  3:  tm_q_baf_t dynamic_baf,
  4:  tm_limit_t hysteresis
}

struct tm_ppg_usage_t {
  1:  i32 gmin_count,
  2:  i32 shared_count,
  3:  i32 skid_count,
  4:  i32 wm
}

struct tm_usage_t {
  1:  i32 count,
  2:  i32 wm
}

service tm {
    # ----------------- PPG APIs ----------------
    tm_ppg_t  tm_allocate_ppg(1:tm_dev_t dev, 2:tm_port_t  port) throws (1:InvalidTmOperation ouch);
    void      tm_free_ppg(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    tm_ppg_t  tm_get_default_ppg(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    void      tm_set_ppg_icos_mapping(1:tm_dev_t dev, 2:tm_ppg_t ppg, 3:tm_icos_t icos_map) throws (1:InvalidTmOperation ouch);
    void      tm_enable_lossless_treatment(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    void      tm_disable_lossless_treatment(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    void      tm_set_ppg_app_pool_usage(1:tm_dev_t dev, 2:tm_ppg_t ppg, 3:tm_pool_t pool, 4:tm_limit_t base_use_limit, 5:tm_ppg_baf_t dynamic_baf, 6:tm_limit_t hysteresis) throws (1:InvalidTmOperation ouch);
    void      tm_disable_ppg_app_pool_usage(1:tm_dev_t dev, 2:tm_pool_t pool, 3:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    void      tm_set_ppg_guaranteed_min_limit(1:tm_dev_t dev, 2:tm_ppg_t ppg, 3:tm_limit_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_ppg_skid_limit(1:tm_dev_t dev, 2:tm_ppg_t ppg, 3:tm_limit_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_guaranteed_min_skid_hysteresis(1:tm_dev_t dev, 2:tm_ppg_t ppg, 3:tm_limit_t cells) throws (1:InvalidTmOperation ouch);

    # ---------------   Q APIs -------------------
    void      tm_set_port_q_mapping(1:tm_dev_t dev, 2:tm_port_t port, 3:i16 q_count, 4:tm_q_map_t q_map) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_app_pool_usage(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_pool_t pool, 5:tm_limit_t base_use_limit, 6:tm_q_baf_t dynamic_baf, 7:tm_limit_t hysteresis) throws (1:InvalidTmOperation ouch);
    void      tm_disable_q_app_pool_usage(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_guaranteed_min_limit(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_limit_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_color_limit(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4: tm_color_t color, 5:tm_limit_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_color_hysteresis(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4: tm_color_t color, 5:tm_limit_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_enable_q_tail_drop(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_disable_q_tail_drop(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_enable_q_color_drop(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_disable_q_color_drop(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_set_negative_mirror_dest(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_port_t port, 4:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_pfc_cos_mapping(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_icos_t cos) throws (1:InvalidTmOperation ouch);

    # ----------------- Pool APIs ----------------
    void      tm_set_app_pool_size(1:tm_dev_t dev, 2:tm_pool_t pool, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_enable_app_pool_color_drop(1:tm_dev_t dev, 2:tm_pool_t pool) throws (1:InvalidTmOperation ouch);
    void      tm_disable_app_pool_color_drop(1:tm_dev_t dev, 2:tm_pool_t pool) throws (1:InvalidTmOperation ouch);
    void      tm_set_app_pool_color_drop_limit(1:tm_dev_t dev, 2:tm_pool_t pool, 3:tm_color_t color, 4:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_app_pool_color_drop_hysteresis(1:tm_dev_t dev, 2:tm_color_t color, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_app_pool_pfc_limit(1:tm_dev_t dev, 2:tm_pool_t pool, 3:tm_icos_t icos, 4:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_skid_pool_size(1:tm_dev_t dev, 2:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_skid_pool_hysteresis(1:tm_dev_t dev, 2:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_negative_mirror_pool_size(1:tm_dev_t dev, 2:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_uc_cut_through_pool_size(1:tm_dev_t dev, 2:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_mc_cut_through_pool_size(1:tm_dev_t dev, 2:tm_cells_t cells) throws (1:InvalidTmOperation ouch);

    # ----------------- Pipe APIs ----------------
    void      tm_set_egress_pipe_limit(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_egress_pipe_hysteresis(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);

    # ----------------- Port APIs ----------------
    void      tm_set_ingress_port_drop_limit(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_ingress_port_hysteresis(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_port_uc_cut_through_limit(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_cells_t cells) throws (1:InvalidTmOperation ouch);
    void      tm_set_port_flowcontrol_mode(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_flow_ctrl_t fctype) throws (1:InvalidTmOperation ouch);
    void      tm_set_port_pfc_cos_mapping(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_pfc_cos_map_t cos_icos_map) throws (1:InvalidTmOperation ouch);
    void      tm_set_cpuport(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    void      tm_reset_cpuport(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);

    # ----------------- SCH APIs ----------------
    void      tm_set_q_sched_priority(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_sched_prio_t prio) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_dwrr_weight(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:i16 weight) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:bool pps, 5:tm_limit_t burstsize, 6:tm_limit_t rate) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_guaranteed_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:bool pps, 5:tm_limit_t burstsize, 6:tm_limit_t rate) throws (1:InvalidTmOperation ouch);
    void      tm_set_q_remaining_bw_sched_priority(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_sched_prio_t prio) throws (1:InvalidTmOperation ouch);
    void      tm_sched_q_l1_set(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node, 4:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_sched_q_l1_reset(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_priority_set(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node, 4:tm_sched_prio_t priority) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_dwrr_weight_set(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node, 4:i16 weight) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_shaping_rate_set(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node, 4:bool pps, 5:i32 burst_size, 6:i32 rate) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_max_shaping_rate_enable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_max_shaping_rate_disable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_priority_prop_enable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_priority_prop_disable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_guaranteed_rate_set(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node, 4:bool pps, 5:i32 burst_size, 6:i32 rate) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_remaining_bw_priority_set(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node, 4:tm_sched_prio_t priority) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_guaranteed_rate_enable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_guaranteed_rate_disable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_enable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_disable(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_sched_l1_free(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_l1_node_t l1_node) throws (1:InvalidTmOperation ouch);
    void      tm_set_port_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:bool pps, 4:tm_limit_t burstsize, 5:tm_limit_t rate) throws (1:InvalidTmOperation ouch);
    void      tm_set_shaper_pkt_ifg_compensation(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:i16 adjustment) throws (1:InvalidTmOperation ouch);
    void      tm_enable_q_sched(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_disable_q_sched(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_enable_port_shaping(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    void      tm_disable_port_shaping(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    void      tm_enable_port_sched(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_port_speed_t speed) throws (1:InvalidTmOperation ouch);
    void      tm_disable_port_sched(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    void      tm_enable_q_max_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_disable_q_max_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_enable_q_min_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    void      tm_disable_q_min_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);

    # ----------------- misc APIs ----------------

    void      tm_complete_operations(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);
    void      tm_set_timestamp_shift(1:tm_dev_t dev, 2:i16 shift) throws (1:InvalidTmOperation ouch);

    # ----------------- Cfg Fetch APIs ----------------
    tm_sched_prio_t   tm_get_q_sched_priority(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    i16               tm_get_q_dwrr_weight(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_shaper_rate_t  tm_get_q_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_shaper_rate_t  tm_get_q_guaranteed_rate(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_sched_prio_t   tm_get_q_remaining_bw_sched_priority(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_shaper_rate_t  tm_get_port_shaping_rate(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    i16               tm_get_shaper_pkt_ifg_compensation(1:tm_dev_t dev, 2:tm_pipe_t pipe) throws (1:InvalidTmOperation ouch);

    tm_cells_t        tm_get_egress_pipe_limit(1:tm_dev_t dev, 2:tm_pipe_t pipe) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_egress_pipe_hysteresis(1:tm_dev_t dev, 2:tm_pipe_t pipe) throws (1:InvalidTmOperation ouch);
    tm_q_map_t        tm_get_port_q_mapping(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    tm_pool_usage_t   tm_get_q_app_pool_usage(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_q_guaranteed_min_limit(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_limit_t        tm_get_q_color_limit(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_color_t color) throws (1:InvalidTmOperation ouch);
    tm_limit_t        tm_get_q_color_hysteresis(1:tm_dev_t dev, 2:tm_port_t port, 3:tm_q_t q, 4:tm_color_t color) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_port_uc_cut_through_limit(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);

    i16               tm_get_total_ppg(1:tm_dev_t dev, 2:tm_pipe_t pipe) throws (1:InvalidTmOperation ouch);
    i16               tm_get_unused_ppg_count(1:tm_dev_t dev, 2:tm_pipe_t pipe) throws (1:InvalidTmOperation ouch);
    tm_pool_usage_t   tm_get_ppg_app_pool_usage(1:tm_dev_t dev, 2:tm_ppg_t ppg, 3:tm_pool_t pool) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_ppg_guaranteed_min_limit(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_ppg_skid_limit(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_ppg_guaranteed_min_skid_hysteresis(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_app_pool_size(1:tm_dev_t dev, 2:tm_pool_t pool) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_app_pool_color_drop_limit(1:tm_dev_t dev, 2:tm_pool_t pool, 3:tm_color_t color) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_app_pool_color_drop_hysteresis(1:tm_dev_t dev, 2:tm_color_t color) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_app_pool_pfc_limit(1:tm_dev_t dev, 2:tm_pool_t pool, 3:tm_icos_t icos) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_skid_pool_size(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_skid_pool_hysteresis(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_negative_mirror_pool_size(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_uc_cut_through_pool_size(1:tm_dev_t dev, 2:tm_pool_t pool) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_mc_cut_through_pool_size(1:tm_dev_t dev, 2:tm_pool_t pool) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_ingress_port_drop_limit(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    tm_cells_t        tm_get_ingress_port_hysteresis(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    tm_flow_ctrl_t    tm_get_port_flowcontrol_mode(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    tm_pfc_cos_map_t  tm_get_port_pfc_cos_mapping(1:tm_dev_t dev, 2:tm_port_t port) throws (1:InvalidTmOperation ouch);
    i16               tm_get_ppg_icos_mapping(1:tm_dev_t dev, 2:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    i16               tm_get_timestamp_shift(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);

    i64               tm_get_ppg_drop(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    i64               tm_get_q_drop(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_port_t port, 4:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_ppg_usage_t    tm_get_ppg_usage(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_ppg_t ppg) throws (1:InvalidTmOperation ouch);
    tm_usage_t        tm_get_q_usage(1:tm_dev_t dev, 2:tm_pipe_t pipe, 3:tm_port_t port, 4:tm_q_t q) throws (1:InvalidTmOperation ouch);
    tm_usage_t        tm_get_pool_usage(1:tm_dev_t dev, 2:tm_pool_t pool) throws (1:InvalidTmOperation ouch);

    # ----------------- Unit Test APIs ----------------
    void      tm_set_ut_mode_as_model(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);
    void      tm_set_ut_mode_as_asic(1:tm_dev_t dev) throws (1:InvalidTmOperation ouch);
}
