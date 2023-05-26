/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2017 Barefoot Networks, Inc.

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
#ifndef _BF_PLTFM_SI5342_H
#define _BF_PLTFM_SI5342_H

#include <bfutils/uCli/ucli.h>

/* Allow the use in C++ code. */
#ifdef __cplusplus
extern "C" {
#endif

#define I2C_ADDR_SI5342 (0x6B << 1)
#define SI5342_FIXED_PAGE_REG 0x01
#define SI5342_NVM_WR_REG 0x00E3
#define SI5342_DEV_RDY_REG 0x00FE
#define SI5342_DEV_RDY 0x0F

int bf_pltfm_si5342_init(void *arg);
int bf_pltfm_si5342_i2c_wr(int chip_id, uint32_t reg, uint8_t data);
int bf_pltfm_si5342_i2c_rd(int chip_id, uint32_t reg, uint8_t *data);
ucli_node_t *bf_pltfm_si5342_ucli_node_create(ucli_node_t *m);
#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _BF_PLTFM_SI5342_H */
