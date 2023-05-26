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
#ifndef _TOFINO_PDFIXED_PD_CONN_MGR_H
#define _TOFINO_PDFIXED_PD_CONN_MGR_H

#include <tofino/pdfixed/pd_common.h>

p4_pd_status_t p4_pd_init(void);

void p4_pd_cleanup(void);

p4_pd_status_t p4_pd_client_init(p4_pd_sess_hdl_t *sess_hdl);

p4_pd_status_t p4_pd_client_cleanup(p4_pd_sess_hdl_t sess_hdl);

p4_pd_status_t p4_pd_begin_txn(p4_pd_sess_hdl_t shdl, bool isAtomic);

p4_pd_status_t p4_pd_verify_txn(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_abort_txn(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_commit_txn(p4_pd_sess_hdl_t shdl, bool hwSynchronous);

p4_pd_status_t p4_pd_complete_operations(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_begin_batch(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_flush_batch(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_end_batch(p4_pd_sess_hdl_t shdl, bool hwSynchronous);

p4_pd_status_t p4_pd_log_state(uint32_t dev, const char *filepath);

p4_pd_status_t p4_pd_restore_state(uint32_t dev, const char *filepath);

p4_pd_status_t p4_pd_advance_model_time(p4_pd_sess_hdl_t shdl,
                                        uint32_t dev,
                                        uint64_t tick_time);

p4_pd_status_t p4_pd_recirculation_enable(p4_pd_sess_hdl_t shdl,
                                          uint32_t dev,
                                          uint32_t port);

p4_pd_status_t p4_pd_recirculation_disable(p4_pd_sess_hdl_t shdl,
                                           uint32_t dev,
                                           uint32_t port);

p4_pd_status_t p4_pd_pktgen_enable(p4_pd_sess_hdl_t shdl,
                                   uint32_t dev,
                                   uint32_t port);

p4_pd_status_t p4_pd_pktgen_disable(p4_pd_sess_hdl_t shdl,
                                    uint32_t dev,
                                    uint32_t port);

p4_pd_status_t p4_pd_pktgen_enable_recirc_pattern_matching(
    p4_pd_sess_hdl_t shdl, uint32_t dev, uint32_t port);

p4_pd_status_t p4_pd_pktgen_disable_recirc_pattern_matching(
    p4_pd_sess_hdl_t shdl, uint32_t dev, uint32_t port);

p4_pd_status_t p4_pd_pktgen_clear_port_down(p4_pd_sess_hdl_t shdl,
                                            uint32_t dev,
                                            uint32_t port);

p4_pd_status_t p4_pd_pktgen_cfg_app(p4_pd_sess_hdl_t shdl,
                                    p4_pd_dev_target_t dev_tgt,
                                    uint32_t app_id,
                                    struct p4_pd_pktgen_app_cfg cfg);

p4_pd_status_t p4_pd_pktgen_cfg_app_tof2(p4_pd_sess_hdl_t shdl,
                                         p4_pd_dev_target_t dev_tgt,
                                         uint32_t app_id,
                                         struct p4_pd_pktgen_app_cfg_tof2 cfg);

p4_pd_status_t p4_pd_pktgen_port_down_msk_tof2(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    uint32_t port_mask_sel,
    struct p4_pd_port_down_mask_tof2 mask);

p4_pd_status_t p4_pd_pktgen_port_down_replay_mode_set(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_pktgen_port_down_mode_t mode);
p4_pd_status_t p4_pd_pktgen_port_down_replay_mode_get(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_pktgen_port_down_mode_t *mode);

p4_pd_status_t p4_pd_pktgen_app_enable(p4_pd_sess_hdl_t shdl,
                                       p4_pd_dev_target_t dev_tgt,
                                       uint32_t app_id);

p4_pd_status_t p4_pd_pktgen_app_disable(p4_pd_sess_hdl_t shdl,
                                        p4_pd_dev_target_t dev_tgt,
                                        uint32_t app_id);

p4_pd_status_t p4_pd_pktgen_write_pkt_buffer(p4_pd_sess_hdl_t shdl,
                                             p4_pd_dev_target_t dev_tgt,
                                             uint32_t offset,
                                             uint32_t size,
                                             uint8_t *buf);

p4_pd_status_t p4_pd_pktgen_get_batch_counter(p4_pd_sess_hdl_t shdl,
                                              p4_pd_dev_target_t dev_tgt,
                                              uint32_t app_id,
                                              uint64_t *count);

p4_pd_status_t p4_pd_pktgen_get_pkt_counter(p4_pd_sess_hdl_t shdl,
                                            p4_pd_dev_target_t dev_tgt,
                                            uint32_t app_id,
                                            uint64_t *count);

p4_pd_status_t p4_pd_pktgen_get_trigger_counter(p4_pd_sess_hdl_t shdl,
                                                p4_pd_dev_target_t dev_tgt,
                                                uint32_t app_id,
                                                uint64_t *count);

p4_pd_status_t p4_pd_pktgen_set_batch_counter(p4_pd_sess_hdl_t shdl,
                                              p4_pd_dev_target_t dev_tgt,
                                              uint32_t app_id,
                                              uint64_t count);

p4_pd_status_t p4_pd_pktgen_set_pkt_counter(p4_pd_sess_hdl_t shdl,
                                            p4_pd_dev_target_t dev_tgt,
                                            uint32_t app_id,
                                            uint64_t count);

p4_pd_status_t p4_pd_pktgen_set_trigger_counter(p4_pd_sess_hdl_t shdl,
                                                p4_pd_dev_target_t dev_tgt,
                                                uint32_t app_id,
                                                uint64_t count);

p4_pd_status_t p4_pd_parser_id_get(int device_id, int port, uint8_t *parser_id);

p4_pd_status_t p4_pd_pipe_id_get(int device_id, int port, uint32_t *pipe_id);

p4_pd_status_t p4_pd_reg_wr(uint32_t dev, uint32_t addr, uint32_t data);
uint32_t p4_pd_reg_rd(uint32_t dev, uint32_t addr);
p4_pd_status_t p4_pd_ind_reg_wr(uint32_t dev,
                                uint64_t addr,
                                uint64_t data_hi,
                                uint64_t data_lo);
void p4_pd_ind_reg_rd(uint32_t dev,
                      uint64_t addr,
                      uint64_t *data_hi,
                      uint64_t *data_lo);
p4_pd_status_t p4_pd_tcam_scrub_timer_set(uint32_t dev, uint32_t msec_timer);
uint32_t p4_pd_tcam_scrub_timer_get(uint32_t dev);

#endif
