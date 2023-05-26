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
 ******************************************************************************/

/**
 * @file ctx_json_utils.h
 *
 * Utility functions used by the driver to facilitate parsing cJSON structures,
 * as well as macro definitions for the Context JSON's fields.
 */

#ifndef __CTX_JSON_UTILS__
#define __CTX_JSON_UTILS__

#include <bf_types/bf_types.h>
#include <bfutils/cJSON.h>
#include <pipe_mgr/pipe_mgr_intf.h>

/*
 * Macro definitions for the Context JSON fields.
 */
#define CTX_JSON_MATCH_ATTRIBUTES_NUMBER_PARTITIONS "number_partitions"
#define CTX_JSON_MATCH_TABLE_STATIC_ENTRIES "static_entries"
#define CTX_JSON_MATCH_TABLE_USES_RANGE "uses_range"
#define CTX_JSON_MATCH_TABLE_DISABLE_ATOMIC_MODIFY "disable_atomic_modify"
#define CTX_JSON_IDLETIME_STAGE_TABLE_DISABLE_NOTIFICATION \
  "disable_notification"
#define CTX_JSON_IDLETIME_STAGE_TABLE_ENABLE_PFE "enable_pfe"
#define CTX_JSON_IDLETIME_STAGE_TABLE_PRECISION "precision"
#define CTX_JSON_IDLETIME_STAGE_TABLE_TWO_WAY_NOTIFICATION \
  "two_way_notification"
#define CTX_JSON_MATCH_TABLE_DEFAULT_ACTION_HANDLE "default_action_handle"
#define CTX_JSON_MATCH_TABLE_DYNAMIC_MATCH_KEY_MASKS "dynamic_match_key_masks"
#define CTX_JSON_METER_STAGE_TABLE_DEFAULT_LOWER_HUFFMAN_BITS_INCLUDED \
  "default_lower_huffman_bits_included"
#define CTX_JSON_METER_TABLE_PRE_COLOR_FIELD_NAME "pre_color_field_name"
#define CTX_JSON_METER_STAGE_TABLE_ALU_INDEX "meter_alu_index"
#define CTX_JSON_METER_TABLE_ENABLE_COLOR_AWARE_PFE "enable_color_aware_pfe"
#define CTX_JSON_METER_TABLE_COLOR_AWARE_PFE_ADDRESS_TYPE_BIT_POSITION \
  "color_aware_pfe_address_type_bit_position"
#define CTX_JSON_METER_TABLE_ENABLE_PFE "enable_pfe"
#define CTX_JSON_METER_TABLE_ENABLE_PFE_BIT_POSITION "pfe_bit_position"
#define CTX_JSON_METER_TABLE_METER_GRANULARITY "meter_granularity"
#define CTX_JSON_METER_TABLE_METER_TYPE "meter_type"
#define CTX_JSON_METER_TABLE_METER_TYPE_STANDARD "standard"
#define CTX_JSON_SELECTION_TABLE_ACTION_DATA_TABLE_HANDLE \
  "action_data_table_handle"
#define CTX_JSON_SELECTION_TABLE_BOUND_TO_STATEFUL_TABLE_HANDLE \
  "bound_to_stateful_table_handle"
#define CTX_JSON_SELECTION_TABLE_BOUND_TO_ACTION_DATA_TABLE_HANDLE \
  "bound_to_action_data_table_handle"
#define CTX_JSON_SELECTION_TABLE_MAX_PORT_POOL_SIZE "max_port_pool_size"
#define CTX_JSON_SELECTION_TABLE_SELECTION_TYPE "selection_type"
#define CTX_JSON_SELECTION_TABLE_SPS_SCRAMBLE_ENABLE "sps_scramble_enable"
#define CTX_JSON_DRIVER_OPTIONS "driver_options"
#define CTX_JSON_DRIVER_OPTIONS_HASH_PARITY "hash_parity_enabled"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS "dynamic_hash_calculations"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_NAME "name"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HANDLE "handle"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LISTS "field_lists"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_NAME "name"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_HANDLE "handle"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_IS_DEFAULT "is_default"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CAN_PERMUTE "can_permute"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CAN_ROTATE "can_rotate"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_FIELDS "fields"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_FIELD_NAME "name"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_FIELD_START_BIT \
  "start_bit"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_FIELD_BIT_WIDTH \
  "bit_width"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_FIELD_OPTIONAL "optional"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_CONFIG \
  "crossbar_configuration"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_STAGE_ID \
  "stage_number"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR "crossbar"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_MOD \
  "crossbar_mod"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_NAME "name"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_BYTE \
  "byte_number"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_BIT "bit_in_byte"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_FIELD_LIST_CROSSBAR_FIELD_BIT \
  "field_bit"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ANY_HASH_ALGORITHM_ALLOWED \
  "any_hash_algorithm_allowed"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_BIT_WIDTH "hash_bit_width"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHMS "algorithms"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_NAME "name"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_HANDLE "handle"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_TYPE "type"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_IS_DEFAULT "is_default"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_MSB "msb"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_EXTEND "extend"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_POLYNOMIAL "poly"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_INIT "init"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_REVERSE "reverse"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_ALGORITHM_FINAL_XOR "final_xor"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_CONFIG "hash_configuration"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_CONFIG_STAGE_ID "stage_number"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH "hash"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_MOD "hash_mod"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_ID "hash_id"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_BITS "hash_bits"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_BIT_GFM "gfm_hash_bit"
