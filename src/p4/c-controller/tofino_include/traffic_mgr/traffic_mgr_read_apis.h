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

/*
 * This file contains APIs for client application to program
 * Traffic Manager block to desired QoS behaviour.
 */

#ifndef __TRAFFIC_MGR_READ_APIS_H__
#define __TRAFFIC_MGR_READ_APIS_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_read_apis.h
 * \brief This file contains APIs for Traffic Manager application to
 *        read/get configuration from hardware.
 */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * Get pipe limit.  Default value of the pipe limit
 * is set to maximum buffering capability of the traffic manager.
 *
 * When admitting packet into Traffic manager, apart from other
 * checks, the packet has to also pass usage check on per egress pipe
 * usage limit. A packet destined to egress pipe whose limit  has
 * crossed, will not be admitted.
 *
 * Related API: bf_tm_pipe_egress_limit_set()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier
 * @param cells      Limits in terms of number of cells.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pipe_egress_limit_get(bf_dev_id_t dev,
                                        bf_dev_pipe_t pipe,
                                        uint32_t *cells);

/**
 * Get pipe hysteresis limit. When usage of cells goes below the hysteresis
 * limit, pipe level drop condition  will be cleared.
 *
 * Related API: bf_tm_pipe_egress_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier
 * @param cells      Limits in terms of number of cells.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pipe_egress_hysteresis_get(bf_dev_id_t dev,
                                             bf_dev_pipe_t pipe,
                                             uint32_t *cells);

/* @} */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * This API can be used to get queue count and mapping of a port.
 *
 * Related APIs: bf_tm_port_q_mapping_set ()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param q_count    number of queues used for the port.
 * @param q_mapping  Array of integer values specifying queue mapping
 *                   Mapping is indexed by ig_intr_md.qid.
 *                   Value q_mapping[ig_intr_md.qid] is port's QID
 *                   :
 *                   Caller has to provide array of size 32.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_q_mapping_get(bf_dev_id_t dev,
                                     bf_dev_port_t port,
                                     uint8_t *q_count,
                                     uint8_t *q_mapping);

/**
 * A queue can be optionally assigned to any application pool.
 * When assigned to application pool, get static or dynamic shared limit
 *
 * Related APIs: bf_tm_q_app_pool_usage_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            port handle.
 * @param queue           queue identifier. Valid range [ 0..31 ]
 * @param pool            Application pool to which queue is assigned to.
 *                        Valid values are BF_TM_EG_POOL0..3.
 * @param base_use_limit  Limit to which PPG can grow inside application
 *                        pool. Once this limit is crossed, if queue burst
 *                        absroption factor (BAF) is non zero, depending
 *                        availability of buffer, queue is allowed to
 *                        use buffer upto BAF limit. If BAF limit is zero,
 *                        queue is treated as static and no dynamic
 *thresholding.
 * @param dynamic_baf     One of the values listed in bf_tm_queue_baf_t
 *                        When BF_TM_QUEUE_BAF_DISABLE is used, queue uses
 *                        static limit.
 * @param hysteresis      Hysteresis value of queue.
 * @return                Status of API call.
 */

bf_status_t bf_tm_q_app_pool_usage_get(bf_dev_id_t dev,
                                       bf_dev_port_t port,
                                       bf_tm_queue_t queue,
                                       bf_tm_app_pool_t *pool,
                                       uint32_t *base_use_limit,
                                       bf_tm_queue_baf_t *dynamic_baf,
                                       uint32_t *hysteresis);

/**
 * Get queue min limits. Returned limits are accounted in terms of cells.
 *
 * Related APIs: bf_tm_q_guaranteed_min_limit_set()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue identifier. Valid range [ 0..31 ]
 * @param cells      Queue limits specified in cell count
 */
bf_status_t bf_tm_q_guaranteed_min_limit_get(bf_dev_id_t dev,
                                             bf_dev_port_t port,
                                             bf_tm_queue_t queue,
                                             uint32_t *cells);

