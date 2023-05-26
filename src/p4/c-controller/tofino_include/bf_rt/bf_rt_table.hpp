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
/** @file bf_rt_table.hpp
 *
 *  @brief Contains BF-RT Table APIs
 */
#ifndef _BF_RT_TABLE_HPP
#define _BF_RT_TABLE_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include <pipe_mgr/pipe_mgr_intf.h>
#ifdef __cplusplus
}
#endif

#include <bf_rt/bf_rt_session.hpp>

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>

namespace bfrt {

/**
 * @brief Enum of Data Types each Data field can take. This is NOT
 *    Data field Type
 */
enum class DataType {
  INT_ARR = 0,
  BOOL_ARR = 1,
  UINT64 = 2,
  BYTE_STREAM = 3,
  FLOAT = 4,
  CONTAINER = 5,
  STRING = 6,
  BOOL = 7,
};

// Forward declarations
class BfRtTableKey;
class BfRtTableData;
enum class KeyFieldType;
enum class TableAttributesType;
enum class TableAttributesIdleTableMode;
class BfRtTableAttributes;
enum class TableOperationsType;
class BfRtTableOperations;

/**
 * @brief Class for Annotations. Contains 2 strings to uniquely identify an
 * annotation. These annotations can be on a Table, Action, Key or Data Field
 *
 * Possible list of annotations are below. This list is not exhaustive since
 * pragmas can be annotations too like alpm_partition ones which will vary
 * according to the params given ->
 *  1. ("$bfrt_field_class","register_data") If a Data field is a register data.
 *      Register data fields are to be set using one value but while
 *      tableEntryGet, this field returns a vector(one value for each field)
 *  2. ("$bfrt_port_type_class","dev_port") If the data field is a dev_port.
 *  3. ("$bfrt_port_type_class","port_hdl_conn_id") If the data field is a port
 *      handle conn ID.
 *  4. ("$bfrt_port_type_class","port_hdl_chnl_id") If the data field is a port
 *      handle channel ID.
 *  5. ("$bfrt_port_type_class","port_name") If the data field is a port name.
 *  6. ("$bfrt_port_type_class","fp_port") If the data field is a front panel
 *      port.
 *  7. ("isFieldSlice","true") If a Data field is a slice of bigger field.
 *  8. ("@defaultonly","") If an action is to be default only
 */
class Annotation {
 public:
  Annotation(std::string name, std::string value) : name_(name), value_(value) {
    full_name_ = name_ + "." + value_;
  };
  bool operator<(const Annotation &other) const;
  bool operator==(const Annotation &other) const;
  bool operator==(const std::string &other_str) const;
  bf_status_t fullNameGet(std::string *fullName) const;
  const std::string name_{""};
  const std::string value_{""};
  struct Less {
    bool operator()(const Annotation &lhs, const Annotation &rhs) const {
      return lhs < rhs;
    }
  };

 private:
  std::string full_name_{""};
};

/**
 * @brief We wrap the annotation in a reference wrapper because we want to send
 * the actual object to the API user and not a copy.
 */
using AnnotationSet =
    std::set<std::reference_wrapper<const Annotation>, Annotation::Less>;

/**
 * @brief Class to contain metadata of Table Objs like Data and Key Fields,
 *  and perform functions like EntryAdd, AttributeSet, OperationsExecute etc<br>
 * <B>Creation: </B> Cannot be created. can only be queried from \ref
 * bfrt::BfRtInfo
 */
class BfRtTable {
 public:
  /**
   * @brief Enum of Flags needed for Table Get Request
   */
  enum class BfRtTableGetFlag { GET_FROM_HW, GET_FROM_SW };

  /**
   * @brief Enum of Flags needed for Table Modify Incremental Request
   */
  enum class BfRtTableModIncFlag {
    MOD_INC_ADD,   /** Flag to add the given data incrementally to the
                       existing table entry */
    MOD_INC_DELETE /** Flag to delete the given data from the
                       existing table entry */
  };

