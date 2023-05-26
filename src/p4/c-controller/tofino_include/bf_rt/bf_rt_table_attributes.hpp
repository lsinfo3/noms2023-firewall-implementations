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
/** @file bf_rt_attributes.hpp
 *
 *  @brief Contains BF-RT Table Attribute APIs
 */
#ifndef _BF_RT_TABLE_ATTRIBUTES_HPP
#define _BF_RT_TABLE_ATTRIBUTES_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include <pipe_mgr/pipe_mgr_intf.h>
#include <bf_rt/bf_rt_common.h>
#include <bf_rt/bf_rt_table_attributes.h>
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
#include <bitset>

#include <bf_rt/bf_rt_table.hpp>
#include <bf_rt/bf_rt_table_key.hpp>

namespace bfrt {

/**
 * @brief Attribute type
 */
enum class TableAttributesType {
  ENTRY_SCOPE = 0,
  DYNAMIC_KEY_MASK = 1,
  IDLE_TABLE_RUNTIME = 2,
  DYNAMIC_HASH_ALG_SEED = 3,
  METER_BYTE_COUNT_ADJ = 4,
  PORT_STATUS_NOTIF = 5,
  PORT_STAT_POLL_INTVL_MS = 6,
  PRE_DEVICE_CONFIG = 7,
  SELECTOR_UPDATE_CALLBACK = 8
};

/**
 * @brief IdleTable Mode
 */
enum class TableAttributesIdleTableMode { POLL_MODE, NOTIFY_MODE };

/**
 * @brief Pipe Entry scope
 */
enum class TableEntryScope {
  ENTRY_SCOPE_ALL_PIPELINES = 0,
  ENTRY_SCOPE_SINGLE_PIPELINE = 1,
  ENTRY_SCOPE_USER_DEFINED = 2
};

/**
 * @brief Gress Scope
 */
enum class TableGressScope { GRESS_SCOPE_ALL_GRESS, GRESS_SCOPE_SINGLE_GRESS };

/**
 * @brief Parser Scope
 */
enum class TablePrsrScope {
  PRSR_SCOPE_ALL_PRSRS_IN_PIPE,
  PRSR_SCOPE_SINGLE_PRSR
};

/**
 * @brief Gress Target
 */
enum class GressTarget {
  GRESS_TARGET_INGRESS,
  GRESS_TARGET_EGRESS,
  GRESS_TARGET_ALL = 0xFF
};

/**
 * @brief IdleTimeout Callback
 */
typedef std::function<void(const bf_rt_target_t &dev_tgt,
                           const BfRtTableKey *match_spec,
                           void *cookie)> BfRtIdleTmoExpiryCb;

/**
 * @brief PortStatusChange Callback
 */
typedef std::function<void(const bf_dev_id_t &dev_id,
                           const BfRtTableKey *key,
                           const bool &port_up,
                           void *cookie)> BfRtPortStatusNotifCb;

/**
 * @brief Selector Table Update Callback
 */
typedef std::function<void(const std::shared_ptr<BfRtSession> session,
                           const bf_rt_target_t &bf_rt_tgt,
                           const void *cookie,
                           const bf_rt_id_t &sel_grp_id,
                           const bf_rt_id_t &act_mbr_id,
                           const int &logical_entry_index,
                           const bool &is_add)> selUpdateCb;
/**
 * @brief Class to expose APIs to set/get the entry scope arguments with
 * std::bitset.The absolute scope val is a 32 bit unsigned int which can be set
 * using a 32-bit std::bitset object or can be set on a per byte basis using an
 * array of size 4 of 8-bit std::bitset objects. The 32-bit bitset looks like
 * 0x00 0x00 0x0c 0x03 if we want pipes 2,3 to be in scope 1 and pipes 0,1 to
 * be in scope 0. Each "byte" of the bitset is a scope. There can be a max of 4
 * scopes. No pipe can belong to more than 1 scope at once. The bf_rt_dev_target
 * should contain the lowest pipe of the scope the entry of the table is wished
 * to be programmed in. So in the above example, if we want an entry to be
 * programmed in scope 1, then pipe_id should contain 2 and then pipe 3 will
 * also
 * be programmed with the entry.
 * <B>Creation: </B> Can only be created using \ref
 * bfrt::BfRtTableAttributes::entryScopeArgumentsAllocate()
 */
class BfRtTableEntryScopeArguments {
 public:
  virtual ~BfRtTableEntryScopeArguments() = default;
  /**
   * @brief Set entry scope as a 32-bit bitset
   *
   * @param[in] val 32-bit bitset
   *
   * @return Status of the API call
   */
  virtual bf_status_t setValue(const std::bitset<32> &val) = 0;
  /**
   * @brief Set entry scope as a 4-length array of 8-bit bitsets
   * <B>Note: </B>The least significant byte of the
   * scope, i.e. byte 0, corresponds to std::bitset array[0], byte 1 = array[1],
   * byte 2 = array[2] and byte 3 = array[3]<br>
   *
   * @param[in] val_arr 4-length array of 8-bit bitset
   *
   * @return Status of the API call
   */
  virtual bf_status_t setValue(
      const std::array<std::bitset<8>, 4> &val_arr) = 0;
  /**
   * @brief Get entry scope as a 32-bit bitset
   *
   * @param[in] val 32-bit bitset
   *
   * @return Status of the API call
   */
  virtual bf_status_t getValue(std::bitset<32> *val) const = 0;
  /**
   * @brief Get entry scope as a 4-length array of 8-bit bitsets
   * <B>Note: </B>The least significant byte of the
   * scope val (byte 0) corresponds to std::bitset array[0], byte 1 = array[1],
   * byte 2 = array[2] and byte 3 = array[3]<br>
   *
   * @param[in] val_arr 4-length array of 8-bit bitset
   *
   * @return Status of the API call
   */
  virtual bf_status_t getValue(
      std::array<std::bitset<8>, 4> *val_arr) const = 0;
};

/**
 * @brief Class to Set and Get Attributes<br>
 * <B>Creation: </B> Can only be created using \ref
 * bfrt::BfRtTable::attributeAllocate()
 */
class BfRtTableAttributes {
 public:
  virtual ~BfRtTableAttributes() = default;
  /**
   * @brief Set IdleTable Poll Mode options. This is only valid if the
   *Attributes Object
   * was allocated using the correct
   * \ref bfrt::BfRtTable::attributeAllocate(const TableAttributesType &, const
   *TableAttributesIdleTableMode &,std::unique_ptr<BfRtTableAttributes>
   **attr)const "attributeAllocate()"
   *
   * @param[in] enable Flag to enable IdleTable
   *
   * @return Status of the API call
   */
  virtual bf_status_t idleTablePollModeSet(const bool &enable) = 0;
  /**
   * @brief Set IdleTable Poll Mode options. This is only valid if the
   *Attributes Object
   * was allocated using the correct
   * \ref bfrt::BfRtTable::attributeAllocate(const TableAttributesType &, const
   *TableAttributesIdleTableMode &,std::unique_ptr<BfRtTableAttributes>
   **attr)const "attributeAllocate()"
   *
   * @param[in] enable Flag to enable IdleTable
   * @param[in] callback Callback on IdleTime Timeout
   * @param[in] ttl_query_interval ttl query interval
   * @param[in] max_ttl Max ttl value that an entry can have
   * @param[in] min_ttl Min ttl value that an entry can have
   * @param[in] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t idleTableNotifyModeSet(
      const bool &enable,
      const BfRtIdleTmoExpiryCb &callback,
      const uint32_t &ttl_query_interval,
      const uint32_t &max_ttl,
      const uint32_t &min_ttl,
      const void *cookie) = 0;

  /**
   * @brief Get Idle Table params
   *
   * @param[out] mode Mode of IdleTable (POLL/NOTIFY)
   * @param[out] enable Enable flag
   * @param[out] callback Calbback on IdleTimeout
   * @param[out] ttl_query_interval ttl query interval
   * @param[out] max_ttl Max ttl value that an entry can have
   * @param[out] min_ttl Min ttl value that an entry can have
   * @param[out] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t idleTableGet(TableAttributesIdleTableMode *mode,
                                   bool *enable,
                                   BfRtIdleTmoExpiryCb *callback,
                                   uint32_t *ttl_query_interval,
                                   uint32_t *max_ttl,
                                   uint32_t *min_ttl,
                                   void **cookie) const = 0;

  /**
   * @brief Allocate entryScopeArguments Object
   *
   * @param[out] scop_args_ret entryScopeArguments Object
   *
   * @return Status of the API call
   */
  virtual bf_status_t entryScopeArgumentsAllocate(
      std::unique_ptr<BfRtTableEntryScopeArguments> *scop_args_ret) const = 0;

