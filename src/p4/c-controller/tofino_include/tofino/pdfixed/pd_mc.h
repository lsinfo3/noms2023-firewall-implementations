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
#ifndef _TOFINO_PDFIXED_PD_MC_H
#define _TOFINO_PDFIXED_PD_MC_H

#include <tofino/pdfixed/pd_common.h>

p4_pd_status_t p4_pd_mc_init();

/* Multicast session APIs. */
p4_pd_status_t p4_pd_mc_create_session(p4_pd_sess_hdl_t *sess_hdl);

p4_pd_status_t p4_pd_mc_destroy_session(p4_pd_sess_hdl_t sess_hdl);

p4_pd_status_t p4_pd_mc_complete_operations(p4_pd_sess_hdl_t sess_hdl);

p4_pd_status_t p4_pd_mc_begin_batch(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_mc_flush_batch(p4_pd_sess_hdl_t shdl);

p4_pd_status_t p4_pd_mc_end_batch(p4_pd_sess_hdl_t shdl, bool hwSynchronous);

/* Multicast group APIs. */
p4_pd_status_t p4_pd_mc_mgrp_create(p4_pd_sess_hdl_t sess_hdl,
                                    int dev,
                                    uint16_t grp,
                                    p4_pd_entry_hdl_t *grp_hdl);
p4_pd_status_t p4_pd_mc_mgrp_get_attr(p4_pd_sess_hdl_t shdl,
                                      int dev,
                                      p4_pd_entry_hdl_t mgrp_hdl,
                                      uint16_t *grp);
p4_pd_status_t p4_pd_mc_mgrp_destroy(p4_pd_sess_hdl_t sess_hdl,
                                     int dev,
                                     p4_pd_entry_hdl_t grp_hdl);

p4_pd_status_t p4_pd_mc_mgrp_get_first(p4_pd_sess_hdl_t shdl,
                                       int dev,
                                       p4_pd_entry_hdl_t *mgrp_hdl);

p4_pd_status_t p4_pd_mc_mgrp_get_count(p4_pd_sess_hdl_t shdl,
                                       int dev,
                                       uint32_t *count);

p4_pd_status_t p4_pd_mc_mgrp_get_next_i(p4_pd_sess_hdl_t shdl,
                                        int dev,
                                        p4_pd_entry_hdl_t mgrp_hdl,
                                        uint32_t i,
                                        p4_pd_entry_hdl_t *next_mgrp_hdls);

p4_pd_status_t p4_pd_mc_mgrp_get_first_node_mbr(p4_pd_sess_hdl_t shdl,
                                                int dev,
                                                p4_pd_entry_hdl_t mgrp_hdl,
                                                p4_pd_entry_hdl_t *node_hdl,
                                                bool *xid_valid,
                                                uint16_t *xid);

p4_pd_status_t p4_pd_mc_mgrp_get_node_mbr_count(p4_pd_sess_hdl_t shdl,
                                                int dev,
                                                p4_pd_entry_hdl_t mgrp_hdl,
                                                uint32_t *count);

p4_pd_status_t p4_pd_mc_mgrp_get_next_i_node_mbr(
    p4_pd_sess_hdl_t shdl,
    int dev,
    p4_pd_entry_hdl_t mgrp_hdl,
    p4_pd_entry_hdl_t node_hdl,
    uint32_t i,
    p4_pd_entry_hdl_t *next_node_hdls,
    bool *next_node_xids_valid,
    uint16_t *next_node_xids);

p4_pd_status_t p4_pd_mc_mgrp_get_first_ecmp_mbr(p4_pd_sess_hdl_t shdl,
                                                int dev,
                                                p4_pd_entry_hdl_t mgrp_hdl,
                                                p4_pd_entry_hdl_t *ecmp_hdl,
                                                bool *xid_valid,
                                                uint16_t *ecmp_xid);

p4_pd_status_t p4_pd_mc_mgrp_get_ecmp_mbr_count(p4_pd_sess_hdl_t shdl,
                                                int dev,
                                                p4_pd_entry_hdl_t mgrp_hdl,
                                                uint32_t *count);

p4_pd_status_t p4_pd_mc_mgrp_get_next_i_ecmp_mbr(
    p4_pd_sess_hdl_t shdl,
    int dev,
    p4_pd_entry_hdl_t mgrp_hdl,
    p4_pd_entry_hdl_t ecmp_hdl,
    uint32_t i,
    p4_pd_entry_hdl_t *next_ecmp_hdls,
    bool *next_ecmp_xids_valid,
    uint16_t *next_ecmp_xids);

p4_pd_status_t p4_pd_mc_ecmp_get_mbr_from_hash(p4_pd_sess_hdl_t shdl,
                                               int dev,
                                               p4_pd_entry_hdl_t mgrp_hdl,
                                               p4_pd_entry_hdl_t ecmp_hdl,
                                               uint16_t level1_mcast_hash,
                                               uint16_t pkt_xid,
                                               p4_pd_entry_hdl_t *node_hdl,
                                               bool *is_pruned);

/* Multicast ECMP APIs. */
p4_pd_status_t p4_pd_mc_ecmp_create(p4_pd_sess_hdl_t sess_hdl,
                                    int dev,
                                    p4_pd_entry_hdl_t *ecmp_hdl);

p4_pd_status_t p4_pd_mc_ecmp_destroy(p4_pd_sess_hdl_t sess_hdl,
                                     int dev,
                                     p4_pd_entry_hdl_t ecmp_hdl);

p4_pd_status_t p4_pd_mc_ecmp_get_first(p4_pd_sess_hdl_t shdl,
                                       int dev,
                                       p4_pd_entry_hdl_t *ecmp_hdl);

p4_pd_status_t p4_pd_mc_ecmp_get_count(p4_pd_sess_hdl_t shdl,
                                       int dev,
                                       uint32_t *count);

p4_pd_status_t p4_pd_mc_ecmp_get_next_i(p4_pd_sess_hdl_t shdl,
                                        int dev,
                                        p4_pd_entry_hdl_t ecmp_hdl,
                                        uint32_t i,
                                        p4_pd_entry_hdl_t *next_ecmp_hdls);

p4_pd_status_t p4_pd_mc_ecmp_mbr_add(p4_pd_sess_hdl_t sess_hdl,
                                     int dev,
                                     p4_pd_entry_hdl_t ecmp_hdl,
                                     p4_pd_entry_hdl_t l1_hdl);

p4_pd_status_t p4_pd_mc_ecmp_mbr_rem(p4_pd_sess_hdl_t sess_hdl,
                                     int dev,
                                     p4_pd_entry_hdl_t ecmp_hdl,
                                     p4_pd_entry_hdl_t l1_hdl);

p4_pd_status_t p4_pd_mc_ecmp_get_first_mbr(p4_pd_sess_hdl_t shdl,
                                           int dev,
                                           p4_pd_entry_hdl_t ecmp_hdl,
                                           p4_pd_entry_hdl_t *node_hdl);

p4_pd_status_t p4_pd_mc_ecmp_get_mbr_count(p4_pd_sess_hdl_t shdl,
                                           int dev,
                                           p4_pd_entry_hdl_t ecmp_hdl,
                                           uint32_t *count);

p4_pd_status_t p4_pd_mc_ecmp_get_next_i_mbr(p4_pd_sess_hdl_t shdl,
                                            int dev,
                                            p4_pd_entry_hdl_t ecmp_hdl,
                                            p4_pd_entry_hdl_t node_hdl,
                                            uint32_t i,
                                            p4_pd_entry_hdl_t *next_node_hdls);

p4_pd_status_t p4_pd_mc_ecmp_get_first_assoc(p4_pd_sess_hdl_t shdl,
                                             int dev,
                                             p4_pd_entry_hdl_t ecmp_hdl,
                                             p4_pd_entry_hdl_t *mgrp_hdl);

p4_pd_status_t p4_pd_mc_ecmp_get_assoc_count(p4_pd_sess_hdl_t shdl,
                                             int dev,
                                             p4_pd_entry_hdl_t ecmp_hdl,
                                             uint32_t *count);

p4_pd_status_t p4_pd_mc_ecmp_get_next_i_assoc(
    p4_pd_sess_hdl_t shdl,
    int dev,
    p4_pd_entry_hdl_t ecmp_hdl,
    p4_pd_entry_hdl_t mgrp_hdl,
    uint32_t i,
    p4_pd_entry_hdl_t *next_mgrp_hdls);

p4_pd_status_t p4_pd_mc_associate_ecmp(p4_pd_sess_hdl_t sess_hdl,
                                       int dev,
                                       p4_pd_entry_hdl_t grp_hdl,
                                       p4_pd_entry_hdl_t ecmp_hdl,
                                       uint16_t xid,
                                       bool xid_valid);

p4_pd_status_t p4_pd_mc_ecmp_get_assoc_attr(p4_pd_sess_hdl_t shdl,
                                            int dev,
                                            p4_pd_entry_hdl_t mgrp_hdl,
                                            p4_pd_entry_hdl_t ecmp_hdl,
                                            bool *xid_valid,
                                            uint16_t *xid);

p4_pd_status_t p4_pd_mc_dissociate_ecmp(p4_pd_sess_hdl_t sess_hdl,
                                        int dev,
                                        p4_pd_entry_hdl_t grp_hdl,
                                        p4_pd_entry_hdl_t ecmp_hdl);

/* Multicast L1-Node APIs. */
p4_pd_status_t p4_pd_mc_node_create(p4_pd_sess_hdl_t sess_hdl,
                                    int dev,
                                    uint16_t rid,
                                    uint8_t *port_map,
                                    uint8_t *lag_map,
                                    p4_pd_entry_hdl_t *node_hdl);

p4_pd_status_t p4_pd_mc_node_get_attr(p4_pd_sess_hdl_t shdl,
                                      int dev,
                                      p4_pd_entry_hdl_t node_hdl,
                                      uint16_t *rid,
                                      uint8_t *port_map,
                                      uint8_t *lag_map);

p4_pd_status_t p4_pd_mc_node_update(p4_pd_sess_hdl_t sess_hdl,
                                    int dev,
                                    p4_pd_entry_hdl_t node_hdl,
                                    uint8_t *port_map,
                                    uint8_t *lag_map);

p4_pd_status_t p4_pd_mc_node_destroy(p4_pd_sess_hdl_t sess_hdl,
                                     int dev,
                                     p4_pd_entry_hdl_t node_hdl);

p4_pd_status_t p4_pd_mc_node_get_first(p4_pd_sess_hdl_t shdl,
                                       int dev,
                                       p4_pd_entry_hdl_t *node_hdl);

p4_pd_status_t p4_pd_mc_node_get_count(p4_pd_sess_hdl_t shdl,
                                       int dev,
                                       uint32_t *count);

p4_pd_status_t p4_pd_mc_node_get_next_i(p4_pd_sess_hdl_t shdl,
                                        int dev,
                                        p4_pd_entry_hdl_t node_hdl,
                                        uint32_t i,
                                        p4_pd_entry_hdl_t *next_node_hdls);

p4_pd_status_t p4_pd_mc_node_get_association(p4_pd_sess_hdl_t shdl,
                                             int dev,
                                             p4_pd_entry_hdl_t node_hdl,
                                             bool *is_associated,
                                             p4_pd_entry_hdl_t *mgrp_hdl,
                                             bool *xid_valid,
                                             uint16_t *xid);

p4_pd_status_t p4_pd_mc_node_is_mbr(p4_pd_sess_hdl_t shdl,
                                    int dev,
                                    p4_pd_entry_hdl_t node_hdl,
                                    bool *is_ecmp_mbr,
                                    p4_pd_entry_hdl_t *ecmp_hdl);

p4_pd_status_t p4_pd_mc_associate_node(p4_pd_sess_hdl_t sess_hdl,
                                       int dev,
                                       p4_pd_entry_hdl_t grp_hdl,
                                       p4_pd_entry_hdl_t l1_hdl,
                                       uint16_t xid,
                                       bool xid_valid);

p4_pd_status_t p4_pd_mc_dissociate_node(p4_pd_sess_hdl_t sess_hdl,
                                        int dev,
                                        p4_pd_entry_hdl_t grp_hdl,
                                        p4_pd_entry_hdl_t node_hdl);

/* Multicast misc APIs. */
p4_pd_status_t p4_pd_mc_set_lag_membership(p4_pd_sess_hdl_t sess_hdl,
                                           int dev,
                                           uint8_t lag,
                                           uint8_t *port_map);

p4_pd_status_t p4_pd_mc_get_lag_membership(p4_pd_sess_hdl_t sess_hdl,
                                           int dev,
                                           uint8_t lag,
                                           uint8_t *port_map);

p4_pd_status_t p4_pd_mc_get_lag_member_from_hash(p4_pd_sess_hdl_t sess_hdl,
                                                 int dev,
                                                 p4_pd_entry_hdl_t node_hdl,
                                                 uint8_t lag,
                                                 uint16_t level2_mcast_hash,
                                                 uint16_t pkt_xid,
                                                 uint16_t pkt_yid,
                                                 uint16_t pkt_rid,
                                                 int *port,
                                                 bool *is_pruned);

p4_pd_status_t p4_pd_mc_set_remote_lag_member_count(
    p4_pd_sess_hdl_t sess_hdl, int dev, uint8_t lag, int left, int right);

p4_pd_status_t p4_pd_mc_update_port_prune_table(p4_pd_sess_hdl_t sess_hdl,
                                                int dev,
                                                uint16_t yid,
                                                uint8_t *port_map);

p4_pd_status_t p4_pd_mc_get_port_prune_table(p4_pd_sess_hdl_t sess_hdl,
                                             int dev,
                                             uint16_t yid,
                                             uint8_t *port_map,
                                             bool from_hw);

p4_pd_status_t p4_pd_mc_set_global_rid(p4_pd_sess_hdl_t sess_hdl,
                                       int dev,
                                       uint16_t rid);

p4_pd_status_t p4_pd_mc_set_port_mc_fwd_state(p4_pd_sess_hdl_t sess_hdl,
                                              int dev,
                                              uint16_t port,
                                              bool is_active);

p4_pd_status_t p4_pd_mc_enable_port_ff(p4_pd_sess_hdl_t sess_hdl, int dev);

p4_pd_status_t p4_pd_mc_disable_port_ff(p4_pd_sess_hdl_t sess_hdl, int dev);

p4_pd_status_t p4_pd_mc_clr_port_ff_state(p4_pd_sess_hdl_t sess_hdl,
                                          int dev,
                                          int port);

p4_pd_status_t p4_pd_mc_enable_port_protection(p4_pd_sess_hdl_t sess_hdl,
                                               int dev);

p4_pd_status_t p4_pd_mc_disable_port_protection(p4_pd_sess_hdl_t sess_hdl,
                                                int dev);

p4_pd_status_t p4_pd_mc_set_port_protection(p4_pd_sess_hdl_t sess_hdl,
                                            int dev,
                                            uint16_t pport,
                                            uint16_t bport);

p4_pd_status_t p4_pd_mc_clear_port_protection(p4_pd_sess_hdl_t sess_hdl,
                                              int dev,
                                              uint16_t pport);

p4_pd_status_t p4_pd_mc_set_max_nodes_before_yield(p4_pd_sess_hdl_t sess_hdl,
                                                   int dev,
                                                   int count);

p4_pd_status_t p4_pd_mc_set_max_node_threshold(p4_pd_sess_hdl_t sess_hdl,
                                               int dev,
                                               int node_count,
                                               int port_lag_count);

p4_pd_status_t p4_pd_mc_get_pipe_vector(p4_pd_sess_hdl_t sess_hdl,
                                        int dev,
                                        uint16_t grp,
                                        int *logical_pipe_vector);
#endif