  /**
   * @brief Enum of Table types supported
   */
  enum class TableType {
    MATCH_DIRECT = 0,            /** Match action table*/
    MATCH_INDIRECT = 1,          /** Match action table with actions of the
                                    table implemented using an
                                    "ActionProfile" */
    MATCH_INDIRECT_SELECTOR = 2, /** Match action table with actions of the
                                    table implemented using an
                                    "ActionSelector"*/
    ACTION_PROFILE = 3,          /** Action Profile table*/
    SELECTOR = 4,                /** Action Selector table*/
    COUNTER = 5,                 /** Counter table*/
    METER = 6,                   /** Meter table*/
    REGISTER = 7,                /** Register table*/
    LPF = 8,                     /** LPF table*/
    WRED = 9,                    /** WRED table*/
    PVS = 10, /** Parser Value Set table. This table contains only Keys and no
                Data*/
    PORT_METADATA = 11,     /** Port Metadata table.*/
    DYN_HASH_CFG = 12,      /** Dynamic Hashing configuration table*/
    SNAPSHOT = 13,          /** Snapshot. */
    SNAPSHOT_LIVENESS = 14, /** Snapshot field Liveness */
    PORT_CFG = 15,          /** Port Configuration */
    PORT_STAT = 16,         /** Port Stats */
    PORT_HDL_INFO = 17,     /** Port Hdl to Dev_port Conversion table */
    PORT_FRONT_PANEL_IDX_INFO =
        18,               /** Front panel Idx to Dev_port Conversion table */
    PORT_STR_INFO = 19,   /** Port Str to Dev_port Conversion table */
    PKTGEN_PORT_CFG = 20, /** Pktgen Port Configuration table */
    PKTGEN_APP_CFG = 21,  /** Pktgen Application Configuration table */
    PKTGEN_PKT_BUFF_CFG = 22,  /** Pktgen Packet Buffer Configuration table */
    PKTGEN_PORT_MASK_CFG = 23, /** Pktgen Port Mask Configuration table */
    PKTGEN_PORT_DOWN_REPLAY_CFG =
        24,         /** Pktgen Port Down Replay Configuration table*/
    PRE_MGID = 25,  /** PRE MGID table */
    PRE_NODE = 26,  /** PRE Node table */
    PRE_ECMP = 27,  /** PRE ECMP table */
    PRE_LAG = 28,   /** PRE LAG table */
    PRE_PRUNE = 29, /** PRE Prune (L2 XID) table */
    INVALID = 30,
  };

  /**
   * @brief Vector of pair of Key and Data. The key and data need to be
   * allocated
   * and pushed in the vector before being passed in to the appropriate Get API.
   */
  using keyDataPairs = std::vector<std::pair<BfRtTableKey *, BfRtTableData *>>;

