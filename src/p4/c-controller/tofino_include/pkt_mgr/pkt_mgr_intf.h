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
 * @file pkt_mgr_intf.h
 * @date
 *
 */
#ifndef _PKT_MGR_INTF_H
#define _PKT_MGR_INTF_H

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

#include "bfsys/bf_sal/bf_sys_dma.h"
#include "dvm/bf_dma_types.h"
#include "dvm/bf_drv_intf.h"
#include <pkt_mgr/bf_pkt.h>

#define PKT_MGR_NUM_DEVICES BF_MAX_DEV_COUNT

/**
 * @addtogroup pkt_mgr-txrx
 * @{
 */

/*!
 * Enum to define PKT TX ring
 */
typedef enum bf_pkt_tx_ring_e {
  BF_PKT_TX_RING_0,
  BF_PKT_TX_RING_1,
  BF_PKT_TX_RING_2,
  BF_PKT_TX_RING_3,
  BF_PKT_TX_RING_MAX
} bf_pkt_tx_ring_t;

/*!
 * Enum to define PKT RX ring
 */
typedef enum bf_pkt_rx_ring_e {
  BF_PKT_RX_RING_0,
  BF_PKT_RX_RING_1,
  BF_PKT_RX_RING_2,
  BF_PKT_RX_RING_3,
  BF_PKT_RX_RING_4,
  BF_PKT_RX_RING_5,
  BF_PKT_RX_RING_6,
  BF_PKT_RX_RING_7,
  BF_PKT_RX_RING_MAX
} bf_pkt_rx_ring_t;

/**
 * Packet Transmit Done notification callback
 */
typedef bf_status_t (*bf_pkt_tx_done_notif_cb)(bf_dev_id_t dev_id,
                                               bf_pkt_tx_ring_t tx_ring,
                                               uint64_t tx_cookie,
                                               uint32_t status);

/**
 * packet rx callback for processing
 */
typedef bf_status_t (*bf_pkt_rx_callback)(bf_dev_id_t dev_id,
                                          bf_pkt *pkt,
                                          void *cookie,
                                          bf_pkt_rx_ring_t rx_ring);
/**
 *  query if pkt_mgr is initialized
 *
 *  @param  dev_id
 *    chip id
 *  @return
 *    true: if initialized, false: otherwise
 */
bool bf_pkt_is_inited(bf_dev_id_t dev_id);

/**
 *  register for rx packet processing
 *
 *  @param  dev_id
 *    chip id
 *  @param cb
 *    call back handler
 *  @param rx_ring
 *    rx ring index
 *  @param rx_cookie
 *    cookie to pass back to callback function
 *  @return
 *    bf_status
 */
bf_status_t bf_pkt_rx_register(bf_dev_id_t dev_id,
                               bf_pkt_rx_callback cb,
                               bf_pkt_rx_ring_t rx_ring,
                               void *rx_cookie);

/**
 *  deregister from rx pkt processing
 *
 *  @param  dev_id
 *    chip id
 *  @param rx_ring
 *    rx ring index
 *  @return
 *    bf_status
 */
bf_status_t bf_pkt_rx_deregister(bf_dev_id_t dev_id, bf_pkt_rx_ring_t rx_ring);

/**
 *  transmit a packet
 *
 *  @param  dev_id
 *    chip id
 *  @param  pkt
 *    pkt to transmit
 *  @param tx_ring
 *    tx ring index
 *  @param tx_cookie
 *    cookie to pass back to tx done notification
 *  @return
 *    bf_status
 */
bf_status_t bf_pkt_tx(bf_dev_id_t dev_id,
                      bf_pkt *pkt,
                      bf_pkt_tx_ring_t tx_ring,
                      void *tx_cookie);

/**
 *  register for tx done notification
 *
 *  @param  dev_id
 *    chip id
 *  @param cb
 *    call back handler
 *  @param tx_ring
 *    tx ring index
 *  @return
 *    bf_status
 */
