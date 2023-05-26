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

#ifndef __TRAFFIC_MGR_MISCAPI_H__
#define __TRAFFIC_MGR_MISCAPI_H__

#include <traffic_mgr/traffic_mgr_types.h>
#include <bf_types/bf_types.h>

/**
 * @addtogroup tm-buffer-mgmt
 * @{
 */

/**
 * Get cells size in bytes. Using this API application can
 * convert bytes into cell units.
 *
 * Related API : bf_tm_total_cell_count_get()
 *
 * @param dev      ASIC device identifier.
 * @param bytes    Byte count to convert to cells.
 * @param cells    Cell count needed to accomodate specified bytes.
 * @return         Status of API call.
 */
bf_status_t bf_tm_cell_size_in_bytes_get(bf_dev_id_t dev, uint32_t *bytes);

/**
 * Total Traffic Manager buffer capability measured in cell count.
 * Get total cell count supported by ASIC.
 *
 * Related API : bf_tm_convert_bytes_to_cell()
 *
 * @param dev         ASIC device identifier.
 * @param total_cells TM buffering capacity measured in cell count.
 *                    Application SW can use this API to get TM
 *                    buffer size to plan buffer carving.
 * @return            Status of API call.
 */
bf_status_t bf_tm_total_cell_count_get(bf_dev_id_t dev, uint32_t *total_cells);

/**
 * Get total unassigned cell counts. Ideally this value should be zero
 * so that all TM buffering capability is used.
 *
 * Related API : bf_tm_total_cell_count_get()
 *
 * @param dev           ASIC device identifier.
 * @param total_cells   Unassigned TM buffering capacity measured
 *                      in cell count.
 * @return              Status of API call.
 */
bf_status_t bf_tm_total_unassigned_cell_count_get(bf_dev_id_t dev,
                                                  int *total_cells);

/**
 * This API can be issued to complete any pending dma operation to asic.
 * API blocks until all dma operations are complete.
 *
 * @param dev           ASIC device identifier.
 * @return              Status of API call.
 */
bf_status_t bf_tm_complete_operations(bf_dev_id_t dev);

/**
 * Set number of Global timestamp bits that is to be right shifted.
 *
 * @param dev           ASIC device identifier.
 * @param shift         Number of Global timestamp bits that are right shifted.
 *                      Upto 16bits can be right shifted. Any shift value
 *                      greater than 16 is capped to 16.
 * @return              Status of API call.
 */
bf_status_t bf_tm_timestamp_shift_set(bf_dev_id_t dev, uint8_t shift);

/* @} */

#endif
