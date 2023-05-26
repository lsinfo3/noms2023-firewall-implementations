/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2019 Barefoot Networks, Inc.
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
#ifndef __BF_SWITCHD_H__
#define __BF_SWITCHD_H__
/*-------------------- bf_switchd.h -----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <bf_types/bf_types.h>
#include <mc_mgr/mc_mgr_types.h>
#include <dvm/bf_drv_intf.h>

#define BF_SWITCHD_MAX_FILE_NAME 512

typedef struct switch_mac_s {
  int configured;  // set from switch config json parsing
} switch_mac_t;

typedef struct switch_serdes_t {
  int configured;  // set from switch config json parsing
  bool polarity_inverted_tx;
  bool polarity_inverted_rx;
  int mapped_to_lane;
  uint32_t tx_eq_pre;
  uint32_t tx_eq_post;
  uint32_t tx_eq_atten;
} switch_serdes_t;

typedef struct switch_mac_block_s {
  int configured;
  int pipeline;
  int parser;
  switch_mac_t mac[4];
  switch_serdes_t serdes[4];
} switch_mac_block_t;

typedef struct switchd_pcie_cfg_s {
  char pci_sysfs_str[128];
  uint16_t domain;
  uint8_t bus;
  uint8_t fn;
  uint8_t dev;
  uint8_t int_mode; /* 0:INTX, 1:MSI, 2:MSIX */
} switchd_pcie_cfg_t;

typedef struct switchd_serdes_cfg_s {
  char sbus_master_fw[BF_SWITCHD_MAX_FILE_NAME];
  char pcie_fw[BF_SWITCHD_MAX_FILE_NAME];
  char serdes_fw[BF_SWITCHD_MAX_FILE_NAME];
  char sds_fw_path[BF_SWITCHD_MAX_FILE_NAME];
} switchd_serdes_cfg_t;

typedef struct switchd_tof2_microp_cfg_s {
  char microp_fw_path[BF_SWITCHD_MAX_FILE_NAME];
  char microp_fw[BF_SWITCHD_MAX_FILE_NAME];
} switchd_tof2_microp_cfg_t;

typedef struct switch_asic_s {
  int pci_dev_id;
  int configured;
  bf_dev_family_t chip_family;
  bool is_virtual;
  bool is_virtual_dev_slave;
  bool is_sw_model;
  switchd_pcie_cfg_t pcie_cfg;
  switchd_serdes_cfg_t serdes_cfg;
  switchd_tof2_microp_cfg_t microp_cfg;
  char bfrt_non_p4_json_dir_path[BF_SWITCHD_MAX_FILE_NAME];
  bf_sys_mutex_t switch_mutex;
  bf_sys_mutex_t pktmgr_mutex;
  bool lrn_poll; /* 0 means interrupts instead of polling */
} switch_asic_t;

#define BF_SWITCHD_MAX_AGENTS 5
#define BF_SWITCHD_MAX_PIPES 4
#define BF_SWITCHD_MAX_P4_PROGRAMS BF_SWITCHD_MAX_PIPES
#define BF_SWITCHD_MAX_P4_PIPELINES BF_SWITCHD_MAX_PIPES
typedef struct p4_pipeline_config_s {
  char *p4_pipeline_name;
  char pd[BF_SWITCHD_MAX_FILE_NAME];
  char pd_thrift[BF_SWITCHD_MAX_FILE_NAME];
  char table_config[BF_SWITCHD_MAX_FILE_NAME];
  char tofino_bin[BF_SWITCHD_MAX_FILE_NAME];
  char pi_native_config_path[BF_SWITCHD_MAX_FILE_NAME];
  int num_pipes_in_scope;
  int pipe_scope[BF_SWITCHD_MAX_PIPES];
} p4_pipeline_config_t;

typedef struct p4_programs_s {
  char *program_name;
  char diag[BF_SWITCHD_MAX_FILE_NAME];
  char mav_diag[BF_SWITCHD_MAX_FILE_NAME];
  char switchapi[BF_SWITCHD_MAX_FILE_NAME];
  char switchsai[BF_SWITCHD_MAX_FILE_NAME];
  char switchlink[BF_SWITCHD_MAX_FILE_NAME];
  bool add_ports_to_switchapi;
  char model_json_path[BF_SWITCHD_MAX_FILE_NAME];
  bool use_eth_cpu_port;
  char eth_cpu_port_name[BF_SWITCHD_MAX_FILE_NAME];
  char bfrt_config[BF_SWITCHD_MAX_FILE_NAME];
  int num_p4_pipelines;
  p4_pipeline_config_t p4_pipelines[BF_SWITCHD_MAX_P4_PIPELINES];
} p4_programs_t;

