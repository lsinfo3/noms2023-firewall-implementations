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
/*!
 * @file pipe_mgr_err.h
 * @date
 *
 * Error code definitions for pipeline management API
 *
 * FIXME: See if errcodes can be defined hierarchically across BF components
 */

#ifndef _PIPE_MGR_ERR_H
#define _PIPE_MGR_ERR_H

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pipeline management API error codes.
 */
typedef enum pipe_status {
  PIPE_SUCCESS = 0, /**< Operation successful. */
  PIPE_NOT_READY = 1,
  PIPE_NO_SYS_RESOURCES = 2, /**< No system resources (e.g. malloc failures). */
  PIPE_INVALID_ARG = 3,      /**< Incorrect inputs. */
  PIPE_ALREADY_EXISTS = 4,
  PIPE_COMM_FAIL = 5,
  PIPE_OBJ_NOT_FOUND = 6,
  PIPE_MAX_SESSIONS_EXCEEDED = 7,
  PIPE_SESSION_NOT_FOUND = 8,
  PIPE_NO_SPACE = 9,
  PIPE_TRY_AGAIN = 10, /**< Temporarily out of resources, try again later (e.g.
                            no free DMA buffers, FIFOs full, etc.). */
  PIPE_INIT_ERROR = 11,
  PIPE_TXN_NOT_SUPPORTED = 12, /**< API call not supported in transactions. */
  PIPE_TABLE_LOCKED = 13,
  PIPE_IO = 14,
  PIPE_UNEXPECTED = 15,
  PIPE_ENTRY_REFERENCES_EXIST = 16,
  PIPE_NOT_SUPPORTED = 17,
  PIPE_LLD_FAILED = 18,
  PIPE_NO_LEARN_CLIENTS = 19,
  PIPE_IDLE_UPDATE_IN_PROGRESS = 20,
  PIPE_DEVICE_LOCKED = 21,
  PIPE_INTERNAL_ERROR = 22,
  PIPE_TABLE_NOT_FOUND = 23,

  /* UPDATE the pipe_err_strings when a new error code is
   * is added here.
   */
  PIPE_STS_MAX
} pipe_status_t;

/* Routine to get error string corresponding to an error code */

static const char *pipe_err_strings[PIPE_STS_MAX + 1] = {
    "Success",                            /* PIPE_SUCCESS */
    "Pipeline manager service not ready", /* PIPE_NOT_READY */
    "No system resources",                /* PIPE_NO_SYS_RESOURCES */
    "Invalid arguments",                  /* PIPE_INVALID_ARG */
    "Object already exists",              /* PIPE_ALREADY_EXISTS */
    "Communication failed",               /* PIPE_COMM_FAIL */
    "Object not found",                   /* PIPE_OBJ_NOT_FOUND */
    "Exceeded max sessions",              /* PIPE_MAX_SESSIONS_EXCEEDED */
    "Session not found",                  /* PIPE_SESSION_NOT_FOUND */
    "Not enough Space",                   /* PIPE_NO_SPACE */
    "Try again later",                    /* PIPE_TRY_AGAIN */
    "Initialization error",               /* PIPE_INIT_ERROR */
    "Not Supported In Transaction",       /* PIPE_TXN_NOT_SUPPORTED" */
    "Table is locked",                    /* PIPE_TABLE_LOCKED */
    "IO Error",                           /* PIPE_IO */
    "Unexpected",                         /* PIPE_UNEXPECTED */
    "Action data entry is being referenced by match entries", /* PIPE_ENTRY_REFERENCES_EXIST
                                                                 */
    "Not supported",                              /* PIPE_NOT_SUPPORTED */
    "Updating hardware failed",                   /* PIPE_LLD_FAILED */
    "No learning clients registered",             /* PIPE_NO_LEARN_CLIENTS */
    "Idle time update state already in progress", /* PIPE_IDLE_UPDATE_IN_PROGRESS
                                                     */
    "Device Locked",                              /* PIPE_DEVICE_LOCKED */
    "Internal Error",                             /* PIPE_INTERNAL_ERROR */
    "Table not found",                            /* PIPE_TABLE_NOT_FOUND */
    "Unknown Error"};
static inline const char *pipe_str_err(pipe_status_t sts) {
  if (sts < PIPE_STS_MAX) return pipe_err_strings[sts];
  return pipe_err_strings[PIPE_STS_MAX - 1];
}

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _PIPE_MGR_ERR_H */