#define CTX_JSON_DYNAMIC_HASH_CALCULATIONS_HASH_BIT_P4 "p4_hash_bit"
#define CTX_JSON_MEMORY_RESOURCE_ALLOCATION_MEMORY_TYPE "memory_type"
#define CTX_JSON_MEMORY_RESOURCE_ALLOCATION_SPARE_BANK_MEMORY_UNIT \
  "spare_bank_memory_unit"
#define CTX_JSON_MEMORY_UNITS_AND_VPNS_MEMORY_UNITS "memory_units"
#define CTX_JSON_MEMORY_UNITS_AND_VPNS_VPNS "vpns"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_HASH_FUNCTION_ID \
  "hash_function_id"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_HASH_SELECT_BIT_LO \
  "hash_select_bit_lo"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_HASH_SELECT_BIT_HI \
  "hash_select_bit_hi"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_HASH_ENTRY_BIT_LO \
  "hash_entry_bit_lo"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_HASH_ENTRY_BIT_HI \
  "hash_entry_bit_hi"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_NUMBER_SELECT_BITS \
  "number_select_bits"
#define CTX_JSON_HASH_MATCH_MEMORY_RESOURCE_ALLOCATION_NUMBER_ENTRY_BITS \
  "number_entry_bits"
#define CTX_JSON_STAGE_TABLE_DEFAULT_NEXT_TABLE "default_next_table"
#define CTX_JSON_STAGE_TABLE_RESULT_PHYSICAL_BUSES "result_physical_buses"
#define CTX_JSON_PACK_FORMAT_ENTRIES_PER_TABLE_WORD "entries_per_table_word"
#define CTX_JSON_PACK_FORMAT_MEMORY_WORD_WIDTH "memory_word_width"
#define CTX_JSON_PACK_FORMAT_NUMBER_MEMORY_UNITS_PER_TABLE_WORD \
  "number_memory_units_per_table_word"
#define CTX_JSON_PACK_FORMAT_TABLE_WORD_WIDTH "table_word_width"
#define CTX_JSON_STAGE_TABLE_SIZE "size"
#define CTX_JSON_STAGE_TABLE_STAGE_TABLE_TYPE "stage_table_type"
#define CTX_JSON_STAGE_TABLE_TYPE_HASH_ACTION "hash_action"
#define CTX_JSON_STAGE_TABLE_TYPE_HASH_MATCH "hash_match"
#define CTX_JSON_STAGE_TABLE_TYPE_PROXY_HASH_MATCH "proxy_hash_match"
#define CTX_JSON_STAGE_TABLE_TYPE_MATCH_WITH_NO_KEY "match_with_no_key"
#define CTX_JSON_STAGE_TABLE_TYPE_TERNARY_MATCH "ternary_match"
#define CTX_JSON_STAGE_TABLE_TYPE_TERNARY_INDIRECTION "ternary_indirection"
#define CTX_JSON_STAGE_TABLE_TYPE_PHASE0_MATCH "phase_0_match"
#define CTX_JSON_STAGE_TABLE_TYPE_DIRECT_MATCH "direct_match"
#define CTX_JSON_STAGE_TABLE_TYPE_ATCAM_MATCH "algorithmic_tcam_match"
#define CTX_JSON_STAGE_TABLE_TYPE_ACTION_DATA "action_data"
#define CTX_JSON_STAGE_TABLE_TYPE_METER "meter"
#define CTX_JSON_STAGE_TABLE_TYPE_STATISTICS "statistics"
#define CTX_JSON_STAGE_TABLE_TYPE_STATEFUL "stateful"
#define CTX_JSON_STAGE_TABLE_TYPE_SELECTION "selection"
#define CTX_JSON_STAGE_TABLE_TYPE_IDLETIME "idletime"
#define CTX_JSON_STATEFUL_TABLE_ACTION_TO_STATEFUL_INSTRUCTION_SLOT \
  "action_to_stateful_instruction_slot"
#define CTX_JSON_ACTION_ALLOWED_AS_DEFAULT_ACTION "allowed_as_default_action"
#define CTX_JSON_ACTION_IS_COMPILER_ADDED_ACTION "is_compiler_added_action"
#define CTX_JSON_ACTION_HANDLE "handle"
#define CTX_JSON_ACTION_NAME "name"
#define CTX_JSON_ACTION_INDIRECT_RESOURCES "indirect_resources"
#define CTX_JSON_INDIRECT_RESOURCE_VALUE "value"
#define CTX_JSON_INDIRECT_RESOURCE_PARAMETER_INDEX "parameter_index"
#define CTX_JSON_INDIRECT_RESOURCE_ACCESS_MODE "access_mode"
#define CTX_JSON_INDIRECT_RESOURCE_ACCESS_MODE_INDEX "index"
#define CTX_JSON_INDIRECT_RESOURCE_RESOURCE_NAME "resource_name"
#define CTX_JSON_INDIRECT_RESOURCE_PARAMETER_NAME "parameter_name"
#define CTX_JSON_ACTION_TO_STATEFUL_INSTRUCTION_SLOT_ACTION_HANDLE \
  "action_handle"
#define CTX_JSON_ACTION_TO_STATEFUL_INSTRUCTION_SLOT_INSTRUCTION_SLOT \
  "instruction_slot"
#define CTX_JSON_STATISTICS_TABLE_ENABLE_PFE "enable_pfe"
#define CTX_JSON_STATISTICS_TABLE_ENABLE_PFE_BIT_POSITION "pfe_bit_position"
#define CTX_JSON_STATISTICS_TABLE_STATISTICS_TYPE "statistics_type"
#define CTX_JSON_STATISTICS_TABLE_BYTE_COUNTER_RESOLUTION \
  "byte_counter_resolution"
