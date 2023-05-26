/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2016 Barefoot Networks, Inc.
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
/*!
 * @file bf_pltfm_rptr.h
 * @date
 *
 * API's for reading and writing to serdes repeaters for Mavericks
 *
 */

#ifndef _BL_PLTFM_RPTR_H
#define _BL_PLTFM_RPTR_H

/* Standard includes */
#include <stdint.h>

/* Module includes */
#include <bf_pltfm_types/bf_pltfm_types.h>
#include <bf_pltfm_bd_cfg/bf_pltfm_bd_cfg_intf.h>
#include <bfutils/uCli/ucli.h>
/* Local header includes */

/* Allow the use in C++ code. */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize repeater library
 * @return Status of the API call.
 */
bf_pltfm_status_t bf_pltfm_rptr_init(void);

/**
 * Set particular port's egress or ingress repeater channel
 * @param port_info info struct of the port on the board
 * @param mode Egress or Ingress mode
 * @param rptr_info Repeater info struct
 * @return Status of the API call.
 */
bf_pltfm_status_t bf_pltfm_rptr_ch_eq_set(bf_pltfm_port_info_t *port_info,
                                          bf_pltfm_rptr_mode_t mode,
                                          bf_pltfm_rptr_info_t *rptr_info);

/**
 * Set all 4 repeater channels of a port in ingress and egress mode
 * @param port_num port number for which eq values need to be set
 * @return Status of the API call.
 */
bf_pltfm_status_t bf_pltfm_rptr_conn_eq_set(uint32_t port_num);

ucli_node_t *bf_pltfm_rptr_ucli_node_create(ucli_node_t *m);

#ifdef __cplusplus
}
#endif /* C++ */

#endif /*_BL_PLTFM_RPTR_H */