  /**
   * @brief Set entry scope params in the Attributes Object
   *
   * @param[in] entry_scope pipe entry scope (ALL/SINGLE/USER)
   * @param[in] scope_args entryScopeArguments Object. Contains data for
   * user-defined pipe entry scope if applicable
   *
   * @return Status of the API call
   */
  virtual bf_status_t entryScopeParamsSet(
      const TableEntryScope &entry_scope,
      const BfRtTableEntryScopeArguments &scope_args) = 0;

  /**
   * @brief Set entry scope params in the Attributes Object
   *
   * @param[in] entry_scope pipe entry scope (All/Single/User)
   *
   * @return Status of the API call
   */
  virtual bf_status_t entryScopeParamsSet(
      const TableEntryScope &entry_scope) = 0;

  /**
   * @brief Set entry scope params in the Attributes Object
   *
   * @param[in] gress_scope   gress (All/Single)
   * @param[in] pipe    pipe entry scope (All/Single/User)
   * @param[in] pipe_args entryScopeArguments Object. Contains data for
   * user-defined pipe entry scope if applicable
   * @param[in] prsr    Parser scope (All/Single)
   * @param[in] gress_target   Gress Target (In/Eg/All)
   *
   * @return Status of the API call
   */
  virtual bf_status_t entryScopeParamsSet(
      const TableGressScope &gress_scope,
      const TableEntryScope &pipe,
      const BfRtTableEntryScopeArguments &pipe_args,
      const TablePrsrScope &prsr,
      const GressTarget &gress_target) = 0;
  /**
   * @brief Get entry scope params from the Attributes Object
   *
   * @param[out] entry_scope entry scope
   * @param[out] scope_args entryScopeArguments Object
   *
   * @return Status of the API call
   */
  virtual bf_status_t entryScopeParamsGet(
      TableEntryScope *entry_scope,
      BfRtTableEntryScopeArguments *scope_args) const = 0;

