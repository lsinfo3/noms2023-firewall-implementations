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
 * This file describes APIs for Traffic Manager application
 * to program Traffic Manager block to desired QoS behaviour.
 */

#ifndef __TRAFFIC_MGR_SCH_INTF_H__
#define __TRAFFIC_MGR_SCH_INTF_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_sched_intf.h
 * \brief This file contains APIs for Traffic Manager application to
 *        program scheduler paramters to implement part of QoS behaviour based
 *        on traffic properties.
 */

/**
 * @addtogroup tm-sched
 * @{
 *  Description of APIs for Traffic Manager application to
 *  program scheduler paramters to implement desired QoS behaviour based
 *  on traffic properties.
 */

/**
 * Set queue scheduling priority. Scheduling priority level used when
 * serving guaranteed bandwidth. Higher the number, higher the  priority to
 * select the queue for scheduling.
 *
 * Default: Queue scheduling priority set to BF_TM_SCH_PRIO_7
 *
 * Related APIs: bf_tm_sched_q_remaining_bw_priority_set ()
 *
 * @param dev                   ASIC device identifier.
 * @param port                  Port
 * @param queue                 queue
 * @param priority              Scheduling priority of queue.
 */
bf_status_t bf_tm_sched_q_priority_set(bf_dev_id_t dev,
                                       bf_dev_port_t port,
                                       bf_tm_queue_t queue,
                                       bf_tm_sched_prio_t priority);

/**
 * Set queue DWRR weights. These weights are used by queues at same
 * priority level. Across prioirty these weights serve as ratio to
 * share excess or remaining bandwidth.
 *
 * Default: Queue scheduling weights set to 1023
 *
 * Related APIs: bf_tm_sched_q_priority_set(),
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param weight          Weight value. Supported range [ 1.. 1023 ]
 */
bf_status_t bf_tm_sched_q_dwrr_weight_set(bf_dev_id_t dev,
                                          bf_dev_port_t port,
                                          bf_tm_queue_t queue,
                                          uint16_t weight);

/**
 * Set queue shaping rate in units of kbps or pps.
 *
 * Default: Queue shaping rate set to match port bandwidth.
 *
 * Related APIs: bf_tm_sched_q_guaranteed_rate_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size in pps or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_q_shaping_rate_set(bf_dev_id_t dev,
                                           bf_dev_port_t port,
                                           bf_tm_queue_t queue,
                                           bool pps,
                                           uint32_t burst_size,
                                           uint32_t rate);

/**
 * Enable token bucket that assures queue shaping rate (pps or bps)
 *
 * Default: Queue shaping rate is enabled
 *
 * Related APIs: bf_tm_sched_q_max_shaping_rate_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_max_shaping_rate_enable(bf_dev_id_t dev,
                                                  bf_dev_port_t port,
                                                  bf_tm_queue_t queue);

/**
 * Disable token bucket that assures queue shaping rate (pps or bps)
 *
 * Default: Queue shaping rate is enabled
 *
 * Related APIs: bf_tm_sched_q_max_shaping_rate_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_max_shaping_rate_disable(bf_dev_id_t dev,
                                                   bf_dev_port_t port,
                                                   bf_tm_queue_t queue);

/**
 * Set queue guaranteed rate in terms of pps or kbps.
 *
 * Default: Queue shaping rate set to match port bandwidth.
 *
 * Related APIs: bf_tm_sched_q_guaranteed_rate_get()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size in pps or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_q_guaranteed_rate_set(bf_dev_id_t dev,
                                              bf_dev_port_t port,
                                              bf_tm_queue_t queue,
                                              bool pps,
                                              uint32_t burst_size,
                                              uint32_t rate);

/**
 * Set scheduling priority when serving remaining bandwidth.
 * Higher the number, higher the  priority to select the queue for
 * scheduling.
 *
 * Default: Queue scheduling priority set to BF_TM_SCH_PRIO_7
 *
 * Related APIs: bf_tm_sched_q_remaining_bw_priority_get ()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param priority        Scheduling priority of queue.
 */
