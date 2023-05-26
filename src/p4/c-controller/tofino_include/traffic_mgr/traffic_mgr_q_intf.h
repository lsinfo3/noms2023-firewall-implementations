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
 * This file describes  APIs for Traffic Manager application
 * to program Traffic Manager block to desired QoS behaviour.
 */

#ifndef __TRAFFIC_MGR_Q_INTF_H__
#define __TRAFFIC_MGR_Q_INTF_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_q_intf.h
 * \brief This file contains APIs for Traffic Manager application to
 *        program Queues meant to implement part of QoS behaviour based on
 *        traffic properties. Traffic with similar characteristics destined
 *        to egress ports can be queued together.
 *        APIs in this file facilitate queue QoS management.
 */

/**
 * @addtogroup tm-egress
 * @{
 *  Description of APIs for Traffic Manager application to manage
 *  egress buffer and queues meant to implement part of QoS behaviour
 *  based on traffic properties.
 */

/* q_mapping : array of 32 integers specifying queue numbering for
 * finer queue allocation to ports. Return type should be checked.
 * Depending upon hardware resources available at the time of API invocation,
 * special queue carving may or may not be possible to accomodate.
 *
 * Related APIs :
 *    dvm_add_port_with_queues()
 *    bf_tm_allocate_deafult_queues()
 *    bf_tm_allocate_queues()
 *
 */
/**
 * This API can be used to allocate flexible number of queues behind a port.
 * By default straight mapping is established. If flexible queue mapping is
 * desired, this API can be used.
 * Default mapping or when q_mapping is NULL, queue mapping is according to
 * following calculation.
 *    queue# = Ig_intr_md.qid % q_count.
 *    Example Queue mapping in default mode:
 *                   Ig_intr_md.qid 0 --> port qid 0
 *                   Ig_intr_md.qid 1 --> port qid 1
 *                         :
 *                   Ig_intr_md.qid 7 --> port qid 7
 *                         :
 *
 * NOTE: If this API gets called for changing the queue carving (queue count),
 * then application should
 *   - always call queue mapping APIs strictly in increasing order of ports
 *      within a port group
 *   - if queue count gets changed for a port/channel in a port group,
 *      then application should call the queue mapping APIs
 *      for rest of the ports after it (if present) in that port group in
 *      increasing order
 *   - if queue count gets changed, then calling this API while traffic
 *      running on any port within the port group is not recommended as
 *      traffic would be disrupted for a short period of time and buffer
 *      accounting would be inconsistent
 * The above restrictions are not applicable if just queue mapping gets changed
 *
 *
 * Related APIs: bf_tm_port_q_mapping_get()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param q_count    number of queues being mapped.
 * @param q_mapping  Array of integer values specifying queue mapping
 *                   Mapping is indexed by ig_intr_md.qid.
                     Value q_mapping[ig_intr_md.qid] is port's QID
 *                   :
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_q_mapping_set(bf_dev_id_t dev,
                                     bf_dev_port_t port,
                                     uint8_t q_count,
                                     uint8_t *q_mapping);

/**
 * This API can be used to allocate flexible number of queues behind a port.
 * By default straight mapping is established. If flexible queue mapping is
 * desired, this API can be used.
 * Default mapping or when q_mapping is NULL, queue mapping is according to
 * following calculation.
 *    queue# = Ig_intr_md.qid % q_count.
 *    Example Queue mapping in default mode:
 *                   Ig_intr_md.qid 0 --> port qid 0
 *                   Ig_intr_md.qid 1 --> port qid 1
 *                         :
 *                   Ig_intr_md.qid 7 --> port qid 7
 *                         :
 *
 * NOTE: If this API gets called for changing the queue carving (queue count),
 * then application should
 *   - always call queue mapping APIs strictly in increasing order of ports
 *      within a port group
 *   - if queue count gets changed for a port/channel in a port group,
 *      then application should call the queue mapping APIs
 *      for rest of the ports after it (if present) in that port group in
 *      increasing order
 *   - if queue count gets changed, then calling this API while traffic
 *      running on any port within the port group is not recommended as
 *      traffic would be disrupted for a short period of time and buffer
 *      accounting would be inconsistent
 * The above restrictions are not applicable if just queue mapping gets changed
 *
 * Queue speeds must be a multiple of 50G in the range 50G - 400G. Resources
 * allow for up to 6400G of queue speed to be allocated across a port group.
 *
 * Related APIs: bf_tm_port_q_mapping_get()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param q_count    number of queues being mapped.
 * @param q_count    Array of integer values specifying queue speeds
 * @param q_mapping  Array of integer values specifying queue mapping
 *                   Mapping is indexed by ig_intr_md.qid.
                     Value q_mapping[ig_intr_md.qid] is port's QID
 *                   :
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_q_mapping_speed_set(bf_dev_id_t dev,
                                           bf_dev_port_t port,
                                           uint8_t q_count,
                                           uint16_t *q_speeds,
                                           uint8_t *q_mapping);

/**
 * A queue can be optionally assigned to any application pool.
 * When assigned to application pool, static or dynamic shared limit
 * can be set. This API aids to achieve that. If it is desired to not
 * assign queue to any pool, then this API need not be invoked.
 * Advantage of belonging to a pool of queues is that queue can share
 * resources. Hence can grow to dynamic limit depending on burst absorption
 * factor and pool usage number. Dynamic limit will be higher than its own
 * queue limit. If statis limit is used, then  queue can usage upto its
 * own limit before tail drop condition occurs.
 *
 * Default: Queues are not assigned to any application pool.
 *
 * Related APIs: bf_tm_q_app_pool_usage_get()
 *
 * @param dev             ASIC device identifier.
 * @param port            port handle.
 * @param queue           queue identifier. Valid range [ 0..31 ]
 * @param pool            Application pool to which queue is assigned to.
 *                        Valid values are BF_TM_EG_POOL0..3.
 * @param base_use_limit  Limit to which PPG can grow inside application
 *                        pool. Limit is specified in terms of cells.
 *                        Once this limit is crossed, if queue burst
 *                        absroption factor (BAF) is non zero, depending
 *                        availability of buffer, queue is allowed to
 *                        use buffer upto BAF limit. If BAF limit is zero,
 *                        queue is treated as static and no dynamic
 *                        buffering is possible.
 * @param dynamic_baf     One of the values listed in bf_tm_queue_baf_t
 *                        When BF_TM_QUEUE_BAF_DISABLE is used, queue uses
 *                        static limit.
 * @param hysteresis      Hysteresis value of queue in cells .
 * @return                Status of API call.
 */