/**
 * Get color drop limits for queue.
 *
 * Related APIs: bf_tm_q_color_limit_set ()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose dynamic limits has to be adjusted.
 * @param color      Color (RED, YELLOW)
 * @param limit      Color Limit is specified in percentage of guaranteed queue
 *                   limit.
 *                   Green Color limit is equal to queue limit.
 *                   For yellow, red, limit obtained is percentage of overall
 *                   queue share limit. Once queue usage reaches the limit,
 *                   appropriate colored packets are tail dropped.
 *                   To get GREEN Color limit use
 *                   bf_tm_q_guaranteed_min_limit_get()
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_color_limit_get(bf_dev_id_t dev,
                                    bf_dev_port_t port,
                                    bf_tm_queue_t queue,
                                    bf_tm_color_t color,
                                    bf_tm_queue_color_limit_t *limit);

/**
 * Get color hysteresis for queue.
 *
 * Related APIs: bf_tm_q_color_hysteresis_get ()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose dynamic limits has to be adjusted.
 * @param color      Color (RED, YELLOW, GREEN)
 * @param cells      Number of cells queue usage drops to
 *                   when drop condition is cleared.
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_color_hysteresis_get(bf_dev_id_t dev,
                                         bf_dev_port_t port,
                                         bf_tm_queue_t queue,
                                         bf_tm_color_t color,
                                         uint32_t *cells);

/**
 * This API can be used to get cut through buffer size on per port basis.
 * The specified size is set aside for unicast traffic in cut through mode.
 *
 * Related APIs: bf_tm_port_uc_cut_through_limit_set()
 *
 * @param dev        ASIC device identifier.
 * @param port       Port handle.
 * @param size       Size in terms of cells (upto 16). Valid value [1..15]
 *                   If size is set to zero, then cut through get disabled.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_uc_cut_through_limit_get(bf_dev_id_t dev,
                                                bf_dev_port_t port,
                                                uint8_t *size);

/* @} */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * Get total number of supported PPGs.
 *
 * Related APIs: bf_tm_ppg_unusedppg_get()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe identifier.
 * @param total_ppg  Pointer to unsigned integer location where total
 *                   supported PPG count will be stored.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_totalppg_get(bf_dev_id_t dev,
                                   bf_dev_pipe_t pipe,
                                   uint32_t *total_ppg);

/**
 * Get total number of unused PPGs.
 *
 * Related APIs: bf_tm_ppg_totalppg_get()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe identifier.
 * @param total_ppg  Pointer to unsigned integer location where
 *                    current unused PPG count will be stored.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_unusedppg_get(bf_dev_id_t dev,
                                    bf_dev_pipe_t pipe,
                                    uint32_t *unused_ppg);

/**
 * A non deafult PPG can be optionally assigned to any application pool.
 * When assigned to application pool, get static or dynamic shared limit
 *
 * Related APIs: bf_tm_ppg_app_pool_usage_set()
 *
 * @param dev             ASIC device identifier.
 * @param ppg             ppg handle.
 * @param pool            Application pool to which PPG is assigned to.
 * @param base_use_limit  Limit to which PPG can grow inside application
 *                        pool. Once this limit is crossed, if PPG burst
 *                        absroption factor (BAF) is non zero, depending
 *                        availability of buffer, PPG is allowed to
 *                        use buffer upto BAF limit. If BAF limit is zero,
 *                        PPG is treated as static and no dynamic thresholding.
 * @param dynamic_baf     One of the values listed in bf_tm_ppg_baf_t
 *                        When BF_TM_PPG_BAF_DISABLE is used, PPG uses
 *                        static limit.
 * @param hysteresis      Hysteresis value.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_app_pool_usage_get(bf_dev_id_t dev,
                                         bf_tm_ppg_hdl ppg,
                                         bf_tm_app_pool_t pool,
                                         uint32_t *base_use_limit,
                                         bf_tm_ppg_baf_t *dynamic_baf,
                                         uint32_t *hysteresis);

/**
 * Get PPG miminum limits. Returned limits are accounted in terms of cells.
 *
 * Related APIs: bf_tm_ppg_guaranteed_min_limit_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg whose limits has to be adjusted.
 * @param cells      Number of cells set as minimum limit
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_guaranteed_min_limit_get(bf_dev_id_t dev,
                                               bf_tm_ppg_hdl ppg,
                                               uint32_t *cells);

/**
 * Get ppg skid limits.
 *
 * Related APIs: bf_tm_ppg_skid_limit_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg whose skid limits has to be fetched.
 * @param cells      Limits in terms of number of cells
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_skid_limit_get(bf_dev_id_t dev,
                                     bf_tm_ppg_hdl ppg,
                                     uint32_t *cells);

/**
 * Get ppg hysteresis limits. Same hysteresis limits are applied to
 * PPGs limits inside MIN pool and PPGs mapped to Skid Pool.
 * Hysterisis limits are numbers of cells the ppg usage should fall by
 * from its limit value. Once usage limits are below hysteresis, appropriate
 * condition is cleared. Example when PPG's skid usage limit falls
 * below its allowed limits limit by hysteresis value, drop condition is
 * cleared.
 *
 * Related APIs: bf_tm_ppg_skid_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg whose hysteresis limits has to be fetched.
 * @param cells      Limits in terms of number of cells
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_guaranteed_min_skid_hysteresis_get(bf_dev_id_t dev,
                                                         bf_tm_ppg_hdl ppg,
                                                         uint32_t *cells);

/**
 * Get all iCoS (iCoS = ig_intr_md.ingress_cos) traffic is attached to PPG
 *
 *
 * Related APIs: bf_tm_ppg_icos_mapping_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg handle
 * @param icos_bmap  Bit map of iCoS (iCoS = ig_intr_md.ingress_cos).
 *                   Bit 7 is interpreted as iCoS 7 that is attached.
 *                   ppg handle.
 * @return           Status of API call.
 *
 */