bf_status_t bf_tm_sched_q_remaining_bw_priority_set(
    bf_dev_id_t dev,
    bf_dev_port_t port,
    bf_tm_queue_t queue,
    bf_tm_sched_prio_t priority);

/**
 * Enable token bucket that assures queue guaranteed rate (pps or bps)
 *
 * Default: Queue guaranteed shaping rate is disabled
 *
 * Related APIs: bf_tm_sched_q_guaranteed_rate_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_guaranteed_rate_enable(bf_dev_id_t dev,
                                                 bf_dev_port_t port,
                                                 bf_tm_queue_t queue);

/**
 * Disable token bucket that assures queue guaranteed rate (pps or bps)
 *
 * Default: Queue guaranteed shaping rate is disabled
 *
 * Related APIs: bf_tm_sched_q_guaranteed_rate_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_guaranteed_rate_disable(bf_dev_id_t dev,
                                                  bf_dev_port_t port,
                                                  bf_tm_queue_t queue);

/**
 * Set port shaping rate in units of kbps or pps.
 *
 * Related APIs: bf_tm_sched_q_shaping_rate_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size in pps or bytes.
 * @param shaper          Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_port_shaping_rate_set(bf_dev_id_t dev,
                                              bf_dev_port_t port,
                                              bool pps,
                                              uint32_t burst_size,
                                              uint32_t rate);

/**
 * Set number of bytes added per packet to packet length by shaper
 *
 * Default: Zero bytes are added to packet to length.
 *
 * Related APIs: bf_tm_sched_pkt_ifg_compensation_get
 *
 * @param dev             ASIC device identifier.
 * @param pipe            Pipe identifier.
 * @param adjustment      Byte adjustment done on every packet.
 */
bf_status_t bf_tm_sched_pkt_ifg_compensation_set(bf_dev_id_t dev,
                                                 bf_dev_pipe_t pipe,
                                                 uint8_t adjustment);

/**
 * Enable queue scheduling. If disabled, queue will not participate in
 * scheduling.
 *
 * Default: By deafult, queue is enabled to schedule its traffic
 *          towards egress pipe/MAC.
 *
 * Related APIs: bf_tm_disable_q
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_enable(bf_dev_id_t dev,
                                 bf_dev_port_t port,
                                 bf_tm_queue_t queue);

/**
 * Disable queue scheduling. If disabled, queue will not participate in
 * scheduling.
 *
 * Default: By deafult, queue is enabled to schedule its traffic
 *          towards egress pipe/MAC.
 *
 * Related APIs: bf_tm_enable_q
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_disable(bf_dev_id_t dev,
                                  bf_dev_port_t port,
                                  bf_tm_queue_t queue);

/**
 * Associate queue with l1 node for further scheduling.
 *
 * Default: By deafult, queue is set to schedule with the default l1 node
 * for a port.
 *
 * Related APIs: bf_tm_sched_q_l1_reset
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_l1_set(bf_dev_id_t dev,
                                 bf_dev_port_t port,
                                 bf_tm_l1_node_t l1_node,
                                 bf_tm_queue_t queue);

/**
 * Set queue to default l1 node for its port. Note that the port must have at
 * least 1 l1 node assigned to it.
 *
 * Related APIs: bf_tm_sched_q_l1_set
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_q_l1_reset(bf_dev_id_t dev,
                                   bf_dev_port_t port,
                                   bf_tm_queue_t queue);

/**
 * Set l1 node scheduling priority. Scheduling priority level used when
 * serving guaranteed bandwidth. Higher the number, higher the  priority to
 * select the l1 node for scheduling.
 *
 * Default: l1 node scheduling priority set to BF_TM_SCH_PRIO_7
 *
 * Related APIs: bf_tm_sched_l1_remaining_bw_priority_set ()
 *
 * @param dev                   ASIC device identifier.
 * @param port                  Port
 * @param l1_node               l1 node
 * @param priority              Scheduling priority of queue.
 */
