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
 * This file contains APIs for client application to
 * read Traffic Manager drop, usage counters.
 */

#ifndef __TRAFFIC_MGR_COUNTERS_H__
#define __TRAFFIC_MGR_COUNTERS_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_counters.h
 * \brief This file contains APIs for Traffic Manager application to
 *        get drop and usage counters from hardware.
 */

/**
 * @addtogroup tm-stats
 * @{
 * Description of APIs for Traffic Manager application to
 * get counters from hardware. All counters in hardware are maintained
 * using 48bits. All usage limits are in units of cells.
 */

/**
 * Get per port drop count.
 * On Ingress, if packet is dropped when usage crosses PPG or
 * or Port drop limit, this counter gets incremented.
 * On Egress, queue tail drop are also accounted against port.
 *
 * @param dev           ASIC device identifier.
 * @param pipe          Pipe Identifier.
 * @param port          Port identifier.
 * @param ig_count      Per port Packet drops from Ingress TM perspective.
 * @param eg_count      Per port Packet drops from Egress TM perspective.
 * @return              Status of API call.
 */
bf_status_t bf_tm_port_drop_get(bf_dev_id_t dev,
                                bf_dev_pipe_t pipe,
                                bf_dev_port_t port,
                                uint64_t *ig_count,
                                uint64_t *eg_count);

/**
 * Clear per port drop count.
 *
 * @param dev           ASIC device identifier.
 * @param port          Port identifier.
 * @return              Status of API call.
 */
bf_status_t bf_tm_port_drop_count_clear(bf_dev_id_t dev, bf_dev_port_t port);

/**
 * Clear per port ingress_drop count.
 *
 * @param dev           ASIC device identifier.
 * @param port          Port identifier.
 * @return              Status of API call.
 */
bf_status_t bf_tm_port_ingress_drop_count_clear(bf_dev_id_t dev,
                                                bf_dev_port_t port);

/**
 * Clear per port egress_drop count.
 *
 * @param dev           ASIC device identifier.
 * @param port          Port identifier.
 * @return              Status of API call.
 */
bf_status_t bf_tm_port_egress_drop_count_clear(bf_dev_id_t dev,
                                               bf_dev_port_t port);

/**
 * Get per ppg drop count.
 *
 * @param dev           ASIC device identifier.
 * @param pipe          Pipe Identifier.
 * @param port          Port identifier.
 * @param count         Counts number of dropped packet.
 * @return              Status of API call.
 */
bf_status_t bf_tm_ppg_drop_get(bf_dev_id_t dev,
                               bf_dev_pipe_t pipe,
                               bf_tm_ppg_hdl ppg,
                               uint64_t *count);

/**
 * Clear per ppg drop count.
 *
 * @param dev           ASIC device identifier.
 * @param ppg           PPG identifier.
 * @return              Status of API call.
 */
bf_status_t bf_tm_ppg_drop_count_clear(bf_dev_id_t dev, bf_tm_ppg_hdl ppg);

/**
 * Get per queue drop count
 *
 * @param dev           ASIC device identifier.
 * @param pipe          Pipe Identifier.
 * @param port          Port identifier.
 * @param queue         Queue identifier behind port.
 * @param count         Counts number of packet.
 * @return              Status of API call.
 */
bf_status_t bf_tm_q_drop_get(bf_dev_id_t dev,
                             bf_dev_pipe_t pipe,
                             bf_dev_port_t port,
                             bf_tm_queue_t queue,
                             uint64_t *count);

/**
 * Clear per queue drop count
 *
 * @param dev           ASIC device identifier.
 * @param port          Port identifier.
 * @param queue         Queue identifier behind port.
 * @return              Status of API call.
 */
bf_status_t bf_tm_q_drop_count_clear(bf_dev_id_t dev,
                                     bf_dev_port_t port,
                                     bf_tm_queue_t queue);

/**
 * Get Buffer full drop  count
 *
 * @param dev           ASIC device identifier.
 * @param pipe          Pipe Identifier.
 * @param count         Counts number of packet.
 * @return              Status of API call.
 */
bf_status_t bf_tm_pipe_buffer_full_drop_get(bf_dev_id_t dev,
                                            bf_dev_pipe_t pipe,
                                            uint64_t *count);