#define CTX_JSON_STATISTICS_TABLE_PACKET_COUNTER_RESOLUTION \
  "packet_counter_resolution"
#define CTX_JSON_TABLE_HOW_REFERENCED "how_referenced"
#define CTX_JSON_TABLE_HOW_REFERENCED_DIRECT "direct"
#define CTX_JSON_TABLE_HOW_REFERENCED_INDIRECT "indirect"
#define CTX_JSON_TABLE_NAME "name"
#define CTX_JSON_TABLE_SIZE "size"
#define CTX_JSON_TABLE_STATEFUL_ALU_WIDTH "alu_width"
#define CTX_JSON_TABLE_STATEFUL_BOUND_TO_SELECTION_TABLE_HANDLE \
  "bound_to_selection_table_handle"
#define CTX_JSON_TABLE_STATEFUL_CLR_INSTR_ADJUST_TOTAL "clr_instr_adjust_total"
#define CTX_JSON_TABLE_STATEFUL_CLR_INSTR "clr_instr"
#define CTX_JSON_TABLE_STATEFUL_DUAL_WIDTH_MODE "dual_width_mode"
#define CTX_JSON_TABLE_STATEFUL_INITIAL_VALUE_HI "initial_value_hi"
#define CTX_JSON_TABLE_STATEFUL_INITIAL_VALUE_LO "initial_value_lo"
#define CTX_JSON_TABLE_STATEFUL_SET_INSTR_ADJUST_TOTAL "set_instr_adjust_total"
#define CTX_JSON_TABLE_STATEFUL_SET_INSTR "set_instr"
#define CTX_JSON_TABLE_STATEFUL_TYPE "stateful_table_type"
#define CTX_JSON_TABLE_STATEFUL_DIRECTION "stateful_direction"
#define CTX_JSON_TABLE_STATEFUL_CNTR_INDEX "stateful_counter_index"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_CONST_TUPLES "const_tuples"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_ENTRY_NUMBER "entry_number"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_FIELD_OFFSET "field_offset"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_FIELD_WIDTH "field_width"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_LSB_MEM_WORD_OFFSET \
  "lsb_mem_word_offset"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_LSB_MEM_WORD_INDEX "lsb_mem_word_idx"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_MOD_FIELD_CONDITIONALLY_MASK \
  "is_mod_field_conditionally_mask"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_MOD_FIELD_CONDITIONALLY_VALUE \
  "is_mod_field_conditionally_value"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_MOD_FIELD_CONDITIONALLY_MASK_FIELD_NAME \
  "mod_field_conditionally_mask_field_name"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_SOURCE "source"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_SOURCE_CONSTANT "constant"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_SOURCE_SPEC "spec"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_SOURCE_VERSION "version"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_SOURCE_ZERO "zero"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_START_BIT "start_bit"
#define CTX_JSON_ACTION_DATA_ENTRY_FORMAT_FIELD_NAME "field_name"
#define CTX_JSON_ACTION_FORMAT_ACTION_NAME "action_name"
#define CTX_JSON_ACTION_FORMAT_ACTION_HANDLE "action_handle"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_METER_ADDR "override_meter_addr"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_METER_FULL_ADDR \
  "override_meter_full_addr"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_METER_PFE_SET "override_meter_addr_pfe"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_STATS_ADDR "override_stat_addr"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_STATS_FULL_ADDR \
  "override_stat_full_addr"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_STATS_PFE_SET "override_stat_addr_pfe"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_STFUL_ADDR "override_stateful_addr"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_STFUL_FULL_ADDR \
  "override_stateful_full_addr"
#define CTX_JSON_ACTION_FORMAT_OVERRIDE_STFUL_PFE_SET \
  "override_stateful_addr_pfe"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_CONST_VALUE "const_value"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_DEST_START "dest_start"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_DEST_WIDTH "dest_width"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_PARAM_NAME "param_name"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_PARAM_TYPE "param_type"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_PARAM_TYPE_CONSTANT "constant"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_PARAM_TYPE_PARAMETER "parameter"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS_PARAM_SHIFT "param_shift"