  virtual ~BfRtTable() = default;
  //// Table APIs
  /**
   * @name Table APIs
   * @{
   */
  /**
   * @brief Add an entry to the table
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] key Entry Key
   * @param[in] data Entry Data
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryAdd(const BfRtSession &session,
                                    const bf_rt_target_t &dev_tgt,
                                    const BfRtTableKey &key,
                                    const BfRtTableData &data) const = 0;

  /**
   * @brief Modify an existing entry of the table
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] key Entry Key
   * @param[in] data Entry Data
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryMod(const BfRtSession &session,
                                    const bf_rt_target_t &dev_tgt,
                                    const BfRtTableKey &key,
                                    const BfRtTableData &data) const = 0;

  /**
   * @brief Modify only a part of an existing entry of the table.
   *            - Either add or delete the given data to the existing entry.
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] key Entry Key
   * @param[in] data Entry Data
   * @param[in] flag Modify inc flag (ADD or DEL)
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryModInc(
      const BfRtSession &session,
      const bf_rt_target_t &dev_tgt,
      const BfRtTableKey &key,
      const BfRtTableData &data,
      const BfRtTable::BfRtTableModIncFlag &flag) const = 0;

  /**
   * @brief Delete an entry of the table
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] key Entry Key
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryDel(const BfRtSession &session,
                                    const bf_rt_target_t &dev_tgt,
                                    const BfRtTableKey &key) const = 0;

  /**
   * @brief Set the default Entry of the table
   *
   * @details There can be a P4 defined default entry with parameters. This API
   *modifies any existing default entry to the one passed in here. Note that
   *this API is idempotent and should be called either when modifying an
   *existing default entry or to program one newly. There could be a particular
   *action which is designated as a default-only action. In that case, an error
   *is returned if the action id of the data object passed in here is different
   *from the designated default action.
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] data Entry Data
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableDefaultEntrySet(const BfRtSession &session,
                                           const bf_rt_target_t &dev_tgt,
                                           const BfRtTableData &data) const = 0;

  /**
   * @brief Reset the default Entry of the table
   *
   * @details The default entry of the table is reset to the P4 specified
   *default action with parameters, if it exists, else its reset to a "no-op"
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableDefaultEntryReset(
      const BfRtSession &session, const bf_rt_target_t &dev_tgt) const = 0;

  /**
   * @brief Get the default Entry of the table
   *
   * @details The default entry returned will be the one programmed or the P4
   *defined one, if it exists. Note that, when the entry is obtained from
   *software, the P4 defined default entry will not be available if the default
   *entry was not programmed ever. However, when the entry is obtained from
   *hardware, the P4 defined default entry will be returned even if the default
   *entry was not programmed ever.
   *
   *default action with parameters, if it exists, else its reset to a "no-op"
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableDefaultEntryGet(
      const BfRtSession &session,
      const bf_rt_target_t &dev_tgt,
      const BfRtTable::BfRtTableGetFlag &flag,
      BfRtTableData *data) const = 0;

  /**
   * @brief Get an entry from the table
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] key Entry Key
   * @param[in] flag Get Flags
   * @param[out] data Entry Data
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryGet(const BfRtSession &session,
                                    const bf_rt_target_t &dev_tgt,
                                    const BfRtTableKey &key,
                                    const BfRtTable::BfRtTableGetFlag &flag,
                                    BfRtTableData *data) const = 0;

  // Get first entry in the table
  /**
   * @brief Get the first entry of the table
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] flag Get Flags
   * @param[out] key Entry Key
   * @param[out] data Entry Data
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryGetFirst(
      const BfRtSession &session,
      const bf_rt_target_t &dev_tgt,
      const BfRtTable::BfRtTableGetFlag &flag,
      BfRtTableKey *key,
      BfRtTableData *data) const = 0;

  // Get next "n" entries in the table
  /**
   * @brief Get next N entries of the table. If the N queried for is greater
   *than
   * the actual entries, then all the entries present are returned
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] key Entry Key from which N entries are queried
   * @param[in] n Number of entries queried 'N'
   * @param[in] flag Get Flags
   * @param[out] key_data_pairs Vector of N Pairs(key, data). This vector needs
   * to have N entries before the API call is made, else error is returned
   * @param[out] num_returned Actual number of entries returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableEntryGetNext_n(
      const BfRtSession &session,
      const bf_rt_target_t &dev_tgt,
      const BfRtTableKey &key,
      const uint32_t &n,
      const BfRtTable::BfRtTableGetFlag &flag,
      keyDataPairs *key_data_pairs,
      uint32_t *num_returned) const = 0;

  /**
   * @brief Get name of the table
   *
   * @param[out] name Name of the table
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableNameGet(std::string *name) const = 0;

  /**
   * @brief Get ID of the table
   *
   * @param[out] id ID of the table
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableIdGet(bf_rt_id_t *id) const = 0;

  /**
   * @brief The maximum size of the table.
   *
   * @param[out] size Size of the table
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableSizeGet(size_t *size) const = 0;

  /**
   * @brief The type of the table
   *
   * @param[out] table_type type of the table
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableTypeGet(BfRtTable::TableType *table_type) const = 0;

  /**
   * @brief Current Usage of the table
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device target
   * @param[in] flag Get Flags
   * @param[out] count table usage
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableUsageGet(const BfRtSession &session,
                                    const bf_rt_target_t &dev_tgt,
                                    const BfRtTable::BfRtTableGetFlag &flag,
                                    uint32_t *count) const = 0;

  /**
   * @brief Get whether this table has a const default action
   *
   * @param[out] is_const_default If default action is const
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableHasConstDefaultAction(
      bool *has_const_default_action) const = 0;

  /**
   * @brief Get a set of annotations on a Table
   *
   * @param[out] annotations Set of annotations on a Table
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableAnnotationsGet(AnnotationSet *annotations) const = 0;

  /** @} */  // End of group Table