  /**
   * @brief Get entry scope params from the Attributes Object
   *
   * @param[out] gress_scope   gress (All/Single)
   * @param[out] pipe    pipe entry scope (All/Single/User)
   * @param[out] pipe_args entryScopeArguments Object. Contains data for
   * user-defined pipe entry scope if applicable
   * @param[out] prsr    Parser scope (All/Single)
   * @param[out] gress_target   Gress Target (In/Eg/All)
   *
   * @return Status of the API call
   */
  virtual bf_status_t entryScopeParamsGet(
      TableGressScope *gress_scope,
      TableEntryScope *pipe,
      BfRtTableEntryScopeArguments *pipe_args,
      TablePrsrScope *prsr,
      GressTarget *gress_target) const = 0;

  /**
   * @brief Set Dynamic Key Mask params in the Attributes Object
   *
   * @param[in] partition_index partition index
   * @param[in] num_valid_match_bits Number of match bits valid
   * @param[in] num_match_bytes Size of padded match_value_bits
   * @param[in] match_value_bits Value of match bits
   * @param[in] match_mask_bits Mash of match bits. Valid only for ternary
   *tables
   * @param[in] num_match_validity_fields Number of match fields that require
   *have validity qual
   * @param[in] match_field_validity Ordered list of match field validity values
   * @param[in] match_field_validity_mask Mask for matching. Valid only for
   *ternary tables
   * @param[in] priority Priority
   *
   * @return Status of the API call
   */
  virtual bf_status_t dynKeyMaskSet(const uint32_t &partition_index,
                                    const uint16_t &num_valid_match_bits,
                                    const uint16_t &num_match_bytes,
                                    const uint8_t *match_value_bits,
                                    const uint8_t *match_mask_bits,
                                    const uint16_t &num_match_validity_fields,
                                    const uint16_t &match_field_validity,
                                    const uint16_t &match_field_validity_mask,
                                    const uint32_t &priority) = 0;

