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
 * Some bit twiddling utility functions gathered from the web and aim_utils.h
 * Particularly http://graphics.stanford.edu/~seander/bithacks.html
 */
#ifndef _BIT_UTILS_H_
#define _BIT_UTILS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

/* Calculate the log2 of a uint32 value and return it's ceil
 * log2(4) = 2
 * log2(5) = 3
 */
static inline uint32_t log2_uint32_ceil(uint32_t x) {
#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
  return (x > 1) ? (32 - __builtin_clz(x - 1)) : 0;
#else
  // not implemented
  assert(0);
  return 0;
#endif
}

/* Calculate the log2 of a uint32 value and return it's floor
 * log2(3) = 1
 * log2(4) = 2
 * log2(5) = 2
 */
static inline uint32_t log2_uint32_floor(uint32_t x) {
#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
  return x ? (31 - __builtin_clz(x)) : 0;
#else
  // not implemented
  assert(0);
  return 0;
#endif
}

/* Count the number of trailing zeroes. */
static inline uint32_t ctz(uint32_t x) {
#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
  return x ? __builtin_ctz(x) : 32;
#else
  // not implemented
  assert(0);
  return 0;
#endif
}

/**
 * Check whether an integer is a power of 2
 */
static inline bool is_uint32_power2(uint32_t x) {
  return x > 0 && (x & (x - 1)) == 0;
}

/* Calculate the next pow2 value. If x is a pow2, x is returned */
static inline uint32_t next_pow2(uint32_t x) {
  return (1 << log2_uint32_ceil(x));
}

#endif  //_BIT_UTILS_H_