bf_status_t bf_tm_ppg_icos_mapping_get(bf_dev_id_t dev,
                                       bf_tm_ppg_hdl ppg,
                                       uint8_t *icos_bmap);

/* @} */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * Get application pool size. Size in units of cell set aside for
 * application pool.
 *
 * Related APIs: bf_tm_pool_size_set()
 *
 * @param dev             ASIC device identifier.
 * @param pool            pool identifier.
 * @param cells           Size of pool in terms of cells.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_size_get(bf_dev_id_t dev,
                                bf_tm_app_pool_t pool,
                                uint32_t *cells);

/**
 * Get Application pool color drop limits.
 *
 * Related APIs: bf_tm_pool_color_drop_limit_set()
 *
 * @param dev             ASIC device identifier.
 * @param pool            pool handle.
 * @param color           Color (Green, Yellow, Red)
 * @param limit           Limits in terms of cells.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_color_drop_limit_get(bf_dev_id_t dev,
                                            bf_tm_app_pool_t pool,
                                            bf_tm_color_t color,
                                            uint32_t *limit);

/**
 * Get Color drop hysteresis. The same hysteresis value is applied on
 * all application pools. Resume condition is triggered when pool usage drops
 * by hysteresis value.
 *
 * Related APIs: bf_tm_pool_color_drop_hysteresis_set()
 *
 * @param dev             ASIC device identifier.
 * @param color           Color (Green, Yellow, Red)
 * @param limit           Limits in terms of cells.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_color_drop_hysteresis_get(bf_dev_id_t dev,
                                                 bf_tm_color_t color,
                                                 uint32_t *limit);

/**
 * Get per PFC level limit values. PFC level limits are configurable on per
 * application pool basis. When usage numbers hit pfc limits, PAUSE is triggered
 * for lossless traffic or PFC enabled traffc.
 *
 * Related APIs: bf_tm_pool_pfc_limit_set()
 *
 * @param dev             ASIC device identifier.
 * @param pool            pool handle for which limits are configured.
 * @param icos            Internal CoS (iCoS = ig_intr_md.ingress_cos) level
 *                        on which limits are applied.
 * @param limit           Limit value in terms of cell count.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_pfc_limit_get(bf_dev_id_t dev,
                                     bf_tm_app_pool_t pool,
                                     bf_tm_icos_t icos,
                                     uint32_t *limit);

/**
 * Get Application pool's color drop policy. Default policy is to
 * trigger drops based on color.
 *
 * @param dev             ASIC device identifier.
 * @param pool            pool identifier.
 * @param drop_state      Drop or no drop condition
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_color_drop_state_get(bf_dev_id_t dev,
                                            bf_tm_app_pool_t pool,
                                            bool *drop_state);

/**
 * Get skid pool size.
 *
 * Related APIs: bf_tm_pool_skid_size_set()
 *
 * @param dev             ASIC device identifier.
 * @param cells           Size of pool in terms of cells.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_skid_size_get(bf_dev_id_t dev, uint32_t *cells);

/**
 * Get global skid pool hysteresis.
 *
 * Related APIs: bf_tm_pool_skid_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param cells      Number of cells set as skid pool hysteresis.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pool_skid_hysteresis_get(bf_dev_id_t dev, uint32_t *cells);

/**
 * Get negative mirror pool limit. Returned limit are accounted
 * in terms of cells.
 *
 * Related APIs: bf_tm_pool_mirror_on_drop_size_set()
 *
 * @param dev        ASIC device identifier.
 * @param cells      Size of pool.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pool_mirror_on_drop_size_get(bf_dev_id_t dev,
                                               uint32_t *cells);

/**
 * Get negative mirror destination in a pipe.
 *
 * Related APIs: bf_tm_port_mirror_on_drop_dest_set()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Device pipe.
 * @param port       Negative mirror traffic destination port.
 * @param queue      Negative mirror traffic queue within destination port.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_mirror_on_drop_dest_get(bf_dev_id_t dev,
                                               bf_dev_pipe_t pipe,
                                               bf_dev_port_t *port,
                                               bf_tm_queue_t *queue);

/**
 * Get cut through pool size for unicast traffic.
 *
 * Related APIs:  bf_tm_pool_uc_cut_through_size_set()
 *
 * @param dev             ASIC device identifier.
 * @param cells           Size of pool in terms of cells.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_uc_cut_through_size_get(bf_dev_id_t dev,
                                               uint32_t *cells);

/**
 * Get cut through pool size for Multicast traffic. This size determines total
 * buffer set aside for multicast cut through traffic.
 *
 * Related APIs:  bf_tm_pool_mc_cut_through_size_set()
 *
 * @param dev             ASIC device identifier.
 * @param cells           Size of pool in terms of cells.
 * @return                Status of API call.
 */
