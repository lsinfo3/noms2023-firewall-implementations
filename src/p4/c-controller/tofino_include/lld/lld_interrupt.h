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
#ifndef LLD_INTERRUPT_INCLUDED
#define LLD_INTERRUPT_INCLUDED

#include <lld/lld_int_cb.h>

typedef bf_int_cb lld_int_cb;
typedef bf_status_t (*lld_blk_int_traverse_cb)(bf_dev_id_t dev_id,
                                               void *blk_lvl_int);

#define LLD_MAX_INT_NBR (511 /* For both Tofino and Tof2, 0-511*/)
#define LLD_TOF_TOF2_SHADOW_REG_NUMB (16) /* For both Tofino and Tof2, 0-15 */

#endif  // LLD_INTERRUPT_INCUDED
