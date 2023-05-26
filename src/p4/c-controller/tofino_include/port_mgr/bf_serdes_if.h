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

#ifndef BF_SERDES_IF_H_INCLUDED
#define BF_SERDES_IF_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
//  Enumerated Types
//----------------------------------------------------------------------------

/** \brief   Enumeration of supported Tofino serdes access modes.
 */
typedef enum {
  BF_SDS_ACCESS_SBUS = 0,
  BF_SDS_ACCESS_CORE,
} bf_serdes_access_method_e;

/** \brief SerDes Line Rates
 */
typedef enum {
  BF_SDS_LINE_RATE_1p25G = 0, /**<  1.25Gbps     */
  BF_SDS_LINE_RATE_2p5G = 1,  /**<  2.5Gbps      */
  BF_SDS_LINE_RATE_10G = 2,   /**< 10.3125Gbps   */
  BF_SDS_LINE_RATE_25G = 3,   /**< 25.78Gbps     */
} bf_sds_line_rate_mode_t;

/** \brief SerDes Loopback Modes
 */
typedef enum {
  BF_SDS_LB_OFF = 0,          /**< Normal Operation, no loopback */
  BF_SDS_LB_SER_TX_TO_RX = 1, /**< Serial TX to RX near end loopback */
  BF_SDS_LB_PAR_RX_TO_TX = 2, /**< Parallel RX to TX far end loopback */
} bf_sds_loopback_t;

/** \brief TX PLL REFCLK Source
 */
typedef enum {
  BF_SDS_TX_PLL_ETH_REFCLK = 0, /**< Source from external ETH_REFCLK */
  BF_SDS_TX_PLL_ALT_REFCLK = 1, /**< Source from external ALT_REFCLK */
  BF_SDS_TX_PLL_RXCLK = 2,      /**< Source from RX Recovered clock */
  BF_SDS_TX_PLL_OFF = 3,        /**< Debug Only. Tie clock input to GND */
  BF_SDS_TX_PLL_PCIECLK = 4,    /**< Debug Only. Source from PCIe clock */
} bf_sds_tx_pll_clksel_t;

/** \brief Management Logic Clock Source
 */
typedef enum {
  BF_SDS_MGMT_CLK_REFCLK = 0,       /**< Source from external REFCLK */
  BF_SDS_MGMT_CLK_REFCLK_DIV2 = 1,  /**< Debug Only. REFCLK/2 */
  BF_SDS_MGMT_CLK_PCIECLK = 2,      /**< Source from external PCIE CLK */
  BF_SDS_MGMT_CLK_PCIECLK_DIV2 = 3, /**< Debug Only. PCIE CLK/2 */
} bf_sds_mgmt_clk_clksel_t;

/** \brief RX Termination Mode
 */
typedef enum {
  BF_SDS_RX_TERM_GND = 0,   /**< Terminate 50 Ohm to GND */
  BF_SDS_RX_TERM_AVDD = 1,  /**< Terminate 50 Ohm to AVDD */
  BF_SDS_RX_TERM_FLOAT = 2, /**< Terminate 100 Ohm between P/N */
} bf_sds_rx_term_t;

/** \brief RX EQ Calibration Command
 */
typedef enum {
  BF_SDS_RX_ICAL_PCAL = 0,       /**< Run iCal follow by pCal_once */
  BF_SDS_RX_ICAL_NO_PCAL = 1,    /**< (Debug) Run iCal without pCal */
  BF_SDS_RX_PCAL_ONCE = 2,       /**< Run pCal once */
  BF_SDS_RX_PCAL_CONT_START = 3, /**< Start pCal continuous mode */
  BF_SDS_RX_PCAL_CONT_STOP = 4,  /**< Stop  pCal */
  BF_SDS_RX_PCAL_RR_DISABLE = 5, /**< Disable Round Robin participation */
  BF_SDS_RX_PCAL_RR_ENABLE = 6,  /**< Enable  Round robin participation */
  BF_SDS_RX_CAL_SLICER_ONLY = 7, /**< Run slicer cal only */
} bf_sds_rx_cal_mode_t;

/** \brief RX Eye Measurement Mode
 */
typedef enum {
  BF_SDS_RX_EYE_MEAS_HEIGHT = 0, /**< Measure Eye Height */
  BF_SDS_RX_EYE_MEAS_WIDTH = 1,  /**< Measure Eye Width */
} bf_sds_rx_eye_meas_mode_t;