#define CTX_JSON_ACTION_FORMAT_TABLE_MASK "table_mask"
#define CTX_JSON_ACTION_FORMAT_VLIW_INSTRUCTION "vliw_instruction"
#define CTX_JSON_ACTION_FORMAT_VLIW_INSTRUCTION_FULL "vliw_instruction_full"
#define CTX_JSON_ACTION_FORMAT_NEXT_TABLE "next_table"
#define CTX_JSON_ACTION_FORMAT_NEXT_TABLE_FULL "next_table_full"
#define CTX_JSON_ACTION_P4_PARAMETERS "p4_parameters"
#define CTX_JSON_P4_PARAMETER_BIT_WIDTH "bit_width"
#define CTX_JSON_P4_PARAMETER_NAME "name"
#define CTX_JSON_P4_PARAMETER_DEFAULT_VALUE "default_value"
#define CTX_JSON_ACTION_NAME "name"
#define CTX_JSON_ACTION_HANDLE "handle"
#define CTX_JSON_CONST_TUPLE_DEST_START "dest_start"
#define CTX_JSON_CONST_TUPLE_DEST_WIDTH "dest_width"
#define CTX_JSON_CONST_TUPLE_VALUE "value"
#define CTX_JSON_DEFAULT_ENTRY_FORMAT_FIELDS "fields"
#define CTX_JSON_MATCH_TABLE_DEFAULT_NEXT_TABLE_MASK "default_next_table_mask"
#define CTX_JSON_DEFAULT_ENTRY_FORMAT_SOURCE "source"
#define CTX_JSON_DEFAULT_ENTRY_FORMAT_SOURCE_SEL_PTR "sel_ptr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_ENTRY_NUMBER "entry_number"
#define CTX_JSON_EXACT_ENTRY_FORMAT_ENABLE_PFE "enable_pfe"
#define CTX_JSON_EXACT_ENTRY_FORMAT_FIELD_NAME "field_name"
#define CTX_JSON_EXACT_ENTRY_FORMAT_FIELD_OFFSET "field_offset"
#define CTX_JSON_EXACT_ENTRY_FORMAT_FIELD_WIDTH "field_width"
#define CTX_JSON_EXACT_ENTRY_FORMAT_IMMEDIATE_NAME "immediate_name"
#define CTX_JSON_EXACT_ENTRY_FORMAT_LSB_MEM_WORD_INDEX "lsb_mem_word_idx"
#define CTX_JSON_EXACT_ENTRY_FORMAT_MSB_MEM_WORD_INDEX "msb_mem_word_idx"
#define CTX_JSON_EXACT_ENTRY_FORMAT_LSB_MEM_WORD_OFFSET "lsb_mem_word_offset"
#define CTX_JSON_EXACT_ENTRY_FORMAT_MATCH_MODE "match_mode"
#define CTX_JSON_EXACT_ENTRY_FORMAT_MATCH_MODE_EXACT "exact"
#define CTX_JSON_EXACT_ENTRY_FORMAT_MATCH_MODE_S1Q0 "s1q0"
#define CTX_JSON_EXACT_ENTRY_FORMAT_MATCH_MODE_S0Q1 "s0q1"
#define CTX_JSON_EXACT_ENTRY_FORMAT_MATCH_MODE_UNUSED "unused"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE "source"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_ADT_PTR "adt_ptr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_IMMEDIATE "immediate"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_INSTR "instr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_METER_PTR "meter_ptr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_NEXT_TABLE "next_table"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_PROXY_HASH "proxy_hash"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_SELECTION_LENGTH "selection_length"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_SELECTION_LENGTH_SHIFT \
  "selection_length_shift"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_SEL_PTR "sel_ptr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_SPEC "spec"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_STATEFUL_PTR "stful_ptr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_STATS_PTR "stats_ptr"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_VERSION "version"
#define CTX_JSON_EXACT_ENTRY_FORMAT_SOURCE_ZERO "zero"
#define CTX_JSON_EXACT_ENTRY_FORMAT_START_BIT "start_bit"
#define CTX_JSON_HASH_BIT_BITS_TO_XOR "bits_to_xor"
#define CTX_JSON_BIT_TO_XOR_FIELD_BIT "field_bit"
#define CTX_JSON_BIT_TO_XOR_FIELD_NAME "field_name"
#define CTX_JSON_BIT_TO_XOR_HASH_MATCH_GROUP_BIT "hash_match_group_bit"
#define CTX_JSON_BIT_TO_XOR_HASH_MATCH_GROUP "hash_match_group"
#define CTX_JSON_HASH_BIT_MATCH_TYPE "match_type"
#define CTX_JSON_HASH_BIT_MATCH_TYPE_EXACT "exact"
#define CTX_JSON_HASH_BIT_MATCH_TYPE_VALID "valid"
#define CTX_JSON_HASH_BIT_SEED "seed"
#define CTX_JSON_HASH_BITS_HASH_BIT "hash_bit"
#define CTX_JSON_GHOST_BIT_INFO_FIELD_NAME "field_name"
#define CTX_JSON_GHOST_BIT_INFO_POSITION "bit_in_match_spec"
#define CTX_JSON_HASH_FUNCTION_HASH_BITS "hash_bits"
#define CTX_JSON_HASH_FUNCTION_HASH_FUNCTION_NUMBER "hash_function_number"
#define CTX_JSON_CONFIG_CACHE_NODE "configuration_cache"
#define CTX_JSON_CONFIG_CACHE_NAME "fully_qualified_name"
#define CTX_JSON_CONFIG_CACHE_VALUE "value"
#define CTX_JSON_LEARN_QUANTA_NODE "learn_quanta"
#define CTX_JSON_LEARN_QUANTUM_LQ_CFG_TYPE "lq_cfg_type"
#define CTX_JSON_LEARN_QUANTUM_HANDLE "handle"
#define CTX_JSON_LEARN_QUANTUM_NAME "name"
#define CTX_JSON_LEARN_QUANTUM_FIELDS "fields"
#define CTX_JSON_LEARN_QUANTUM_FIELD_NAME "field_name"
#define CTX_JSON_LEARN_QUANTUM_FIELD_START_BIT "start_bit"
#define CTX_JSON_LEARN_QUANTUM_FIELD_START_BYTE "start_byte"
#define CTX_JSON_LEARN_QUANTUM_FIELD_WIDTH "field_width"
#define CTX_JSON_MATCH_ATTRIBUTES_SET_PARTITION_ACTION_HANDLE \
  "set_partition_action_handle"
