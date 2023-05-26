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

#ifndef PORT_MGR_UCLI_H_INCLUDED
#define PORT_MGR_UCLI_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

bf_status_t port_diag_prbs_stats_display(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port,
                                         void *display_ucli_cookie);
bf_status_t port_diag_perf_display(bf_dev_id_t dev_id,
                                   bf_dev_port_t dev_port,
                                   int fp,
                                   int ch,
                                   void *display_ucli_cookie);
bf_status_t port_diag_plot_eye(bf_dev_id_t dev_id,
                               bf_dev_port_t dev_port,
                               void *display_ucli_cookie);
bf_status_t port_diag_dfe_set(bf_dev_id_t dev_id,
                              bf_dev_port_t dev_port,
                              uint32_t lane,
                              bool set_all_lane,
                              uint32_t dfe_ctrl,
                              uint32_t hf_val,
                              uint32_t lf_val,
                              uint32_t dc_val,
                              void *display_ucli_cookie);
bf_status_t port_diag_set_tx_eq(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                uint32_t lane,
                                bool set_all_lane,
                                int pre,
                                int atten,
                                int post,
                                int slew,
                                void *display_ucli_cookie);
bf_status_t port_diag_rx_inv_set(bf_dev_id_t dev_id,
                                 bf_dev_port_t dev_port,
                                 uint32_t lane,
                                 bool set_all_lane,
                                 int polarity,
                                 void *display_ucli_cookie);
bf_status_t port_diag_tx_inv_set(bf_dev_id_t dev_id,
                                 bf_dev_port_t dev_port,
                                 uint32_t lane,
                                 bool set_all_lane,
                                 int polarity,
                                 void *display_ucli_cookie);
bf_status_t port_diag_dfe_ical_set(bf_dev_id_t dev_id,
                                   bf_dev_port_t dev_port,
                                   uint32_t lane,
                                   bool set_all_lane,
                                   void *display_ucli_cookie);
bf_status_t port_diag_dfe_pcal_set(bf_dev_id_t dev_id,
                                   bf_dev_port_t dev_port,
                                   uint32_t lane,
                                   bool set_all_lane,
                                   void *display_ucli_cookie);
bf_status_t port_diag_chg_to_prbs(bf_dev_id_t dev_id,
                                  bf_dev_port_t dev_port,
                                  void *display_ucli_cookie);

#ifdef __cplusplus
}
#endif /* C++ */

#endif  // PORT_MGR_UCLI_H