bf_status_t bf_tm_q_app_pool_usage_set(bf_dev_id_t dev,
                                       bf_dev_port_t port,
                                       bf_tm_queue_t queue,
                                       bf_tm_app_pool_t pool,
                                       uint32_t base_use_limit,
                                       bf_tm_queue_baf_t dynamic_baf,
                                       uint32_t hysteresis);

/**
 * This API can be used to disable queue participation in application
 * pool. In such case, once q's gmin limits are used, queue tail drop
 * can occur.
 *
 * Related APIs: bf_tm_q_app_pool_usage_set()
 *
 * @param dev        ASIC device identifier.
 * @param port       Port handle.
 * @param queue      queue identifier
 * @return           Status of API call.
 *
 */

bf_status_t bf_tm_q_app_pool_usage_disable(bf_dev_id_t dev,
                                           bf_dev_port_t port,
                                           bf_tm_queue_t queue);

/**
 * Set queue min limits. Inorder to increase min limits, MIN pool should
 * have that many free cells unused. If not available, limits cannot be
 * increased and API fails.When queue limits are decreased, in the absence
 * of shared/application pools, decreased number of cells will be unused
 * and earmarked for future use. These unused cells can be used in future
 * to increase queue limits. If application pools are carved out, then the
 * decreased number of cells are equally distributed to all application pools
 * by raising their pool limits.
 *
 * Default: TM buffer is equally distribted to all queues assuming all queues
 *          are active.
 *
 * Related APIs: bf_tm_q_guaranteed_min_limit_get()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue identifier. Valid range [ 0..31 ]
 * @param cells      Queue limits specified in cell count
 */
bf_status_t bf_tm_q_guaranteed_min_limit_set(bf_dev_id_t dev,
                                             bf_dev_port_t port,
                                             bf_tm_queue_t queue,
                                             uint32_t cells);

/**
 * Set color drop limits for queue. Color drop limits for red should
 * be less than color drop limits of yellow, which inturn is less than
 * color drop limits of green.
 *
 * Default: Color drop limits for yellow and red are set to 75% of gmin
 *          size of queue.
 *
 * Related APIs: bf_tm_q_color_drop_enable(), bf_tm_q_color_limit_get()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose color drop limit to be set.
 * @param color      Color (RED, YELLOW)
 * @param limit      Color Limit is specified in percentage of
 *                   guaranteed queue limit.
 *                   Green Color limit is equal to queue limit.
 *                   For yellow, red, limit can be set as percentage of
 *                   overall queue limit. Once queue usage reaches the limit,
 *                   appropriate colored packets are dropped.
 *                   To set GREEN Color limit use
 *                   bf_tm_q_guaranteed_min_limit_set()
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_color_limit_set(bf_dev_id_t dev,
                                    bf_dev_port_t port,
                                    bf_tm_queue_t queue,
                                    bf_tm_color_t color,
                                    bf_tm_queue_color_limit_t limit);

/**
 * Set queue's color drop hysteresis. When queue's usage for a color
 * falls below by hysteresis value, tail drop condition is cleared.
 *
 * Default: Color hysteresis limits are set to  zero.
 *
 * Related APIs: bf_tm_q_color_drop_enable(), bf_tm_q_color_limit_get()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose color drop limit to be set.
 * @param color      Color (RED, YELLOW)
 * @param limit      Number of cells queue usage should reduce before
 *                   before drop condition for appropriate colored packets is
 *                   cleared.
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_color_hysteresis_set(bf_dev_id_t dev,
                                         bf_dev_port_t port,
                                         bf_tm_queue_t queue,
                                         bf_tm_color_t color,
                                         bf_tm_queue_color_limit_t limit);

/**
 * Enable queue tail drop condition. When queue
 * threshold limits (guranteed min limit + shared limit)
 * are reached, packets are dropped.
 *
 * Default : Trigger drops when queue threshold limits are reached.
 *
 * Related APIs: bf_tm_q_tail_drop_disable()
 *
 * param dev        ASIC device identifier.
 * param port       port handle.
 * param queue      queue for which tail drop has to be enabled.
 * return           Status of API call.
 */
