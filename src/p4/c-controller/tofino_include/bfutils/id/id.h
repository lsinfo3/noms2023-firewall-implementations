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
//
//  bf_id.h
//
//
//  Created on 6/20/14.
//
//

#ifndef _bf_id_h
#define _bf_id_h

#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void *bf_id_allocator;

bf_id_allocator *bf_id_allocator_new(unsigned int initial_size,
                                     bool zero_based);

void bf_id_allocator_destroy(bf_id_allocator *allocator);

unsigned int bf_id_allocator_allocate(bf_id_allocator *allocator);

int bf_id_allocator_allocate_contiguous(bf_id_allocator *allocator,
                                        uint8_t count);

void bf_id_allocator_release(bf_id_allocator *allocator, unsigned int id);

void bf_id_allocator_set(bf_id_allocator *allocator, unsigned int id);

int bf_id_allocator_is_set(bf_id_allocator *allocator, unsigned int id);

int bf_id_allocator_get_first(bf_id_allocator *allocator);

int bf_id_allocator_get_next(bf_id_allocator *allocator, unsigned int id);

void bf_id_allocator_copy(bf_id_allocator *dst_allocator,
                          bf_id_allocator *src_allocator);

#ifdef __cplusplus
}
#endif

#endif
