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
 * APIs for client application to program Traffic Manager block to
 * desired QoS behaviour.
 */

#ifndef __TRAFFIC_MGR_APIMODE_H__
#define __TRAFFIC_MGR_APIMODE_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @file traffic_mgr_apimode.h
 * \brief This file contains Traffic Manager helper functions
 *        that application/client can make use.
 */

/**
 * @addtogroup tm-api
 * @{
 *  This file contains Traffic Manager helper functions
 *  that application/client can make use.
 */

/**
 * By default traffic manager updates are non batched. All configuration
 * updates are pushed to hardware/asic immediately.  Updates are made
 * efficient by batching writes over DMA to hardware.
 * Batch mode is very useful during system start. Bulk of Traffic Manager
 * configuration during TM initialization can be pushed to hardware in
 * batch mode.
 *
 * Related API : bf_tm_batch_update_end()
 *
 * @param dev      ASIC device identifier.
 * @return         Status of API call.
 */
bf_status_t bf_tm_batch_update_start(bf_dev_id_t dev);

/**
 * All traffic manager configurations that are not pushed to hardware
 * during batch mode processing will be flushed to hardware. Also
 * Traffic Manager update mode is set back to non batch mode.
 * If write bulk mode is desired, application is expected to invoke
 * bf_tm_batch_update_start().
 *
 * Related API : bf_tm_batch_update_start()
 *
 * @param dev      ASIC device identifier.
 * @return         Status of API call.
 */
bf_status_t bf_tm_batch_update_end(bf_dev_id_t dev);

/* @} */

#endif
