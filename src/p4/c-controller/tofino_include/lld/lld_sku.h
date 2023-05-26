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
#ifndef LLD_SKU_H_INCLUDED
#define LLD_SKU_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

// FIXME: get real part #s
typedef enum {
  BFN_PART_NBR_BFNT10064Q = 0,     // T-6.4-Full
  BFN_PART_NBR_BFNT10032Q = 0x10,  // T-3.2-Full
  BFN_PART_NBR_BFNT10032D = 0x08,  // T-3.2-Half
  BFN_PART_NBR_BFNT10024D = 0x18,  // T-1.8-Full
  BFN_PART_NBR_BFNT10018D = 0x0c,  // T-1.8-Half
  BFN_PART_NBR_BFNT10017D = 0x1c,  // T-1.28-Half
  BFN_PART_NBR_BFNT20128Q = 0x20,  // T2-12.8-Full
  BFN_PART_NBR_BFNT20096T,         // FIXME
  BFN_PART_NBR_BFNT20080T,         // FIXME
  BFN_PART_NBR_BFNT20064Q,         // FIXME
  BFN_PART_NBR_BFNT20064D,         // FIXME
  BFN_PART_NBR_BFNT20032D,         // FIXME
  BFN_PART_NBR_BFNT20032S,         // FIXME
  BFN_PART_NBR_BFNT20048D,         // FIXME
  BFN_PART_NBR_BFNT20036D,         // FIXME
} bfn_part_nbr_e;

typedef enum {
  BFN_SKU_BFN77110 = 0,  // T-6.4-Full BFNT10064Q
  BFN_SKU_BFN77120,      // T-3.2-Full BFNT10032Q
  BFN_SKU_BFN77121,      // T-3.2-Half BFNT10032D
  BFN_SKU_BFN77130,      // T-1.8-Full BFNT10018Q
  BFN_SKU_BFN77131,      // T-1.8-Half BFNT10018D
  BFN_SKU_BFN77140,      // T-1.28-Half
  BFN_SKU_BFN0128Q,      // T2-12.8-Qual
  BFN_SKU_BFN0096T,      // T2-9.6-Triple
  BFN_SKU_BFN0080T,      // T2-8.0-Triple
  BFN_SKU_BFN0064Q,      // T2-6.4-Quad
  BFN_SKU_BFN0064D,      // T2-6.4-Dual
  BFN_SKU_BFN0032D,      // T2-3.2-Dual
  BFN_SKU_BFN0032S,      // T2-3.2-Single
  BFN_SKU_BFN0048D,      // T2-4.8-Dual
  BFN_SKU_BFN0036D,      // T2-3.6-Dual
} bfn_sku_e;

typedef enum {
  BF_SKU_PORT_SPEED_INVALID = 0,
  BF_SKU_PORT_SPEED_100G,
  BF_SKU_PORT_SPEED_50G,
  BF_SKU_PORT_SPEED_25G
} bf_sku_port_speed_t;

typedef enum {
  BF_SKU_CORE_CLK_UNDEF_GHZ = 0,
  BF_SKU_CORE_CLK_1_5_GHZ,
  BF_SKU_CORE_CLK_1_35_GHZ,
  BF_SKU_CORE_CLK_1_3_GHZ,
  BF_SKU_CORE_CLK_1_25_GHZ,
  BF_SKU_CORE_CLK_1_1_GHZ,
  BF_SKU_CORE_CLK_1_0_GHZ,
} bf_sku_core_clk_freq_t;

typedef enum {
  BF_SKU_CHIP_PART_REV_A0 = 0,
  BF_SKU_CHIP_PART_REV_B0,
} bf_sku_chip_part_rev_t;

uint32_t lld_sku_get_sku(bf_dev_id_t dev_id);
bf_dev_type_t lld_sku_get_dev_type(bf_dev_id_t dev_id);
lld_err_t lld_sku_map_pipe_id_to_phy_pipe_id(bf_dev_id_t dev_id,
                                             uint32_t pipe_id,
                                             uint32_t *phy_pipe_id);
