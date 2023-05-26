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
#ifndef _TOFINO_BF_PAL_PLATFORM_INTF_H
#define _TOFINO_BF_PAL_PLATFORM_INTF_H

#include <bf_types/bf_types.h>

/**
 * @brief Get the type of the device (model or asic)
 * @param dev_id Device id
 * @param is_sw_model Pointer to bool flag to return true for model and
                      false for asic devices
 * @return Status of the API call
 */
bf_status_t bf_pal_pltfm_type_get(bf_dev_id_t dev_id, bool *is_sw_model);

#endif