  //// Key APIs
  /**
   * @name Key APIs
   * @{
   */
  /**
   * @brief Allocate key for the table
   *
   * @param[out] key_ret Key object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyAllocate(
      std::unique_ptr<BfRtTableKey> *key_ret) const = 0;

  /**
   * @brief Get a vector of Key field IDs
   *
   * @param[out] id Vector of Key field IDs
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldIdListGet(std::vector<bf_rt_id_t> *id) const = 0;

  /**
   * @brief Get field type of Key Field
   *
   * @param[in] field_id Field ID
   * @param[out] field_type Field Type (Exact/Ternary/LPM/Range)
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldTypeGet(const bf_rt_id_t &field_id,
                                      KeyFieldType *field_type) const = 0;

  /**
   * @brief Get data type of Key Field
   *
   * @param[in] field_id Field ID
   * @param[out] data_type Field Type (uint64, float, string)
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldDataTypeGet(const bf_rt_id_t &field_id,
                                          DataType *data_type) const = 0;

  /**
   * @brief Get field ID of Key Field from name
   *
   * @param[in] name Key Field name
   * @param[out] field_id Field ID
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldIdGet(const std::string &name,
                                    bf_rt_id_t *field_id) const = 0;

  /**
   * @brief Get field size
   *
   * @param[in] field_id Field ID
   * @param[out] size Field Size in bits
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldSizeGet(const bf_rt_id_t &field_id,
                                      size_t *size) const = 0;

  /**
   * @brief Get whether Key Field is of type ptr or not. If the field is
   * of ptr type, then only ptr sets/gets are applicable on the field. Else
   * both the ptr versions and the uint64_t versions work
   *
   * @param[in] field_id Field ID
   * @param[out] is_ptr Boolean type indicating whether Field is of type ptr
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldIsPtrGet(const bf_rt_id_t &field_id,
                                       bool *is_ptr) const = 0;

  /**
   * @brief Get name of field
   *
   * @param[in] field_id Field ID
   * @param[out] name Field name
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldNameGet(const bf_rt_id_t &field_id,
                                      std::string *name) const = 0;

  /**
   * @brief Reset the key object associated with the table
   *
   * @param[in/out] Pointer to a key object, previously allocated using
   *keyAllocate on the table.
   *
   * @return Status of the API call. Error is returned if the key object is not
   *associated with the table.
   */
  virtual bf_status_t keyReset(BfRtTableKey *key) const = 0;

  /**
   * @brief Get a list of all the allowed values that a particular field can
   * have. This API is only for fields with string type. If the returned
   * vector is empty, it indicates that the allowed choices have not been
   * published in bfrt json
   *
   * @param[in] field_id Field ID
   * @param[out] choices Vector of const references of the values that are
   * allowed for this field
   *
   * @return Status of the API call
   */
  virtual bf_status_t keyFieldAllowedChoicesGet(
      const bf_rt_id_t &field_id,
      std::vector<std::reference_wrapper<const std::string>> *choices)
      const = 0;

  /** @} */  // End of group Key

  //// Data APIs
  /**
   * @name Data APIs
   * There are 2 base versions of every Data API. One, which takes in an
   * action_id and another which doesn't. All action_id APIs work only for
   * tables which have any actions. All non-action_id APIs work only for
   * tables which do NOT have actions.
   *
   * Exceptions: <br>
   * 1. Tables with Actions <br>
   *  a. \ref
   *bfrt::BfRtTable::dataAllocate(std::unique_ptr<BfRtTableData>*data_ret)const
   *    "dataAllocate(std::unique_ptr<BfRtTableData>*)"
   *  : This API is allowed
   *    with Gets and GetAlls in mind. However, if a tableAdd requires an
   *    action ID, an error will be thrown during runtime. <br>
   *
   * @{
   */
  /**
   * @brief Allocate Data Object for the table
   *
   * @param[out] data_ret Data Object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataAllocate(
      std::unique_ptr<BfRtTableData> *data_ret) const = 0;
  /**
   * @brief Allocate Data Object for the table
   *
   * @param[in] action_id Action ID
   * @param[out] data_ret Data Object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataAllocate(
      const bf_rt_id_t &action_id,
      std::unique_ptr<BfRtTableData> *data_ret) const = 0;

  /**
   * @brief Data Allocate with a list of field-ids. This allocates the data
   *object for
   * the list of field-ids. The field-ids passed must be valid for this table.
   * The Data Object then entertains APIs to read/write only those set of fields
   *
   * @param[in] fields Vector of field IDs
   * @param[out] data_ret Data Object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataAllocate(
      const std::vector<bf_rt_id_t> &fields,
      std::unique_ptr<BfRtTableData> *data_ret) const = 0;
  /**
   * @brief Data Allocate with a list of field-ids. This allocates the data
   *object for
   * the list of field-ids. The field-ids passed must be valid for this table.
   * The Data Object then entertains APIs to read/write only those set of fields
   *
   * @param[in] fields Vector of field IDs
   * @param[in] action_id Action ID
   * @param[out] data_ret Data Object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataAllocate(
      const std::vector<bf_rt_id_t> &fields,
      const bf_rt_id_t &action_id,
      std::unique_ptr<BfRtTableData> *data_ret) const = 0;

  /**
   * @brief Get vector of DataField IDs. Only applicable for tables
   * without Action IDs
   *
   * @param[out] id vector of IDs
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldIdListGet(std::vector<bf_rt_id_t> *id) const = 0;

  /**
   * @brief Get vector of DataField IDs for a particular action. Only applicable
   * for tables with Action IDs
   *
   * @param[in] action_id action ID
   * @param[out] id vector of IDs
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldIdListGet(const bf_rt_id_t &action_id,
                                         std::vector<bf_rt_id_t> *id) const = 0;

  /**
   * @brief Get vector of DataField IDs for a container's field id.
   *
   * @param[in] Field ID
   * @param[out] id vector of IDs
   *
   * @return Status of the API call
   */
  virtual bf_status_t containerDataFieldIdListGet(
      const bf_rt_id_t &field_id, std::vector<bf_rt_id_t> *id) const = 0;