bf_status_t bf_tm_sched_l1_priority_set(bf_dev_id_t dev,
                                        bf_dev_port_t port,
                                        bf_tm_l1_node_t l1_node,
                                        bf_tm_sched_prio_t priority);

/**
 * Set l1 node DWRR weights. These weights are used by l1 nodes at same
 * priority level. Across prioirty these weights serve as ratio to
 * share excess or remaining bandwidth.
 *
 * Default: l1 node scheduling weights set to 1023
 *
 * Related APIs: bf_tm_sched_l1_priority_set(),
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1 node         l1 node
 * @param weight          Weight value. Supported range [ 1.. 1023 ]
 */
bf_status_t bf_tm_sched_l1_dwrr_weight_set(bf_dev_id_t dev,
                                           bf_dev_port_t port,
                                           bf_tm_l1_node_t l1_node,
                                           uint16_t weight);

/**
 * Set l1 node shaping rate in units of kbps or pps.
 *
 * Default: l1 node shaping rate set to match port bandwidth.
 *
 * Related APIs: bf_tm_sched_l1_guaranteed_rate_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size in pps or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_l1_shaping_rate_set(bf_dev_id_t dev,
                                            bf_dev_port_t port,
                                            bf_tm_l1_node_t l1_node,
                                            bool pps,
                                            uint32_t burst_size,
                                            uint32_t rate);

/**
 * Enable token bucket that assures l1 node shaping rate (pps or bps)
 *
 * Default: l1 node shaping rate is enabled
 *
 * Related APIs: bf_tm_sched_l1_max_shaping_rate_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_max_shaping_rate_enable(bf_dev_id_t dev,
                                                   bf_dev_port_t port,
                                                   bf_tm_l1_node_t l1_node);

/**
 * Disable token bucket that assures l1 node shaping rate (pps or bps)
 *
 * Default: l1 node shaping rate is enabled
 *
 * Related APIs: bf_tm_sched_l1_max_shaping_rate_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_max_shaping_rate_disable(bf_dev_id_t dev,
                                                    bf_dev_port_t port,
                                                    bf_tm_l1_node_t l1_node);

/**
 * Enable priority propagation from child queues
 *
 * Default: priority propagation is disabled
 *
 * Related APIs: bf_tm_sched_l1_priority_prop_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */
bf_status_t bf_tm_sched_l1_priority_prop_enable(bf_dev_id_t dev,
                                                bf_dev_port_t port,
                                                bf_tm_l1_node_t l1_node);

/**
 * Disable priority propagation from child queues
 *
 * Default: priority propagation is disabled
 *
 * Related APIs: bf_tm_sched_l1_priority_prop_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 */

bf_status_t bf_tm_sched_l1_priority_prop_disable(bf_dev_id_t dev,
                                                 bf_dev_port_t port,
                                                 bf_tm_l1_node_t l1_node);

/**
 * Set l1 node guaranteed rate in terms of pps or kbps.
 *
 * Default: l1 node shaping rate set to match port bandwidth.
 *
 * Related APIs: bf_tm_sched_l1_guaranteed_rate_get()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size in pps or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_l1_guaranteed_rate_set(bf_dev_id_t dev,
                                               bf_dev_port_t port,
                                               bf_tm_l1_node_t l1_node,
                                               bool pps,
                                               uint32_t burst_size,
                                               uint32_t rate);

/**
 * Set scheduling priority when serving remaining bandwidth.
 * Higher the number, higher the  priority to select the l1 node for
 * scheduling.
 *
 * Default: l1 node scheduling priority set to BF_TM_SCH_PRIO_7
 *
 * Related APIs: bf_tm_sched_l1_remaining_bw_priority_get ()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 * @param priority        Scheduling priority of l1 node.
 */
