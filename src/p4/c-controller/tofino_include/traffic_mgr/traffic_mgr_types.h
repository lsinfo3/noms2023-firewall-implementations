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

#ifndef __TRAFFIC_MGR_TYPES_H__
#define __TRAFFIC_MGR_TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_types.h
 * \brief Details traffic manager specific types used by traffic manager APIs
 */

/**
 * @addtogroup tm-types
 * @{
 */

/** Internal CoS value used by Traffic manager. Supported range <0-7> */
typedef uint8_t bf_tm_icos_t;

/** PFC priority used by Traffic manager. Supported range <0-7> */
typedef uint8_t bf_tm_pfc_priority_t;

/** Priority flow controlled (PFC) port group used for Traffic Isolation.
 *  Upto 256 additional PPGs are supported in Tofino version
 *  The handle is encoded as 16bit port, 4bit Pipe, 12bit ppg
 */
typedef uint32_t bf_tm_ppg_hdl;

/**
 * L1 nodes behind Port. Up to 32 L1 nodes per port group.
 */
typedef uint32_t bf_tm_l1_node_t;

/**
 * Queues behind L1 nodes. Up to 128 queues per port group.
 */
typedef uint32_t bf_tm_queue_t;

/**
 * Packet Color enumeration
 */
typedef enum {
  BF_TM_COLOR_GREEN /** Enum to use for Green Color */,
  BF_TM_COLOR_YELLOW /** Enum to use for Yellow Color */,
  BF_TM_COLOR_RED /** Enum to use for Red Color */,
} bf_tm_color_t;

/**
 * Enumeration of supported pool identifiers.
 * 1. Four application pools are supported in both ingress and egress
 *    direction. On ingress side, PPGs can be mapped to application pool
 *    BF_TM_IG_APP_POOL_0..3. On egress side queues can be mapped to
 *    application pools BF_TM_EG_APP_POOL_0..3
 * 2. Skid pool is a pool of PPGs that carry lossless traffic. When buffer
 *    space usage spills into skid pool, PFC is asserted.
 * 3. Negative mirror pool is used to mirror traffic that is experiencing
 *    drop. Buffers needed to accomodate traffic under drop comes from
 *    this pool. Size of this pool can be independently set for ingress
 *    and egress direction.
 */
typedef enum {
  BF_TM_IG_APP_POOL_0 /** Ingress Application Pool 0 */,
  BF_TM_IG_APP_POOL_1 /** Ingress Application Pool 1 */,
  BF_TM_IG_APP_POOL_2 /** Ingress Application Pool 2 */,
  BF_TM_IG_APP_POOL_3 /** Ingress Application Pool 3 */,
  BF_TM_EG_APP_POOL_0 /** Egress Application Pool 0 */,
  BF_TM_EG_APP_POOL_1 /** Egress Application Pool 1 */,
  BF_TM_EG_APP_POOL_2 /** Egress Application Pool 2 */,
  BF_TM_EG_APP_POOL_3 /** Egress Application Pool 3 */,
  BF_TM_APP_POOL_LAST
} bf_tm_app_pool_t;

/**
 * D(t) : Dynamic-PPG-Limit at time t.
 * Size : Size of Shared/Application Pool.
 * U(t) : In use cell count at time t. Cells used by all PPGs
 *        of the pool.
 * BAF  : One of the percentages listed in bf_tm_ppg_baf_t enum.
 *
 * D(t) = (Size - U(t)) * BAF
 */
typedef enum {
  BF_TM_PPG_BAF_1_POINT_5_PERCENT /** 1.5%  */,
  BF_TM_PPG_BAF_3_PERCENT /** 3%    */,
  BF_TM_PPG_BAF_6_PERCENT /** 6%    */,
  BF_TM_PPG_BAF_11_PERCENT /** 11%   */,
  BF_TM_PPG_BAF_20_PERCENT /** 20%   */,
  BF_TM_PPG_BAF_33_PERCENT /** 33%   */,
  BF_TM_PPG_BAF_50_PERCENT /** 50%   */,
  BF_TM_PPG_BAF_66_PERCENT /** 66%   */,
  BF_TM_PPG_BAF_80_PERCENT /** 80%   */,
  BF_TM_PPG_BAF_DISABLE /** No Burst Absorption  */,
} bf_tm_ppg_baf_t;

