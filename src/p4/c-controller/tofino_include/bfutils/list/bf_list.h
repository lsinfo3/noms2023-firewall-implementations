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
#ifndef _BF_LIST_H_
#define _BF_LIST_H_

//
// Simple double linked list macros.  Head's prev points to tail.  Tail's
// next is NULL.
//

// Prepend.
#define BF_LIST_DLL_PP(l, e, n, p) \
  do {                             \
    bf_sys_assert(e);              \
    (e)->n = l;                    \
    if (l) {                       \
      (e)->p = (l)->p;             \
      (l)->p = e;                  \
    } else {                       \
      (e)->p = e;                  \
    }                              \
    (l) = e;                       \
  } while (0);
// Get last.
#define BF_LIST_DLL_LAST(l, r, n, p) \
  do {                               \
    if (l) {                         \
      r = (l)->p;                    \
    } else {                         \
      r = NULL;                      \
    }                                \
  } while (0);
// Append.
#define BF_LIST_DLL_AP(l, e, n, p) \
  do {                             \
    bf_sys_assert(e);              \
    (e)->n = NULL;                 \
    if (l) {                       \
      (e)->p = (l)->p;             \
      bf_sys_assert((l)->p);       \
      (l)->p->n = e;               \
      (l)->p = e;                  \
    } else {                       \
      (e)->p = (e);                \
      l = e;                       \
    }                              \
  } while (0);
// Remove.
#define BF_LIST_DLL_REM(l, e, n, p) \
  do {                              \
    bf_sys_assert(e);               \
    if ((e)->p == (e)) {            \
      l = NULL;                     \
    } else if ((e) == (l)) {        \
      bf_sys_assert((e)->n);        \
      (e)->n->p = (e)->p;           \
      (l) = (e)->n;                 \
    } else {                        \
      bf_sys_assert((e)->p);        \
      (e)->p->n = (e)->n;           \
      if ((e)->n) {                 \
        (e)->n->p = (e)->p;         \
      } else {                      \
        bf_sys_assert(l);           \
        (l)->p = (e)->p;            \
      }                             \
    }                               \
    (e)->p = NULL;                  \
    (e)->n = NULL;                  \
  } while (0);
// Concatenate
#define BF_LIST_DLL_CAT(f, s, n, p)       \
  do {                                    \
    if ((s) && (f)) {                     \
      void *BF_LIST_DLL_CAT_TMP = (f)->p; \
      bf_sys_assert((f)->p);              \
      (f)->p->n = (s);                    \
      (f)->p = (s)->p;                    \
      (s)->p = BF_LIST_DLL_CAT_TMP;       \
      (s) = NULL;                         \
    } else if ((s)) {                     \
      (f) = (s);                          \
      (s) = NULL;                         \
    }                                     \
  } while (0);

#endif