  /**
   * @brief Get the field ID of a Data Field from a name. Only applicable for
   * tables without Action IDs
   *
   * @param[in] name Name of a Data field
   * @param[out] field_id Field ID
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldIdGet(const std::string &name,
                                     bf_rt_id_t *field_id) const = 0;

  /**
   * @brief Get the field ID of a Data Field from a name. Only applicable for
   * tables with Action IDs
   *
   * @param[in] name Name of a Data field
   * @param[in] action_id Action ID
   * @param[out] field_id Field ID
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldIdGet(const std::string &name,
                                     const bf_rt_id_t &action_id,
                                     bf_rt_id_t *field_id) const = 0;

  /**
   * @brief Get the Size of a field. Only applicable for tables without
   * Action IDs
   *
   * @param[in] field_id Field ID
   * @param[out] size Size of the field in bits
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldSizeGet(const bf_rt_id_t &field_id,
                                       size_t *size) const = 0;

  /**
   * @brief Get the Size of a field. Only applicable for tables with
   * Action IDs
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] size Size of the field in bits
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldSizeGet(const bf_rt_id_t &field_id,
                                       const bf_rt_id_t &action_id,
                                       size_t *size) const = 0;

  /**
   * @brief Get whether a field is a ptr type.
   * Only applicable for tables without Action IDs.
   * Only the ptr versions of setValue/getValue will work on fields
   * for which this API returns true
   *
   * @param[in] field_id Field ID
   * @param[out] is_ptr Boolean value indicating if it is ptr type
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldIsPtrGet(const bf_rt_id_t &field_id,
                                        bool *is_ptr) const = 0;

  /**
   * @brief Get whether a field is a ptr type.
   * Only applicable for tables with Action IDs.
   * Only the ptr versions of setValue/getValue will work on fields
   * for which this API returns true
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] is_ptr Boolean value indicating if it is ptr type
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldIsPtrGet(const bf_rt_id_t &field_id,
                                        const bf_rt_id_t &action_id,
                                        bool *is_ptr) const = 0;

  /**
 * @brief Get whether a field is mandatory.
 * Only applicable for tables without Action IDs.
 * Only the ptr versions of setValue/getValue will work on fields
 * for which this API returns true
 *
 * @param[in] field_id Field ID
 * @param[out] is_mandatory Boolean value indicating if it is mandatory
 *
 * @return Status of the API call
 */
  virtual bf_status_t dataFieldMandatoryGet(const bf_rt_id_t &field_id,
                                            bool *is_mandatory) const = 0;

  /**
   * @brief Get whether a field is mandatory.
   * Only applicable for tables with Action IDs.
   * Only the ptr versions of setValue/getValue will work on fields
   * for which this API returns true
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] is_mandatory Boolean value indicating if it is mandatory
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldMandatoryGet(const bf_rt_id_t &field_id,
                                            const bf_rt_id_t &action_id,
                                            bool *is_mandatory) const = 0;

  /**
* @brief Get whether a field is ReadOnly.
* Only applicable for tables without Action IDs.
* Only the ptr versions of setValue/getValue will work on fields
* for which this API returns true
*
* @param[in] field_id Field ID
* @param[out] is_read_only Boolean value indicating if it is ReadOnly
*
* @return Status of the API call
*/
  virtual bf_status_t dataFieldReadOnlyGet(const bf_rt_id_t &field_id,
                                           bool *is_read_only) const = 0;