#define CTX_JSON_MATCH_ATTRIBUTES_PARTITION_FIELD_NAME "partition_field_name"
#define CTX_JSON_MATCH_ATTRIBUTES_LPM_FIELD_NAME "lpm_field_name"
#define CTX_JSON_MATCH_ATTRIBUTES_MATCH_TYPE "match_type"
#define CTX_JSON_MATCH_ATTRIBUTES_USES_RANGE "uses_range"
#define CTX_JSON_MATCH_ATTRIBUTES_USES_DYNAMIC_KEY_MASKS \
  "uses_dynamic_key_masks"
#define CTX_JSON_MATCH_ATTRIBUTES_UNITS "units"
#define CTX_JSON_MATCH_ATTRIBUTES_ATCAM_TABLE "atcam_table"
#define CTX_JSON_MATCH_ATTRIBUTES_STAGE_TABLES "stage_tables"
#define CTX_JSON_MATCH_ATTRIBUTES_PREFIX_LOWER "prefix_lower"
#define CTX_JSON_MATCH_ATTRIBUTES_PREFIX_UPPER "prefix_upper"
#define CTX_JSON_MATCH_ATTRIBUTES_PREFIX_LENGTH "prefix_length"
#define CTX_JSON_MATCH_ATTRIBUTES_BINS_PER_PARTITION "bins_per_partition"
#define CTX_JSON_MATCH_ATTRIBUTES_PRE_CLASSIFIER "pre_classifier"
#define CTX_JSON_MATCH_ATTRIBUTES_MAX_SUBTREES_PER_PARTITION \
  "max_subtrees_per_partition"
#define CTX_JSON_MATCH_ATTRIBUTES_EXCLUDED_FIELDS "excluded_field_msb_bits"
#define CTX_JSON_MATCH_ATTRIBUTES_EXCLUDED_FIELD_BITS "msb_bits_excluded"
#define CTX_JSON_MATCH_ATTRIBUTES_EXCLUDED_FIELD_NAME "field_name"
#define CTX_JSON_STAGE_TABLE_IDLETIME_STAGE_TABLE "idletime_stage_table"
#define CTX_JSON_MATCH_KEY_FIELDS_BIT_WIDTH "bit_width"
#define CTX_JSON_MATCH_KEY_FIELDS_BIT_WIDTH_FULL "bit_width_full"
#define CTX_JSON_MATCH_KEY_FIELDS_MATCH_TYPE "match_type"
#define CTX_JSON_MATCH_KEY_FIELDS_MATCH_TYPE_EXACT "exact"
#define CTX_JSON_MATCH_KEY_FIELDS_MATCH_TYPE_LPM "lpm"
#define CTX_JSON_MATCH_KEY_FIELDS_MATCH_TYPE_TERNARY "ternary"
#define CTX_JSON_MATCH_KEY_FIELDS_MATCH_TYPE_RANGE "range"
#define CTX_JSON_MATCH_KEY_FIELDS_MATCH_TYPE_VALID "valid"
#define CTX_JSON_MATCH_KEY_FIELDS_NAME "name"
#define CTX_JSON_MATCH_TABLE_ACTION_DATA_TABLE_REFS "action_data_table_refs"
#define CTX_JSON_MATCH_TABLE_METER_TABLE_REFS "meter_table_refs"
#define CTX_JSON_MATCH_TABLE_SELECTION_TABLE_REFS "selection_table_refs"
#define CTX_JSON_MATCH_TABLE_STATISTICS_TABLE_REFS "statistics_table_refs"
#define CTX_JSON_MATCH_TABLE_STATEFUL_TABLE_REFS "stateful_table_refs"
#define CTX_JSON_MATCH_TABLE_REFERENCES_HANDLE "handle"
#define CTX_JSON_MATCH_TABLE_ACTIONS "actions"
#define CTX_JSON_ACTION_HANDLE "handle"
#define CTX_JSON_ACTION_NAME "name"
#define CTX_JSON_ACTION_P4_PARAMETERS "p4_parameters"
#define CTX_JSON_MATCH_TABLE_MATCH_ATTRIBUTES "match_attributes"
#define CTX_JSON_MATCH_TABLE_MATCH_KEY_FIELDS "match_key_fields"
#define CTX_JSON_MATCH_TABLE_TYPE_EXACT "exact"
#define CTX_JSON_MATCH_TABLE_TYPE_TERNARY "ternary"
#define CTX_JSON_MATCH_TABLE_TYPE_PHASE0 "phase_0_match"
#define CTX_JSON_MATCH_TABLE_TYPE_NO_KEY "match_with_no_key"
#define CTX_JSON_MATCH_TABLE_TYPE_HASH_ACTION "hash_action"
#define CTX_JSON_MATCH_TABLE_TYPE_ATCAM "algorithmic_tcam"
#define CTX_JSON_MATCH_TABLE_TYPE_ALPM "algorithmic_lpm"
#define CTX_JSON_MATCH_TABLE_TYPE_CLPM "chained_lpm"
#define CTX_JSON_MEMORY_RESOURCE_ALLOCATION_COLUMN_PRIORITY "column_priority"
#define CTX_JSON_MEMORY_RESOURCE_ALLOCATION_MEMORY_UNITS_AND_VPNS \
  "memory_units_and_vpns"
