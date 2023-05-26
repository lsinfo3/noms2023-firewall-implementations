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

#ifndef PORT_MGR_PORT_EVT_H_INCLUDED
#define PORT_MGR_PORT_EVT_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PORT_MGR_PORT_EVT_NONE = 0,
  PORT_MGR_PORT_EVT_UP,
  PORT_MGR_PORT_EVT_DOWN,
  PORT_MGR_PORT_EVT_SPEED_SET,
} port_mgr_port_event_t;

typedef void (*port_mgr_port_callback_t)(bf_dev_id_t chip,
                                         bf_dev_port_t port,
                                         port_mgr_port_event_t reason,
                                         void *userdata);

bf_status_t port_mgr_register_port_cb(bf_dev_id_t dev_id,
                                      port_mgr_port_callback_t fn,
                                      void *userdata);
#ifdef __cplusplus
}
#endif /* C++ */

#endif  // PORT_MGR_PORT_EVT_H_INCLUDED
