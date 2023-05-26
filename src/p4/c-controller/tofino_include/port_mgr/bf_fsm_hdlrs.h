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

#ifndef BF_FSM_HDLRS_H_INCLUDED
#define BF_FSM_HDLRS_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

// non-AN port fsm handlers
bf_status_t bf_fsm_init_serdes(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_re_init_serdes_rx(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port);
bf_status_t bf_fsm_wait_pll(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_wait_signal_ok(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_dfe_quick(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_wait_dfe_done(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_wait_pcs_up(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_ena_mac(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_abort(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

// AN port fsm handlers
bf_status_t bf_fsm_an_init_serdes(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_pll1(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_base_pg(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_next_pg(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_an_good(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_pll2(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_an_cmplt(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_pcs_up(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_wait_pcal_done(bf_dev_id_t dev_id,
                                     bf_dev_port_t dev_port);
bf_status_t bf_fsm_an_abort(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

bf_status_t bf_fsm_config_serdes(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_wait_for_port_dwn_event(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port);
bf_status_t bf_fsm_re_config_serdes_rx(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port);

bf_status_t bf_fsm_wait_for_port_dwn_event(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port);
// Non serdes fsm handlers
bf_status_t bf_fsm_enable_mac_tx_rx(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_assert_rs_fec(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_deassert_rs_fec(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_fsm_default_abort(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

// Port fsm handlers based on port-directions
bf_status_t bf_fsm_config_for_tx_mode(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port);
bf_status_t bf_fsm_wait_for_port_up_in_tx_mode(bf_dev_id_t dev_id,
                                               bf_dev_port_t dev_port);
#ifdef __cplusplus
}
#endif /* C++ */

#endif  // BF_FSM_HDLRS_H_INCLUDED