/** \brief RX Eye Measurement BER
 */
typedef enum {
  BF_SDS_RX_EYE_BER_1E6 = 0, /**< Receive 3e6 bits with up to 1 error */
  BF_SDS_RX_EYE_BER_1E9 = 1, /**< Receive 3e9 bits with up to 1 error */
} bf_sds_rx_eye_meas_ber_t;

/** \brief Pattern Generator/Checker Pattern Select
 */
typedef enum {
  BF_SDS_PAT_PATSEL_OFF = 0,    /**< Select Core Data */
  BF_SDS_PAT_PATSEL_PRBS7 = 1,  /**< Select PRBS-7   Pattern */
  BF_SDS_PAT_PATSEL_PRBS9 = 2,  /**< Select PRBS-9   Pattern */
  BF_SDS_PAT_PATSEL_PRBS11 = 3, /**< Select PRBS-11  Pattern */
  BF_SDS_PAT_PATSEL_PRBS15 = 4, /**< Select PRBS-15  Pattern */
  BF_SDS_PAT_PATSEL_PRBS23 = 5, /**< Select PRBS-23  Pattern */
  BF_SDS_PAT_PATSEL_PRBS31 = 6, /**< Select PRBS-31  Pattern */
  BF_SDS_PAT_PATSEL_FIXED = 7,  /**< Select 80b Fixed Pattern */
} bf_sds_pat_patsel_t;

/** \brief INT 0x2B bit 15 defs
 */
typedef enum {
  BF_SDS_RR_PCAL_DISABLE = 0,
  BF_SDS_RR_PCAL_ENABLE = 1,
} bf_sds_rr_pcal_mode_t;

/** \brief PMRO temperature sensor channel defs
 */
typedef enum {
  BF_SDS_MAIN_TEMP_SENSOR_CH = 0,
  BF_SDS_REMOTE_TEMP_SENSOR_0_CH,
} bf_sds_temp_sensor_channel_t;

/** \brief PMRO voltage sensor channel defs
 */
typedef enum {
  BF_SDS_MAIN_VOLT_SENSOR_CH = 0,
  BF_SDS_REMOTE_VOLT_SENSOR_0_CH,
} bf_sds_voltage_sensor_channel_t;

/** \brief Serdes reset types
 */
typedef enum {
  BF_SDS_RESET_NODE = 0,
  BF_SDS_RESET_MICROPROCESSOR,
  BF_SDS_RESET_NODE_AND_MICROPROCESSOR,
} bf_sds_reset_type_t;

/** \brief Tofino-specific Serdes DFE control
 * Used to customize DFE step of bring-up FSM
 */
typedef enum {
  BF_SDS_TOF_DFE_CTRL_DEFAULT = 0,
  BF_SDS_TOF_DFE_CTRL_ICAL = BF_SDS_TOF_DFE_CTRL_DEFAULT,
  BF_SDS_TOF_DFE_CTRL_PCAL = 0x0001,
  BF_SDS_TOF_DFE_CTRL_SEEDED_HF = 0x0002,
  BF_SDS_TOF_DFE_CTRL_SEEDED_LF = 0x0004,
  BF_SDS_TOF_DFE_CTRL_SEEDED_DC = 0x0008,
  BF_SDS_TOF_DFE_CTRL_FIXED_HF = 0x0010,
  BF_SDS_TOF_DFE_CTRL_FIXED_LF = 0x0020,
  BF_SDS_TOF_DFE_CTRL_FIXED_DC = 0x0040,
} bf_sds_tof_dfe_ctrl_t;

/** \brief Tofino-specific loopbandwidth settings
 * Only the below values have been tested by Barefoot
 * Any other setting may be used but Barefoot cannot
 * guarantee proper operation.
 */
typedef enum {
  BF_SDS_TOF_TX_LOOP_BANDWIDTH_DEFAULT = 0,
  BF_SDS_TOF_TX_LOOP_BANDWIDTH_1MHZ = 0x503,
  BF_SDS_TOF_TX_LOOP_BANDWIDTH_3MHZ = 0x511,
  BF_SDS_TOF_TX_LOOP_BANDWIDTH_9MHZ = 0x51b,
  BF_SDS_TOF_TX_LOOP_BANDWIDTH_A0_DEFAULT = BF_SDS_TOF_TX_LOOP_BANDWIDTH_3MHZ,
  BF_SDS_TOF_TX_LOOP_BANDWIDTH_B0_DEFAULT = BF_SDS_TOF_TX_LOOP_BANDWIDTH_1MHZ,
} bf_sds_tof_tx_loop_bandwidth_t;