/**
 * Get port current usage count in units of cells.
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param port       port identifier.
 * @param ig_count   Port usage count in cells from Ingress TM perspective.
 * @param eg_count   Port usage count in cells from Egress TM perspective.
 * @param ig_wm      Watermark of port in units of cell from
 *                   Ingress TM view point.
 * @param eg_wm      Watermark of port in units of cell from
 *                   Egress TM view point.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_usage_get(bf_dev_id_t dev,
                                 bf_dev_pipe_t pipe,
                                 bf_dev_port_t port,
                                 uint32_t *ig_count,
                                 uint32_t *eg_count,
                                 uint32_t *ig_wm,
                                 uint32_t *eg_wm);

/**
 * Clear port watermark counter.
 *
 * @param dev        ASIC device identifier.
 * @param port       port identifier.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_watermark_clear(bf_dev_id_t dev, bf_dev_port_t port);

/**
 * Get Pool usage counters. Valid pools are application/shared pool,
 * negative mirror pool and skid pool. There is no water mark support
 * for negative mirror pool. In negative mirror pool case water mark
 * value will be zero all the time.
 * Water mark value indicates maximum usage ever reached
 *
 * @param dev        ASIC device identifier.
 * @param pool       pool identifier.
 * @param count      Pool usage count in cells.
 * @param wm         Water mark value in units of cell.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pool_usage_get(bf_dev_id_t dev,
                                 bf_tm_app_pool_t pool,
                                 uint32_t *count,
                                 uint32_t *wm);

/**
 * Clear shared AP pool watermark counter
 *
 * @param dev        ASIC device identifier.
 * @param pool       pool identifier.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pool_watermark_clear(bf_dev_id_t dev, bf_tm_app_pool_t pool);

/**
 * Get PPG usage count.
 * Water mark value indicates maximum usage ever reached.
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param ppg        PPG identifier.
 * @param gmin_count   Cell inuse from gmin pool.
 * @param shared_count Cell inuse from shared pool.
 * @param skid_count   Cell inuse from skid pool.
 * @param wm         Water mark value in units of cell.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_usage_get(bf_dev_id_t dev,
                                bf_dev_pipe_t pipe,
                                bf_tm_ppg_hdl ppg,
                                uint32_t *gmin_count,
                                uint32_t *shared_count,
                                uint32_t *skid_count,
                                uint32_t *wm);

/**
 * Clear PPG watermark counter.
 *
 * @param dev        ASIC device identifier.
 * @param ppg        PPG identifier.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_watermark_clear(bf_dev_id_t dev, bf_tm_ppg_hdl ppg);

/**
 * Get queue usage count
 * Water mark value indicates maximum usage ever reached
 *
 * @param dev           ASIC device identifier.
 * @param pipe          Pipe Identifier.
 * @param port          Port identifier.
 * @param queue         Queue identifier behind port.
 * @param count         Cell inuse .
 * @param wm            Water mark value in units of cell.
 * @return              Status of API call.
 */
bf_status_t bf_tm_q_usage_get(bf_dev_id_t dev,
                              bf_dev_pipe_t pipe,
                              bf_dev_port_t port,
                              bf_tm_queue_t queue,
                              uint32_t *count,
                              uint32_t *wm);

/**
 * Clear queue watermark counter.
 *
 * @param dev           ASIC device identifier.
 * @param port          Port identifier.
 * @param queue         Queue identifier behind port.
 * @return              Status of API call.
 */
bf_status_t bf_tm_q_watermark_clear(bf_dev_id_t dev,
                                    bf_dev_port_t port,
                                    bf_tm_queue_t queue);

/**
 * Get discard queue current usage counter.
 * Water mark value indicates maximum usage ever reached.
 *
 * @param dev           ASIC device identifier.
 * @param pipe          Pipe Identifier.
 * @param count         Cell inuse.
 * @param wm            Water mark value in units of cell.
 * @return              Status of API call.
 */
bf_status_t bf_tm_q_discard_usage_get(bf_dev_id_t dev,
                                      bf_dev_pipe_t pipe,
                                      uint32_t *count,
                                      uint32_t *wm);

/**
 * Get Pipe counters. Total number of cells, packets received by a pipe.
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param cell_count Total Cell count through the pipe.
 * @param pkt_count  Total Cell count through the pipe.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pipe_counters_get(bf_dev_id_t dev,
                                    bf_dev_pipe_t pipe,
                                    uint64_t *cell_count,
                                    uint64_t *pkt_count);

/**
 * Get Unicast and Multicast cut through packet count through a pipe.
 * Counters are incremented after packet is admitted into TM in egress
 * direction.
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param uc_count   Total Unicast cut through packets through the pipe.
 * @param mc_count   Total Multicast cut through packets through the pipe.
 * @return           Status of API call.
 */
bf_status_t bf_tm_cut_through_counters_get(bf_dev_id_t dev,
                                           bf_dev_pipe_t pipe,
                                           uint64_t *uc_count,
                                           uint64_t *mc_count);

#if 0
/**
 * Get per port number of packets
 *
 * @param dev        ASIC device identifier.
 * @param port       Port Identifier.
 * @param cell_count Total Cell count through the pipe.
 * @param pkt_count  Total Cell count through the pipe.
 * @return           Status of API call.
 */
bf_status_t bf_tm_port_stats_get(bf_dev_id_t dev,
                                 bf_dev_port_t port,
                                 uint32_t *ig_pkt_count,
                                 uint32_t *eg_pkt_count);
#endif

/* @} */

#endif
