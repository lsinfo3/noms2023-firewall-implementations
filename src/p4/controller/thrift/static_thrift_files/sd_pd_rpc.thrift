include "res.thrift"

namespace py sd_pd_rpc
namespace cpp sd_pd_rpc
namespace c_glib sd_pd_rpc


typedef i32 bf_status_t
typedef i32 bf_dev_id_t
typedef i32 bf_dev_port_t

struct tx_eq_data {
  1: required i32 status;
  2: required i32 pre;
  3: required i32 atten;
  4: required i32 post;
}

struct bool_state {
  1: required i32 status;
  2: required bool st;
}

struct bool_value {
  1: required i32 status;
  2: required bool value;
}

struct i32_value {
  1: required i32 status;
  2: required i32 value;
}

struct lane_map {
  1: required i32 tx_l0;
  2: required i32 tx_l1;
  3: required i32 tx_l2;
  4: required i32 tx_l3;
  5: required i32 rx_l0;
  6: required i32 rx_l1;
  7: required i32 rx_l2;
  8: required i32 rx_l3;
  9: required i32 status;
}

struct pll_status {
  1: required i32 status;
  2: required bool locked;
  3: required i32 div;
  4: required i32 freq;
}

struct drv_attn {
  1: required i32 status;
  2: required i32 attn_main;
  3: required i32 attn_post;
  4: required i32 attn_pre;
}

struct drv_amp {
  1: required i32 status;
  2: required i32 amp_main;
  3: required i32 amp_post;
  4: required i32 amp_pre;
}

struct tx_drv_sts {
  1: required i32 status;
  2: required bool tx_en;
  3: required bool tx_drv_en;
  4: required bool tx_inv;
  5: required i32 amp_main;
  6: required i32 amp_post;
  7: required i32 amp_pre;
}

struct rx_los_cfg {
  1: required i32 status;
  2: required bool rx_los_en;
  3: required i32  rx_los_thres;
}

struct rx_eq_ctle {
  1: required i32 status;
  2: required i32 ctle_dc;
  3: required i32 ctle_lf;
  4: required i32 ctle_hf;
  5: required i32 ctle_bw;
}

struct dfe_tap {
  1: required i32 status;
  2: required i32 tap_num;
  3: required i32 tap_val;
}

struct dfe_taps {
  1: required i32 status;
  2: required i32 dfe_gain;
  3: required i32 tap1;
  4: required i32 tap2;
  5: required i32 tap3;
  6: required i32 tap4;
}

struct eq_cal_params {
  1: required i32 status;
  2: required i32 ctle_dc_hint;
  3: required i32 dfe_gain_range;
  4: required i32 pcal_loop_cnt;
} 

struct ical_result {
  1: required i32 status;
  2: required i32 cal_done;
  3: required i32 cal_good;
  4: required i32 cal_eye;
}

struct rx_eq_status {
  1: required i32 status;
  2: required bool  cal_done;     /**< 1: Completed. 0: In progress                   */
  3: required i32   cal_good;     /**< 1: Good Eye. 0: Poor Eye. -1: Bad Eye          */
  4: required i32   cal_eye;      /**< (mVppd) Eye height observed by cal algorithm   */
  5: required i32   ctle_dc;      /**< DC boost (0..255) */
  6: required i32   ctle_lf;      /**< Peaking filter low frequency gain (0..15) */
  7: required i32   ctle_hf;      /**< Peaking filter high frequency gain (0..15) */
  8: required i32   ctle_bw;      /**< Peaking filter peakign frequency (0..15) */
  9: required i32   dfe_taps_0; /**< Array of DFE Taps (each -127..127) */
  10: required i32  dfe_taps_1; /**< Array of DFE Taps (each -127..127) */
  11: required i32  dfe_taps_2; /**< Array of DFE Taps (each -127..127) */
  12: required i32  dfe_taps_3; /**< Array of DFE Taps (each -127..127) */
  13: required i32  dfe_taps_4; /**< Array of DFE Taps (each -127..127) */
  14: required i32  dfe_taps_5; /**< Array of DFE Taps (each -127..127) */
  15: required i32  dfe_taps_6; /**< Array of DFE Taps (each -127..127) */
  16: required i32  dfe_taps_7; /**< Array of DFE Taps (each -127..127) */
  17: required i32  dfe_taps_8; /**< Array of DFE Taps (each -127..127) */
  18: required i32  dfe_taps_9; /**< Array of DFE Taps (each -127..127) */
  19: required i32  dfe_taps_10; /**< Array of DFE Taps (each -127..127) */
  20: required i32  dfe_taps_11; /**< Array of DFE Taps (each -127..127) */
  21: required i32  dfe_taps_12; /**< Array of DFE Taps (each -127..127) */
  22: required i32  dfe_taps_13; /**< Array of DFE Taps (each -127..127) */
  23: required i32  dfe_taps_14; /**< Array of DFE Taps (each -127..127) */
  24: required i32  dfe_taps_15; /**< Array of DFE Taps (each -127..127) */
  25: required i32  dfe_taps_16; /**< Array of DFE Taps (each -127..127) */
}

