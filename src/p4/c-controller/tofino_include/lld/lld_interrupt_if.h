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
#ifndef LLD_INTERRUPT_IF_INCLUDED
#define LLD_INTERRUPT_IF_INCLUDED
#include <lld/lld_interrupt.h>

void lld_int_gbl_en_set(bf_dev_id_t dev_id, bool en);

bf_status_t lld_int_claim(bf_dev_id_t dev_id, bf_int_nbr_t int_nbr);
void lld_int_svc(bf_dev_id_t dev_id, uint32_t sh_int_val, uint16_t sh_int_reg);
bf_status_t lld_int_msk(bf_dev_id_t dev_id, bf_int_nbr_t int_nbr);
bf_status_t lld_int_ena(bf_dev_id_t dev_id, bf_int_nbr_t int_nbr);
int lld_int_register_cb(bf_dev_id_t dev_id,
                        uint32_t offset,
                        lld_int_cb cb_fn,
                        void *userdata);
lld_int_cb lld_get_int_cb(bf_dev_id_t dev_id, uint32_t offset, void **userdata);
int lld_register_mac_int_poll_cb(lld_mac_int_poll_cb fn);
int lld_register_mac_int_dump_cb(lld_mac_int_dump_cb fn);
bf_status_t lld_int_poll(bf_dev_id_t dev_id, bool all_ints);
uint32_t lld_int_get_glb_status(bf_dev_id_t dev_id);
uint32_t lld_int_get_shadow_int_status(bf_dev_id_t dev_id, uint16_t sh_int_reg);
uint32_t lld_int_get_shadow_msk_status(bf_dev_id_t dev_id, uint16_t sh_msk_reg);
void lld_int_set_shadow_msk_status(bf_dev_id_t dev_id,
                                   uint16_t sh_msk_reg,
                                   uint32_t value);
uint32_t lld_map_int_nbr_to_sh_int_reg(bf_int_nbr_t int_nbr);
uint32_t lld_map_int_nbr_to_sh_int_bit(bf_int_nbr_t int_nbr);
bf_status_t lld_int_disable_all(bf_dev_id_t dev_id);

void lld_int_host_leaf_enable_set(bf_dev_id_t dev_id, bool en);
void lld_int_mbus_leaf_enable_set(bf_dev_id_t dev_id, bool en);

#endif  // LLD_INTERRUPT_IF_INCUDED