/**
 * D(t) : Dynamic-Q-Limit at time t.
 * Size : Size of Shared/Application Pool to which queue belongs to.
 * U(t) : In use cell count at time t. Cells used by all queues
 *        of the pool.
 * BAF  : One of the percentages listed in bf_tm_q_baf_en enum.
 *
 * D(t) = (Size - U(t)) * BAF
 */
typedef enum {
  BF_TM_Q_BAF_1_POINT_5_PERCENT /** 1.5%  */,
  BF_TM_Q_BAF_3_PERCENT /** 3%    */,
  BF_TM_Q_BAF_6_PERCENT /** 6%    */,
  BF_TM_Q_BAF_11_PERCENT /** 11%   */,
  BF_TM_Q_BAF_20_PERCENT /** 20%   */,
  BF_TM_Q_BAF_33_PERCENT /** 33%   */,
  BF_TM_Q_BAF_50_PERCENT /** 50%   */,
  BF_TM_Q_BAF_66_PERCENT /** 66%   */,
  BF_TM_Q_BAF_80_PERCENT /** 80%   */,
  BF_TM_Q_BAF_DISABLE /* If BAF is disabled, queue threshold is static. */,
} bf_tm_queue_baf_t;

/**
 * Color drop limits specified in terms of percentage of green color limits.
 * Green color limits by default is same as queue's minimum limit value.
 */
typedef enum {
  BF_TM_Q_COLOR_LIMIT_12_POINT_5_PERCENT /** 12.5% of green color limits */,
  BF_TM_Q_COLOR_LIMIT_25_PERCENT /** 25% of green color limits   */,
  BF_TM_Q_COLOR_LIMIT_37_POINT_5_PERCENT /** 37.5% of green color limits */,
  BF_TM_Q_COLOR_LIMIT_50_PERCENT /** 50% of green color limits   */,
  BF_TM_Q_COLOR_LIMIT_62_POINT_5_PERCENT /** 62.5% of green color limits */,
  BF_TM_Q_COLOR_LIMIT_75_PERCENT /** 75% of green color limits   */,
  BF_TM_Q_COLOR_LIMIT_87_POINT_5_PERCENT /** 87% of green color limits   */,
  BF_TM_Q_COLOR_LIMIT_100_PERCENT /** 100% of green color limits  */,
} bf_tm_queue_color_limit_t;

/**
 * Various pause mode supported on ingress TM
 */
typedef enum {
  BF_TM_PAUSE_NONE /** No FlowControl */,
  BF_TM_PAUSE_PFC /** FlowControl Type PFC */,
  BF_TM_PAUSE_PORT /** FlowControl Type, Port */
} bf_tm_flow_ctrl_type_t;

/**
 * Enum for assigning scheudling priority
 */

typedef enum {
  BF_TM_SCH_PRIO_LOW /**  */,
  BF_TM_SCH_PRIO_0 /** Scheduling Priority (Low) */ = BF_TM_SCH_PRIO_LOW,
  BF_TM_SCH_PRIO_1 /**  One of eight scheduling priority */,
  BF_TM_SCH_PRIO_2 /**  One of eight scheduling priority */,
  BF_TM_SCH_PRIO_3 /**  One of eight scheduling priority */,
  BF_TM_SCH_PRIO_4 /**  One of eight scheduling priority */,
  BF_TM_SCH_PRIO_5 /**  One of eight scheduling priority */,
  BF_TM_SCH_PRIO_6 /**  One of eight scheduling priority */,
  BF_TM_SCH_PRIO_7 /**  Scheduling Priority (High) */,
  BF_TM_SCH_PRIO_HIGH = BF_TM_SCH_PRIO_7,
} bf_tm_sched_prio_t;

/* @} */

#endif