  /**
   * @brief Get whether a field is ReadOnly.
   * Only applicable for tables with Action IDs.
   * Only the ptr versions of setValue/getValue will work on fields
   * for which this API returns true
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] is_read_only Boolean value indicating if it is ReadOnly
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldReadOnlyGet(const bf_rt_id_t &field_id,
                                           const bf_rt_id_t &action_id,
                                           bool *is_read_only) const = 0;

  /**
   * @brief Get the Name of a field. Only applicable for tables without
   * Action IDs
   *
   * @param[in] field_id Field ID
   * @param[out] name name of the field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldNameGet(const bf_rt_id_t &field_id,
                                       std::string *name) const = 0;

  /**
   * @brief Get the Name of a field. Only applicable for tables with
   * Action IDs
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] name name of the field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldNameGet(const bf_rt_id_t &field_id,
                                       const bf_rt_id_t &action_id,
                                       std::string *name) const = 0;
  /**
   * @brief Get the Data type of a field (INT/BOOL/ENUM/INT_ARR/BOOL_ARR)
   * Only applicable for tables without Action IDs
   *
   * @param[in] field_id Field ID
   * @param[out] type Data type of a data field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldDataTypeGet(const bf_rt_id_t &field_id,
                                           DataType *type) const = 0;
  /**
   * @brief Get the Data type of a field (INT/BOOL/ENUM/INT_ARR/BOOL_ARR)
   * Only applicable for tables with Action IDs
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] type Data type of a data field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldDataTypeGet(const bf_rt_id_t &field_id,
                                           const bf_rt_id_t &action_id,
                                           DataType *type) const = 0;

  /**
   * @brief Reset the data object previously allocated using dataAllocate on the
   *table
   *
   * @details Note that this API can also be called on the tables for which
   *action Id
   *is applicable. Calling this API resets the action-id in the object to an
   *invalid value. Typically this needs to be done when doing an entry get,
   *since the caller does not know the action-id associated with the entry.
   *Using the data object for an entry add on a table where action-id is
   *applicable will result in an error.
   *
   * @param[in/out] data Pointer to the data object allocated using dataAllocate
   *on
   *the table.
   *
   * @return Status of the API call. An error is returned if the data object is
   *not associated with the table
   */
  virtual bf_status_t dataReset(BfRtTableData *data) const = 0;

  /**
   * @brief Reset the data object previously allocated using dataAllocate on the
   *table
   *
   * @details Note that this API can be called only on the tables for which
   *action Id
   *is applicable. Calling this API sets the action-id in the object to the
   *passed in value.
   *
   * @param[in] action_id  new action id of the object
   *the table.
   * @param[in/out] Pointer to the data object allocated using dataAllocate on
   *the table.
   *
   * @return Status of the API call. An error is returned if the data object is
   *not associated with the table or if action-id is not applicable on the
   *table.
   */
  virtual bf_status_t dataReset(const bf_rt_id_t &action_id,
                                BfRtTableData *data) const = 0;

  /**
   * @brief Reset the data object previously allocated using dataAllocate on the
   *table
   *
   * @details Note that this API can also be called on the tables for which
   *action Id
   *is applicable. Calling this API resets the action-id in the object to an
   *invalid value. Typically this needs to be done when doing an entry get,
   *since the caller does not know the action-id associated with the entry.
   *Using the data object for an entry add on a table where action-id is
   *applicable will result in an error. The data object will contain the passed
   *in vector of field-ids active. This is typically done when reading an
   *entry's fields. Note that, the fields passed in must be common data fields
   *across all action-ids (common data fields, such as direct counter/direct
   *meter etc), for tables on which action-id is applicable.
   *
   * @param[in] fields Vector of field-ids that are to be activated in the data
   *object
   *the table.
   * @param[in/out] Pointer to the data object allocated using dataAllocate on
   *the table.
   *
   * @return Status of the API call. An error is returned if the data object is
   *not associated with the table, or if any field-id is action-specific, for
   *tables on which action-id is applicable..
   */
  virtual bf_status_t dataReset(const std::vector<bf_rt_id_t> &fields,
                                BfRtTableData *data) const = 0;

