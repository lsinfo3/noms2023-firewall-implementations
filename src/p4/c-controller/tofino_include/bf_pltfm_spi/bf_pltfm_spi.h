/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2016 Barefoot Networks, Inc.
 *
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

#ifndef _BF_PLTFM_SPI_H
#define _BF_PLTFM_SPI_H
#include <bfutils/uCli/ucli.h>
/* Allow the use in C++ code. */
#ifdef __cplusplus
extern "C" {
#endif

int bf_pltfm_spi_wr(int chip_id, const char *fname, int offset, int size);
int bf_pltfm_spi_rd(int chip_id, const char *fname, int offset, int size);
int bf_pltfm_spi_init(void *arg);
ucli_node_t *bf_pltfm_spi_ucli_node_create(ucli_node_t *m);
#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _BF_PLTFM_SPI_H */