//----------------------------------------------------------------------------
//  Structure Types
//----------------------------------------------------------------------------

/** \brief Lane Status
 */
typedef struct {
  bf_sds_line_rate_mode_t line_rate; /**< Configured line rate mode */
  bool tx_en;         /**< 1: TX path enabled.                0: Disabled */
  bool tx_drv_en;     /**< 1: TX output enabled.              0: Disabled */
  bool tx_pll_lock;   /**< 1: TX PLL locked.                  0: Unlocked */
  bool rx_pll_lock;   /**< 1: RX PLL locked.                  0: Unlocked */
  bool rx_sigdet;     /**< 1: RX signal detected              0: No signal */
  bool kr_en;         /**< 1: KR mode enabled.                0: Disabled */
  bool kr_lt_success; /**< 1: KR link training successful.    0: Failed */
  bool kr_an_success; /**< 1: KR auto negotiation successful. 0: Failed */
  int rx_eye_adp;     /**< Eye height reported by adaptation engine */
} bf_sds_lane_status_t;

/** \brief TX Driver Status
 */
typedef struct {
  bool tx_en;     /**< 1: TX path enabled.            0: Disabled */
  bool tx_drv_en; /**< 1: TX output enabled.          0: Disabled */
  bool tx_inv;    /**< 1: invert P/N.                 0: no inversion */
  int amp_main;   /**< Main-cursor amplitude  */
  int amp_post;   /**< Post-cursor amplitude  */
  int amp_pre;    /**< Pre-cursor  amplitude  */
} bf_sds_tx_drv_status_t;

/** \brief RX EQ Status
 */
typedef struct {
  bool cal_done;    /**< 1: Completed. 0: In progress                   */
  bool cal_good;    /**< 1: Good Eye. 0: Poor Eye. -1: Bad Eye          */
  int cal_eye;      /**< (mVppd) Eye height observed by cal algorithm   */
  int ctle_dc;      /**< DC boost (0..255) */
  int ctle_lf;      /**< Peaking filter low frequency gain (0..15) */
  int ctle_hf;      /**< Peaking filter high frequency gain (0..15) */
  int ctle_bw;      /**< Peaking filter peakign frequency (0..15) */
  int dfe_taps[16]; /**< Array of DFE Taps (each -127..127) */
} bf_sds_rx_eq_status_t;

typedef struct {
  uint32_t tx_phy_lane_id;
  uint32_t rx_phy_lane_id;
  bool tx_phy_pn_swap;
  bool rx_phy_pn_swap;
  uint32_t tx_attn;
  uint32_t tx_pre;
  uint32_t tx_post;
} bf_sds_lane_info_t;

//----------------------------------------------------------------------------
//   Function Declaration
//----------------------------------------------------------------------------
bf_status_t bf_serdes_lane_info_set(bf_dev_id_t dev_id,
                                    bf_mac_block_id_t mac_block,
                                    uint32_t tx_chnl,
                                    uint32_t rx_chnl,
                                    bf_sds_lane_info_t *lane_info);

bf_status_t bf_serdes_mgmt_clksel_set(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bf_sds_mgmt_clk_clksel_t clk_src);

bf_status_t bf_serdes_mgmt_clksel_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bf_sds_mgmt_clk_clksel_t *clk_src);

bf_status_t bf_serdes_mgmt_access_method_set(bf_dev_id_t dev_id,
                                             bf_serdes_access_method_e method);

bf_status_t bf_serdes_mgmt_access_method_get(bf_dev_id_t dev_id,
                                             bf_serdes_access_method_e *method);

bf_status_t bf_serdes_mgmt_bcast_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool tx_dir,
                                     bool bcast_en);

bf_status_t bf_serdes_mgmt_bcast_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool tx_dir,
                                     bool *bcast_en);

bf_status_t bf_serdes_mgmt_reg_set(bf_dev_id_t dev_id,
                                   bf_dev_port_t dev_port,
                                   int lane,
                                   bool tx_dir,
                                   int reg,
                                   uint32_t data);

bf_status_t bf_serdes_mgmt_reg_get(bf_dev_id_t dev_id,
                                   bf_dev_port_t dev_port,
                                   int lane,
                                   bool tx_dir,
                                   int reg,
                                   uint32_t *data);