#define CTX_JSON_PACK_FORMAT_ACTION_HANDLE "action_handle"
#define CTX_JSON_PACK_FORMAT_ENTRIES "entries"
#define CTX_JSON_PACK_FORMAT_ENTRY_FIELDS "fields"
#define CTX_JSON_STAGE_TABLE_ACTION_FORMAT "action_format"
#define CTX_JSON_ACTION_FORMAT_IMMEDIATE_FIELDS "immediate_fields"
#define CTX_JSON_STAGE_TABLE_HASH_FUNCTIONS "hash_functions"
#define CTX_JSON_STAGE_TABLE_GHOST_BIT_INFO "ghost_bit_info"
#define CTX_JSON_STAGE_TABLE_GHOST_BITS_TO_HASH_BIT "ghost_bit_to_hash_bit"
#define CTX_JSON_STAGE_TABLE_PROXY_HASH_FUNCTION "proxy_hash_function"
#define CTX_JSON_STAGE_TABLE_LOGICAL_TABLE_ID "logical_table_id"
#define CTX_JSON_STAGE_TABLE_HAS_ATTACHED_GATEWAY "has_attached_gateway"
#define CTX_JSON_STAGE_TABLE_MEMORY_RESOURCE_ALLOCATION \
  "memory_resource_allocation"
#define CTX_JSON_STAGE_TABLE_COLOR_MEMORY_RESOURCE_ALLOCATION \
  "color_memory_resource_allocation"
#define CTX_JSON_STAGE_TABLE_PACK_FORMAT "pack_format"
#define CTX_JSON_STAGE_TABLE_STASH_ALLOCATION "stash_allocation"
#define CTX_JSON_STAGE_TABLE_STASH_NUM_ENTRY "num_stash_entries"
#define CTX_JSON_STAGE_TABLE_STASH_ENTRIES "stash_entries"
#define CTX_JSON_STAGE_TABLE_STASH_ENTRY_ID "stash_entry_id"
#define CTX_JSON_STAGE_TABLE_STASH_MATCH_DATA_SELECT "stash_match_data_select"
#define CTX_JSON_STAGE_TABLE_STASH_HASHBANK_SELECT "stash_hashbank_select"
#define CTX_JSON_STAGE_TABLE_STASH_HASH_FUNCTION_ID "hash_function_id"
#define CTX_JSON_STAGE_TABLE_STAGE_NUMBER "stage_number"
#define CTX_JSON_STAGE_TABLE_TERNARY_INDIRECTION_STAGE_TABLE \
  "ternary_indirection_stage_table"
#define CTX_JSON_STAGE_TABLE_WAYS "ways"
#define CTX_JSON_TABLE_ACTIONS "actions"
#define CTX_JSON_TABLE_HANDLE "handle"
#define CTX_JSON_TABLE_DIRECTION "direction"
#define CTX_JSON_TABLE_DIRECTION_INGRESS "ingress"
#define CTX_JSON_TABLE_DIRECTION_EGRESS "egress"
#define CTX_JSON_TABLE_DIRECTION_GHOST "ghost"
#define CTX_JSON_TABLE_STAGE_TABLES "stage_tables"
#define CTX_JSON_TABLE_TABLE_TYPE "table_type"
#define CTX_JSON_TABLE_TYPE_ACTION_DATA "action"
#define CTX_JSON_TABLE_TYPE_CONDITION "condition"
#define CTX_JSON_TABLE_TYPE_MATCH "match"
#define CTX_JSON_TABLE_TYPE_METER "meter"
#define CTX_JSON_TABLE_TYPE_SELECTION "selection"
#define CTX_JSON_TABLE_TYPE_STATEFUL "stateful"
#define CTX_JSON_TABLE_TYPE_STATISTICS "statistics"
#define CTX_JSON_COMPILER_VERSION "compiler_version"
#define CTX_JSON_SCHEMA_VERSION "schema_version"
#define CTX_JSON_TABLES_NODE "tables"
#define CTX_JSON_PARSER_NODE "parser"
#define CTX_JSON_PARSER_INGRESS "ingress"
#define CTX_JSON_PARSER_EGRESS "egress"
#define CTX_JSON_PVS_USES_PVS "uses_pvs"
#define CTX_JSON_PVS_PVS_NAME "pvs_name"
#define CTX_JSON_PVS_PVS_HANDLE "pvs_handle"
#define CTX_JSON_PVS_PARSER_STATE_ID "parser_state_id"
#define CTX_JSON_MATCH_REGISTER_CONTAINER_HARDWARE_ID "container_hardware_id"
#define CTX_JSON_MATCH_REGISTER_CONTAINER_WIDTH "container_width"
#define CTX_JSON_MATCH_REGISTER_MASK "mask"
#define CTX_JSON_PVS_TCAM_ROWS "tcam_rows"
#define CTX_JSON_PVS_MATCH_REGISTERS "match_registers"
#define CTX_JSON_PVS_MATCH_REGISTER_FIELD_MAPPING "field_mapping"
#define CTX_JSON_PVS_MATCH_REGISTER_FIELD_MAPPING_REGISTER_BIT "register_bit"
#define CTX_JSON_PVS_MATCH_REGISTER_FIELD_MAPPING_SELECT_STATEMENT_BIT \
  "select_statement_bit"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_ENTRY_NUMBER "entry_number"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_FIELD_NAME "field_name"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_FIELD_OFFSET "field_offset"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_FIELD_WIDTH "field_width"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_LSB_MEM_WORD_INDEX "lsb_mem_word_idx"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_LSB_MEM_WORD_OFFSET "lsb_mem_word_offset"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_SOURCE "source"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_SOURCE_IMMEDIATE "immediate"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_SOURCE_SPEC "spec"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_SOURCE_ZERO "zero"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_START_BIT "start_bit"
