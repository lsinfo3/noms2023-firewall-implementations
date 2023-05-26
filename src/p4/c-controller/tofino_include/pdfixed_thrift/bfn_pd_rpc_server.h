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
 * C/C++ header file for calling server start function from C code
 */

#ifndef _BFN_PD_RPC_SERVER_H_
#define _BFN_PD_RPC_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BFN_PD_RPC_SERVER_PORT 9090

extern int start_bfn_pd_rpc_server(void **server_cookie);

#ifdef __cplusplus
}
#endif

#endif /* _BFN_PD_RPC_SERVER_H_ */