bf_status_t bf_pkt_tx_done_notif_register(bf_dev_id_t dev_id,
                                          bf_pkt_tx_done_notif_cb cb,
                                          bf_pkt_tx_ring_t tx_ring);

/**
 *  deregister from tx done notification
 *
 *  @param  dev_id
 *    chip id
 *  @param tx_ring
 *    tx ring index
 *  @return
 *    bf_status
 */
bf_status_t bf_pkt_tx_done_notif_deregister(bf_dev_id_t dev_id,
                                            bf_pkt_tx_ring_t tx_ring);

/**
 * packet manager lock message handler
 *
 * @param dev_id
 *  chip id
 * @return
 *  bf_status
 */
bf_status_t pkt_mgr_lock_device(bf_dev_id_t dev_id);

/**
 * packet manager unlock message handler
 *
 * @param dev_id
 *  chip id
 * @return
 *  bf_status
 */
bf_status_t pkt_mgr_unlock_device(bf_dev_id_t dev_id);

/**
 * is packet manager in device lock state
 *
 * @param dev_id
 *  chip id
 * @return
 *  true if device is locked, false if device is unlocked
 */
bool bf_pkt_is_locked(bf_dev_id_t dev_id);

/* @} */

/**
 * @addtogroup pkt_mgr-pkt_mgr
 * @{
 */

/*!
 * Structure for the TBUS configuration
 */
typedef struct bf_tbus_cfg_s {
  uint8_t pfc_fm_thr;         // num of free mem messages to turn on PFC
  uint8_t pfc_rx_thr;         // num of rx messages to turn on PFC
  uint8_t ecc_dis;            // disable ECC decoder/checker
  uint8_t crcrmv_dis;         // control bit to keep/remove crc32
  uint8_t port_en;            // enable MAC port for PCIE
  uint8_t port_alive;         // port aliveness
  uint16_t ts_offset;         // timestamp offset
  uint8_t rx_channel_offset;  // 4bits, RX channel byte offset
  uint8_t crcerr_keep;        // enable keeping the CRC of input error pkt
} bf_tbus_cfg_t;

/**
 * configure tbus control register
 *
 * @param chip
 *  chip id
 * @param tsu_cfg
 *  configuration param structure
 * @return
 *  0 on Success, -1 on error
 */
int bf_tbus_config(uint8_t chip, bf_tbus_cfg_t *txxibussu_cfg);

/**
 * flush tbus DMA
 *
 * @param chip
 *  chip id
 * @return
 *  0 on Success, -1 on error
 */
int bf_tbus_flush_dma(uint8_t chip);

/**
 * set tbus timestamp offset
 *
 * @param chip
 *  chip id
 * @param offset
 *  offset
 * @return
 *  0 on Success, -1 on error
 */
int bf_tbus_set_ts_offset(uint8_t chip, uint16_t offset);

/**
 * set tbus interrupt enable register
 *
 * @param chip
 *  chip id
 * @param int_id
 *  int register enumeration ID, 0, 1 or 2
 * @param high_prio
 *  int priorirt register to access, 1 for high priority, 0 for low priority
 * @param val
 *   pointer to value to be read or written
 * @param get
 *  get ot set, 1 = get, 0= set
 * @return
 *  0 on Success, -1 on error
 */
int bf_tbus_int(
    uint8_t chip, int int_id, int high_prio, uint32_t *val, int get);

/**
 * services tx completion and receive pkt DRs
 *
 * @param chip
 *  chip id
 * @return
 *  none
 */
bf_status_t bf_dma_service_pkt(uint8_t chip);

/**
 * enable or disable packet tx and rx DR interrupts at leaf level
 *
 * @param chip
 *  chip id
 * @param en
 *  true to enable, false to disable interrupt
 * @return
 *  none
 */
bf_status_t pkt_mgr_dr_int_en(uint8_t chip, bool en);

/**
 * Initialize the driver.  This should be called exactly once before any other
 * APIs are called.
 */
bf_status_t bf_pkt_init();

/* @} */

#ifdef __cplusplus
}
#endif /* C++ */

#endif
