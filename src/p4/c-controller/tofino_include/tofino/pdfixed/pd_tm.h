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

#ifndef _TOFINO_PDFIXED_PD_TM_H
#define _TOFINO_PDFIXED_PD_TM_H

#include <tofino/pdfixed/pd_common.h>

typedef int32_t p4_pd_tm_dev_t;
typedef uint32_t p4_pd_tm_port_t;
typedef uint32_t p4_pd_tm_ppg_t;
typedef uint16_t p4_pd_tm_icos_map_t;
typedef uint32_t p4_pd_tm_queue_t;
typedef uint32_t p4_pd_tm_l1_node_t;
typedef uint16_t p4_pd_tm_icos_t;
typedef uint16_t p4_pd_tm_pipe_t;

typedef enum {
  PD_COLOR_GREEN = 0,
  PD_COLOR_YELLOW = 1,
  PD_COLOR_RED = 2
} p4_pd_color_t;

typedef enum {
  PD_TM_COLOR_12_POINT_5_PERCENT,
  PD_TM_COLOR_25_PERCENT,
  PD_TM_COLOR_37_POINT_5_PERCENT,
  PD_TM_COLOR_50_PERCENT,
  PD_TM_COLOR_62_POINT_5_PERCENT,
  PD_TM_COLOR_75_PERCENT,
  PD_TM_COLOR_87_POINT_5_PERCENT,
  PD_TM_COLOR_100_PERCENT,
} p4_pd_color_limit_t;

typedef enum {
  PD_INGRESS_POOL_0,
  PD_INGRESS_POOL_1,
  PD_INGRESS_POOL_2,
  PD_INGRESS_POOL_3,
  PD_EGRESS_POOL_0,
  PD_EGRESS_POOL_1,
  PD_EGRESS_POOL_2,
  PD_EGRESS_POOL_3,
} p4_pd_pool_id_t;

typedef enum {
  PD_PPG_BAF_1_POINT_5_PERCENT,
  PD_PPG_BAF_3_PERCENT,
  PD_PPG_BAF_6_PERCENT,
  PD_PPG_BAF_11_PERCENT,
  PD_PPG_BAF_20_PERCENT,
  PD_PPG_BAF_33_PERCENT,
  PD_PPG_BAF_50_PERCENT,
  PD_PPG_BAF_66_PERCENT,
  PD_PPG_BAF_80_PERCENT,
  PD_PPG_BAF_DISABLE,
} p4_pd_tm_ppg_baf_t;

typedef enum {
  PD_Q_BAF_1_POINT_5_PERCENT,
  PD_Q_BAF_3_PERCENT,
  PD_Q_BAF_6_PERCENT,
  PD_Q_BAF_11_PERCENT,
  PD_Q_BAF_20_PERCENT,
  PD_Q_BAF_33_PERCENT,
  PD_Q_BAF_50_PERCENT,
  PD_Q_BAF_66_PERCENT,
  PD_Q_BAF_80_PERCENT,
  PD_Q_BAF_DISABLE,
} p4_pd_tm_queue_baf_t;

typedef enum {
  PD_TM_SCH_PRIO_LOW,
  PD_TM_SCH_PRIO_0 = PD_TM_SCH_PRIO_LOW,
  PD_TM_SCH_PRIO_1,
  PD_TM_SCH_PRIO_2,
  PD_TM_SCH_PRIO_3,
  PD_TM_SCH_PRIO_4,
  PD_TM_SCH_PRIO_5,
  PD_TM_SCH_PRIO_6,
  PD_TM_SCH_PRIO_7,
  PD_TM_SCH_PRIO_HIGH = PD_TM_SCH_PRIO_7
} p4_pd_tm_sched_prio_t;

typedef enum {
  PD_TM_PAUSE_NONE,
  PD_TM_PAUSE_PFC,
  PD_TM_PAUSE_PORT
} p4_pd_tm_flow_ctrl_type_t;

p4_pd_status_t p4_pd_tm_allocate_ppg(p4_pd_tm_dev_t dev,
                                     p4_pd_tm_port_t port,
                                     p4_pd_tm_ppg_t *ppg);

