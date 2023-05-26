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
/**************************************************************************/ /**
  *
  * @file
  * @brief traffic_mgr Porting Macros.
  *
  * @addtogroup traffic_mgr-porting
  * @{
  *
  *****************************************************************************/
#ifndef __TRAFFIC_MGR_PORTING_H__
#define __TRAFFIC_MGR_PORTING_H__

/* <auto.start.portingmacro(ALL).define> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <memory.h>
#include <bfsys/bf_sal/bf_sys_intf.h>

#define TRAFFIC_MGR_MALLOC bf_sys_malloc
#define TRAFFIC_MGR_REALLOC bf_sys_realloc
#define TRAFFIC_MGR_CALLOC bf_sys_calloc
#define TRAFFIC_MGR_FREE bf_sys_free

#define TRAFFIC_MGR_ASSERT bf_sys_assert
#define TRAFFIC_MGR_DBGCHK bf_sys_dbgchk

#ifndef TRAFFIC_MGR_MEMSET
#if defined(GLOBAL_MEMSET)
#define TRAFFIC_MGR_MEMSET GLOBAL_MEMSET
#else
#define TRAFFIC_MGR_MEMSET memset
#endif
#endif

#ifndef TRAFFIC_MGR_MEMCPY
#if defined(GLOBAL_MEMCPY)
#define TRAFFIC_MGR_MEMCPY GLOBAL_MEMCPY
#else
#define TRAFFIC_MGR_MEMCPY memcpy
#endif
#endif

#ifndef TRAFFIC_MGR_STRNCPY
#if defined(GLOBAL_STRNCPY)
#define TRAFFIC_MGR_STRNCPY GLOBAL_STRNCPY
#else
#define TRAFFIC_MGR_STRNCPY strncpy
#endif
#endif

#ifndef TRAFFIC_MGR_VSNPRINTF
#if defined(GLOBAL_VSNPRINTF)
#define TRAFFIC_MGR_VSNPRINTF GLOBAL_VSNPRINTF
#else
#define TRAFFIC_MGR_VSNPRINTF vsnprintf
#endif
#endif

#ifndef TRAFFIC_MGR_SNPRINTF
#if defined(GLOBAL_SNPRINTF)
#define TRAFFIC_MGR_SNPRINTF GLOBAL_SNPRINTF
#else
#define TRAFFIC_MGR_SNPRINTF snprintf
#endif
#endif

#ifndef TRAFFIC_MGR_STRLEN
#if defined(GLOBAL_STRLEN)
#define TRAFFIC_MGR_STRLEN GLOBAL_STRLEN
#else
#define TRAFFIC_MGR_STRLEN strlen
#endif
#endif

/* <auto.end.portingmacro(ALL).define> */

#include <bf_types/bf_types.h>
#define BF_TM_NUM_ASIC BF_MAX_DEV_COUNT  // From bf_types.h

#ifdef TM_MT_SAFE
#include <bfsys/bf_sal/bf_sys_sem.h>
#include <time.h>
#define tm_mutex_t bf_sys_rmutex_t
#define TM_LOCK(dev, x)                                             \
  do {                                                              \
    if (g_tm_ctx[dev]->internal_call) break;                        \
    int A_A = bf_sys_rmutex_lock(&x);                               \
    if (A_A) {                                                      \
      char errStr[32] = {0};                                        \
      strerror_r(A_A, errStr, 32);                                  \
      LOG_ERROR("LOCK: Error \"%s\" (%d) taking \"%s\" from %s:%d", \
                errStr,                                             \
                A_A,                                                \
                #x,                                                 \
                __func__,                                           \
                __LINE__);                                          \
    }                                                               \
  } while (0);

#define TM_UNLOCK(dev, x)                                                \
  do {                                                                   \
    if (g_tm_ctx[dev]->internal_call) break;                             \
    int A_A = bf_sys_rmutex_unlock(&x);                                  \
    if (A_A) {                                                           \
      char errStr[32] = {0};                                             \
      strerror_r(A_A, errStr, 32);                                       \
      LOG_ERROR("UNLOCK: Error \"%s\" (%d) releasing \"%s\" from %s:%d", \
                errStr,                                                  \
                A_A,                                                     \
                #x,                                                      \
                __func__,                                                \
                __LINE__);                                               \
    }                                                                    \
  } while (0);

#define TM_LOCK_INIT(x)       \
  do {                        \
    bf_sys_rmutex_init(&(x)); \
  } while (0);

#define TM_MUTEX_LOCK(x)                                            \
  do {                                                              \
    int A_A = bf_sys_rmutex_lock(x);                                \
    if (A_A) {                                                      \
      char errStr[32] = {0};                                        \
      strerror_r(A_A, errStr, 32);                                  \
      LOG_ERROR("LOCK: Error \"%s\" (%d) taking \"%s\" from %s:%d", \
                errStr,                                             \
                A_A,                                                \
                #x,                                                 \
                __func__,                                           \
                __LINE__);                                          \
    }                                                               \
  } while (0);

#define TM_MUTEX_UNLOCK(x)                                               \
  do {                                                                   \
    int A_A = bf_sys_rmutex_unlock(x);                                   \
    if (A_A) {                                                           \
      char errStr[32] = {0};                                             \
      strerror_r(A_A, errStr, 32);                                       \
      LOG_ERROR("UNLOCK: Error \"%s\" (%d) releasing \"%s\" from %s:%d", \
                errStr,                                                  \
                A_A,                                                     \
                #x,                                                      \
                __func__,                                                \
                __LINE__);                                               \
    }                                                                    \
  } while (0);
#else
#define tm_mutex_t int
#define TM_LOCK(dev, x)
#define TM_UNLOCK(dev, x)
#define TM_LOCK_INIT(x)
#define TM_MUTEX_LOCK(x)
#define TM_MUTEX_UNLOCK(x)
#endif

#endif /* __TRAFFIC_MGR_PORTING_H__ */
       /* @} */