#define CTX_JSON_PHASE0_ENTRY_FORMAT_CONST_VALUE "const_value"
#define CTX_JSON_TERN_ENTRY_FORMAT_ENTRY_NUMBER "entry_number"
#define CTX_JSON_TERN_ENTRY_FORMAT_FIELD_NAME "field_name"
#define CTX_JSON_TERN_ENTRY_FORMAT_FIELD_OFFSET "field_offset"
#define CTX_JSON_TERN_ENTRY_FORMAT_FIELD_WIDTH "field_width"
#define CTX_JSON_TERN_ENTRY_FORMAT_LSB_MEM_WORD_INDEX "lsb_mem_word_idx"
#define CTX_JSON_TERN_ENTRY_FORMAT_MSB_MEM_WORD_INDEX "msb_mem_word_idx"
#define CTX_JSON_TERN_ENTRY_FORMAT_LSB_MEM_WORD_OFFSET "lsb_mem_word_offset"
#define CTX_JSON_TERN_ENTRY_FORMAT_RANGE "range"
#define CTX_JSON_TERN_ENTRY_FORMAT_RANGE_TYPE "type"
#define CTX_JSON_TERN_ENTRY_FORMAT_RANGE_IS_DUPLICATE "is_duplicate"
#define CTX_JSON_TERN_ENTRY_FORMAT_RANGE_NIBBLE_OFFSET "nibble_offset"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE "source"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE_PARITY "parity"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE_PAYLOAD "payload"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE_RANGE "range"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE_SPEC "spec"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE_VERSION "version"
#define CTX_JSON_TERN_ENTRY_FORMAT_SOURCE_ZERO "zero"
#define CTX_JSON_TERN_ENTRY_FORMAT_START_BIT "start_bit"
#define CTX_JSON_TIND_ENTRY_FORMAT_ENABLE_PFE "enable_pfe"
#define CTX_JSON_TIND_ENTRY_FORMAT_ENTRY_NUMBER "entry_number"
#define CTX_JSON_TIND_ENTRY_FORMAT_FIELD_NAME "field_name"
#define CTX_JSON_TIND_ENTRY_FORMAT_FIELD_OFFSET "field_offset"
#define CTX_JSON_TIND_ENTRY_FORMAT_FIELD_WIDTH "field_width"
#define CTX_JSON_TIND_ENTRY_FORMAT_IMMEDIATE_NAME "immediate_name"
#define CTX_JSON_TIND_ENTRY_FORMAT_LSB_MEM_WORD_OFFSET "lsb_mem_word_offset"
#define CTX_JSON_TIND_ENTRY_FORMAT_LSB_MEM_WORD_INDEX "lsb_mem_word_idx"
#define CTX_JSON_TIND_ENTRY_FORMAT_MSB_MEM_WORD_INDEX "msb_mem_word_idx"
#define CTX_JSON_TIND_ENTRY_FORMAT_MS_BIT "ms_bit"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE "source"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_ADT_PTR "adt_ptr"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_IMMEDIATE "immediate"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_INSTR "instr"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_METER_PTR "meter_ptr"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_NEXT_TABLE "next_table"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_PROXY_HASH "proxy_hash"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_SELECTION_LENGTH "selection_length"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_SELECTION_LENGTH_SHIFT \
  "selection_length_shift"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_SEL_PTR "sel_ptr"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_SPEC "spec"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_STATEFUL_PTR "stful_ptr"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_STATS_PTR "stats_ptr"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_VERSION "version"
#define CTX_JSON_TIND_ENTRY_FORMAT_SOURCE_ZERO "zero"
#define CTX_JSON_TIND_ENTRY_FORMAT_START_BIT "start_bit"
#define CTX_JSON_PHV_CONTAINER_PHV_NUMBER "phv_number"
#define CTX_JSON_PHV_CONTAINER_WORD_BIT_WIDTH "word_bit_width"
#define CTX_JSON_PHV_CONTAINER_TYPE "container_type"
#define CTX_JSON_PHV_CONTAINER_RECORDS "records"
#define CTX_JSON_PHV_RECORD_FIELD_NAME "field_name"
#define CTX_JSON_PHV_RECORD_POSITION_OFFSET "position_offset"
#define CTX_JSON_PHV_RECORD_FIELD_LSB "field_lsb"
#define CTX_JSON_PHV_RECORD_FIELD_MSB "field_msb"
#define CTX_JSON_PHV_RECORD_FIELD_WIDTH "field_width"
#define CTX_JSON_PHV_RECORD_PHV_LSB "phv_lsb"
#define CTX_JSON_PHV_RECORD_PHV_MSB "phv_msb"
#define CTX_JSON_PHV_RECORD_IS_COMPILER_GENERATED "is_compiler_generated"
#define CTX_JSON_PHV_RECORD_IS_POV "is_pov"
#define CTX_JSON_PHV_RECORD_POV_HEADERS "pov_headers"
#define CTX_JSON_POV_HEADER_HEADER_NAME "header_name"
#define CTX_JSON_POV_HEADER_BIT_INDEX "bit_index"
#define CTX_JSON_POV_HEADER_POSITION_OFFSET "position_offset"
#define CTX_JSON_POV_HEADER_HIDDEN "hidden"
#define CTX_JSON_STATIC_ENTRY_IS_DEFAULT_ENTRY "is_default_entry"
#define CTX_JSON_STATIC_ENTRY_PRIORITY "priority"
#define CTX_JSON_STATIC_ENTRY_ACTION_HANDLE "action_handle"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELDS_VALUES "match_key_fields_values"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELD_NAME "field_name"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELD_VALUE "value"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELD_MASK "mask"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELD_PREFIX_LENGTH "prefix_length"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELD_RANGE_START "range_start"
#define CTX_JSON_STATIC_ENTRY_MATCH_KEY_FIELD_RANGE_END "range_end"
#define CTX_JSON_STATIC_ENTRY_ACTION_PARAMETERS_VALUES \
  "action_parameters_values"
