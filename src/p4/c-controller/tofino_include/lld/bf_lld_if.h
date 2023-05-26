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

#ifndef BF_LLD_IF_H_INCLUDED
#define BF_LLD_IF_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file bf_lld_if.h
 * \brief Details Device-level APIs.
 *
 */

/**
 * @addtogroup lld-api
 * @{
 * This is a description of some APIs.
 */

typedef bf_status_t (*bf_reg_wr_fn)(bf_dev_id_t dev_id,
                                    uint32_t addr,
                                    uint32_t data);
typedef bf_status_t (*bf_reg_rd_fn)(bf_dev_id_t dev_id,
                                    uint32_t addr,
                                    uint32_t *data);

bf_status_t bf_lld_bind_wr_fn(bf_reg_wr_fn fn);
bf_status_t bf_lld_bind_rd_fn(bf_reg_rd_fn fn);
bf_status_t bf_lld_init(bool is_master, bf_reg_wr_fn wr_fn, bf_reg_rd_fn rd_fn);

// legacy APIs
bf_status_t bf_bind_wr_fn(bf_reg_wr_fn fn);
bf_status_t bf_bind_rd_fn(bf_reg_rd_fn fn);
char *bf_dbg_get_full_reg_path_name(uint32_t offset);
bool bf_lld_dev_is_tof1(bf_dev_id_t dev_id);
bool bf_lld_dev_is_tof2(bf_dev_id_t dev_id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* C++ */

#endif  // BF_LLD_IF_H_INCLUDED
