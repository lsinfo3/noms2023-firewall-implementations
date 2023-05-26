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
#ifndef _BF_PAL_TYPES_H
#define _BF_PAL_TYPES_H

// File includes
#include <bf_types/bf_types.h>

// Defined Macros
#define MAX_PORT_HDL_STRING_LEN 100

/**
 * Identifies the admin state of a port in the system
 */
typedef enum bf_pm_port_admin_state_e {
  PM_PORT_DISABLED = 0,
  PM_PORT_ENABLED = 1
} bf_pm_port_admin_state_e;

/**
 * Identifies the oper status of a port in the system
 */
typedef enum bf_pm_port_oper_status_e {
  PM_PORT_DOWN = 0,
  PM_PORT_UP = 1
} bf_pm_port_oper_status_e;

/**
 * Identifies if a port should autonegotiate or not
 */
typedef enum bf_pm_port_autoneg_policy_e {
  // PM_AN_DEFAULT meant to be used by BSP. Applications should NOT set this
  // value.
  // If default,  AN will be enabled/disabled based on Module plugged-in.
  // For copper it will be enabled.
  PM_AN_DEFAULT = 0,

  // Applications can use AN_FORCE to enable/disable the auto-neg
  PM_AN_FORCE_ENABLE = 1,
  PM_AN_FORCE_DISABLE = 2,
  PM_AN_MAX = 3
} bf_pm_port_autoneg_policy_e;

/**
 * Identifies if a port-directions
 */
typedef enum bf_pm_port_dir_e {
  PM_PORT_DIR_DEFAULT = 0,  // both rx and tx
  PM_PORT_DIR_TX_ONLY = 1,
  PM_PORT_DIR_RX_ONLY = 2,
  PM_PORT_DIR_MAX
} bf_pm_port_dir_e;

/**
 * Identifies a front panel port on the system
 */
typedef struct bf_pal_front_port_handle_t {
  uint32_t conn_id;
  uint32_t chnl_id;
} bf_pal_front_port_handle_t;

/**
 * Identifies all the information about a specific front panel port. This
 * information is derived from the platforms modules
 */
typedef struct bf_pal_front_port_info_t {
  bf_dev_id_t dev_id;
  bf_pal_front_port_handle_t port_hdl;
  char port_str[MAX_PORT_HDL_STRING_LEN];
  uint32_t log_mac_id;
  uint32_t log_mac_lane;
} bf_pal_front_port_info_t;

/**
 * Identifies all the information to configure the serdes. This information
 * is derived from the platforms modules
 */
typedef struct bf_pal_serdes_info_t {
  bool tx_inv;
  bool rx_inv;
  int tx_attn;
  int tx_pre;
  int tx_post;
} bf_pal_serdes_info_t;

/**
 * Identifies the MAC lane to Serdes lane mappings based on the board layout.
 * This information is derived from the platforms modules
 */
typedef struct bf_pal_mac_to_serdes_lane_map_t {
  uint32_t tx_lane;  // Indicates which TX serdes slice this MAC lane is
                     // connected to
  uint32_t rx_lane;  // Indicates which RX serdes slice this MAC lane is
                     // connected to
} bf_pal_mac_to_serdes_lane_map_t;

/**
 * Indentifies the information configured for the port. This information
 * is passed to the platforms module during the registered callbacks.
 * Information is valid only AFTER the port has been added successfully
 */
typedef struct bf_pal_front_port_cb_cfg_t {
  bf_port_speed_t speed_cfg;  // Speed configured for the port
  int num_lanes;              // Number of MAC lanes consumed by the port
  bool is_an_on;              // Is port Auto-Negotiating?
  bf_pm_port_dir_e port_dir;  // Port direction configured
} bf_pal_front_port_cb_cfg_t;

/**
 * Identifies information required to configure the serdes coefficients.
 * Needs to be set before port-enable.
 * Any settings done via Json confiuration file will be overwritten.
 */
typedef struct bf_pal_serdes_params_t {
  /* tx coefficients */
  int tx_attn;
  int tx_pre;
  int tx_post;
} bf_pal_serdes_params_t;

#endif