bf_status_t bf_tm_sched_l1_remaining_bw_priority_set(
    bf_dev_id_t dev,
    bf_dev_port_t port,
    bf_tm_l1_node_t l1_node,
    bf_tm_sched_prio_t priority);

/**
 * Enable token bucket that assures l1 node guaranteed rate (pps or bps)
 *
 * Default: l1 node guaranteed shaping rate is disabled
 *
 * Related APIs: bf_tm_sched_l1_guaranteed_rate_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_guaranteed_rate_enable(bf_dev_id_t dev,
                                                  bf_dev_port_t port,
                                                  bf_tm_l1_node_t l1_node);

/**
 * Disable token bucket that assures l1 node guaranteed rate (pps or bps)
 *
 * Default: l1 node guaranteed shaping rate is disabled
 *
 * Related APIs: bf_tm_sched_l1_guaranteed_rate_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_guaranteed_rate_disable(bf_dev_id_t dev,
                                                   bf_dev_port_t port,
                                                   bf_tm_l1_node_t l1_node);

/**
 * Enable l1 node scheduling. If l1 is not associated with a port, the l1 node
 * will be allocated to the port. l1 node cannot already be associated with
 * another port.
 *
 * Default: By deafult, each port receives an l1 one when a queue is first
 * allocated to it.
 *
 * Related APIs: bf_tm_sched_l1_disable
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_enable(bf_dev_id_t dev,
                                  bf_dev_port_t port,
                                  bf_tm_l1_node_t l1_node);

/**
 * Disable l1 node scheduling. If disabled, l1 node will not participate in
 * scheduling.
 *
 * Default: By deafult, each port receives an l1 one when a queue is first
 * allocated to it.
 *
 * Related APIs: bf_tm_sched_l1_enable
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_disable(bf_dev_id_t dev,
                                   bf_dev_port_t port,
                                   bf_tm_l1_node_t l1_node);

/**
 * Disable l1 node and deallocate node from port. All queues must have been
 * dissocated from this l1 node before calling this function.
 *
 * Default: By deafult, each port receives an l1 one when a queue is first
 * allocated to it.
 *
 * Related APIs: bf_tm_sched_l1_enable
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param l1_node         l1 node
 */
bf_status_t bf_tm_sched_l1_free(bf_dev_id_t dev,
                                bf_dev_port_t port,
                                bf_tm_l1_node_t l1_node);

/**
 * Enable token bucket that assures port shaping rate (pps or kbps)
 *
 * Default: Port shaping rate is disabled
 *
 * Related APIs: bf_tm_sched_port_shaping_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 */
bf_status_t bf_tm_sched_port_shaping_enable(bf_dev_id_t dev,
                                            bf_dev_port_t port);

/**
 * Disable token bucket that assures port shaping rate (pps or kbps)
 *
 * Default: Port shaping rate is disabled
 *
 * Related APIs: bf_tm_sched_port_shaping_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 */
bf_status_t bf_tm_sched_port_shaping_disable(bf_dev_id_t dev,
                                             bf_dev_port_t port);

/**
 * Enable port into scheduler. When enabled, the port will participate
 * in scheduling and also port shaping is enabled.
 *
 * Default: By deafult, port is enabled to schedule its traffic
 *          towards egress pipe/MAC.
 *
 * Related APIs: bf_tm_sched_port_disable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param speed           Speed (10G/25G/40G/50G/100G)
 */
bf_status_t bf_tm_sched_port_enable(bf_dev_id_t dev,
                                    bf_dev_port_t port,
                                    bf_port_speeds_t speed);

/**
 * Disable port from scheduler. If disabled, the port will not participate
 * in scheduling and also port shaping is disabled.
 *
 * Default: By deafult, port is enabled to schedule its traffic
 *          towards egress pipe/MAC.
 *
 * Related APIs: bf_tm_sched_port_enable()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 */