bf_status_t bf_tm_pool_mc_cut_through_size_get(bf_dev_id_t dev,
                                               uint32_t *cells);

/* @} */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * Get port limit. When buffer usage accounted on port basis
 * crosses the limit, traffic is not admitted into traffic manager.
 *
 * Related APIs: bf_tm_port_ingress_drop_limit_set()
 *
 * @param dev        ASIC device identifier.
 * @param port       Port Identifier
 * @param cells      Limit in terms of number of cells.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_ingress_drop_limit_get(bf_dev_id_t dev,
                                              bf_dev_port_t port,
                                              uint32_t *cells);

/**
 * Get port hysteresis limits.
 * When usage of cells goes below hysteresis value  port pause or drop
 * condition  will be cleared.
 *
 * Related APIs: bf_tm_port_ingress_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param port       Port Identifier
 * @param cells      Offset Limit
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_ingress_hysteresis_get(bf_dev_id_t dev,
                                              bf_dev_port_t port,
                                              uint32_t *cells);

/* @} */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * This API can be used to get pause type set on port.
 *
 * Related APIs: bf_tm_port_flowcontrol_mode_set()
 *
 * Default : No Pause or flow control.
 *
 * @param dev        ASIC device identifier.
 * @param port       Port handle.
 * @param type       Pause type.
 * @return           Status of API call.
 *
 */
bf_status_t bf_tm_port_flowcontrol_mode_get(bf_dev_id_t dev,
                                            bf_dev_port_t port,
                                            bf_tm_flow_ctrl_type_t *type);

/**
 * This API can be used to get pause type set on port to react when
 * port sees pause or pfc from peer.
 *
 * Related APIs: bf_tm_port_flowcontrol_rx_set()
 *               bf_tm_port_flowcontrol_mode_set()
 *
 * Default : Ignore Pause, PFC.
 *
 * @param dev        ASIC device identifier.
 * @param port       Port handle.
 * @param type       Pause type.
 * @return           Status of API call.
 *
 */
bf_status_t bf_tm_port_flowcontrol_rx_get(bf_dev_id_t dev,
                                          bf_dev_port_t port,
                                          bf_tm_flow_ctrl_type_t *type);

/**
 * Get iCoS(iCoS = ig_intr_md.ingress_cos) to packet CoS.
 *
 * Default: No PFC
 *
 * Related APIs: bf_tm_port_pfc_cos_mapping_set()
 *
 * @param dev         ASIC device identifier.
 * @param port        Port handle
 * @param cos_to_icos Array of 8 uint8_t values.
 *                    Array index is CoS and array value is iCoS.
 * @return            Status of API call.
 *
 */
bf_status_t bf_tm_port_pfc_cos_mapping_get(bf_dev_id_t dev,
                                           bf_dev_port_t port,
                                           uint8_t *cos_to_icos);

/**
 * This API can be used to get cut-through enable status of a port.
 *
 * Related APIs: bf_tm_port_cut_through_enable()
 *               bf_tm_port_cut_through_disable()
 *
 * Default : Cut-through is disabled.
 *
 * @param dev        ASIC device identifier.
 * @param port       Port handle.
 * @param sw_ct_enabled      Cut-through enable status in TM SW cache
 * @param hw_ct_enabled      Cut-through enable status in TM HW register
 * @return           Status of API call.
 *
 */
bf_status_t bf_tm_port_cut_through_enable_status_get(bf_dev_id_t dev,
                                                     bf_dev_port_t port,
                                                     bool *sw_ct_enabled,
                                                     bool *hw_ct_enabled);

/**
 * Get number of Global timestamp bits that are right shifted.
 *
 * @param dev           ASIC device identifier.
 * @param shift         Number of Global timestamp bits that are right shifted.
 * @return              Status of API call.
 */
bf_status_t bf_tm_timestamp_shift_get(bf_dev_id_t dev, uint8_t *shift);

/* @} */

#endif
