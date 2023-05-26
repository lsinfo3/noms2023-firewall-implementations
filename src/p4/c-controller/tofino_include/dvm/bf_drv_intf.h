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

#ifndef BF_DRV_INTF_H_INCLUDED
#define BF_DRV_INTF_H_INCLUDED

#ifndef PORT_MGR_HA_UNIT_TESTING
#define PORT_MGR_HA_UNIT_TESTING
#endif

#include <bf_types/bf_types.h>
#include <dvm/bf_drv_profile.h>
#include <dvm/bf_dma_types.h>
#include <port_mgr/port_mgr_port_evt.h>
#include <bfsys/bf_sal/bf_sys_intf.h>
#ifndef __KERNEL__
#include <bfutils/uCli/ucli.h>
#include <bfutils/cJSON.h>
#endif

/**
 * @addtogroup dvm-device-mgmt
 * @{
 */

typedef enum bf_client_prio_e {
  BF_CLIENT_PRIO_0 = 0,  // lowest
  BF_CLIENT_PRIO_1,
  BF_CLIENT_PRIO_2,
  BF_CLIENT_PRIO_3,
  BF_CLIENT_PRIO_4,
  BF_CLIENT_PRIO_5,  // highest for lowest on stack
} bf_drv_client_prio_t;

typedef struct bf_dma_dr_info_s {
  bf_sys_dma_pool_handle_t dma_dr_pool_handle;
  unsigned int dma_buf_size;
  unsigned int dma_dr_entry_count[BF_DMA_DR_DIRS];
} bf_dma_dr_info_t;

typedef struct bf_dma_bufpool_info_s {
  bf_sys_dma_pool_handle_t dma_buf_pool_handle;
  unsigned int dma_buf_size;
  unsigned int dma_buf_cnt;
} bf_dma_buf_info_t;

typedef struct bf_dma_info_s {
  bf_sys_dma_pool_handle_t dma_dr_pool_handle;
  uint64_t dma_dr_mem_phy_addr;
  void *dma_dr_mem_virt_addr;
  unsigned int dma_dr_mem_size;
  bf_dma_dr_info_t dma_dr_info[BF_DMA_TYPE_MAX];
  bf_dma_buf_info_t dma_buff_info[BF_DMA_TYPE_MAX];
} bf_dma_info_t;

typedef enum bf_dev_init_mode_s {
  BF_DEV_INIT_COLD,
  // Device incurs complete reset
  BF_DEV_WARM_INIT_FAST_RECFG,
  // Device incurs a fast-reconfig reset with minimal traffic disruption
  BF_DEV_WARM_INIT_HITLESS,
  // Device incurs a hitless warm init
  BF_DEV_WARM_INIT_FAST_RECFG_QUICK,
  // Device incurs a fast-reconfig reset with minimal traffic disruption
  // bf-drivers pushes all the cached config back to the asic, there is no
  // config replay
} bf_dev_init_mode_t;

typedef enum bf_dev_serdes_upgrade_mode_s {
  BF_DEV_SERDES_UPD_NONE,
  // No serdes update needed
  BF_DEV_SERDES_UPD_FORCED_PORT_RECFG,
  // Update serdes by flapping ports immediately
  BF_DEV_SERDES_UPD_DEFERRED_PORT_RECFG
  // Defer the serdes update until a port flap occurs
} bf_dev_serdes_upgrade_mode_t;

typedef struct bf_port_attributes_ {
  bool autoneg_enable;
  bf_port_speeds_t port_speeds;
  bf_fec_types_t port_fec_types;
  bf_pause_cfg_t tx_pause;
  bf_pause_cfg_t rx_pause;
  uint32_t n_lanes;  // reqd to distinguish e.g. 100GBASE-R4 from 100GBASE-R2
} bf_port_attributes_t;

/*
 * HA corrective action type so that the port delta can be successfully applied
 * during the delta push phase
 */
typedef enum bf_ha_corrective_action {
  BF_HA_CA_PORT_NONE = 0,
  BF_HA_CA_PORT_ADD,
  BF_HA_CA_PORT_ENABLE,
  BF_HA_CA_PORT_ADD_THEN_ENABLE,
  BF_HA_CA_PORT_FLAP,
  BF_HA_CA_PORT_DISABLE,
  BF_HA_CA_PORT_DELETE_THEN_ADD,
  BF_HA_CA_PORT_DELETE_THEN_ADD_THEN_ENABLE,
  BF_HA_CA_PORT_DELETE,
  BF_HA_CA_PORT_FSM_LINK_MONITORING,
  BF_HA_CA_PORT_MAX
} bf_ha_corrective_action_t;

/*
 * This is per port structure which holds the port number and the corrective
 * action
 * required for the delta to be applied during delta push phase of HA
 */
typedef struct bf_ha_port_reconcile_info {
  bf_dev_id_t dev_id;
  bf_dev_port_t dev_port;
  bf_ha_corrective_action_t ca;
  bf_port_attributes_t port_attrib;
} bf_ha_port_reconcile_info_t;