bf_status_t bf_tm_q_tail_drop_enable(bf_dev_id_t dev,
                                     bf_dev_port_t port,
                                     bf_tm_queue_t queue);

/**
 * Disable queue tail drop condition. When queue
 * threshold limits (guranteed min limit + shared limit)
 * are reached, packets are not dropped in Egress. This
 * will lead to Ingress drops eventually.
 *
 * Default : Trigger drops when queue threshold limits are reached.
 *
 * Related APIs: bf_tm_q_tail_drop_enable()
 *
 * param dev        ASIC device identifier.
 * param port       port handle.
 * param queue      queue for which tail drop has to be disabled.
 * return           Status of API call.
 */
bf_status_t bf_tm_q_tail_drop_disable(bf_dev_id_t dev,
                                      bf_dev_port_t port,
                                      bf_tm_queue_t queue);

/**
 * Enable queue color drop condition. Based on packet color, when queue
 * color threshold limit are reached, packets are dropped.
 * When color drop is not enabled, packets do not get any treatment
 * based on their color.
 *
 * Default : Trigger drops based on color.
 *
 * Related APIs: bf_tm_q_color_drop_disable()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose color drop is to set.
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_color_drop_enable(bf_dev_id_t dev,
                                      bf_dev_port_t port,
                                      bf_tm_queue_t queue);

/**
 * Disable queue color drop condition. Based on packet color, when queue
 * color threshold limit are reached, packets are dropped. When color drop
 * is not enabled, packets do not get any treatment based on their color.
 *
 * Related APIs: bf_tm_q_color_drop_enable()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose color drop is to set.
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_color_drop_disable(bf_dev_id_t dev,
                                       bf_dev_port_t port,
                                       bf_tm_queue_t queue);

/**
 * Set visible condition. Visible queues will be reported to ingress
 * MAU for Queue length cross any color threshold.
 *
 * Default : False
 *
 * Related APIs: bf_tm_q_visible_get()
 *
 * param dev        ASIC device identifier.
 * param port       port handle.
 * param queue      queue for port.
 * param visible    desired visiblity state.
 * return           Status of API call.
 */
bf_status_t bf_tm_q_visible_set(bf_dev_id_t dev,
                                bf_dev_port_t port,
                                bf_tm_queue_t queue,
                                bool visible);

/**
 * Get visible condition. Visible queues will be reported to ingress
 * MAU for Queue length cross any color threshold.
 *
 * Default : False
 *
 * Related APIs: bf_tm_q_visible_set()
 *
 * param dev        ASIC device identifier.
 * param port       port handle.
 * param queue      queue for port.
 * param visible    desired visiblity state.
 * return           Status of API call.
 */
bf_status_t bf_tm_q_visible_get(bf_dev_id_t dev,
                                bf_dev_port_t port,
                                bf_tm_queue_t queue,
                                bool *visible_sw,
                                bool *visible_hw);

/**
 * Set queue hysteresis value.
 *
 * Related APIs: bf_tm_q_app_pool_usage_set()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param queue      queue whose hysteresis is to set.
 * @param hysteresis Hysteresis value of queue in cells .
 * @return           Status of API call.
 */
bf_status_t bf_tm_q_hysteresis_set(bf_dev_id_t dev,
                                   bf_dev_port_t port,
                                   bf_tm_queue_t queue,
                                   uint32_t cells);

/**
 * Use this API to set (port, queue) used for egressing out
 * negative mirror traffic. Its possible to set one such
 * (port,queue) value for each pipe.
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param port       Negative Mirror port .
 * @param queue      Queue where negative mirror traffic is enqueued.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_mirror_on_drop_dest_set(bf_dev_id_t dev,
                                               bf_dev_pipe_t pipe,
                                               bf_dev_port_t port,
                                               bf_tm_queue_t queue);

/* @} */

/**
 * @addtogroup tm-flowcontrol
 * @{
 */
/**
 * When egress queues need to honour received PFC from downstream,
 * by mapping cos to queue using the API below, queues
 * will not participate in scheduling until PFC gets cleared.
 *
 * Default: All queues are mapping CoS zero.
 *
 * Related APIs: bf_tm_ppg_icos_mapping_set()
 *
 * @param dev         ASIC device identifier.
 * @param port        Port handle
 * @param queue       queue whose color drop is to set.
 * @param cos         CoS associated with the queue.
 * @return            Status of API call.
 */
bf_status_t bf_tm_q_pfc_cos_mapping_set(bf_dev_id_t dev,
                                        bf_dev_port_t port,
                                        bf_tm_queue_t queue,
                                        uint8_t cos);

/* @} */

#endif