#define CTX_JSON_STATIC_ENTRY_ACTION_PARAMETER_NAME "parameter_name"
#define CTX_JSON_STATIC_ENTRY_ACTION_PARAMETER_VALUE "value"
#define CTX_JSON_STAGE_PHV_ALLOCATION_INGRESS "ingress"
#define CTX_JSON_STAGE_PHV_ALLOCATION_EGRESS "egress"
#define CTX_JSON_STAGE_PHV_ALLOCATION_STAGE_NUMBER "stage_number"
#define CTX_JSON_PHV_ALLOCATION_NODE "phv_allocation"
#define CTX_JSON_WAY_WAY_NUMBER "way_number"
#define CTX_JSON_STAGE_DEPENDENCY_NODE "stage_dependency"
#define CTX_JSON_STAGE_DEPENDENCY_STAGE "stage"
#define CTX_JSON_STAGE_DEPENDENCY_GRESS "gress"
#define CTX_JSON_STAGE_DEPENDENCY_MATCH "match_dependent"
/*
 * Macro definition that allows iterating over a cJSON array.
 */
#define CTX_JSON_FOR_EACH(it, parent) \
  for ((it) = (parent)->child; (it) != NULL; (it) = (it)->next)

#define GETARRITEM(arr, i) (cJSON_GetArrayItem((arr), i))
#define GETARRSZ(arr) (cJSON_GetArraySize((arr)))

typedef enum {
  CTX_JSON_MATCH_TYPE_VALID,
  CTX_JSON_MATCH_TYPE_EXACT,
  CTX_JSON_MATCH_TYPE_LPM,
  CTX_JSON_MATCH_TYPE_TERNARY,
  CTX_JSON_MATCH_TYPE_RANGE,
  CTX_JSON_MATCH_TYPE_INVALID
} ctx_json_match_type;

int bf_cjson_get_string(cJSON *cjson, char *property, char **ret);
int bf_cjson_get_string_dup(cJSON *cjson, char *property, char **ret);
int bf_cjson_try_get_string(cJSON *cjson, char *property, char **ret);
int bf_cjson_try_get_string_dup(cJSON *cjson, char *property, char **ret);
int bf_cjson_get_hex(cJSON *cjson, char *property, uint8_t *ret, uint8_t len);
int bf_cjson_try_get_hex(cJSON *cjson,
                         char *property,
                         uint8_t *ret,
                         uint8_t len);
int bf_cjson_get_int(cJSON *cjson, char *property, int *ret);
int bf_cjson_try_get_int(cJSON *cjson, char *property, int *ret);
int bf_cjson_get_double(cJSON *cjson, char *property, double *ret);
int bf_cjson_try_get_double(cJSON *cjson, char *property, double *ret);
int bf_cjson_get_bool(cJSON *cjson, char *property, bool *ret);
int bf_cjson_try_get_bool(cJSON *cjson, char *property, bool *ret);
int bf_cjson_get_first(cJSON *cjson, cJSON **ret);
int bf_cjson_try_get_first(cJSON *cjson, cJSON **ret);
int bf_cjson_get_object(cJSON *cjson, char *property, cJSON **ret);
int bf_cjson_try_get_object(cJSON *cjson, char *property, cJSON **ret);
int bf_cjson_get_handle(bf_dev_id_t devid,
                        profile_id_t prof_id,
                        cJSON *cjson,
                        char *property,
                        int *ret);
int bf_cjson_try_get_handle(bf_dev_id_t devid,
                            profile_id_t prof_id,
                            cJSON *cjson,
                            char *property,
                            int *ret);
int ctx_json_parse_action_spec_details_for_field(cJSON *action_cjson,
                                                 char *field_to_find,
                                                 int *spec_length_ret,
                                                 int *spec_offset_ret);
int ctx_json_parse_spec_details_for_field(cJSON *match_key_fields_cjson,
                                          char *field_to_find,
                                          int *spec_length_ret,
                                          int *spec_offset_ret,
                                          int *match_type_ret);
int ctx_json_parse_all_match_stage_tables(cJSON *tables_cjson,
                                          int max_number_stage_tables,
                                          cJSON **all_stage_tables_cjson,
                                          int *number_stage_tables);
int ctx_json_parse_all_match_stage_tables_for_table(
    cJSON *table_cjson,
    int max_number_stage_tables,
    cJSON **all_stage_tables_cjson,
    int *number_stage_tables);
int ctx_json_parse_action_for_action_handle(bf_dev_id_t devid,
                                            profile_id_t prof_id,
                                            cJSON *actions_cjson,
                                            int action_handle,
                                            cJSON **ret);
int ctx_json_parse_action_parameter_for_parameter(cJSON *action_cjson,
                                                  char *parameter_to_find,
                                                  int *bit_width_ret);
int ctx_json_parse_match_key_fields_for_field(cJSON *match_key_fields_cjson,
                                              char *field_to_find,
                                              int *bit_width_ret,
                                              int *match_type_ret);
void ctx_json_hex_to_stream(char *hex, uint8_t *ret, uint8_t len);

#endif  // __CTX_JSON_UTILS__