typedef struct bf_ha_port_reconcile_info_per_device {
  bf_ha_port_reconcile_info_t recon_info_per_port[BF_PORT_COUNT];
} bf_ha_port_reconcile_info_per_device_t;

/**
 * Get the dma buff pool handle associated with a DR
 *
 * @param dma_info
 *   dma info
 * @param dma_type
 *   dma DR type
 * @return
 *   dma_buf_pool_handle
 */
static inline void *bf_dma_get_buf_pool_hndl(bf_dma_info_t *dma_info,
                                             bf_dma_type_t dma_type) {
  if (!dma_info || dma_type >= BF_DMA_TYPE_MAX) {
    return NULL;
  }
  return (dma_info->dma_buff_info[dma_type].dma_buf_pool_handle);
}

/**
 * Get the dma buffer size associated with a DR
 *
 * @param dma_info
 *   dma info
 * @param dma_type
 *   dma DR type
 * @return
 *   dma_buf_size
 */
static inline unsigned int bf_dma_get_buf_size(bf_dma_info_t *dma_info,
                                               bf_dma_type_t dma_type) {
  if (!dma_info || dma_type >= BF_DMA_TYPE_MAX) {
    return 0;
  }
  return (dma_info->dma_buff_info[dma_type].dma_buf_size);
}

/**
 * Get the dma buffer count associated with a DR
 *
 * @param dma_info
 *   dma info
 * @param dma_type
 *   dma DR type
 * @return
 *   dma_buf_cnt
 */
static inline unsigned int bf_dma_get_buf_cnt(bf_dma_info_t *dma_info,
                                              bf_dma_type_t dma_type) {
  if (!dma_info || dma_type >= BF_DMA_TYPE_MAX) {
    return 0;
  }
  return (dma_info->dma_buff_info[dma_type].dma_buf_cnt);
}

/**
 * Initialize device mgr
 * @return Status of the API call.
 */
bf_status_t bf_drv_init(void);

/**
 * Add a new device to the pktmgr on the device. After this call, the device is
 * ready for
 * packet rx/tx api processing.
 * @param dev_id The ASIC id.
 * @param dma_info Information regarding DMA DRs and associated buffer pools for
 * the CPU Pkt receive/transmit DRs
 * @param flags Device related flags passed by application to drivers
 * @return Status of the API call.
 */
bf_status_t bf_pktmgr_device_add(bf_dev_family_t dev_family,
                                 bf_dev_id_t dev_id,
                                 bf_dma_info_t *dma_info,
                                 bf_dev_flags_t flags);

/**
 * Add a new device.
 * @param dev_family The type of device, e.g. BF_DEV_FAMILY_TOFINO
 * @param dev_id The ASIC id.
 * @param profile Profile-details, program name, cfg file path.
 * @param dma_info Information regarding DMA DRs and associated buffer pools
 * @param flags Device related flags passed by application to drivers
 * @return Status of the API call.
 */
bf_status_t bf_device_add(bf_dev_family_t dev_family,
                          bf_dev_id_t dev_id,
                          bf_device_profile_t *profile,
                          bf_dma_info_t *dma_info,
                          bf_dev_flags_t flags);

/**
 * Add a new virtual device.
 * @param dev_id The ASIC id.
 * @param profile Profile-details, program name, cfg file path.
 * @param dev_type Type of device.
 * @return Status of the API call.
 */
bf_status_t bf_virtual_device_add(bf_dev_id_t dev_id,
                                  bf_device_profile_t *profile,
                                  bf_dev_type_t dev_type);

/**
 * Deletes an existing device.
 * @param dev_id The ASIC id.
 * @return Status of the API call.
 */
bf_status_t bf_device_remove(bf_dev_id_t dev_id);

/**
 * Logs an existing device.
 * @param dev_id The ASIC id.
 * @param filepath The logfile path/name.
 * @return Status of the API call.
 */
bf_status_t bf_device_log(bf_dev_id_t dev_id, const char *filepath);

/**
 * Restores an existing device.
 * @param dev_id The ASIC id.
 * @param filepath The logfile path/name.
 * @return Status of the API call.
 */
bf_status_t bf_device_restore(bf_dev_id_t dev_id, const char *filepath);

/**
 * Enables/Disables Error interrupt handling on asic
 * @param dev_id The ASIC id.
 * @param enable Enable/Disable
 * @return Status of the API call.
 */
bf_status_t bf_err_interrupt_handling_mode_set(bf_dev_id_t dev_id, bool enable);

/* @} */

/**
 * @addtogroup dvm-port-mgmt
 * @{
 */

typedef bf_status_t (*bf_drv_port_status_cb)(bf_dev_id_t dev_id,
                                             bf_dev_port_t port,
                                             bool up,
                                             void *userdata);
typedef bf_status_t (*bf_drv_port_speed_cb)(bf_dev_id_t dev_id,
                                            bf_dev_port_t port,
                                            bf_port_speed_t speed,
                                            void *userdata);

