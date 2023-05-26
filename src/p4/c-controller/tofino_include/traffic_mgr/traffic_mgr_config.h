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
  * @brief traffic_mgr Configuration Header
  *
  * @addtogroup traffic_mgr-config
  * @{
  *
  *****************************************************************************/
#ifndef __TRAFFIC_MGR_CONFIG_H__
#define __TRAFFIC_MGR_CONFIG_H__

#ifdef GLOBAL_INCLUDE_CUSTOM_CONFIG
#include <global_custom_config.h>
#endif
#ifdef TRAFFIC_MGR_INCLUDE_CUSTOM_CONFIG
#include <traffic_mgr_custom_config.h>
#endif

/**
 * TRAFFIC_MGR_CONFIG_PORTING_STDLIB
 *
 * Default all porting macros to use the C standard libraries. */

#ifndef TRAFFIC_MGR_CONFIG_PORTING_STDLIB
#define TRAFFIC_MGR_CONFIG_PORTING_STDLIB 1
#endif

/**
 * TRAFFIC_MGR_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS
 *
 * Include standard library headers for stdlib porting macros. */

#ifndef TRAFFIC_MGR_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS
#define TRAFFIC_MGR_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS \
  TRAFFIC_MGR_CONFIG_PORTING_STDLIB
#endif

/**
 * TRAFFIC_MGR_CONFIG_INCLUDE_UCLI
 *
 * Include generic uCli support. */

#ifndef TRAFFIC_MGR_CONFIG_INCLUDE_UCLI
#define TRAFFIC_MGR_CONFIG_INCLUDE_UCLI 0
#endif

#include "traffic_mgr_porting.h"

#endif /* __TRAFFIC_MGR_CONFIG_H__ */
/* @} */
