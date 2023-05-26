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

#ifndef port_mgr_intf_included
#define port_mgr_intf_included

typedef enum {
  PORT_MGR_OK = 0,
  PORT_MGR_ERR_BAD_PARM,
  PORT_MGR_ERR_NOT_READY,
  PORT_MGR_ERR_LOCK_FAILED,
  PORT_MGR_ERR_INVALID_CFG,
  PORT_MGR_ERR,
} port_mgr_err_t;

/** \brief User-defined function (with the given signature) to be called
 *         whenever the a MAC stats DMA operation completes. The msg_id
 *         field will match that given in the call to bf_port_mac_stats_get
 *         that initiated the DMA.
 */
typedef void (*bf_mac_stats_callback_t)(bf_dev_id_t dev_id,
                                        int status,
                                        uint64_t msg_id);
void port_mgr_init(void);
bf_status_t bf_bind_mac_stats_cb(bf_dev_id_t dev_id,
                                 bf_mac_stats_callback_t fn);
#endif  // port_mgr_intf_included
