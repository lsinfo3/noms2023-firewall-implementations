/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2017-2018 Barefoot Networks, Inc.

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
 *
 ******************************************************************************/

#ifndef _BF_RT_SERVER_H
#define _BF_RT_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

// Start server and bind to default address (0.0.0.0:50052)
void bf_rt_grpc_server_run();

// Start server and bind to given address
void bf_rt_grpc_server_run_with_addr(const char *server_address);

#ifdef __cplusplus
}
#endif

#endif  // _BF_RT_SERVER_H