p4_pd_status_t p4_pd_tm_free_ppg(p4_pd_tm_dev_t dev, p4_pd_tm_ppg_t ppg);

p4_pd_status_t p4_pd_tm_get_default_ppg(p4_pd_tm_dev_t dev,
                                        p4_pd_tm_port_t port,
                                        p4_pd_tm_ppg_t *ppg);

p4_pd_status_t p4_pd_tm_set_ppg_icos_mapping(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_ppg_t ppg,
                                             p4_pd_tm_icos_map_t icos_map);

p4_pd_status_t p4_pd_tm_ppg_icos_mapping_get(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_ppg_t ppg,
                                             uint8_t *icos_map);

p4_pd_status_t p4_pd_tm_enable_lossless_treatment(p4_pd_tm_dev_t dev,
                                                  p4_pd_tm_ppg_t ppg);

p4_pd_status_t p4_pd_tm_disable_lossless_treatment(p4_pd_tm_dev_t dev,
                                                   p4_pd_tm_ppg_t ppg);

p4_pd_status_t p4_pd_tm_set_ppg_app_pool_usage(p4_pd_tm_dev_t dev,
                                               p4_pd_tm_ppg_t ppg,
                                               p4_pd_pool_id_t pool_id,
                                               uint32_t base_use_limit,
                                               p4_pd_tm_ppg_baf_t dynamic_baf,
                                               uint32_t hysteresis);

p4_pd_status_t p4_pd_tm_disable_ppg_app_pool_usage(p4_pd_tm_dev_t dev,
                                                   p4_pd_pool_id_t pool_id,
                                                   p4_pd_tm_ppg_t ppg);

p4_pd_status_t p4_pd_tm_set_ppg_guaranteed_min_limit(p4_pd_tm_dev_t dev,
                                                     p4_pd_tm_ppg_t ppg,
                                                     uint32_t cells);

p4_pd_status_t p4_pd_tm_set_ppg_skid_limit(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_ppg_t ppg,
                                           uint32_t cells);

p4_pd_status_t p4_pd_tm_set_guaranteed_min_skid_hysteresis(p4_pd_tm_dev_t dev,
                                                           p4_pd_tm_ppg_t ppg,
                                                           uint32_t cells);

p4_pd_status_t p4_pd_tm_set_port_q_mapping(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port,
                                           int16_t q_count,
                                           uint8_t *q_map);

p4_pd_status_t p4_pd_tm_set_q_app_pool_usage(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port,
                                             p4_pd_tm_queue_t queue,
                                             p4_pd_pool_id_t pool,
                                             uint32_t base_use_limit,
                                             p4_pd_tm_queue_baf_t dynamic_baf,
                                             uint32_t hysteresis);

