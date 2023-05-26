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
#ifndef _bf_map_h_
#define _bf_map_h_

#include <stdint.h>

/* Utility to map an unsigned long to a pointer.  Pointers can be added to a
 * database using unsigned longs as their keys.  They can then be looked up
 * and/or removed from the database using the key.
 * Implemented as a wrapper around JudyL
 */

typedef void *bf_map_t;

typedef enum bf_map_sts_t {
  BF_MAP_OK,
  BF_MAP_ERR,
  BF_MAP_NO_KEY,
  BF_MAP_KEY_EXISTS
} bf_map_sts_t;

bf_map_sts_t bf_map_add(bf_map_t *map, unsigned long key, void *data);
bf_map_sts_t bf_map_rmv(bf_map_t *map, unsigned long key);
bf_map_sts_t bf_map_get(bf_map_t *map, unsigned long key, void **data);
bf_map_sts_t bf_map_get_rmv(bf_map_t *map, unsigned long key, void **data);
bf_map_sts_t bf_map_get_first(bf_map_t *map, unsigned long *key, void **data);
bf_map_sts_t bf_map_get_next(bf_map_t *map, unsigned long *key, void **data);
bf_map_sts_t bf_map_get_first_rmv(bf_map_t *map,
                                  unsigned long *key,
                                  void **data);
bf_map_sts_t bf_map_init(bf_map_t *map);
void bf_map_destroy(bf_map_t *map);
uint32_t bf_map_count(bf_map_t *map);

#endif
