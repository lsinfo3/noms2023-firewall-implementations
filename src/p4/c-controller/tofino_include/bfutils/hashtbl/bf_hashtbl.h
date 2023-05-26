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
#ifndef _bf_hashtbl_h_
#define _bf_hashtbl_h_

#include <stdint.h>
#include <stddef.h>

typedef uint32_t bf_hash_t;

typedef enum bf_hashtbl_sts_t {
  BF_HASHTBL_OK,
  BF_HASHTBL_INVALID_ARG,
  BF_HASHTBL_ERR,
} bf_hashtbl_sts_t;

typedef int (*bf_htbl_cmp_fn)(const void *, const void *);
typedef void (*bf_htbl_free_fn)(void *);

typedef struct bf_hashtable_ {
  /* Comparison function */
  bf_htbl_cmp_fn cmp_fn;
  /* Free function during table cleanup */
  bf_htbl_free_fn free_fn;
  size_t key_sz;  /* Key size in bytes */
  size_t data_sz; /* Data size in bytes */
  uint32_t seed;  /* Seed for the hash table */
  void *phtbl;
} bf_hashtable_t;

bf_hashtbl_sts_t bf_hashtbl_init(bf_hashtable_t *htbl,
                                 int (*fn)(const void *, const void *),
                                 void (*free_fn)(void *),
                                 uint8_t key_sz,
                                 uint8_t data_sz,
                                 uint32_t seed);

void *bf_hashtbl_search(bf_hashtable_t *htbl, void *key);

bf_hashtbl_sts_t bf_hashtbl_insert(bf_hashtable_t *htbl, void *node, void *key);

void *bf_hashtbl_get_remove(bf_hashtable_t *htbl, void *key);

typedef void bf_hashtable_foreach_fn_t(void *arg, void *obj);

/* Invoke the function for each element in the hash table with arg as the
 * argument */
void bf_hashtbl_foreach_fn(bf_hashtable_t *htbl,
                           bf_hashtable_foreach_fn_t *foreach_fn,
                           void *arg);

void bf_hashtbl_delete(bf_hashtable_t *htbl);

void *bf_hashtbl_get_cmp_data(const void *arg);

#endif