bf_status_t bf_tm_sched_port_disable(bf_dev_id_t dev, bf_dev_port_t port);

/* @} */

/**
 * @addtogroup tm-get
 * @{
 */

/**
 * Get queue scheduling priority.
 * Scheduling priority level when serving guaranteed bandwidth. Higher the
 * number, higher the  priority to select the queue for scheduling.
 *
 * Related APIs: bf_tm_sched_q_priority_set()
 *
 * @param dev                   ASIC device identifier.
 * @param port                  Port
 * @param queue                 queue
 * @param priority              Scheduling priority of queue.
 */
bf_status_t bf_tm_sched_q_priority_get(bf_dev_id_t dev,
                                       bf_dev_port_t port,
                                       bf_tm_queue_t queue,
                                       bf_tm_sched_prio_t *priority);

/**
 * Get queue DWRR weights. These weights are used when queues at same
 * priority level are scheduled during excess bandwidth sharing.
 *
 * Related APIs: bf_tm_sched_q_dwrr_weight_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param weight          Weight value. Supported range [ 0.. 1023 ]
 */
bf_status_t bf_tm_sched_q_dwrr_weight_get(bf_dev_id_t dev,
                                          bf_dev_port_t port,
                                          bf_tm_queue_t queue,
                                          uint16_t *weight);

/**
 * Get queue shaping rate. Rate is in units of kbps or pps.
 *
 * Related APIs: bf_tm_sched_q_shaping_rate_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size packets or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_q_shaping_rate_get(bf_dev_id_t dev,
                                           bf_dev_port_t port,
                                           bf_tm_queue_t queue,
                                           bool *pps,
                                           uint32_t *burst_size,
                                           uint32_t *rate);

/**
 * Get queue guaranteed rate. Rate is in units of kbps or pps.
 *
 * Related APIs: bf_tm_sched_q_guaranteed_rate_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size packets or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_q_guaranteed_rate_get(bf_dev_id_t dev,
                                              bf_dev_port_t port,
                                              bf_tm_queue_t queue,
                                              bool *pps,
                                              uint32_t *burst_size,
                                              uint32_t *rate);

/**
 * Get scheduling priority when serving remaining bandwidth.
 * Higher the number, higher the  priority to select the queue for scheduling.
 *
 * Related APIs: bf_tm_sched_q_remaining_bw_priority_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param queue           queue
 * @param priority        Scheduling priority of queue.
 */
bf_status_t bf_tm_sched_q_remaining_bw_priority_get(
    bf_dev_id_t dev,
    bf_dev_port_t port,
    bf_tm_queue_t queue,
    bf_tm_sched_prio_t *priority);

/**
 * Get port shaping rate. Rate is in units of kbps or pps.
 *
 * Related APIs: bf_tm_sched_port_shaping_rate_set()
 *
 * @param dev             ASIC device identifier.
 * @param port            Port
 * @param pps             If set to true, rates are applied in terms of pps
 *                        else in terms of kbps.
 * @param burst_size      Burst size packets or bytes.
 * @param rate            Shaper value in pps or kbps.
 */
bf_status_t bf_tm_sched_port_shaping_rate_get(bf_dev_id_t dev,
                                              bf_dev_port_t port,
                                              bool *pps,
                                              uint32_t *burst_size,
                                              uint32_t *rate);

/**
 * Get per packet byte adjustment value
 *
 * Related APIs: bf_tm_sched_pkt_ifg_compensation_set ()
 *
 * @param dev             ASIC device identifier.
 * @param pipe            Pipe identifier.
 * @param adjustment      Byte adjustment done on every packet.
 */
bf_status_t bf_tm_sched_pkt_ifg_compensation_get(bf_dev_id_t dev,
                                                 bf_dev_pipe_t pipe,
                                                 uint8_t *adjustment);

/* @} */

#endif
