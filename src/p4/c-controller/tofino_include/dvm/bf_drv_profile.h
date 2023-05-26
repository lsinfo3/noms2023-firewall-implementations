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
#ifndef BF_DRV_PROFILE_H_INCLUDED
#define BF_DRV_PROFILE_H_INCLUDED

#ifdef __KERNEL__
#include <bf_types/bf_kernel_types.h>
#endif
#include <bf_types/bf_types.h>

#define DEF_PROFILE_INDEX 0
#define DEF_PROGRAM_INDEX 0
#define DEF_PROFILE_ID 0
#define PROF_FUNC_NAME_LEN 200
#define PIPE_MGR_CFG_FILE_LEN 250
#define PIPE_MGR_DYN_LIB_STR_LENGTH 250

/**
 * @addtogroup dvm-device-mgmt
 * @{
 */

#define MAX_P4_PIPELINES 4
#define PROG_NAME_LEN 256
#define MAX_PROGRAMS_PER_DEVICE MAX_P4_PIPELINES

typedef struct bf_p4_pipeline {
  char p4_pipeline_name[PROG_NAME_LEN];
  char *cfg_file;
  char *runtime_context_file;        // json context
  char *pi_config_file;              // json PI config
  int num_pipes_in_scope;            // num pipes in scope
  int pipe_scope[MAX_P4_PIPELINES];  // logical pipe list
} bf_p4_pipeline_t;

typedef struct serdes_fw_profile {
  char *sbus_master_fw;
  char *pcie_fw;
  char *serdes_fw;
} serdes_fw_profile_t;

typedef struct microp_fw_profile { char *microp_fw; } microp_fw_profile_t;

typedef struct bf_p4_program {
  char prog_name[PROG_NAME_LEN];
  char *bfrt_json_file;  // bf-rt info json file
  uint8_t num_p4_pipelines;
  bf_p4_pipeline_t p4_pipelines[MAX_P4_PIPELINES];
} bf_p4_program_t;

typedef struct bf_device_profile {
  uint8_t num_p4_programs;
  bf_p4_program_t p4_programs[MAX_PROGRAMS_PER_DEVICE];
  serdes_fw_profile_t sds_prof;
  microp_fw_profile_t microp_prof;
  char *bfrt_non_p4_json_dir_path;  // bfrt fixed feature info json files path
} bf_device_profile_t;

/* @} */

#endif  // BF_DRV_PROFILE_H_INCLUDED