/**
 * Adds a port to a device.
 * @param dev_id The ASIC id.
 * @param dev_port The ASIC port id.
 * @param port_speed The supported speed of the port as defined in
 * bf_port_speed_t.
 * @param port_fec_type Port FEC type as defined in bf_fec_type_t.
 * @return Status of the API call.
 */
bf_status_t bf_port_add(bf_dev_id_t dev_id,
                        bf_dev_port_t port,
                        bf_port_speeds_t port_speed,
                        bf_fec_types_t port_fec_type);

/**
 * Adds a port to a device. Specify lane numbers.
 * @param dev_id The ASIC id.
 * @param dev_port The ASIC port id.
 * @param port_speed The supported speed of the port as defined in
 * bf_port_speed_t.
 * @param lane_numb The lane number the port is using
 * @param port_fec_type Port FEC type as defined in bf_fec_type_t.
 * @return Status of the API call.
 */
bf_status_t bf_port_add_with_lane_numb(bf_dev_id_t dev_id,
                                       bf_dev_port_t port,
                                       bf_port_speeds_t port_speed,
                                       uint32_t lane_numb,
                                       bf_fec_types_t port_fec_type);

/**
 * Get the number of lanes is going to use for a port_speed by default.
 * @param dev_id The ASIC id.
 * @param port_speed The supported speed of the port as defined in
 * bf_port_speed_t.
 * @param lane_numb The lane number the port is using by default.
 * @return Status of the API call.
 */
bf_status_t bf_port_get_default_lane_numb(bf_dev_id_t dev_id,
                                          bf_port_speeds_t port_speed,
                                          uint32_t *lane_numb);
/**
 * Remove a port from a device.
 * @param dev_id The ASIC id.
 * @param dev_port The ASIC port id.
 * @return Status of the API call.
 */