typedef struct p4_devices_s {
  bool configured;
  uint8_t num_p4_programs;
  p4_programs_t p4_programs[BF_SWITCHD_MAX_P4_PROGRAMS];
  char agent[BF_SWITCHD_MAX_AGENTS][BF_SWITCHD_MAX_FILE_NAME];
} p4_devices_t;

typedef struct switchd_p4_pipeline_state_s {
  void *pd_lib_handle;
  void *pd_thrift_lib_handle;
} switchd_p4_pipeline_state_t;

typedef struct switchd_p4_program_state_s {
  void *switchapi_lib_handle;
  void *switchsai_lib_handle;
  void *switchlink_lib_handle;
  void *diag_lib_handle;
  void *mav_diag_lib_handle;
  switchd_p4_pipeline_state_t p4_pipeline_state[BF_SWITCHD_MAX_P4_PIPELINES];
} switchd_p4_program_state_t;

typedef struct switchd_state_s {
  switchd_p4_program_state_t p4_programs_state[BF_SWITCHD_MAX_P4_PROGRAMS];
  void *agent_lib_handle[BF_SWITCHD_MAX_AGENTS];
  bool device_locked;
  bool device_ready;
  bool device_pktmgr_ready;
  bf_dma_info_t dma_info;
} switchd_state_t;

typedef struct switchd_pcie_map_s {
  uint8_t *dev_base_addr; /* BAR0 base addr */
  size_t dev_base_size;   /* BAR0 mem size */
  int dev_fd;             /* file handle */
} switchd_pcie_map_t;

typedef struct switchd_skip_hld_s {
  bool pipe_mgr;
  bool mc_mgr;
  bool traffic_mgr;
  bool pkt_mgr;
  bool port_mgr;
} switchd_skip_hld_t;

#ifdef STATIC_LINK_LIB
typedef int32_t (*switch_api_init_fn_t)(uint16_t device_id,
                                        uint32_t num_ports,
                                        char *cpu_port,
                                        bool add_ports,
                                        void *rpc_server_cookie);
typedef int32_t (*switch_api_deinit_fn_t)(uint16_t device_id,
                                          void *rpc_server_cookie);

typedef void (*switch_sai_init_fn_t)();

typedef void *(*bf_switchd_agent_init_fn_t)(void *arg);
typedef void *(*bf_switchd_agent_init_done_fn_t)(void *arg);
typedef int (*bf_pltfm_device_type_get_fn_t)(bf_dev_id_t dev_id,
                                             bool *is_sw_model);
#ifdef THRIFT_ENABLED
typedef int (*agent_rpc_server_thrift_service_add_fn_t)(void *processor);
typedef int (*agent_rpc_server_thrift_service_rmv_fn_t)(void *processor);
#endif  // THRIFT_ENABLED

#endif  // STATIC_LINK_LIB

