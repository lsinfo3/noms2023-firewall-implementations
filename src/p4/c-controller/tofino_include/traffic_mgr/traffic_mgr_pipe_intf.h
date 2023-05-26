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

#ifndef __TRAFFIC_MGR_PIPE_INTF_H__
#define __TRAFFIC_MGR_PIPE_INTF_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_pipe_intf.h
 * \brief This file contains APIs for Traffic Manager application to
 *        program pipe threshold values meant to implement part of
 *        QoS behaviour.
 */

/**
 * @addtogroup tm-egress
 * @{
 */

/**
 * Set egress pipe limit.  Default value of the pipe limit
 * is set to maximum buffering capability of the traffic manager.
 * When admitting packet into Traffic manager, apart from other
 * checks, the packet has to also pass usage check on per egress pipe
 * usage limit. A packet destined to egress pipe whose usage limit
 * has crossed, will not be admitted.
 *
 * Default: Set to maximum TM buffer.
 *
 * Related APIs: bf_tm_pipe_egress_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier
 * @param cells      Limit in terms of number of cells.
 * @return           Status of API call.
 */
bf_status_t bf_tm_pipe_egress_limit_set(bf_dev_id_t dev,
                                        bf_dev_pipe_t pipe,
                                        uint32_t cells);

/**
 * Egress Pipe Queue States Reporting Mode
 * False: Trigger Qstat reporting from Q color threshold
 * True: Trigger Qstat reporting from Q any updates
 *
 * Default: 0
 *
 * Related APIs: bf_tm_pipe_egress_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param mode       Queue states reporting mode.
 * @return           Status of API call.
 */
bf_status_t bf_tm_qstat_report_mode_set(bf_dev_id_t dev,
                                        bf_dev_pipe_t pipe,
                                        bool mode);

/**
 * Egress Pipe Queue States Reporting Mode
 * False: Trigger Qstat reporting from Q color threshold
 * True: Trigger Qstat reporting from Q any updates
 *
 * Default: 0
 *
 * Related APIs: bf_tm_pipe_egress_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier.
 * @param mode       Queue states reporting mode.
 * @return           Status of API call.
 */
bf_status_t bf_tm_qstat_report_mode_get(bf_dev_id_t dev,
                                        bf_dev_pipe_t pipe,
                                        bool *mode);

/**
 * Set pipe hysteresis limit.
 * When usage of cells goes below the hysteresis limit, pipe level
 * drop condition will be cleared.
 *
 * Default : Hysteresis is set to zero or no hysteresis.
 *
 * Related APIs: bf_tm_pipe_egress_limit_set(),
 *               bf_tm_pipe_egress_hysteresis_get()
 *
 * @param dev        ASIC device identifier.
 * @param pipe       Pipe Identifier
 * @param cells      New threshold limit
 * @return           Status of API call.
 */
bf_status_t bf_tm_pipe_egress_hysteresis_set(bf_dev_id_t dev,
                                             bf_dev_pipe_t pipe,
                                             uint32_t cells);

/* @} */

#endif
