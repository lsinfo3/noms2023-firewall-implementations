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
/** fbitset.h - Faster bitset implemented using judy.
 * Almost double the performance over bitset implemented using
 * bit arrays
 */

#ifndef _BF_FBITSET_H_
#define _BF_FBITSET_H_

#include <inttypes.h>
#include <stdbool.h>

typedef struct bf_fbitset_s {
  unsigned int width;  // Number of bits;
  void *fbs;
} bf_fbitset_t;

typedef enum bf_fbitset_sts_e {
  BF_FBITSET_OK,
  BF_FBITSET_MALLOC_ERR
} bf_fbitset_sts_t;

/* Initialize a bitset. */
void bf_fbs_init(bf_fbitset_t *bs, unsigned int width);

/* Set the bit at "position" to "val", return it's previous value. */
bool bf_fbs_set(bf_fbitset_t *bs, int position, int val);

/* Return the value of the bit at "position". */
bool bf_fbs_get(bf_fbitset_t *bs, int position);

/* Position is exclusive. Start search from width to find the last free */
int bf_fbs_prev_clr_contiguous(bf_fbitset_t *bs,
                               int position,
                               unsigned int count);

/* Position is exclusive. Start searching from -1 to find the first free*/
int bf_fbs_first_clr_contiguous(bf_fbitset_t *bs,
                                int position,
                                unsigned int count);

/* Position is exclusive. Start searching from -1 to find the first set. */
int bf_fbs_first_set(bf_fbitset_t *bs, int position);

void bf_fbs_destroy(bf_fbitset_t *bs);

#endif /* _BF_FBITSET_H_ */