  /**
   * @brief Get Dynamic Key Mask params in the Attributes Object
   *
   * @param[out] partition_index partition index
   * @param[out] num_valid_match_bits Number of match bits valid
   * @param[out] num_match_bytes Size of padded match_value_bits
   * @param[out] match_value_bits Value of match bits
   * @param[out] match_mask_bits Mash of match bits. Valid only for ternary
   *tables
   * @param[out] num_match_validity_fields Number of match fields that require
   *have validity qual
   * @param[out] match_field_validity Ordered list of match field validity
   *values
   * @param[out] match_field_validity_mask Mask for matching. Valid only for
   *ternary tables
   * @param[out] priority Priority
   *
   * @return Status of the API call
   */
  virtual bf_status_t dynKeyMaskGet(uint32_t *partition_index,
                                    uint16_t *num_valid_match_bits,
                                    uint16_t *num_match_bytes,
                                    uint8_t **match_value_bits,
                                    uint8_t **match_mask_bits,
                                    uint16_t *num_match_validity_fields,
                                    uint16_t *match_field_validity,
                                    uint16_t *match_field_validity_mask,
                                    uint32_t *priority) const = 0;

  /**
   * @brief Set Dynamic Hashing Algorithm and Seed in the Attributes Object
   * @param[in] alg_hdl algorithm handler for hashing
   * @param[in] seed seed for hashing
   *
   * @return Status of the API call
   */
  virtual bf_status_t dynHashingSet(const uint32_t &alg_hdl,
                                    const uint64_t &seed) = 0;

  /**
  * @brief Get Dynamic Hashing Algorithm and Seed in the Attributes Object
  * @param[out] alg_hdl algorithm handler for hashing
  * @param[out] seed seed for hashing
  *
  * @return Status of the API call
  */
  virtual bf_status_t dynHashingGet(uint32_t *alg_hdl,
                                    uint64_t *seed) const = 0;

  /**
  * @brief Set Meter Byte Count Adjust in the Attributes Object
  * @param[in] byte_count number of adjust bytes for meter tables
  *
  * @return Status of the API call
  */
  virtual bf_status_t meterByteCountAdjSet(const int &byte_count) = 0;

  /**
  * @brief Get Meter Byte Count Adjust in the Attributes Object
  * @param[out] byte_count number of adjust bytes for meter tables
  *
  * @return Status of the API call
  */
  virtual bf_status_t meterByteCountAdjGet(int *byte_count) const = 0;

  /**
   * @brief Set Port Status Change Notification Callback Function in the
   *Attributes Object
   * @param[in] enable port status change notification enable
   * @param[in] callback callback function
   * @param[in] cookie pointer client data
   *
   * @return Status of the API call
   */
  virtual bf_status_t portStatusChangeNotifSet(
      const bool &enable,
      const BfRtPortStatusNotifCb &callback,
      const bf_rt_port_status_chg_cb &callback_c,
      const void *cookie) = 0;

  /**
   * @brief Get Port Status Change Notification Callback Function in the
   *Attributes Object
   * @param[out] enable port status change notification enable
   * @param[out] callback callback function
   * @param[out] cookie pointer client data
   *
   * @return Status of the API call
   */
  virtual bf_status_t portStatusChangeNotifGet(
      bool *enable,
      BfRtPortStatusNotifCb *callback,
      bf_rt_port_status_chg_cb *callback_c,
      void **cookie) const = 0;

