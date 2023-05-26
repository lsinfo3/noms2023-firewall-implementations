/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2017-2018 Barefoot Networks, Inc.

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
/** @file bf_rt_table_operations.hpp
 *
 *  @brief Contains BF-RT Table Operations APIs
 */
#ifndef _BF_RT_TABLE_OPERATIONS_HPP
#define _BF_RT_TABLE_OPERATIONS_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include <bf_rt/bf_rt_common.h>
#ifdef __cplusplus
}
#endif

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>
#include <functional>

#include <bf_rt/bf_rt_table.hpp>
#include <bf_rt/bf_rt_table_key.hpp>

namespace bfrt {

/**
 * @brief Table Operations Type
 */
enum class TableOperationsType {
  COUNTER_SYNC = 0,
  REGISTER_SYNC = 1,
  HIT_STATUS_UPDATE = 2,
  INVALID = 3
};

/**
 * @brief Register Sync Callback
 */
typedef std::function<void(const bf_rt_target_t &dev_tgt, void *cookie)>
    BfRtRegisterSyncCb;

/**
 * @brief Counter Sync Callback
 */
typedef std::function<void(const bf_rt_target_t &dev_tgt, void *cookie)>
    BfRtCounterSyncCb;

/**
 * @brief Hit State Update Callback
 */
typedef std::function<void(const bf_rt_target_t &dev_tgt, void *cookie)>
    BfRtHitStateUpdateCb;

/**
 * @brief Class to construct Operations Object<br>
 * <B>Creation: </B> Can only be created using \ref
 * bfrt::BfRtTable::operationsAllocate()
 */
class BfRtTableOperations {
 public:
  virtual ~BfRtTableOperations() = default;

  /**
   * @brief Set Register sync callback.
   * Works on Match Action tables and register tables only
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] callback Register sync callback
   * @param[in] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t registerSyncSet(const BfRtSession &session,
                                      const bf_rt_target_t &dev_tgt,
                                      const BfRtRegisterSyncCb &callback,
                                      const void *cookie) = 0;

  /**
   * @brief Set Counter sync callback.
   * Works on Match Action tables and counter tables only
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] callback Counter sync callback
   * @param[in] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t counterSyncSet(const BfRtSession &session,
                                     const bf_rt_target_t &dev_tgt,
                                     const BfRtCounterSyncCb &callback,
                                     const void *cookie) = 0;

  /**
   * @brief Set Hit State Update callback.
   * Works on Match Action tables only
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] callback Hit State update sync callback
   * @param[in] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t hitStateUpdateSet(const BfRtSession &session,
                                        const bf_rt_target_t &dev_tgt,
                                        const BfRtHitStateUpdateCb &callback,
                                        const void *cookie) = 0;
};
}  // bfrt

#endif  // _BF_RT_TABLE_OPERATIONS_HPP
