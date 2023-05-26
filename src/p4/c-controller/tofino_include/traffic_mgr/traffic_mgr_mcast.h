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

#ifndef __TRAFFIC_MGR_MCAST_INTF_H__
#define __TRAFFIC_MGR_MCAST_INTF_H__

#include <mc_mgr/mc_mgr_types.h>
#include <traffic_mgr/traffic_mgr_types.h>

/**
 * @file traffic_mgr_mcast.h
 * \brief Details multicast specific APIs.
 */

/**
 * @addtogroup tm-mcast
 * @{
 *  Description of APIs for Traffic Manager application
 *  to program multicast traffic FIFO sizes.
 */

/**
 * Set the input FIFO arbitration mode to strict priority or weighted round
 * robin.  Note that if strict priority is enabled on a FIFO, all FIFOs higher
 * will also be enabled for strict priority.  For example, to set FIFO 1 as
 * strict priority, 2 and 3 must also be strict priority.
 *
 * @param dev               The ASIC id.
 * @param pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC manual to find maximum number of fifos per
 *pipe.
 * @param use_strict_pri    If @c true, use strict priority.  If @c false, use
 *                          weighted round robin.
 * @return                  Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_arb_mode_set(bf_dev_id_t dev,
                                       uint8_t pipe_bmap,
                                       int fifo,
                                       bool use_strict_pri);

/**
 * Set the input FIFO arbitration weights used by the weighted round robin
 * arbitration mode.
 *
 * @param dev               The ASIC id.
 * @param pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC capabilites to find maximum number of fifos
 * @param weight            The weight assigned to FIFO.
 * @return                  Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_wrr_weight_set(bf_dev_id_t dev,
                                         uint8_t pipe_bmap,
                                         int fifo,
                                         uint8_t weight);

/**
 * Set multicast fifo to iCoS mapping.
 *
 * @param dev               The ASIC id.
 * @param pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC manual to find maximum number of fifos per
 *pipe.
 * @param icos_bmap         iCoS bit map.
 * @return                  Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_icos_mapping_set(bf_dev_id_t dev,
                                           uint8_t pipe_bmap,
                                           int fifo,
                                           uint8_t icos_bmap);

/**
 * Set the input FIFO depth.  Sum of all four sizes cannot exceed 8192,
 * additionally, each size must be a multiple of 8.
 *
 * @param dev               The ASIC id.
 * @param pipe_bmap         Pipe bit mask. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC manual to find maximum number of fifos per
 *pipe.
 * @param size              The size assigned to FIFO.
 * @return                  Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_depth_set(bf_dev_id_t dev,
                                    uint8_t pipe_bmap,
                                    int fifo,
                                    int size);

/**
 * Get the input FIFO arbitration mode to strict priority or weighted round
 * robin.  Note that if strict priority is enabled on a FIFO, all FIFOs higher
 * must also be enabled for strict priority.  For example, to set FIFO 1 as
 * strict priority, 2 and 3 must also be strict priority.
 *
 * @param dev               The ASIC id.
 * @param pipe              Pipe number. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC manual to find maximum number of fifos per
 *pipe.
 * @param arb_mode          If @c true, arbitration mode is strict priority.
 *                          If @c false, arbitration is weighted round robin.
 * @return Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_arb_mode_get(bf_dev_id_t dev,
                                       int pipe,
                                       int fifo,
                                       bool *use_strict_pri);

/**
 * Get the input FIFO arbitration weights used by the weighted round robin
 * arbitration mode.
 *
 * @param dev               The ASIC id.
 * @param pipe              Pipe number. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC manual to find maximum number of fifos per
 *pipe.
 * @param weight            The weight assigned to FIFO.
 * @return                  Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_wrr_weight_get(bf_dev_id_t dev,
                                         int pipe,
                                         int fifo,
                                         uint8_t *weight);

/**
 * Get the input FIFO depth.
 *
 * @param dev               The ASIC id.
 * @param pipe              Pipe number. Check ASIC manual to find maximum
 *                          of pipes.
 * @param fifo              The FIFO to configure, must be 0, 1, 2 or 3. Check
 *                          ASIC manual to find maximum number of fifos per
 *pipe.
 * @param                   size The size assigned to FIFO.
 * @return                  Status of the API call.
 */
bf_status_t bf_tm_mc_fifo_depth_get(bf_dev_id_t dev,
                                    int pipe,
                                    int fifo,
                                    int *size);

/* @} */

#endif