p4_pd_status_t p4_pd_tm_disable_q_app_pool_usage(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_port_t port,
                                                 p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_set_q_guaranteed_min_limit(p4_pd_tm_dev_t dev,
                                                   p4_pd_tm_port_t port,
                                                   p4_pd_tm_queue_t queue,
                                                   uint32_t cells);

p4_pd_status_t p4_pd_tm_set_q_color_limit(p4_pd_tm_dev_t dev,
                                          p4_pd_tm_port_t port,
                                          p4_pd_tm_queue_t queue,
                                          p4_pd_color_t color,
                                          p4_pd_color_limit_t limit);

p4_pd_status_t p4_pd_tm_set_q_color_hysteresis(p4_pd_tm_dev_t dev,
                                               p4_pd_tm_port_t port,
                                               p4_pd_tm_queue_t queue,
                                               p4_pd_color_t color,
                                               p4_pd_color_limit_t limit);

p4_pd_status_t p4_pd_tm_set_q_hysteresis(p4_pd_tm_dev_t dev,
                                         p4_pd_tm_port_t port,
                                         p4_pd_tm_queue_t queue,
                                         uint32_t cells);

p4_pd_status_t p4_pd_tm_enable_q_tail_drop(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port,
                                           p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_disable_q_tail_drop(p4_pd_tm_dev_t dev,
                                            p4_pd_tm_port_t port,
                                            p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_enable_q_color_drop(p4_pd_tm_dev_t dev,
                                            p4_pd_tm_port_t port,
                                            p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_disable_q_color_drop(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port,
                                             p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_set_negative_mirror_dest(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_pipe_t pipe,
                                                 p4_pd_tm_port_t port,
                                                 p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_set_q_pfc_cos_mapping(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port,
                                              p4_pd_tm_queue_t queue,
                                              p4_pd_tm_icos_t cos);

p4_pd_status_t p4_pd_tm_set_app_pool_size(p4_pd_tm_dev_t dev,
                                          p4_pd_pool_id_t pool,
                                          uint32_t cells);

p4_pd_status_t p4_pd_tm_enable_app_pool_color_drop(p4_pd_tm_dev_t dev,
                                                   p4_pd_pool_id_t pool);

p4_pd_status_t p4_pd_tm_disable_app_pool_color_drop(p4_pd_tm_dev_t dev,
                                                    p4_pd_pool_id_t pool);

p4_pd_status_t p4_pd_tm_set_app_pool_color_drop_limit(p4_pd_tm_dev_t dev,
                                                      p4_pd_pool_id_t pool,
                                                      p4_pd_color_t color,
                                                      uint32_t limit);

p4_pd_status_t p4_pd_tm_set_app_pool_color_drop_hysteresis(p4_pd_tm_dev_t dev,
                                                           p4_pd_color_t color,
                                                           uint32_t limit);

p4_pd_status_t p4_pd_tm_set_app_pool_pfc_limit(p4_pd_tm_dev_t dev,
                                               p4_pd_pool_id_t pool,
                                               p4_pd_tm_icos_t icos,
                                               uint32_t limit);

p4_pd_status_t p4_pd_tm_set_skid_pool_size(p4_pd_tm_dev_t dev, uint32_t cells);

p4_pd_status_t p4_pd_tm_set_skid_pool_hysteresis(p4_pd_tm_dev_t dev,
                                                 uint32_t cells);

p4_pd_status_t p4_pd_tm_set_negative_mirror_pool_size(p4_pd_tm_dev_t dev,
                                                      uint32_t cells);

p4_pd_status_t p4_pd_tm_set_uc_cut_through_pool_size(p4_pd_tm_dev_t dev,
                                                     uint32_t cells);

p4_pd_status_t p4_pd_tm_set_mc_cut_through_pool_size(p4_pd_tm_dev_t dev,
                                                     uint32_t cells);

p4_pd_status_t p4_pd_tm_set_egress_pipe_limit(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_pipe_t pipe,
                                              uint32_t cells);

p4_pd_status_t p4_pd_tm_set_egress_pipe_hysteresis(p4_pd_tm_dev_t dev,
                                                   p4_pd_tm_pipe_t pipe,
                                                   uint32_t cells);

p4_pd_status_t p4_pd_tm_set_ingress_port_drop_limit(p4_pd_tm_dev_t dev,
                                                    p4_pd_tm_port_t port,
                                                    uint32_t cells);

p4_pd_status_t p4_pd_tm_set_ingress_port_hysteresis(p4_pd_tm_dev_t dev,
                                                    p4_pd_tm_port_t port,
                                                    uint32_t cells);

p4_pd_status_t p4_pd_tm_set_port_uc_cut_through_limit(p4_pd_tm_dev_t dev,
                                                      p4_pd_tm_port_t port,
                                                      uint32_t cells);

p4_pd_status_t p4_pd_tm_set_port_flowcontrol_mode(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_flow_ctrl_type_t fctype);

p4_pd_status_t p4_pd_tm_set_port_pfc_cos_mapping(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_port_t port,
                                                 uint8_t *cos_map);

p4_pd_status_t p4_pd_tm_set_cpuport(p4_pd_tm_dev_t dev, p4_pd_tm_port_t port);

p4_pd_status_t p4_pd_tm_reset_cpuport(p4_pd_tm_dev_t dev);

p4_pd_status_t p4_pd_tm_set_q_sched_priority(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port,
                                             p4_pd_tm_queue_t queue,
                                             uint16_t priority);

p4_pd_status_t p4_pd_tm_set_q_dwrr_weight(p4_pd_tm_dev_t dev,
                                          p4_pd_tm_port_t port,
                                          p4_pd_tm_queue_t queue,
                                          uint16_t weight);

p4_pd_status_t p4_pd_tm_set_q_shaping_rate(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port,
                                           p4_pd_tm_queue_t queue,
                                           bool pps,
                                           uint32_t burstsize,
                                           uint32_t rate);

p4_pd_status_t p4_pd_tm_set_q_guaranteed_rate(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port,
                                              p4_pd_tm_queue_t queue,
                                              bool pps,
                                              uint32_t burstsize,
                                              uint32_t rate);

p4_pd_status_t p4_pd_tm_set_q_remaining_bw_sched_priority(
    p4_pd_tm_dev_t dev,
    p4_pd_tm_port_t port,
    p4_pd_tm_queue_t queue,
    uint16_t priority);

p4_pd_status_t p4_pd_tm_sched_q_l1_set(p4_pd_tm_dev_t dev,
                                       p4_pd_tm_port_t port,
                                       p4_pd_tm_l1_node_t l1_node,
                                       p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_sched_q_l1_reset(p4_pd_tm_dev_t dev,
                                         p4_pd_tm_port_t port,
                                         p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_sched_l1_priority_set(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port,
                                              p4_pd_tm_l1_node_t l1_node,
                                              uint16_t priority);

p4_pd_status_t p4_pd_tm_sched_l1_dwrr_weight_set(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_port_t port,
                                                 p4_pd_tm_l1_node_t l1_node,
                                                 uint16_t weight);

p4_pd_status_t p4_pd_tm_sched_l1_shaping_rate_set(p4_pd_tm_dev_t dev,
                                                  p4_pd_tm_port_t port,
                                                  p4_pd_tm_l1_node_t l1_node,
                                                  bool pps,
                                                  uint32_t burst_size,
                                                  uint32_t rate);

p4_pd_status_t p4_pd_tm_sched_l1_max_shaping_rate_enable(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_max_shaping_rate_disable(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_priority_prop_enable(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_priority_prop_disable(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_guaranteed_rate_set(p4_pd_tm_dev_t dev,
                                                     p4_pd_tm_port_t port,
                                                     p4_pd_tm_l1_node_t l1_node,
                                                     bool pps,
                                                     uint32_t burst_size,
                                                     uint32_t rate);

p4_pd_status_t p4_pd_tm_sched_l1_remaining_bw_priority_set(
    p4_pd_tm_dev_t dev,
    p4_pd_tm_port_t port,
    p4_pd_tm_l1_node_t l1_node,
    uint16_t priority);

p4_pd_status_t p4_pd_tm_sched_l1_guaranteed_rate_enable(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_guaranteed_rate_disable(
    p4_pd_tm_dev_t dev, p4_pd_tm_port_t port, p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_enable(p4_pd_tm_dev_t dev,
                                        p4_pd_tm_port_t port,
                                        p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_disable(p4_pd_tm_dev_t dev,
                                         p4_pd_tm_port_t port,
                                         p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_sched_l1_free(p4_pd_tm_dev_t dev,
                                      p4_pd_tm_port_t port,
                                      p4_pd_tm_l1_node_t l1_node);

p4_pd_status_t p4_pd_tm_set_port_shaping_rate(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port,
                                              bool pps,
                                              uint32_t burstsize,
                                              uint32_t rate);

p4_pd_status_t p4_pd_tm_set_shaper_pkt_ifg_compensation(p4_pd_tm_dev_t dev,
                                                        p4_pd_tm_pipe_t pipe,
                                                        uint8_t adjustment);

p4_pd_status_t p4_pd_tm_enable_q_sched(p4_pd_tm_dev_t dev,
                                       p4_pd_tm_port_t port,
                                       p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_disable_q_sched(p4_pd_tm_dev_t dev,
                                        p4_pd_tm_port_t port,
                                        p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_enable_port_shaping(p4_pd_tm_dev_t dev,
                                            p4_pd_tm_port_t port);

p4_pd_status_t p4_pd_tm_disable_port_shaping(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port);

p4_pd_status_t p4_pd_tm_enable_port_sched(p4_pd_tm_dev_t dev,
                                          p4_pd_tm_port_t port,
                                          uint16_t port_speed);

p4_pd_status_t p4_pd_tm_disable_port_sched(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port);

void p4_pd_tm_complete_operations(p4_pd_tm_dev_t dev);

p4_pd_status_t p4_pd_tm_get_q_sched_priority(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port,
                                             p4_pd_tm_queue_t queue,
                                             p4_pd_tm_sched_prio_t *priority);

p4_pd_status_t p4_pd_tm_get_q_dwrr_weight(p4_pd_tm_dev_t dev,
                                          p4_pd_tm_port_t port,
                                          p4_pd_tm_queue_t queue,
                                          uint16_t *weight);

p4_pd_status_t p4_pd_tm_get_q_shaping_rate(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port,
                                           p4_pd_tm_queue_t queue,
                                           bool *pps,
                                           uint32_t *burstsize,
                                           uint32_t *rate);

p4_pd_status_t p4_pd_tm_get_q_guaranteed_rate(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port,
                                              p4_pd_tm_queue_t queue,
                                              bool *pps,
                                              uint32_t *burstsize,
                                              uint32_t *rate);

p4_pd_status_t p4_pd_tm_get_q_remaining_bw_sched_priority(
    p4_pd_tm_dev_t dev,
    p4_pd_tm_port_t port,
    p4_pd_tm_queue_t queue,
    p4_pd_tm_sched_prio_t *priority);

p4_pd_status_t p4_pd_tm_get_port_shaping_rate(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port,
                                              bool *pps,
                                              uint32_t *burstsize,
                                              uint32_t *rate);

p4_pd_status_t p4_pd_tm_get_shaper_pkt_ifg_compensation(p4_pd_tm_dev_t dev,
                                                        p4_pd_tm_pipe_t pipe,
                                                        uint8_t *adjust);

p4_pd_status_t p4_pd_tm_get_egress_pipe_limit(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_pipe_t pipe,
                                              uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_egress_pipe_hysteresis(p4_pd_tm_dev_t dev,
                                                   p4_pd_tm_pipe_t pipe,
                                                   uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_port_q_mapping(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port,
                                           uint8_t *q_count,
                                           uint8_t *q_map);

p4_pd_status_t p4_pd_tm_get_q_app_pool_usage(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port,
                                             p4_pd_tm_queue_t queue,
                                             p4_pd_pool_id_t *pool,
                                             uint32_t *base_use_limit,
                                             p4_pd_tm_queue_baf_t *dynamic_baf,
                                             uint32_t *hysteresis);

p4_pd_status_t p4_pd_tm_get_q_guaranteed_min_limit(p4_pd_tm_dev_t dev,
                                                   p4_pd_tm_port_t port,
                                                   p4_pd_tm_queue_t queue,
                                                   uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_q_color_limit(p4_pd_tm_dev_t dev,
                                          p4_pd_tm_port_t port,
                                          p4_pd_tm_queue_t queue,
                                          p4_pd_color_t color,
                                          p4_pd_color_limit_t *limit);

p4_pd_status_t p4_pd_tm_get_q_color_hysteresis(p4_pd_tm_dev_t dev,
                                               p4_pd_tm_port_t port,
                                               p4_pd_tm_queue_t queue,
                                               p4_pd_color_t color,
                                               uint32_t *limit);

p4_pd_status_t p4_pd_tm_get_port_uc_cut_through_limit(p4_pd_tm_dev_t dev,
                                                      p4_pd_tm_port_t port,
                                                      uint8_t *cells);

p4_pd_status_t p4_pd_tm_get_total_ppg(p4_pd_tm_dev_t dev,
                                      p4_pd_tm_pipe_t pipe,
                                      uint32_t *total_ppg);

p4_pd_status_t p4_pd_tm_get_unused_ppg_count(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_pipe_t pipe,
                                             uint32_t *unused_ppg);

p4_pd_status_t p4_pd_tm_get_ppg_app_pool_usage(p4_pd_tm_dev_t dev,
                                               p4_pd_tm_ppg_t ppg,
                                               p4_pd_pool_id_t pool_id,
                                               uint32_t *base_use_limit,
                                               p4_pd_tm_ppg_baf_t *dynamic_baf,
                                               uint32_t *hysteresis);

p4_pd_status_t p4_pd_tm_get_ppg_guaranteed_min_limit(p4_pd_tm_dev_t dev,
                                                     p4_pd_tm_ppg_t ppg,
                                                     uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_ppg_skid_limit(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_ppg_t ppg,
                                           uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_ppg_guaranteed_min_skid_hysteresis(
    p4_pd_tm_dev_t dev, p4_pd_tm_ppg_t ppg, uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_app_pool_size(p4_pd_tm_dev_t dev,
                                          p4_pd_pool_id_t pool_id,
                                          uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_app_pool_color_drop_limit(p4_pd_tm_dev_t dev,
                                                      p4_pd_pool_id_t pool_id,
                                                      p4_pd_color_t color,
                                                      uint32_t *limit);

p4_pd_status_t p4_pd_tm_get_app_pool_color_drop_hysteresis(p4_pd_tm_dev_t dev,
                                                           p4_pd_color_t color,
                                                           uint32_t *limit);

p4_pd_status_t p4_pd_tm_get_app_pool_pfc_limit(p4_pd_tm_dev_t dev,
                                               p4_pd_pool_id_t pool_id,
                                               p4_pd_tm_icos_t icos,
                                               uint32_t *limit);

p4_pd_status_t p4_pd_tm_get_skid_pool_size(p4_pd_tm_dev_t dev, uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_skid_pool_hysteresis(p4_pd_tm_dev_t dev,
                                                 uint32_t *limit);

p4_pd_status_t p4_pd_tm_get_negative_mirror_pool_size(p4_pd_tm_dev_t dev,
                                                      uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_uc_cut_through_pool_size(p4_pd_tm_dev_t dev,
                                                     p4_pd_pool_id_t pool_id,
                                                     uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_mc_cut_through_pool_size(p4_pd_tm_dev_t dev,
                                                     p4_pd_pool_id_t pool_id,
                                                     uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_ingress_port_drop_limit(p4_pd_tm_dev_t dev,
                                                    p4_pd_tm_port_t port,
                                                    uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_ingress_port_hysteresis(p4_pd_tm_dev_t dev,
                                                    p4_pd_tm_port_t port,
                                                    uint32_t *cells);

p4_pd_status_t p4_pd_tm_get_port_flowcontrol_mode(
    p4_pd_tm_dev_t dev,
    p4_pd_tm_port_t port,
    p4_pd_tm_flow_ctrl_type_t *fctype);

p4_pd_status_t p4_pd_tm_get_port_pfc_cos_mapping(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_port_t port,
                                                 uint8_t *cos_map);

p4_pd_status_t p4_pd_tm_get_total_buffer_size(p4_pd_tm_dev_t dev,
                                              uint64_t *buffer_size);

p4_pd_status_t p4_pd_tm_get_cell_size_in_bytes(p4_pd_tm_dev_t dev,
                                               uint32_t *cell_size);

p4_pd_status_t p4_pd_tm_get_cell_count(p4_pd_tm_dev_t dev,
                                       uint32_t *total_cells);

p4_pd_status_t p4_pd_tm_q_max_rate_shaper_enable(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_port_t port,
                                                 p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_q_max_rate_shaper_disable(p4_pd_tm_dev_t dev,
                                                  p4_pd_tm_port_t port,
                                                  p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_q_min_rate_shaper_enable(p4_pd_tm_dev_t dev,
                                                 p4_pd_tm_port_t port,
                                                 p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_q_min_rate_shaper_disable(p4_pd_tm_dev_t dev,
                                                  p4_pd_tm_port_t port,
                                                  p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_set_timestamp_shift(p4_pd_tm_dev_t dev,
                                            uint8_t ts_shift);

p4_pd_status_t p4_pd_tm_get_timestamp_shift(p4_pd_tm_dev_t dev,
                                            uint8_t *ts_shift);

p4_pd_status_t p4_pd_tm_ppg_drop_get(p4_pd_tm_dev_t dev,
                                     p4_pd_tm_pipe_t pipe,
                                     p4_pd_tm_ppg_t ppg,
                                     uint64_t *count);

p4_pd_status_t p4_pd_tm_ppg_drop_count_clear(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_ppg_t ppg);

p4_pd_status_t p4_pd_tm_q_drop_get(p4_pd_tm_dev_t dev,
                                   p4_pd_tm_pipe_t pipe,
                                   p4_pd_tm_port_t port,
                                   p4_pd_tm_queue_t queue,
                                   uint64_t *count);

p4_pd_status_t p4_pd_tm_q_drop_count_clear(p4_pd_tm_dev_t dev,
                                           p4_pd_tm_port_t port,
                                           p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_pool_usage_get(p4_pd_tm_dev_t dev,
                                       p4_pd_pool_id_t pool_id,
                                       uint32_t *count,
                                       uint32_t *wm);

p4_pd_status_t p4_pd_tm_pool_watermark_clear(p4_pd_tm_dev_t dev,
                                             p4_pd_pool_id_t pool_id);

p4_pd_status_t p4_pd_tm_port_drop_get(p4_pd_tm_dev_t dev,
                                      p4_pd_tm_pipe_t pipe,
                                      p4_pd_tm_port_t port,
                                      uint64_t *ig_count,
                                      uint64_t *eg_count);

p4_pd_status_t p4_pd_tm_port_drop_count_clear(p4_pd_tm_dev_t dev,
                                              p4_pd_tm_port_t port);

p4_pd_status_t p4_pd_tm_port_ingress_drop_count_clear(p4_pd_tm_dev_t dev,
                                                      p4_pd_tm_port_t port);

p4_pd_status_t p4_pd_tm_port_egress_drop_count_clear(p4_pd_tm_dev_t dev,
                                                     p4_pd_tm_port_t port);

p4_pd_status_t p4_pd_tm_ppg_usage_get(p4_pd_tm_dev_t dev,
                                      p4_pd_tm_pipe_t pipe,
                                      p4_pd_tm_ppg_t ppg,
                                      uint32_t *gmin_count,
                                      uint32_t *shared_count,
                                      uint32_t *skid_count,
                                      uint32_t *wm);

p4_pd_status_t p4_pd_tm_ppg_watermark_clear(p4_pd_tm_dev_t dev,
                                            p4_pd_tm_ppg_t ppg);

p4_pd_status_t p4_pd_tm_q_usage_get(p4_pd_tm_dev_t dev,
                                    p4_pd_tm_pipe_t pipe,
                                    p4_pd_tm_port_t port,
                                    p4_pd_tm_queue_t queue,
                                    uint32_t *count,
                                    uint32_t *wm);

p4_pd_status_t p4_pd_tm_q_watermark_clear(p4_pd_tm_dev_t dev,
                                          p4_pd_tm_port_t port,
                                          p4_pd_tm_queue_t queue);

p4_pd_status_t p4_pd_tm_port_usage_get(p4_pd_tm_dev_t dev,
                                       p4_pd_tm_pipe_t pipe,
                                       p4_pd_tm_port_t port,
                                       uint32_t *ig_count,
                                       uint32_t *eg_count,
                                       uint32_t *ig_wm,
                                       uint32_t *eg_wm);

p4_pd_status_t p4_pd_tm_port_watermark_clear(p4_pd_tm_dev_t dev,
                                             p4_pd_tm_port_t port);

#endif