  /**
   * @brief Reset the data object previously allocated using dataAllocate on the
   *table
   *
   * @details Note that this API can be called only on the tables for which
   *action Id
   *is applicable. Calling this API sets the action-id in the object to the
   *passed in value and the list of fields passed in will be active in the data
   *object. The list of fields passed in must belong to the passed in action-id
   *or common across all action-ids associated with the table.
   *
   * @param[in] fields Vector of field-ids that are to be activated in the data
   *object
   *the table.
   * @param[in] action_id  new action id of the object
   *the table.
   * @param[in/out] Pointer to the data object allocated using dataAllocate on
   *the table.
   *
   * @return Status of the API call. An error is returned if the data object is
   *not associated with the table or if action-id is not applicable on the
   *table.
   */
  virtual bf_status_t dataReset(const std::vector<bf_rt_id_t> &fields,
                                const bf_rt_id_t &action_id,
                                BfRtTableData *data) const = 0;

  /**
   * @brief Get a list of all the allowed values that a particular field can
   * have. This API is only for fields with string type. If the returned
   * vector is empty, it indicates that the allowed choices have not been
   * published in bfrt json
   *
   * @param[in] field_id Field ID
   * @param[out] choices Vector of const references of the values that are
   * allowed for this field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldAllowedChoicesGet(
      const bf_rt_id_t &field_id,
      std::vector<std::reference_wrapper<const std::string>> *choices)
      const = 0;

  /**
   * @brief Get a list of all the allowed values that a particular field can
   * have. This API is only for fields with string type. If the returned
   * vector is empty, it indicates that the allowed choices have not been
   * published in bfrt json
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] choices Vector of const references of the values that are
   * allowed for this field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldAllowedChoicesGet(
      const bf_rt_id_t &field_id,
      const bf_rt_id_t &action_id,
      std::vector<std::reference_wrapper<const std::string>> *choices)
      const = 0;

  /**
   * @brief Get a set of annotations on a data field
   *
   * @param[in] field_id Field ID
   * @param[out] annotations Set of annotations on a data field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldAnnotationsGet(
      const bf_rt_id_t &field_id, AnnotationSet *annotations) const = 0;

  /**
   * @brief Get a set of annotations on a data field
   *
   * @param[in] field_id Field ID
   * @param[in] action_id Action ID
   * @param[out] annotations Set of annotations on a data field
   *
   * @return Status of the API call
   */
  virtual bf_status_t dataFieldAnnotationsGet(
      const bf_rt_id_t &field_id,
      const bf_rt_id_t &action_id,
      AnnotationSet *annotations) const = 0;

  /** @} */  // End of group Data

  // Action ID APIs
  /**
   * @name Action ID APIs
   * @{
   */
  /**
   * @brief Get Action ID from Name
   *
   * @param[in] name Action Name
   * @param[out] action_id Action ID
   *
   * @return Status of the API call
   */
  virtual bf_status_t actionIdGet(const std::string &name,
                                  bf_rt_id_t *action_id) const = 0;

  /**
   * @brief Get Action Name
   *
   * @param[in] action_id Action ID
   * @param[out] name Action Name
   *
   * @return Status of the API call
   */
  virtual bf_status_t actionNameGet(const bf_rt_id_t &action_id,
                                    std::string *name) const = 0;

  /**
   * @brief Get vector of Action IDs
   *
   * @param[out] action_id vector of Action IDs
   *
   * @return Status of the API call
   */
  virtual bf_status_t actionIdListGet(
      std::vector<bf_rt_id_t> *action_id) const = 0;

  /**
   * @brief Are Action IDs applicable for this table
   *
   * @retval True : If Action ID applicable
   * @retval False : If not
   *
   */
  virtual bool actionIdApplicable() const = 0;

  /**
   * @brief Get a set of annotations for this action.
   *
   * @param[in] action_id Action ID
   * @param[out] annotations set of annotations
   *
   * @return Status of the API call
   */
  virtual bf_status_t actionAnnotationsGet(
      const bf_rt_id_t &action_id, AnnotationSet *annotations) const = 0;

  /** @} */  // End of group Action IDs