  /**
   * @brief Set Port Stat Poll Interval in Millisecond in the Attributes Object
   * @param[in] poll_intvl_ms poll interval
   *
   * @return Status of the API call
   */
  virtual bf_status_t portStatPollIntvlMsSet(const uint32_t &poll_intvl_ms) = 0;

  /**
   * @brief Get Port Stat Poll Interval in Millisecond in the Attributes Object
   * @param[out] poll_intvl_ms poll interval
   *
   * @return Status of the API call
   */
  virtual bf_status_t portStatPollIntvlMsGet(uint32_t *poll_intvl_ms) const = 0;

  /**
   * @brief Set PRE Global RID in the PRE Attributes Object
   * @param[in] global_rid global rid value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preGlobalRidSet(const uint32_t &global_rid) = 0;

  /**
   * @brief Get PRE Global RID in the PRE Attributes Object
   * @param[out] global_rid global rid value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preGlobalRidGet(uint32_t *global_rid) const = 0;

  /**
   * @brief Set PRE Port Protection Status in the PRE Attributes Object
   * @param[in] enable Enable/Disable status value
   *
   * @return Status of the API call
   */
  virtual bf_status_t prePortProtectionSet(const bool &enable) = 0;

  /**
   * @brief Get PRE Port Protection Status in the PRE Attributes Object
   * @param[out] enable Enable/Disable status value
   *
   * @return Status of the API call
   */
  virtual bf_status_t prePortProtectionGet(bool *enable) const = 0;

  /**
 * @brief Set PRE Fast Failover Status in the PRE Attributes Object
 * @param[in] enable Enable/Disable status value
 *
 * @return Status of the API call
 */
  virtual bf_status_t preFastFailoverSet(const bool &enable) = 0;

  /**
   * @brief Get PRE Fast Failover Status in the PRE Attributes Object
   * @param[out] enable Enable/Disable status value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preFastFailoverGet(bool *enable) const = 0;

  /**
   * @brief Set PRE Max Nodes Before Yield in the PRE Attributes Object
   * @param[in] count  max node before yield count value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preMaxNodesBeforeYieldSet(const uint32_t &count) = 0;

  /**
   * @brief Get PRE Max Nodes Before Yield in the PRE Attributes Object
   * @param[out] count  max node before yield count value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preMaxNodesBeforeYieldGet(uint32_t *count) const = 0;

  /**
   * @brief Set PRE Max Node Threshold in the PRE Attributes Object
   * @param[in] node_count  node count value
   * @param[in] node_port_lag_count  node port lag count value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preMaxNodeThresholdSet(
      const uint32_t &node_count, const uint32_t &node_port_lag_count) = 0;

  /**
   * @brief Get PRE Max Node Threshold in the PRE Attributes Object
   * @param[out] node_count  node count value
   * @param[out] node_port_lag_count  node port lag count value
   *
   * @return Status of the API call
   */
  virtual bf_status_t preMaxNodeThresholdGet(
      uint32_t *node_count, uint32_t *node_port_lag_count) const = 0;

  /**
   * @brief Set Selector Update Notification Callback
   * @param[in] enable Flag to enable selector update notifications
   * @param[in] session Session
   * @param[in] callback_fn Callback on Selector table update
   * @param[in] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t selectorUpdateCbSet(
      const bool &enable,
      const std::shared_ptr<BfRtSession> session,
      const selUpdateCb &callback_fn,
      const void *cookie) = 0;

  /**
   * @brief Get Selector Update Notification Callback
   * @param[out] enable Enable Flag
   * @param[out] session Session
   * @param[out] callback_fn Callback fn set for Selector table update
   * @param[out] cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t selectorUpdateCbGet(bool *enable,
                                          BfRtSession **session,
                                          selUpdateCb *callback_fn,
                                          void **cookie) const = 0;
};
}  // bfrt

#endif  // _BF_RT_TABLE_ATTRIBUTES_HPP