bf_status_t bf_serdes_mgmt_uc_int(bf_dev_id_t dev_id,
                                  bf_dev_port_t dev_port,
                                  int lane,
                                  bool tx_dir,
                                  int interrupt,
                                  uint32_t int_data,
                                  uint32_t *rtn_data);

bf_status_t bf_port_tof1_lane_map_set(bf_dev_id_t dev_id,
                                      bf_mac_block_id_t mac_block,
                                      bf_mac_block_lane_map_t *lane_map);

bf_status_t bf_port_lane_map_get(bf_dev_id_t dev_id,
                                 bf_mac_block_id_t mac_block,
                                 bf_mac_block_lane_map_t *lane_map);

bf_status_t bf_dev_rx_eq_cal_rr_set(bf_dev_id_t dev_id, int fine_tune_lane_cnt);

bf_status_t bf_dev_rx_eq_cal_rr_get(bf_dev_id_t dev_id,
                                    int *fine_tune_lane_cnt);

bf_status_t bf_serdes_tx_pll_clksel_set(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bf_sds_tx_pll_clksel_t clk_source);

bf_status_t bf_serdes_tx_pll_clksel_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bf_sds_tx_pll_clksel_t *clk_source);

bf_status_t bf_serdes_lane_init_run(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bf_sds_line_rate_mode_t line_rate,
                                    bool init_rx,
                                    bool init_tx,
                                    bool tx_drv_en,
                                    bool phase_cal);

bf_status_t bf_serdes_tx_pll_lock_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bool *locked);

bf_status_t bf_serdes_rx_cdr_lock_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bool *locked);

bf_status_t bf_serdes_rx_and_tx_lock_get(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         int lane,
                                         bool *rx_locked,
                                         bool *tx_locked);

bf_status_t bf_serdes_tx_pll_status_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bool *locked,
                                        int *div,
                                        int *freq);

bf_status_t bf_serdes_rx_cdr_status_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bool *locked,
                                        int *div,
                                        int *freq);

bf_status_t bf_serdes_lane_loopback_set(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bf_sds_loopback_t loopback_mode);

bf_status_t bf_serdes_lane_loopback_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bf_sds_loopback_t *loopback_mode);

bf_status_t bf_serdes_lane_status_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bf_sds_lane_status_t *lane_status);

bf_status_t bf_serdes_tx_en_set(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                bool tx_en);

bf_status_t bf_serdes_tx_en_get(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                bool *tx_en);

bf_status_t bf_serdes_tx_drv_en_set(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool tx_drv_en);

bf_status_t bf_serdes_tx_drv_en_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool *tx_drv_en);

bf_status_t bf_serdes_tx_drv_inv_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool tx_inv);
bf_status_t bf_serdes_tx_drv_inv_set_allow_unassigned(bf_dev_id_t dev_id,
                                                      bf_dev_port_t dev_port,
                                                      int lane,
                                                      bool tx_inv);

bf_status_t bf_serdes_tx_drv_inv_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool *tx_inv);

bf_status_t bf_serdes_tx_drv_attn_is_valid(int attn_main,
                                           int attn_post,
                                           int attn_pre);

bf_status_t bf_serdes_tx_drv_attn_set(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int attn_main,
                                      int attn_post,
                                      int attn_pre);
bf_status_t bf_serdes_tx_drv_attn_set_allow_unassigned(bf_dev_id_t dev_id,
                                                       bf_dev_port_t dev_port,
                                                       int lane,
                                                       int attn_main,
                                                       int attn_post,
                                                       int attn_pre);

bf_status_t bf_serdes_tx_drv_attn_set_allow_unassigned(bf_dev_id_t dev_id,
                                                       bf_dev_port_t dev_port,
                                                       int lane,
                                                       int attn_main,
                                                       int attn_post,
                                                       int attn_pre);

bf_status_t bf_serdes_tx_drv_attn_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int *attn_main,
                                      int *attn_post,
                                      int *attn_pre);

bf_status_t bf_serdes_tx_drv_attn_get_allow_unassigned(bf_dev_id_t dev_id,
                                                       bf_dev_port_t dev_port,
                                                       int lane,
                                                       int *attn_main,
                                                       int *attn_post,
                                                       int *attn_pre);

bf_status_t bf_serdes_tx_drv_amp_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int amp_main,
                                     int amp_post,
                                     int amp_pre);