typedef struct bf_switchd_context_s {
  /* Per device context */
  switch_asic_t asic[BF_MAX_DEV_COUNT];
  p4_devices_t p4_devices[BF_MAX_DEV_COUNT];
  switchd_state_t state[BF_MAX_DEV_COUNT];
  switchd_pcie_map_t pcie_map[BF_MAX_DEV_COUNT];
  /* Global context */
  bf_dev_init_mode_t init_mode;
  int no_of_devices;
  char *install_dir;   // install directory for BF-SDE build
  char *conf_file;     // switchd conf_file
  int tcp_port_base;   // TCP port base to be used with dru_sim
  bool skip_p4;        // Skip P4 config load
  bool skip_port_add;  // Skip port-add for all bf-driver-mgrs including lld
  switchd_skip_hld_t skip_hld;  // Skip some high level mgr
  bool is_sw_model;             // Flag to identify operating mode (for model)
  bool is_virtual_dev_slave;    // Flag to identify if a device is a virtual
                                // device slave
  bool is_asic;                 // Flag to identify operating mode (for asic)
  bool kernel_pkt;              // pkt processing in kernel
  bool dev_sts_thread;
  uint16_t dev_sts_port;
  bool running_in_background;  // Do we expect our process to be backgrounded?
  bool shell_set_ucli;         // Load uCLI as default shell instead of BFShell
  bool bfshell_local_only;     // Only allow bfshell connections on loopback.
  bool init_done;
  bf_mc_session_hdl_t mc_session_handle;
  pthread_t dev_sts_t_id;
  pthread_t tmr_t_id;
  pthread_t drusim_t_id;
  pthread_t dma_t_id;
  pthread_t int_t_id;
  pthread_t pkt_t_id;
  pthread_t port_fsm_t_id;
  pthread_t agent_t_id[BF_SWITCHD_MAX_AGENTS];
  pthread_t mav_diag_t_id;
  void *rpc_server_cookie;
  uint32_t (*dru_sim_cpu_to_pcie_rd_fn)(uint32_t asic, uint32_t addr);
  void (*dru_sim_cpu_to_pcie_wr_fn)(uint32_t asic,
                                    uint32_t addr,
                                    uint32_t value);
  uint32_t num_active_devices;
  char *p4rt_server;  // Socket (addr:port) on which to run the P4RT server
  uint32_t non_default_port_ppgs;
  char board_port_map_conf_file[BF_SWITCHD_MAX_FILE_NAME];
  bool sai_default_init;  // Flag to create default ports, initialize port
                          // speed, vlan and buffer configs.

#ifdef STATIC_LINK_LIB
  switch_api_init_fn_t switch_api_init_fn;
  switch_api_deinit_fn_t switch_api_deinit_fn;
  switch_sai_init_fn_t switch_sai_init_fn;
  bf_switchd_agent_init_fn_t bf_switchd_agent_init_fn;
  bf_switchd_agent_init_done_fn_t bf_switchd_agent_init_done_fn;
  bf_pltfm_device_type_get_fn_t bf_pltfm_device_type_get_fn;
#ifdef THRIFT_ENABLED
  agent_rpc_server_thrift_service_add_fn_t
      agent_rpc_server_thrift_service_add_fn;
  agent_rpc_server_thrift_service_rmv_fn_t
      agent_rpc_server_thrift_service_rmv_fn;
#endif  // THRIFT_ENABLED
#endif  // STATIC_LINK_LIB
} bf_switchd_context_t;

typedef void *(*agent_init_fn_t)(void *);
typedef void *(*agent_init_done_fn_t)(void *);

typedef int (*bf_pltfm_reg_dir_i2c_rd)(bf_dev_id_t dev_id,
                                       uint32_t addr,
                                       uint32_t *data);
typedef int (*bf_pltfm_reg_dir_i2c_wr)(bf_dev_id_t dev_id,
                                       uint32_t addr,
                                       uint32_t data);

void bf_switchd_i2c_fn_reg(bf_pltfm_reg_dir_i2c_rd rd_fn,
                           bf_pltfm_reg_dir_i2c_wr wr_fn);

void switchd_register_ucli_node(void);

int bf_switchd_lib_init(bf_switchd_context_t *ctx);

bool bf_switchd_is_kernel_pkt_proc(bf_dev_id_t dev_id);

void bf_switchd_exit_sighandler(int signum);

bf_status_t bf_switchd_enable_interrupt_pipe_learning(bf_dev_id_t dev_id,
                                                      bool enable);

int bf_switchd_device_type_update(bf_dev_id_t dev_id, bool is_sw_model);

bf_status_t bf_switchd_warm_init_end(bf_dev_id_t dev_id);

/******************************************************************************
*******************************************************************************
                          BF_SWITCHD OPERATIONAL MODE SETTINGS
*******************************************************************************
******************************************************************************/
/*
 * Defines to be set based on the target device type for EMULATOR,
 * IPOSER_FPGA and SERDES_EVAL. Define only ONE for any of the above
 * three targets!!!
 * Note that for SW_MODEL and ASIC targets, nothing has to be defined and
 * device type will be identified at runtime without the need
 * for compile time flags.
 */
//#define DEVICE_IS_EMULATOR
//#define DEVICE_IS_SERDES_EVAL
//#define DEVICE_IS_IPOSER_FPGA

#if defined(DEVICE_IS_SERDES_EVAL)
// TODO - What needs to be defined here?

#endif

/* Define for exercising FASTRECFG test */
#define FASTRECFG_TEST

/* Define for enabling register access log */
#define REG_ACCESS_LOG
/******************************************************************************
*******************************************************************************
                          BF_SWITCHD OPERATIONAL MODE SETTINGS
*******************************************************************************
******************************************************************************/
#endif /* __BF_SWITCHD_H__ */
