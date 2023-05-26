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
#ifndef _TOFINO_PDFIXED_PD_PKT_H
#define _TOFINO_PDFIXED_PD_PKT_H

#include <tofino/pdfixed/pd_common.h>

p4_pd_status_t pkt_pd_init(void);

void pkt_pd_cleanup(void);

p4_pd_status_t pkt_pd_client_init(p4_pd_sess_hdl_t *sess_hdl);

p4_pd_status_t pkt_pd_client_cleanup(p4_pd_sess_hdl_t sess_hdl);

p4_pd_status_t pkt_pd_pkt_tx(p4_pd_sess_hdl_t shdl,
                             const uint8_t *buf,
                             uint32_t size,
                             uint32_t tx_ring);

p4_pd_status_t pkt_pd_verify_tx(p4_pd_sess_hdl_t shdl);

void pkt_pd_get_rx(p4_pd_sess_hdl_t shdl,
                   char *buf,
                   uint32_t *size,
                   uint32_t *rx_ring);

#endif