lld_err_t lld_sku_map_phy_pipe_id_to_pipe_id(bf_dev_id_t dev_id,
                                             uint32_t phy_pipe_id,
                                             uint32_t *pipe_id);
lld_err_t lld_sku_map_mac_ch_to_dev_port_id(bf_dev_id_t dev_id,
                                            uint32_t mac_blk,
                                            uint32_t ch,
                                            bf_dev_port_t *dev_port_id);
lld_err_t lld_sku_map_dev_port_id_to_mac_ch(bf_dev_id_t dev_id,
                                            uint32_t dev_port_id,
                                            uint32_t *mac_blk,
                                            uint32_t *ch);
lld_err_t lld_sku_get_num_active_pipes(bf_dev_id_t dev_id, uint32_t *num_pipes);
lld_err_t lld_sku_get_num_active_mau_stages(bf_dev_id_t dev_id,
                                            uint32_t *num_stages,
                                            uint32_t phy_pipe_id);
lld_err_t lld_sku_get_prsr_stage(bf_dev_id_t dev_id, uint32_t *stage);
lld_err_t lld_sku_get_dprsr_stage(bf_dev_id_t dev_id, uint32_t *stage);
lld_err_t lld_sku_check_efuse_consistency(bf_dev_id_t dev_id);
lld_err_t lld_sku_get_pcie_lanes(bf_dev_id_t dev_id, int *num_lanes);
lld_err_t lld_sku_get_port_speed(bf_dev_id_t dev_id, bf_sku_port_speed_t *sp);
lld_err_t lld_sku_get_baresync_en(bf_dev_id_t dev_id, int *en);
lld_err_t lld_sku_get_resubmit_en(bf_dev_id_t dev_id, int *en);
lld_err_t lld_sku_get_pkt_generator_en(bf_dev_id_t dev_id, int *en);
lld_err_t lld_sku_pipe_id_map_get(bf_dev_id_t dev_id,
                                  uint32_t pipe_log2phy[BF_PIPE_COUNT]);
lld_err_t lld_sku_get_core_clk_freq(bf_dev_id_t dev_id,
                                    bf_sku_core_clk_freq_t *bps_freq,
                                    bf_sku_core_clk_freq_t *pps_freq);
lld_err_t lld_sku_map_log2phy_mac_block(bf_dev_id_t dev_id,
                                        uint32_t log_mac_block,
                                        uint32_t *phy_mac_block);
lld_err_t lld_sku_map_phy2log_mac_block(bf_dev_id_t dev_id,
                                        uint32_t phy_mac_block,
                                        uint32_t *log_mac_block);
lld_err_t lld_sku_get_chip_part_revision_number(bf_dev_id_t dev_id,
                                                bf_sku_chip_part_rev_t *rev_no);

lld_err_t lld_sku_is_dev_port_internal(bf_dev_id_t dev_id,
                                       uint32_t dev_port_id,
                                       bool *is_internal);
int lld_get_min_cpu_port(bf_dev_id_t dev_id);
int lld_get_max_cpu_port(bf_dev_id_t dev_id);
int lld_get_max_frontport_mac_per_pipe(bf_dev_id_t dev_id);
int lld_get_max_mac_blocks(bf_dev_id_t dev_id);
int lld_get_chnls_per_mac(bf_dev_id_t dev_id);
int lld_get_chnls_dev_port(bf_dev_id_t dev_id, bf_dev_port_t dev_port_id);
int lld_get_internal_pipe_numb(bf_dev_id_t dev_id);
int lld_get_min_fp_port(bf_dev_id_t dev_id);
int lld_get_max_fp_port(bf_dev_id_t dev_id);
#ifdef __cplusplus
}
#endif /* C++ */

#endif  // LLD_SKU_H_INCLUDED