bf_status_t bf_serdes_tx_drv_amp_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int *amp_main,
                                     int *amp_post,
                                     int *amp_pre);

bf_status_t bf_serdes_tx_drv_status_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bf_sds_tx_drv_status_t *tx_status);

bf_status_t bf_serdes_rx_en_set(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                bool rx_en);

bf_status_t bf_serdes_rx_en_get(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                bool *rx_en);

bf_status_t bf_serdes_rx_afe_inv_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool rx_inv);

bf_status_t bf_serdes_rx_afe_inv_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool *rx_inv);

bf_status_t bf_serdes_rx_afe_term_set(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bf_sds_rx_term_t rx_term);

bf_status_t bf_serdes_rx_afe_term_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bf_sds_rx_term_t *rx_term);

bf_status_t bf_serdes_rx_afe_los_thres_set(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           bool rx_los_en,
                                           int rx_los_thres);

bf_status_t bf_serdes_rx_afe_los_thres_get(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           bool *rx_los_en,
                                           int *rx_los_thres);

bf_status_t bf_serdes_rx_afe_los_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool *rx_los);

bf_status_t bf_serdes_rx_eq_param_set(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int row,
                                      int col,
                                      int value);

bf_status_t bf_serdes_rx_eq_param_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int row,
                                      int col,
                                      int *value);

bf_status_t bf_serdes_rx_eq_cal_busy_get(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         int lane,
                                         int chk_cnt,
                                         int chk_wait,
                                         bool *uc_busy);

bf_status_t bf_serdes_rx_eq_ctle_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int ctle_dc,
                                     int ctle_lf,
                                     int ctle_hf,
                                     int ctle_bw);

bf_status_t bf_serdes_rx_eq_ctle_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int *ctle_dc,
                                     int *ctle_lf,
                                     int *ctle_hf,
                                     int *ctle_bw);

bf_status_t bf_serdes_rx_eq_dfe_adv_set(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        int dfe_tap_num,
                                        int dfe_tap_val);

bf_status_t bf_serdes_rx_eq_dfe_adv_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        int dfe_tap_num,
                                        int *dfe_tap_val);

bf_status_t bf_serdes_rx_eq_dfe_set(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    int dfe_gain,
                                    int dfe_tap[4]);

bf_status_t bf_serdes_rx_eq_dfe_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    int *dfe_gain,
                                    int dfe_taps[4]);

bf_status_t bf_serdes_rx_eq_cal_param_set(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          int lane,
                                          int ctle_dc_hint,
                                          int dfe_gain_range,
                                          int pcal_loop_cnt);

bf_status_t bf_serdes_rx_eq_cal_param_get(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          int lane,
                                          int *ctle_dc_hint,
                                          int *dfe_gain_range,
                                          int *pcal_loop_cnt);

bf_status_t bf_serdes_rx_eq_cal_adv_run(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bf_sds_rx_cal_mode_t cal_cmd,
                                        int ctle_cal_cfg,
                                        int dfe_fixed);

bf_status_t bf_serdes_rx_eq_ical_run(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane);

bf_status_t bf_serdes_rx_eq_cal_eye_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        int *cal_eye);

bf_status_t bf_serdes_rx_eq_ical_eye_get(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         int lane,
                                         int cal_good_thres,
                                         bool *cal_done,
                                         bool *cal_good,
                                         int *cal_eye);

bf_status_t bf_serdes_rx_eq_pcal_run(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int cal_cont);

bf_status_t bf_serdes_rx_eq_status_get(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int lane,
                                       bf_sds_rx_eq_status_t *rx_status);

bf_status_t bf_serdes_rx_eye_offset_set(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        int offset_en,
                                        int pos_x,
                                        int pos_y);

bf_status_t bf_serdes_rx_eye_get(bf_dev_id_t dev_id,
                                 bf_dev_port_t dev_port,
                                 int lane,
                                 bf_sds_rx_eye_meas_mode_t meas_mode,
                                 bf_sds_rx_eye_meas_ber_t meas_ber,
                                 int *meas_eye);

bf_status_t bf_serdes_rx_eye_3d_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bf_sds_rx_eye_meas_ber_t meas_ber,
                                    char *eye_plot_data,
                                    int max_eye_plot_data);

bf_status_t bf_serdes_rx_eye_3d_save(int *meas_data, int *file_loc);

bf_status_t bf_serdes_tx_err_inj_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int num_bits);

bf_status_t bf_serdes_rx_err_inj_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int num_bits);

