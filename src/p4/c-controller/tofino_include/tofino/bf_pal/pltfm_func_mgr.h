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
#ifndef _TOFINO_BF_PAL_PLATFORM_FUNC_MGR_H
#define _TOFINO_BF_PAL_PLATFORM_FUNC_MGR_H

#include <bf_types/bf_types.h>

typedef bf_status_t (*bf_pal_pltfm_type_get_fn)(bf_dev_id_t dev_id,
                                                bool *is_sw_model);

typedef struct pltfm_func_s {
  bf_pal_pltfm_type_get_fn pltfm_type_get; /* Device type (model or asic) */
} pltfm_func_s;

/**
 * @brief Get pointer to the function to get the device type (model or asic)
 * @param pltfm_type_get_fn Pointer to the function to get the device type
 * @return Status of the API call
 */
bf_status_t bf_pal_pltfm_type_get_fn_get(
    bf_pal_pltfm_type_get_fn *pltfm_type_get_fn);

/**
 * @brief Register all appropriate platform related functions with the
 * corresponding function pointers encapsulated in a structure
 * @param all_func Pointer to the structure containing all the function pointers
 * @return Status of the API call
 */
bf_status_t bf_pal_pltfm_fn_reg(pltfm_func_s *all_func);

/**
 * @brief Get all the platform function pointers in a structure populated with
 * the registered function pointers
 * @param all_func Pointer to the structure containing all the function pointers
 * @return Status of the API call
 */
bf_status_t bf_pal_pltfm_fn_get(pltfm_func_s *all_func);

#endif