struct tx_fixed_pat {
  1: required i32 status;
  2: required i32 tx_fixed_pat_0;
  3: required i32 tx_fixed_pat_1;
  4: required i32 tx_fixed_pat_2;
  5: required i32 tx_fixed_pat_3;
}

struct rx_cap_pat {
  1: required i32 status;
  2: required i32 rx_cap_pat_0;
  3: required i32 rx_cap_pat_1;
  4: required i32 rx_cap_pat_2;
  5: required i32 rx_cap_pat_3;
}


exception InvalidSdOperation {
  1:i32 code
}

service sd {
    bf_status_t sd_mgmt_clksel_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 clk_src) throws (1:InvalidSdOperation ouch);
    i32_value   sd_mgmt_clksel_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_mgmt_access_method_set(1: bf_dev_id_t dev_id, 2: i32 method) throws (1:InvalidSdOperation ouch);
    i32_value   sd_mgmt_access_method_get(1: bf_dev_id_t dev_id) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_mgmt_bcast_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_dir, 5: bool en) throws (1:InvalidSdOperation ouch);
    bool_value  sd_mgmt_bcast_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_dir) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_mgmt_reg_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_dir, 5: i32 reg, 6: i32 data) throws (1:InvalidSdOperation ouch);
    i32_value   sd_mgmt_reg_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_dir, 5: i32 reg) throws (1:InvalidSdOperation ouch);
    i32_value   sd_mgmt_uc_int(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_dir, 5: i32 interrupt, 6: i32 int_data);
    bf_status_t sd_port_lane_map_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 tx_l0, 4: i32 tx_l1, 5: i32 tx_l2, 6: i32 tx_l3, 7: i32 rx_l0, 8: i32 rx_l1, 9: i32 rx_l2, 10: i32 rx_l3);
    lane_map    sd_port_lane_map_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_dev_rx_eq_cal_rr_set(1: bf_dev_id_t dev_id, 2: i32 fine_tune_lane_cnt) throws (1:InvalidSdOperation ouch);
    i32_value   sd_dev_rx_eq_cal_rr_get(1: bf_dev_id_t dev_id) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_tx_pll_clksel_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 clk_source) throws (1:InvalidSdOperation ouch);
    i32_value   sd_tx_pll_clksel_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_lane_init_run(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 line_rate, 5: bool init_rx, 6: bool init_tx, 7: bool tx_drv_en, 8: bool phase_cal);
    bool_value  sd_tx_pll_lock_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bool_value  sd_rx_cdr_lock_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    pll_status  sd_tx_pll_status_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    pll_status  sd_rx_cdr_status_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_lane_loopback_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 loopback_mode) throws (1:InvalidSdOperation ouch);
    i32_value   sd_lane_loopback_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_tx_en_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_en) throws (1:InvalidSdOperation ouch);
    bool_value  sd_tx_en_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_tx_drv_en_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool tx_en) throws (1:InvalidSdOperation ouch);
    bool_value  sd_tx_drv_en_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_tx_drv_inv_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool inv) throws (1:InvalidSdOperation ouch);
    bool_value  sd_tx_drv_inv_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_tx_drv_attn_is_valid(1: i32 attn_main, 2: i32 attn_post, 3: i32 attn_pre); 
    bf_status_t sd_tx_drv_attn_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 attn_main, 5: i32 attn_post, 6: i32 attn_pre); 
    drv_attn    sd_tx_drv_attn_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_tx_drv_amp_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 amp_main, 5: i32 amp_post, 6: i32 amp_pre); 
    drv_amp     sd_tx_drv_amp_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    tx_drv_sts  sd_tx_drv_status_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);

    bf_status_t sd_rx_en_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool rx_en) throws (1:InvalidSdOperation ouch);
    bool_value  sd_rx_en_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_rx_afe_inv_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool inv_en) throws (1:InvalidSdOperation ouch);
    bool_value  sd_rx_afe_inv_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_rx_afe_term_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 rx_term) throws (1:InvalidSdOperation ouch);
    i32_value   sd_rx_afe_term_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_rx_afe_los_thres_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: bool rx_los_en, 5: i32 rx_los_thres) throws (1:InvalidSdOperation ouch);
    rx_los_cfg  sd_rx_afe_los_thres_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bool_value  sd_rx_afe_los_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bool_value  sd_rx_eq_cal_busy_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 chk_cnt, 5: i32 chk_wait);
    bf_status_t sd_rx_eq_ctle_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 ctle_dc, 5: i32 ctle_lf, 6: i32 ctle_hf, 7: i32 ctle_bw);
    rx_eq_ctle  sd_rx_eq_ctle_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_rx_eq_dfe_adv_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 dfe_tap_num, 5: i32 dfe_tap_val);
    i32_value   sd_rx_eq_dfe_adv_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 dfe_tap_num);
    bf_status_t sd_rx_eq_dfe_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 dfe_gain, 5: i32 dfe_tap1, 6: i32 dfe_tap2, 7: i32 dfe_tap3, 8: i32 dfe_tap4);
    dfe_taps    sd_rx_eq_dfe_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_rx_eq_cal_param_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 ctle_dc_hint, 5: i32 dfe_gain_range, 6: i32 pcal_loop_cnt);
    eq_cal_params sd_rx_eq_cal_param_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_rx_eq_cal_adv_run(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 cal_cmd, 5: i32 ctle_cal_cfg, 6: i32 dfe_fixed);
    i32_value   sd_rx_eq_cal_eye_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane)
    bf_status_t sd_rx_eq_ical_run(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    ical_result sd_rx_eq_ical_eye_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 cal_good_thres);
    bf_status_t sd_rx_eq_pcal_run(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 cal_cont);
    rx_eq_status sd_rx_eq_status_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_rx_eye_offset_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 offset_en, 5: i32 pos_x, 6: i32 pos_y);
    i32_value   sd_rx_eye_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 meas_mode, 5: i32 meas_ber);
    i32_value   sd_rx_eye_3d_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 meas_ber);
    bf_status_t sd_tx_err_inj_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 num_bits);
    bf_status_t sd_rx_err_inj_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 num_bits);
    bf_status_t sd_tx_patsel_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 tx_patsel);
    i32_value   sd_tx_patsel_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_rx_patsel_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 rx_patsel);
    i32_value   sd_rx_patsel_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    i32_value   sd_rx_err_cnt_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    bf_status_t sd_tx_fixed_pat_set(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 tx_fixed_pat_0, 5: i32 tx_fixed_pat_1, 6: i32 tx_fixed_pat_2, 7: i32 tx_fixed_pat_3);
    tx_fixed_pat sd_tx_fixed_pat_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);
    rx_cap_pat  sd_rx_data_cap_get(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane);





 
    tx_eq_data  sd_get_tx_eq(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_set_tx_eq(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 pre, 5: i32 atten, 6: i32 post) throws (1:InvalidSdOperation ouch);
    bf_status_t sd_get_pll_state(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane, 4: i32 expected_divider) throws (1:InvalidSdOperation ouch);
    bool_state  sd_get_tx_output_en(1: bf_dev_id_t dev_id, 2: bf_dev_port_t dev_port, 3: i32 lane) throws (1:InvalidSdOperation ouch);
}
