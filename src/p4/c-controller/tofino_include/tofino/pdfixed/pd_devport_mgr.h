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
#ifndef _TOFINO_PDFIXED_PD_DEVPORT_MGR_H
#define _TOFINO_PDFIXED_PD_DEVPORT_MGR_H

#include <tofino/pdfixed/pd_common.h>
#include <dvm/bf_drv_intf.h>

typedef enum p4_devport_mgr_ha_corrective_action {
  HA_CA_PORT_NONE = 0,
  HA_CA_PORT_ADD,
  HA_CA_PORT_ENABLE,
  HA_CA_PORT_ADD_THEN_ENABLE,
  HA_CA_PORT_FLAP,
  HA_CA_PORT_DISABLE,
  HA_CA_PORT_DELETE_THEN_ADD,
  HA_CA_PORT_DELETE_THEN_ADD_THEN_ENABLE,
  HA_CA_PORT_DELETE,
  HA_CA_PORT_MAX
} p4_devport_mgr_ha_corrective_action_e;

p4_pd_status_t p4_devport_mgr_add_port(uint32_t dev_id,
                                       uint32_t port_id,
                                       uint32_t port_speeds,
                                       uint32_t port_fec_types);

p4_pd_status_t p4_devport_mgr_add_port_with_lanes(uint32_t dev_id,
                                                  uint32_t port_id,
                                                  uint32_t port_speeds,
                                                  uint32_t port_lanes,
                                                  uint32_t port_fec_types);

p4_pd_status_t p4_devport_mgr_remove_port(uint32_t dev_id, uint32_t port_id);

int p4_devport_mgr_port_ca_get(const int32_t dev_id, const int32_t port_id);

int p4_devport_mgr_serdes_ca_get(const int32_t dev_id, const int32_t port_id);

typedef enum p4_devport_mgr_warm_init_mode {
  DEV_INIT_COLD,
  // Device incurs complete reset
  DEV_WARM_INIT_FAST_RECFG,
  // Device incurs a fast-reconfig reset with minimal traffic disruption
  DEV_WARM_INIT_HITLESS,
  // Device incurs a hitless warm init
} p4_devport_mgr_warm_init_mode_e;

typedef enum p4_devport_mgr_serdes_upgrade_mode {
  DEV_SERDES_UPD_NONE,
  // No serdes update needed
  DEV_SERDES_UPD_FORCED_PORT_RECFG,
  // Update serdes by flapping ports immediately
  DEV_SERDES_UPD_DEFERRED_PORT_RECFG
  // Defer the serdes update until a port flap occurs
} p4_devport_mgr_serdes_upgrade_mode_e;

p4_pd_status_t p4_devport_mgr_warm_init_begin(
    uint32_t dev_id,
    p4_devport_mgr_warm_init_mode_e warm_init_mode,
    p4_devport_mgr_serdes_upgrade_mode_e serdes_upgrade_mode,
    bool upgrade_agents);

p4_pd_status_t p4_devport_mgr_warm_init_end(uint32_t dev_id);

typedef int (*warm_init_begin_fn)(
    int asic,
    bf_dev_init_mode_t warm_init_mode,
    bf_dev_serdes_upgrade_mode_t serdes_upgrade_mode,
    bool upgrade_agents);
typedef int (*warm_init_end_fn)(int asic);

p4_pd_status_t p4_devport_mgr_register_test_handlers(warm_init_begin_fn f1,
                                                     warm_init_end_fn f2);

p4_pd_status_t p4_devport_mgr_set_copy_to_cpu(int dev,
                                              bool enable,
                                              uint16_t port);
int p4_devport_mgr_pcie_cpu_port_get(int dev);
int p4_devport_mgr_eth_cpu_port_get(int dev);

p4_pd_status_t p4_devport_mgr_set_virtual_dev_slave_mode(uint32_t dev_id);

p4_pd_status_t p4_devport_mgr_get_clock_speed(uint32_t dev_id,
                                              uint64_t *bps_clock_speed,
                                              uint64_t *pps_clock_speed);

p4_pd_status_t p4_devport_mgr_lrt_dr_timeout_set(uint32_t dev_id,
                                                 uint32_t timeout_ms);
p4_pd_status_t p4_devport_mgr_lrt_dr_timeout_get(uint32_t dev_id,
                                                 uint32_t *timeout_ms);
#endif