bf_status_t bf_serdes_tx_patsel_set(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bf_sds_pat_patsel_t tx_patsel);

bf_status_t bf_serdes_tx_patsel_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bf_sds_pat_patsel_t *tx_patsel);

bf_status_t bf_serdes_tx_fixed_pat_set(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int lane,
                                       int tx_fixed_pat[4]);

bf_status_t bf_serdes_tx_fixed_pat_get(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int lane,
                                       int tx_fixed_pat[4]);

bf_status_t bf_serdes_rx_patsel_set(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bf_sds_pat_patsel_t rx_patsel);

bf_status_t bf_serdes_rx_patsel_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bf_sds_pat_patsel_t *rx_patsel);

bf_status_t bf_serdes_rx_data_cap_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int rx_cap_pat[4]);

bf_status_t bf_serdes_rx_err_cnt_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     uint32_t *rx_err_cnt);

bf_status_t bf_serdes_get_tx_eq(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                int *pre,
                                int *atten,
                                int *post);
bf_status_t bf_serdes_set_tx_eq(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                int pre,
                                int atten,
                                int post);
bf_status_t bf_serdes_get_pll_state(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    int expected_divider);
bf_status_t bf_serdes_get_tx_output_en(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int lane,
                                       bool *en);
bf_status_t bf_serdes_set_tx_output_en(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int lane,
                                       bool en);
bf_status_t bf_serdes_set_rx_tx_and_tx_output_en(bf_dev_id_t dev_id,
                                                 bf_dev_port_t dev_port,
                                                 int lane,
                                                 bool rx_en,
                                                 bool tx_en,
                                                 bool tx_output_en);
bf_status_t bf_serdes_set_rx_tx_and_tx_output_en_allow_unassigned(
    bf_dev_id_t dev_id,
    bf_dev_port_t dev_port,
    int lane,
    bool rx_en,
    bool tx_en,
    bool tx_output_en);
bf_status_t bf_serdes_get_signal_ok_thresh(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           int *thresh);
bf_status_t bf_serdes_set_signal_ok_thresh(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           int thresh);
bf_status_t bf_serdes_get_signal_ok(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool *sig_ok);
bf_status_t bf_serdes_get_los(bf_dev_id_t dev_id,
                              bf_dev_port_t dev_port,
                              int lane,
                              bool *los);
bf_status_t bf_serdes_start_dfe_ical(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane);
bf_status_t bf_serdes_start_dfe_ical_allow_unassigned(bf_dev_id_t dev_id,
                                                      bf_dev_port_t dev_port,
                                                      int lane);
bf_status_t bf_serdes_start_dfe_pcal(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane);
bf_status_t bf_serdes_start_dfe_pi_cal(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int lane);
bf_status_t bf_serdes_start_dfe_adaptive(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         int lane);
bf_status_t bf_serdes_stop_dfe_adaptive(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane);
bf_status_t bf_serdes_stop_dfe(bf_dev_id_t dev_id,
                               bf_dev_port_t dev_port,
                               int lane);
bf_status_t bf_serdes_get_dfe_running(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      bool *dfe_running);
bf_status_t bf_serdes_get_tx_invert(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool *inv);
bf_status_t bf_serdes_set_tx_invert(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool inv);
bf_status_t bf_serdes_get_rx_invert(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool *inv);
bf_status_t bf_serdes_set_rx_invert(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool inv);
bf_status_t bf_serdes_set_tx_inject_error(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          int lane,
                                          int num_bits);
bf_status_t bf_serdes_set_rx_inject_error(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          int lane,
                                          int num_bits);
bf_status_t bf_serdes_get_tx_pll_clk_source(bf_dev_id_t dev_id,
                                            bf_dev_port_t dev_port,
                                            int lane,
                                            int *clk);
bf_status_t bf_serdes_set_tx_pll_clk_source(bf_dev_id_t dev_id,
                                            bf_dev_port_t dev_port,
                                            int lane,
                                            int clk);
bf_status_t bf_serdes_get_spico_clk_source(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           int *clk);
bf_status_t bf_serdes_set_spico_clk_source(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           int clk);
bf_status_t bf_serdes_set_dfe_param(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    int row,
                                    int col,
                                    int value);
bf_status_t bf_serdes_init(bf_dev_id_t dev_id,
                           bf_dev_port_t dev_port,
                           int lane,
                           int reset,
                           int init_mode,
                           int divider,
                           int data_width,
                           int phase_cal,
                           int output_en);

