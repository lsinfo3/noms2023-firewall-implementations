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

#ifndef lld_err_h
#define lld_err_h

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  LLD_OK = 0,
  LLD_ERR_BAD_PARM = -1,
  LLD_ERR_NOT_READY = -2,
  LLD_ERR_LOCK_FAILED = -3,
  LLD_ERR_DR_FULL = -4,
  LLD_ERR_DR_EMPTY = -5,
  LLD_ERR_INVALID_CFG = -6,
  LLD_ERR_UT = -7,
} lld_err_t;

#ifdef __cplusplus
}
#endif /* C++ */

#endif  // lld_err_h