bf_status_t bf_port_remove(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

/**
 * Enable/Disable a port on a device.
 * @param dev_id The ASIC id.
 * @param dev_port The ASIC port id.
 * @param enable enable/disable flag.
 * @return Status of the API call.
 */
bf_status_t bf_port_enable(bf_dev_id_t dev_id, bf_dev_port_t port, bool enable);

/**
 * Mark a port for serdes upgrade on a device
 * @param dev_id The ASIC id.
 * @param dev_port The ASIC port id
 * @return Status of the API call.
 */
bf_status_t bf_port_serdes_upgrade_notify(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port);

/**
 * Get Pcie CPU port number on the device. Based on skew and asci-type
 * the API will return appropriate port number to be used as CPU pcie port.
 * @param dev_id The ASIC id.
 * @return valid pcie port. In case of error returns -1.
 */
int bf_pcie_cpu_port_get(bf_dev_id_t dev_id);

/**
 * Get ethernet CPU port number on the device. Based on skew and asci-type
 * the API will return appropriate port number to be used as CPU ethernet port.
 * @param dev_id The ASIC id.
 * @return valid eth port. In case of error returns -1.
 */
int bf_eth_cpu_port_get(bf_dev_id_t dev_id);

/**
 * Register port status (link up/down) callback.
 * @param port_status Port status callback.
 * @param cookie Data to be given back in callback fn.
 * @return Status of the API call.
 */
bf_status_t bf_port_client_register_status_notif(
    bf_drv_port_status_cb port_status, void *cookie);

/**
 * Register port speed callback.
 * @param port_speed Port speed callback.
 * @param cookie Data to be given back in callback fn.
 * @return Status of the API call.
 */
bf_status_t bf_port_client_register_speed_notif(bf_drv_port_speed_cb port_speed,
                                                void *cookie);

/**
 * Configure the C2C (Copy-to-CPU) control.  The default state is disabled.
 * @param dev The ASIC id.
 * @param enable If @c true C2C is enabled, if @c false C2C is disable and
 *               the @a port is ignored.
 * @param port The port representing the CPU port.
 * @return Status of the API call.
 */
bf_status_t bf_set_copy_to_cpu(bf_dev_id_t dev,
                               bool enable,
                               bf_dev_port_t port);

/**
 * Lock device
 * @param dev_id The ASIC id.
 * @return Status of the API call.
 */
bf_status_t bf_drv_reconfig_lock_device(bf_dev_id_t dev_id);

/**
 * Set device mode to be a virtual device slave
 * @param dev_id The ASIC id.
 * @return Status of the API call.
 */
bf_status_t bf_device_set_virtual_dev_slave_mode(bf_dev_id_t dev_id);

typedef enum bf_error_sev_level_e {
  BF_ERR_SEV_CORRECTABLE,
  BF_ERR_SEV_NON_CORRECTABLE,
  BF_ERR_SEV_FATAL,
} bf_error_sev_level_t;

typedef enum bf_error_type_e {
  BF_ERR_TYPE_GENERIC = 0,
  BF_ERR_TYPE_SINGLE_BIT_ECC,
  BF_ERR_TYPE_MULTI_BIT_ECC,
  BF_ERR_TYPE_PARITY,
  BF_ERR_TYPE_OVERFLOW,
  BF_ERR_TYPE_UNDERFLOW,
} bf_error_type_t;

typedef enum bf_error_block_e {
  BF_ERR_BLK_NONE = 0,
  BF_ERR_BLK_MAU,
  BF_ERR_BLK_TCAM,
  BF_ERR_BLK_SRAM,
  BF_ERR_BLK_MAP_RAM,
  BF_ERR_BLK_STATS,
  BF_ERR_BLK_METERS,
  BF_ERR_BLK_SYNTH2PORT,
  BF_ERR_BLK_SELECTOR_ALU,
  BF_ERR_BLK_IMEM,
  BF_ERR_BLK_MIRROR,
  BF_ERR_BLK_TM_PRE,
  BF_ERR_BLK_TM_WAC,
  BF_ERR_BLK_TM_QAC,
  BF_ERR_BLK_TM_CLC,
  BF_ERR_BLK_TM_PEX,
  BF_ERR_BLK_TM_QLC,
  BF_ERR_BLK_TM_PRC,
  BF_ERR_BLK_TM_PSC,
  BF_ERR_BLK_TM_CAA,
  BF_ERR_BLK_TM_SCH,
  BF_ERR_BLK_PRSR,
  BF_ERR_BLK_DEPRSR,
  BF_ERR_BLK_PKTGEN,
  BF_ERR_BLK_GFM,
  BF_ERR_BLK_DMA,
} bf_error_block_t;

typedef enum bf_error_block_location_e {
  BF_ERR_LOC_NONE = 0,
  BF_ERR_LOC_MAU_IDLETIME,
  BF_ERR_LOC_MAU_STATEFUL_LOG,
  BF_ERR_LOC_SELECTOR_ALU_ST_MINMAX,
  BF_ERR_LOC_SELECTOR_ALU_DEV_BY0,
  BF_ERR_LOC_SELECTOR_ALU_SALU_PRED,
  BF_ERR_LOC_MIRR_POINTER_FIFO,
  BF_ERR_LOC_MIRR_IG,
  BF_ERR_LOC_MIRR_EG,
  BF_ERR_LOC_MIRR_OUT_DESC,
  BF_ERR_LOC_MIRR_DATA_BUFFER,
  BF_ERR_LOC_MIRR_DROP_NEG,
  BF_ERR_LOC_MIRR_DROP_COAL,
  BF_ERR_LOC_MIRR_IG_DIS_SESS,
  BF_ERR_LOC_MIRR_EG_DIS_SESS,
  BF_ERR_LOC_MIRR_OUT,
  BF_ERR_LOC_MIRR_CRC12,
  BF_ERR_LOC_MIRR_SESSION,
  BF_ERR_LOC_MIRR_S2P_CREDIT,
  BF_ERR_LOC_MIRR_IDPRSR_SOPEOP_MISMATCH,
  BF_ERR_LOC_MIRR_EDPRSR_SOPEOP_MISMATCH,
  BF_ERR_LOC_MIRR_DATA_MEM,
  BF_ERR_LOC_TM_PRE_FIFO,
  BF_ERR_LOC_TM_PRE_MIT,
  BF_ERR_LOC_TM_PRE_LIT0_BM,
  BF_ERR_LOC_TM_PRE_LIT1_BM,
  BF_ERR_LOC_TM_PRE_LIT0_NP,
  BF_ERR_LOC_TM_PRE_LIT1_NP,
  BF_ERR_LOC_TM_PRE_PMT0,
  BF_ERR_LOC_TM_PRE_PMT1,
  BF_ERR_LOC_TM_PRE_RDM,
  BF_ERR_LOC_TM_PRE_BANKID_MEM,
  BF_ERR_LOC_TM_WAC_PPG_MAP,
  BF_ERR_LOC_TM_WAC_DROP_CNT,
  BF_ERR_LOC_TM_WAC_PFC_VIS,
  BF_ERR_LOC_TM_WAC_SCH_FCR,
  BF_ERR_LOC_TM_WAC_QID_MAP,
  BF_ERR_LOC_TM_WAC_WAC2QAC,
  BF_ERR_LOC_TM_QAC_QUE_DROP,
  BF_ERR_LOC_TM_QAC_PORT_DROP,
  BF_ERR_LOC_TM_QAC_QID_MAP,
  BF_ERR_LOC_TM_QAC_QAC2PRC,
  BF_ERR_LOC_TM_QAC_PRC2PSC,
  BF_ERR_LOC_TM_CLC_ENQ_FIFO,
  BF_ERR_LOC_TM_CLC_QAC_FIFO,
  BF_ERR_LOC_TM_CLC_PH_FIFO,
  BF_ERR_LOC_TM_CLC_QAC_PH_FIFO,
  BF_ERR_LOC_TM_PEX_CLM,
  BF_ERR_LOC_TM_PEX_PH_FIFO,
  BF_ERR_LOC_TM_PEX_META_FIFO,
  BF_ERR_LOC_TM_PEX_PH_AFIFO,
  BF_ERR_LOC_TM_PEX_DISCARD_FIFO,
  BF_ERR_LOC_TM_QLC_QLM,
  BF_ERR_LOC_TM_QLC_SCHDEQ,
  BF_ERR_LOC_TM_QLC_PH_FIFO,
  BF_ERR_LOC_TM_PRC_T3,
  BF_ERR_LOC_TM_PSC_PSM,
  BF_ERR_LOC_TM_PSC_COMM,
  BF_ERR_LOC_TM_CAA,
  BF_ERR_LOC_TM_SCH_TDM,
  BF_ERR_LOC_TM_SCH_UPD_WAC,
  BF_ERR_LOC_TM_SCH_UPD_EDPRSR_ADVFC,
  BF_ERR_LOC_TM_SCH_Q_MINRATE,
  BF_ERR_LOC_TM_SCH_Q_EXCRATE,
  BF_ERR_LOC_TM_SCH_Q_MAXRATE,
  BF_ERR_LOC_TM_SCH_L1_MINRATE,
  BF_ERR_LOC_TM_SCH_L1_EXCRATE,
  BF_ERR_LOC_TM_SCH_L1_MAXRATE,
  BF_ERR_LOC_TM_SCH_P_MAXRATE,
  BF_ERR_LOC_TM_SCH_UPD_PEX,
  BF_ERR_LOC_TM_SCH_UPD_EDPRSR,
  BF_ERR_LOC_TM_SCH_PEX_CREDIT,
  BF_ERR_LOC_TM_SCH_PEX_MAC_CREDIT,
  BF_ERR_LOC_TM_SCH_Q_WATCHDOG,
  BF_ERR_LOC_PRSR_ACT_RAM,
  BF_ERR_LOC_PRSR_INP_BUFF,
  BF_ERR_LOC_PRSR_OUT_FIFO,
  BF_ERR_LOC_PRSR_TCAM_PARITY,
  BF_ERR_LOC_PRSR_CSUM,
  BF_ERR_LOC_DEPRSR_PIPE_VEC_TBL0,
  BF_ERR_LOC_DEPRSR_PIPE_VEC_TBL1,
  BF_ERR_LOC_DEPRSR_MIRRTBL,
  BF_ERR_LOC_DEPRSR_IPKT_MAC,
  BF_ERR_LOC_DEPRSR_CMD_FIFO,
  BF_ERR_LOC_DEPRSR_CRED_ERR,
  BF_ERR_LOC_DEPRSR_PKTST,
  BF_ERR_LOC_DEPRSR_META_FIFO,
  BF_ERR_LOC_DEPRSR_PKTHDR,
  BF_ERR_LOC_DEPRSR_MIRRHDR,
  BF_ERR_LOC_DEPRSR_DATAST,
  BF_ERR_LOC_DEPRSR_PKTDATA,
  BF_ERR_LOC_DEPRSR_TMSCH,
  BF_ERR_LOC_DEPRSR_ARB_FIFO,
  BF_ERR_LOC_DEPRSR_CTL_CHAN,
  BF_ERR_LOC_PKTGEN_BUFFER,
  BF_ERR_LOC_PKTGEN_PFC,
  BF_ERR_LOC_PKTGEN_TBC_FIFO,
  BF_ERR_LOC_PKTGEN_ETH_CPU_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P0_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P1_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P2_FIFO,
  BF_ERR_LOC_PKTGEN_EBUF_P3_FIFO,
  BF_ERR_LOC_PKTGEN_APP_EVT,
  BF_ERR_LOC_PKTGEN_IPB_CHNL_SEQ,
  BF_ERR_LOC_PKTGEN_ETH_CPU_TBC_SAMECHNL,
  BF_ERR_LOC_PKTGEN_ETH_PORT_FIFO,
  BF_ERR_LOC_PKTGEN_PHASE0,
  BF_ERR_LOC_GFM_INGRESS,
  BF_ERR_LOC_GFM_EGRESS,
  BF_ERR_LOC_DMA_PBC,
  BF_ERR_LOC_DMA_CBC,
  BF_ERR_LOC_DMA_MBC,
} bf_error_block_location_t;

typedef bf_status_t (*bf_error_event_cb)(bf_error_sev_level_t severity,
                                         bf_dev_id_t dev_id,
                                         bf_dev_pipe_t pipe,
                                         uint8_t stage,
                                         uint64_t address,
                                         bf_error_type_t type,
                                         bf_error_block_t blk,
                                         bf_error_block_location_t loc,
                                         bf_dev_port_t *port_list,
                                         int num_ports,
                                         char *string,
                                         void *cookie);

/**
 * The function is used to register for error notifications
 *
 * @param  dev                  ASIC device identifier
 & @param  event_cb             Event callback API
 * @param  cookie               User data passed into the callback
 * @return                      Status of the API call
 */
bf_status_t bf_register_error_events(bf_dev_id_t dev,
                                     bf_error_event_cb event_cb,
                                     void *cookie);

/* @} */

/* Non-doxy */
typedef enum bf_port_cb_direction_ {
  BF_PORT_CB_DIRECTION_INGRESS = 0,
  BF_PORT_CB_DIRECTION_EGRESS
} bf_port_cb_direction_t;

typedef bf_status_t (*bf_drv_pkt_mgr_device_add_cb)(
    bf_dev_id_t dev_id,
    bf_dev_family_t dev_family,
    bf_dma_info_t *dma_info,
    bf_dev_init_mode_t warm_init_mode);

typedef bf_status_t (*bf_drv_device_add_cb)(bf_dev_id_t dev_id,
                                            bf_dev_family_t dev_family,
                                            bf_device_profile_t *profile,
                                            bf_dma_info_t *dma_info,
                                            bf_dev_init_mode_t warm_init_mode);

typedef bf_status_t (*bf_drv_virtual_device_add_cb)(
    bf_dev_id_t dev_id,
    bf_dev_type_t dev_type,
    bf_device_profile_t *profile,
    bf_dev_init_mode_t warm_init_mode);

/**
 * The function is used to notify memory error events
 *
 * @param  sev                   Severity of event
 * @param  dev                   ASIC device identifier
 * @param  pipe                  Pipeline identifier
 * @param  all_ports_in_pipe     All ports in pipe
 * @param  port_list             Port list
 * @param  num_ports             Number of ports
 * @return                       Status of the API call
 */
bf_status_t bf_notify_error_events(bf_error_sev_level_t sev,
                                   bf_dev_id_t dev,
                                   bf_dev_pipe_t pipe,
                                   uint8_t stage,
                                   uint64_t address,
                                   bf_error_type_t type,
                                   bf_error_block_t blk,
                                   bf_error_block_location_t loc,
                                   bool all_ports_in_pipe,
                                   bf_dev_port_t *port_list,
                                   int num_ports,
                                   const char *format,
                                   ...);

bf_status_t bf_fill_pipe_ports(bf_dev_id_t dev,
                               bf_dev_pipe_t pipe,
                               bf_dev_port_t *port_list,
                               int *num_ports);
typedef bf_status_t (*bf_drv_device_del_cb)(bf_dev_id_t dev_id);
#ifndef __KERNEL__
typedef bf_status_t (*bf_drv_device_log_cb)(bf_dev_id_t dev_id, cJSON *node);
typedef bf_status_t (*bf_drv_device_restore_cb)(bf_dev_id_t dev_id,
                                                cJSON *node);
#else
typedef bf_status_t (*bf_drv_device_log_cb)(bf_dev_id_t dev_id, void *node);
typedef bf_status_t (*bf_drv_device_restore_cb)(bf_dev_id_t dev_id, void *node);
#endif
typedef bf_status_t (*bf_drv_port_add_cb)(bf_dev_id_t dev_id,
                                          bf_dev_port_t port,
                                          bf_port_attributes_t *port_attrib,
                                          bf_port_cb_direction_t direction);
typedef bf_status_t (*bf_drv_port_del_cb)(bf_dev_id_t dev_id,
                                          bf_dev_port_t port,
                                          bf_port_cb_direction_t direction);
typedef bf_status_t (*bf_drv_port_status_int_cb)(bf_dev_id_t dev_id,
                                                 bf_dev_port_t port,
                                                 bool up);
typedef bf_status_t (*bf_drv_port_speed_int_cb)(bf_dev_id_t dev_id,
                                                bf_dev_port_t port);
typedef bf_status_t (*bf_drv_port_admin_state_cb)(bf_dev_id_t dev_id,
                                                  bf_dev_port_t port,
                                                  bool enable);
typedef bf_status_t (*bf_drv_err_intr_hdl_mode_cb)(bf_dev_id_t dev_id,
                                                   bool enable);

typedef bf_status_t (*bf_drv_rcfg_step_cb)(bf_dev_id_t dev_id);

typedef bf_status_t (*bf_drv_ha_complete_hitless_hw_read_cb)(
    bf_dev_id_t dev_id);
typedef bf_status_t (*bf_drv_ha_compute_delta_changes_cb)(bf_dev_id_t dev_id);
typedef bf_status_t (*bf_drv_ha_push_delta_changes_cb)(bf_dev_id_t dev_id);
typedef bf_status_t (*bf_drv_ha_set_dev_type_virtual_dev_slave_cb)(
    bf_dev_id_t dev_id);
typedef bf_status_t (*bf_drv_ha_register_port_corr_action_cb)(
    bf_dev_id_t dev_id, bf_ha_port_reconcile_info_per_device_t *recon_info);
typedef bf_status_t (*bf_drv_ha_port_delta_push_done_cb)(bf_dev_id_t dev_id);
typedef bf_status_t (*bf_drv_ha_port_serdes_upgrade_cb)(bf_dev_id_t dev_id,
                                                        bf_dev_port_t port,
                                                        uint32_t serdes_fw_ver,
                                                        char *serdes_fw_path);

typedef struct bf_drv_client_callbacks_s {
  bf_drv_pkt_mgr_device_add_cb pkt_mgr_dev_add;
  bf_drv_device_add_cb device_add;
  bf_drv_virtual_device_add_cb virtual_device_add;
  bf_drv_device_del_cb device_del;
  bf_drv_device_log_cb device_log;
  bf_drv_device_restore_cb device_restore;
  bf_drv_port_add_cb port_add;
  bf_drv_port_del_cb port_del;
  bf_drv_port_status_int_cb port_status;
  bf_drv_port_speed_int_cb port_speed;
  bf_drv_port_admin_state_cb port_admin_state;
  bf_drv_err_intr_hdl_mode_cb err_intr_mode;

  /* Fast reconfig callbacks */
  bf_drv_rcfg_step_cb lock;
  bf_drv_rcfg_step_cb create_dma;
  bf_drv_rcfg_step_cb disable_input_pkts;
  bf_drv_rcfg_step_cb wait_for_flush;
  bf_drv_rcfg_step_cb core_reset;
  bf_drv_rcfg_step_cb unlock_reprogram_core;
  bf_drv_rcfg_step_cb config_complete;
  bf_drv_rcfg_step_cb enable_input_pkts;
  bf_drv_rcfg_step_cb error_cleanup;
  bf_drv_rcfg_step_cb warm_init_quick;

  /* Hitless Restart */
  bf_drv_ha_complete_hitless_hw_read_cb complete_hitless_hw_read;
  bf_drv_ha_compute_delta_changes_cb compute_delta_changes;
  bf_drv_ha_push_delta_changes_cb push_delta_changes;
  bf_drv_ha_set_dev_type_virtual_dev_slave_cb device_mode_virtual_dev_slave;

  /* Warm Init Port callbacks */
  bf_drv_ha_register_port_corr_action_cb register_port_corr_action;
  bf_drv_ha_port_delta_push_done_cb port_delta_push_done;
  bf_drv_ha_port_serdes_upgrade_cb port_serdes_upgrade;
} bf_drv_client_callbacks_t;

typedef int bf_drv_client_handle_t;

/**
 * Get sizing requirements for DMA descriptor rings (DRs)
 * @param dma_dr_entry_count DMA DR entry counts desired per DMA function
 * @param total_bytes Total contiguous bytes of DMA'ble memory that needs to be
 * allocated
 * @return Status of the API call.
 */
bf_status_t bf_drv_get_dma_dr_size_in_bytes(
    int dma_dr_entry_count[BF_DMA_TYPE_MAX][BF_DMA_DR_DIRS],
    unsigned int *total_bytes);

/**
 * Register as device-manager-client.
 * @param client_name Client Name.
 * @param client_handle The client handle allocated.
 * @return Status of the API call.
 */
bf_status_t bf_drv_register(const char *client_name,
                            bf_drv_client_handle_t *client_handle);

/**
 * De-Register as device-manager-client.
 * @param client_handle The client handle allocated.
 * @return Status of the API call.
 */
bf_status_t bf_drv_deregister(bf_drv_client_handle_t client_handle);

/**
 * Register all callbacks.
 * @param client_handle The client handle allocated.
 * @return Status of the API call.
 */
bf_status_t bf_drv_client_register_callbacks(
    bf_drv_client_handle_t client_handle,
    bf_drv_client_callbacks_t *callbacks,
    bf_drv_client_prio_t add_priority);

/**
 * Register warm init flags
 * @param client_handle The client handle allocated.
 * @param override_fast_recfg Flag to inficate if the fast recfg sequence is to
 *        overriden by the hitless ha sequence
 * @param issue_fast_recfg_port_cb Flag to indicate if the client supports port
 * 	  add/del/enb/dis callbacks during fast reconfig
 * @return Status of the API call
 */
bf_status_t bf_drv_client_register_warm_init_flags(
    bf_drv_client_handle_t client_handle,
    bool override_fast_recfg,
    bool issue_fast_recfg_port_cb);

const char *bf_drv_get_version(void);
const char *bf_drv_get_internal_version(void);

/* Driver shell related API */
/* Initialize the debug shell */
bf_status_t bf_drv_shell_init(void);
/* Start the debug shell */
bf_status_t bf_drv_shell_start(void);
/* Stop the debug shell */
bf_status_t bf_drv_shell_stop(void);
#ifndef __KERNEL__
/* Register ucli node with bf-sde shell */
bf_status_t bf_drv_shell_register_ucli(ucli_node_t *ucli_node);
/* Unregister ucli node from bf-sde shell */
bf_status_t bf_drv_shell_unregister_ucli(ucli_node_t *ucli_node);
void bf_drv_ucli_run(FILE *fin, FILE *fout);
#endif

/**
 * Perform a compatibility check prior to planned warm-restarts
 * @param dev_id The device id
 * @param new_profile The new profile to perform compatibility check against
 * @param new_drv_path The path of the new bf-drivers
 * @param serdes_upgrade_p Function returns the best warm initialization mode
 * @param serdes_upgrade_p Function returns whether SerDes upgrade is needed
 * @return Status of the API call
 */

bf_status_t bf_device_compat_check(bf_dev_id_t dev_id,
                                   bf_device_profile_t *new_profile,
                                   char *new_drv_path,
                                   bf_dev_init_mode_t *warm_init_mode_p,
                                   bool *serdes_upgrade_p);

/**
 * Initiate a warm init process for a device
 * @param dev_id The device id
 * @param warm_init_mode The warm init mode to use for this device
 * @param serdes_upgrade_mode The mode to use for updating SerDes
 * @return Status of the API call.
 */
bf_status_t bf_device_warm_init_begin(
    bf_dev_id_t dev_id,
    bf_dev_init_mode_t warm_init_mode,
    bf_dev_serdes_upgrade_mode_t serdes_upgrade_mode);

/**
 * End the warm init sequence for the device and resume normal operation
 * @param dev_id The device id
 * @return Status of the API call.
 */
bf_status_t bf_device_warm_init_end(bf_dev_id_t dev_id);

/**
 * Return if a port needs to be brought up using the FSM at the end of warm init
 * end
 * @param dev_id The device id
 * @param dev_port Device port number
 * @param bring_up Flag to indicate if this port needs to be brought up
 * @return Status of the API call
 */
bf_status_t bf_device_warm_init_port_bring_up(bf_dev_id_t dev_id,
                                              bf_dev_port_t dev_port,
                                              bool *bring_up);

/**
 * Get the init mode of a device
 * @param dev_id The device id
 * @param warm_init_mode The warm init mode to use for this device
 * @return Status of the API call
 */
bf_status_t bf_device_init_mode_get(bf_dev_id_t dev_id,
                                    bf_dev_init_mode_t *warm_init_mode);
#ifdef PORT_MGR_HA_UNIT_TESTING
/**
 * Get the mac/port corrective action for a port as determined by the port mgr
 *
 * @param dev_id
 *   Device id
 * @param dev_port
 *   device port number
 * @param ca
 *   mac/port corrective action req for that port
 * @return
 *   status of the API call
 */
bf_status_t bf_ha_port_mgr_port_corrective_action_get(
    bf_dev_id_t dev_id, bf_dev_port_t dev_port, bf_ha_corrective_action_t *ca);

/**
 * Get the serdes corrective action for a port as determined by the port mgr
 *
 * @param dev_id
 *   Device id
 * @param dev_port
 *   device port number
 * @param ca
 *   serdes corrective action req for that port
 * @return
 *   status of the API call
 */
bf_status_t bf_ha_port_mgr_serdes_corrective_action_get(
    bf_dev_id_t dev_id, bf_dev_port_t dev_port, bf_ha_corrective_action_t *ca);
#endif
/**
 * Get the device type (model or asic)
 * @param dev_id The device id
 * @param is_sw_model Pointer to bool flag to return true for model and
 *                    false for asic devices
 * @return Status of the API call.
 */
bf_status_t bf_drv_device_type_get(bf_dev_id_t dev_id, bool *is_sw_model);

/**
 * Check if the device type is a virtual device slave
 * @param dev_id The device id
 * @param is_sw_model Pointer to bool flag to return true for virtual dev slave
 * and otherwise
 * @return Status of the API call.
 */
bf_status_t bf_drv_device_type_virtual_dev_slave(bf_dev_id_t dev_id,
                                                 bool *is_virtual_dev_slave);

/**
 * Get the clock speed of the given device
 * @param dev_id          The device id
 * @param clock_speed     The pointer in which to save the device clock speed
 * @return                Status of the API call
 */
bf_status_t bf_drv_get_clock_speed(bf_dev_id_t dev_id,
                                   uint64_t *bps_clock_speed,
                                   uint64_t *pps_clock_speed);

/*
 * This allows you to set the timeout (ms) for the LRT descriptor ring timer
 * This is amount of time hardware waits for before shipping the buffer to sw
 * hence this increases the utilization of these buffers by allowing hardware
 * pack in more messages per buffer
 * @param dev_id 	  The devide id
 * @param timeout_ms 	  The timeout in milliseconds for the timer
 * @return 		  Status of the API call
 */
bf_status_t bf_drv_lrt_dr_timeout_set(bf_dev_id_t dev_id, uint32_t timeout_ms);

/*
 * This allows you to get the timeout (ms) for the LRT descriptor ring timer
 * This is amount of time hardware waits for before shipping the buffer to sw
 * @param dev_id 	  The devide id
 * @param timeout_ms 	  The timeout in milliseconds for the timer
 * @return 		  Status of the API call
 */
bf_status_t bf_drv_lrt_dr_timeout_get(bf_dev_id_t dev_id, uint32_t *timeout_ms);

#endif  // BF_DRV_INTF_H_INCLUDED