bf_status_t bf_serdes_params_an_set(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool do_tx_eq);
bf_status_t bf_serdes_params_set(bf_dev_id_t dev_id,
                                 bf_dev_port_t dev_port,
                                 int lane);
bf_status_t bf_serdes_get_tx_data_sel(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int *data_sel);
bf_status_t bf_serdes_set_tx_data_sel(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int data_sel);
bf_status_t bf_serdes_get_rx_cmp_sel(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int *cmp_sel);
bf_status_t bf_serdes_set_rx_cmp_sel(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int cmp_sel);
bf_status_t bf_serdes_get_rx_cmp_mode(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int *cmp_mode);
bf_status_t bf_serdes_set_rx_cmp_mode(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int cmp_mode);
bf_status_t bf_serdes_get_rx_term(bf_dev_id_t dev_id,
                                  bf_dev_port_t dev_port,
                                  int lane,
                                  int *term);
bf_status_t bf_serdes_set_rx_term(bf_dev_id_t dev_id,
                                  bf_dev_port_t dev_port,
                                  int lane,
                                  int term);
bf_status_t bf_serdes_autoneg_en_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bool en);
bf_status_t bf_serdes_autoneg_advert_set(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         int lane,
                                         uint64_t base_pg,
                                         int num_next_pg,
                                         uint64_t *next_pg);
bf_status_t bf_serdes_autoneg_start(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    uint64_t base_pg,
                                    int num_next_pg,
                                    bool disable_nonce_match,
                                    bool disable_link_inhibit_timer);
bf_status_t bf_serdes_autoneg_stop(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_serdes_an_good_get(bf_dev_id_t dev_id,
                                  bf_dev_port_t dev_port,
                                  bool *an_good);
bf_status_t bf_serdes_an_complete_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      bool *an_cmplt);
bf_status_t bf_serdes_autoneg_st_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     bf_an_state_e *st);
bf_status_t bf_serdes_autoneg_hcd_fec_get(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          bf_port_speed_t *hcd,
                                          bf_fec_type_t *fec,
                                          uint32_t *av_hcd);
bf_status_t bf_serdes_link_training_st_get(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int lane,
                                           bf_lt_state_e *lt_st);
bf_status_t bf_serdes_link_training_st_extended_get(bf_dev_id_t dev_id,
                                                    bf_dev_port_t dev_port,
                                                    int lane,
                                                    int *failed,
                                                    int *in_prg,
                                                    int *rx_trnd,
                                                    int *frm_lk,
                                                    int *rmt_rq,
                                                    int *lcl_rq,
                                                    int *rmt_rcvr_rdy);
bf_status_t bf_serdes_autoneg_all_state(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bool *lp_base_pg_rdy,
                                        bool *lp_next_pg_rdy,
                                        bool *an_good,
                                        bool *an_complete,
                                        bool *an_failed);
bf_status_t bf_serdes_autoneg_lp_base_pg_get(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             int lane,
                                             uint64_t *lp_base_pg);
bf_status_t bf_serdes_autoneg_lp_next_pg_get(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             int lane,
                                             uint64_t *lp_next_pg);
bf_status_t bf_serdes_autoneg_next_pg_set(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          int lane,
                                          uint64_t next_pg);
int port_mgr_av_sd_rx_patsel_set(bf_dev_id_t dev_id,
                                 int ring,
                                 int sd,
                                 int rx_patsel);
bf_status_t bf_serdes_temperature_read_start(
    bf_dev_id_t dev_id, int sensor, bf_sds_temp_sensor_channel_t channel);
bf_status_t bf_serdes_temperature_read_get(bf_dev_id_t dev_id,
                                           int sensor,
                                           bf_sds_temp_sensor_channel_t channel,
                                           uint32_t *temp_mC);

bf_status_t bf_serdes_voltage_read_start(
    bf_dev_id_t dev_id, int sensor, bf_sds_voltage_sensor_channel_t channel);
bf_status_t bf_serdes_voltage_read_get(bf_dev_id_t dev_id,
                                       int sensor,
                                       bf_sds_voltage_sensor_channel_t channel,
                                       uint32_t *voltage_mV);
bf_status_t bf_serdes_reset(bf_dev_id_t dev_id,
                            bf_dev_port_t dev_port,
                            int lane,
                            bf_sds_reset_type_t reset_type);
