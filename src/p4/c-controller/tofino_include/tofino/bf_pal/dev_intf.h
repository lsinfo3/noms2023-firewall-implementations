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
#ifndef _TOFINO_BF_PAL_DEV_INTF_H
#define _TOFINO_BF_PAL_DEV_INTF_H

#include <bf_types/bf_types.h>
#include <dvm/bf_drv_intf.h>
#include <dvm/bf_drv_profile.h>

bf_status_t bf_pal_device_warm_init_begin(
    bf_dev_id_t dev_id,
    bf_dev_init_mode_t warm_init_mode,
    bf_dev_serdes_upgrade_mode_t serdes_upgrade_mode,
    bool upgrade_agents);

bf_status_t bf_pal_device_add(bf_dev_id_t dev_id,
                              bf_device_profile_t *device_profile);

bf_status_t bf_pal_device_warm_init_end(bf_dev_id_t dev_id);

typedef bf_status_t (*bf_pal_device_warm_init_begin_fn)(
    bf_dev_id_t dev_id,
    bf_dev_init_mode_t warm_init_mode,
    bf_dev_serdes_upgrade_mode_t serdes_upgrade_mode,
    bool upgrade_agents);

typedef bf_status_t (*bf_pal_device_add_fn)(
    bf_dev_id_t dev_id, bf_device_profile_t *device_profile);

typedef bf_status_t (*bf_pal_device_warm_init_end_fn)(bf_dev_id_t dev_id);
typedef bf_status_t (*bf_pal_device_cpuif_netdev_name_get_fn)(
    bf_dev_id_t dev_id, char *cpuif_netdev_name, size_t cpuif_name_size);

typedef bf_status_t (*bf_pal_device_pltfm_type_get_fn)(bf_dev_id_t dev_id,
                                                       bool *is_sw_model);

typedef struct bf_pal_dev_callbacks_s {
  bf_pal_device_warm_init_begin_fn warm_init_begin;
  bf_pal_device_add_fn device_add;
  bf_pal_device_warm_init_end_fn warm_init_end;
  bf_pal_device_cpuif_netdev_name_get_fn cpuif_netdev_name_get;
  bf_pal_device_pltfm_type_get_fn pltfm_type_get;
} bf_pal_dev_callbacks_t;

bf_status_t bf_pal_device_callbacks_register(bf_pal_dev_callbacks_t *callbacks);
bf_status_t bf_pal_cpuif_netdev_name_get(bf_dev_id_t dev_id,
                                         char *cpuif_netdev_name,
                                         size_t cpuif_name_size);
#endif
