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
#ifndef DRU_MTI_INCLUDED
#define DRU_MTI_INCLUDED

typedef enum {
  MTI_TYP_RX_PKT_0 = 0,
  MTI_TYP_RX_PKT_1,
  MTI_TYP_RX_PKT_2,
  MTI_TYP_RX_PKT_3,
  MTI_TYP_RX_PKT_4,
  MTI_TYP_RX_PKT_5,
  MTI_TYP_RX_PKT_6,
  MTI_TYP_RX_PKT_7,
  MTI_TYP_LRT,
  MTI_TYP_IDLE,
  MTI_TYP_LEARN_PIPE0,
  MTI_TYP_LEARN_PIPE1,
  MTI_TYP_LEARN_PIPE2,
  MTI_TYP_LEARN_PIPE3,
  MTI_TYP_DIAG,
  MTI_TYP_NUM
} mti_typ_e;

void dru_mti_tx(int asic, mti_typ_e data_type, void *data, int len);
void dru_learn(int asic, uint8_t *learn_filter_data, int len, int pipe_nbr);
void dru_rx_pkt(int asic, uint8_t *pkt, int len, int cos);
void dru_lrt_update(int asic, uint8_t *lrt_stat_data, int len);
void dru_idle_update(int asic, uint8_t *idle_timeout_data, int len);
void dru_diag_event(int asic, uint8_t *diag_data, int len);

typedef void *(*dru_sim_dma2virt_dbg_callback_fn_mti)(uint32_t asic,
                                                      bf_dma_addr_t addr);
void dru_mti_register_dma2virt_cb(
    dru_sim_dma2virt_dbg_callback_fn_mti dma2virt_fn);

#endif  // DRU_MTI_INCLUDED