bf_status_t bf_serdes_bcast_firmware_load(bf_dev_id_t dev_id,
                                          uint32_t fw_ver,
                                          char *fw_path);
bf_status_t bf_serdes_sbm_firmware_load(bf_dev_id_t dev_id,
                                        uint32_t fw_ver,
                                        char *fw_path);
bf_status_t bf_serdes_ucast_firmware_load(
    bf_dev_id_t dev_id, int ring, int sd, uint32_t fw_ver, char *fw_path);
bf_status_t bf_serdes_link_training_set(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane,
                                        bool en);
bf_status_t bf_serdes_link_training_restart(bf_dev_id_t dev_id,
                                            bf_dev_port_t dev_port,
                                            int lane);
bf_status_t bf_serdes_link_training_mode_set(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             int lane,
                                             bf_link_training_mode_t mode);
bf_status_t bf_serdes_assert_hcd_link_status(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             int lane,
                                             uint32_t hcd);
bf_status_t bf_serdes_eye_metric_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     uint32_t *metric);
bf_status_t bf_serdes_delay_cal_set(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane);
bf_status_t bf_serdes_eye_height_get(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     int *eye_ht_1e06,
                                     int *eye_ht_1e10,
                                     int *eye_ht_1e12,
                                     int *eye_ht_1e15,
                                     int *eye_ht_1e17);
bf_status_t bf_serdes_eye_quality_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int *qualifying_eye_ht_1e06,
                                      int *qualifying_eye_ht_1e10,
                                      int *qualifying_eye_ht_1e12);
bf_status_t bf_serdes_eye_quality_set(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      int qualifying_eye_ht_1e06,
                                      int qualifying_eye_ht_1e10,
                                      int qualifying_eye_ht_1e12);
bf_status_t bf_serdes_eye_quality_configured_set(bf_dev_id_t dev_id,
                                                 bf_dev_port_t dev_port,
                                                 int lane,
                                                 int qualifying_eye_ht_1e06,
                                                 int qualifying_eye_ht_1e10,
                                                 int qualifying_eye_ht_1e12);
bf_status_t bf_serdes_eye_quality_reset(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane);
bf_status_t bf_serdes_prbs_init(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                int lane,
                                bf_port_prbs_speed_t prbs_speed);

bf_status_t bf_serdes_prbs_mode_set(bf_dev_id_t dev_id,
                                    bf_port_prbs_mode_t prbs_mode);

bf_status_t bf_serdes_prbs_cmp_mode_set(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        int lane);

bf_status_t bf_serdes_prbs_diag_off(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane);

bf_status_t bf_serdes_prbs_stats_banner_display(void *display_ucli_cookie);

bf_status_t bf_serdes_debug_stats_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int lane,
                                      uint32_t *errors,
                                      uint32_t *eye_metric);
bf_status_t bf_serdes_quick_eye_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    int *eye_ht);
bf_status_t bf_serdes_hw_addr_get(bf_dev_id_t dev_id,
                                  bf_dev_port_t dev_port,
                                  int lane,
                                  bool tx_dir,
                                  uint32_t *hw_addr1, /*ring*/
                                  uint32_t *hw_addr2 /*sd*/);
bf_status_t bf_serdes_dfe_config_set(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port,
                                     int lane,
                                     bf_sds_tof_dfe_ctrl_t dfe_ctrl,
                                     uint32_t hf_val,
                                     uint32_t lf_val,
                                     uint32_t dc_val);
bf_status_t bf_serdes_elec_idle_get(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    int lane,
                                    bool *ei);
bf_status_t bf_serdes_tx_loop_bandwidth_set(
    bf_dev_id_t dev_id,
    bf_dev_port_t dev_port,
    int lane,
    bf_sds_tof_tx_loop_bandwidth_t setting);
bf_status_t bf_serdes_frequency_lock_get(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         int lane,
                                         bool *flock);
bf_status_t bf_serdes_signal_ok_thresh_enable_set(bf_dev_id_t dev_id,
                                                  bf_dev_port_t dev_port,
                                                  int lane,
                                                  bool en);
bf_status_t bf_serdes_signal_ok_thresh_calibration_disable(bf_dev_id_t dev_id,
                                                           bool true_or_false);
bf_status_t bf_serdes_calibration_status_get(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             int lane,
                                             bool *failed);

#ifdef __cplusplus
}
#endif /* C++ */

#endif  // BF_SERDES_IF_H_INCLUDED