  // table attribute APIs
  /**
   * @name Attribute APIs
   * @{
   */
  /**
   * @brief Allocate Attribute object of the table.
   *
   * @param[in]  type Type of the attribute
   * @param[out] attr Attribute object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t attributeAllocate(
      const TableAttributesType &type,
      std::unique_ptr<BfRtTableAttributes> *attr) const = 0;

  /**
   * @brief Allocate Attribute object of the table. This API
   * is to be used when idle_table attribute is being set
   *
   * @param[in]  type Type of the attribute
   * @param[in]  idle_table_type Idle table type (POLL/NOTIFY)
   * @param[out] attr Attribute object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t attributeAllocate(
      const TableAttributesType &type,
      const TableAttributesIdleTableMode &idle_table_type,
      std::unique_ptr<BfRtTableAttributes> *attr) const = 0;

  /**
   * @brief Reset Attribute object of the table.
   *
   * @param[in]  type Type of the attribute
   * @param[out] attr Attribute object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t attributeReset(
      const TableAttributesType &type,
      std::unique_ptr<BfRtTableAttributes> *attr) const = 0;

  /**
   * @brief Reset Attribute type and the Idle Table Mode
   *
   * @param[in]  type Type of the attribute
   * @param[in]  idle_table_type Idle table type (POLL/NOTIFY)
   * @param[out] attr Attribute object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t attributeReset(
      const TableAttributesType &type,
      const TableAttributesIdleTableMode &idle_table_type,
      std::unique_ptr<BfRtTableAttributes> *attr) const = 0;

  /**
   * @brief Apply an Attribute from an Attribute Object on the
   * table. Before using this API, the Attribute object needs to
   * be allocated and all the necessary values need to
   * be set on the Attribute object
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device Target
   * @param[in] tableAttributes Attribute Object
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableAttributesSet(
      const BfRtSession &session,
      const bf_rt_target_t &dev_tgt,
      const BfRtTableAttributes &tableAttributes) const = 0;

  /**
   * @brief Get the current Attributes set on the table. The attribute
   * object passed in as input param needs to be allocated first with
   * the required attribute type.
   *
   * @param[in] session Session Object
   * @param[in] dev_tgt Device Target
   * @param[out] tableAttributes Attribute Object
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableAttributesGet(
      const BfRtSession &session,
      const bf_rt_target_t &dev_tgt,
      BfRtTableAttributes *tableAttributes) const = 0;

  /**
   * @brief Get the set of supported attributes
   *
   * @param type_set Set of the supported Attributes
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableAttributesSupported(
      std::set<TableAttributesType> *type_set) const = 0;

  /** @} */  // End of group Attributes

  // table operations APIs
  /**
   * @name Operations APIs
   * @{
   */
  /**
   * @brief Allocate Operations object
   *
   * @param[in] type Operations type
   * @param[out] table_ops Operations Object returned
   *
   * @return Status of the API call
   */
  virtual bf_status_t operationsAllocate(
      const TableOperationsType &type,
      std::unique_ptr<BfRtTableOperations> *table_ops) const = 0;

  /**
   * @brief Get set of supported Operations
   *
   * @param[out] type_set Set of supported Operations
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableOperationsSupported(
      std::set<TableOperationsType> *type_set) const = 0;
  /**
   * @brief Execute Operations on a table
   *
   * @param[in] tableOperations Operations Object
   *
   * @return Status of the API call
   */
  virtual bf_status_t tableOperationsExecute(
      const BfRtTableOperations &tableOperations) const = 0;
  /** @} */  // End of group Operations

  // Table update callback registration APIs
  /**
   * @name Update callback APIs
   * @{
   */
  /**
   * @brief Callback registration for a Match-Action Table Update
   *
   * @param session Session Object
   * @param dev_tgt Device target
   * @param cb MAT update callback
   * @param cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t registerMatUpdateCb(const BfRtSession &session,
                                          const bf_rt_target_t &dev_tgt,
                                          const pipe_mat_update_cb &cb,
                                          const void *cookie) const = 0;
  /**
   * @brief Callback registration for an Action Table Update
   *
   * @param session Session Object
   * @param dev_tgt Device target
   * @param cb Action table update callback
   * @param cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t registerAdtUpdateCb(const BfRtSession &session,
                                          const bf_rt_target_t &dev_tgt,
                                          const pipe_adt_update_cb &cb,
                                          const void *cookie) const = 0;
  /**
   * @brief Callback registration for a Selector Table Update
   *
   * @param session Session Object
   * @param dev_tgt Device target
   * @param cb Selector table update callback
   * @param cookie User cookie
   *
   * @return Status of the API call
   */
  virtual bf_status_t registerSelUpdateCb(const BfRtSession &session,
                                          const bf_rt_target_t &dev_tgt,
                                          const pipe_sel_update_cb &cb,
                                          const void *cookie) const = 0;

  /** @} */  // End of group Callbacks
};

}  // bfrt

#endif  // _BF_RT_TABLE_HPP
