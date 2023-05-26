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
#ifndef _TOFINO_PDFIXED_PD_MS_H
#define _TOFINO_PDFIXED_PD_MS_H

#include <tofino/pdfixed/pd_common.h>
#include <bfutils/cJSON.h>

typedef uint32_t p4_pd_act_hdl_t;
typedef struct p4_pd_ms_table_state_s p4_pd_ms_table_state_t;

typedef struct pd_res_spec_t {
  uint32_t tbl_hdl;
  uint32_t tbl_idx;
} pd_res_spec_t;

typedef p4_pd_status_t (*PDMSGrpFn)(uint8_t dev_id,
                                    p4_pd_mbr_hdl_t mbr_hdl,
                                    p4_pd_grp_hdl_t grp_hdl,
                                    void *aux);

void p4_pd_ms_init(void);
void p4_pd_ms_cleanup(void);

p4_pd_ms_table_state_t *p4_pd_ms_init_state(void);

void p4_pd_ms_destroy_state(p4_pd_ms_table_state_t *state);
void p4_pd_ms_destroy_state_for_dev(p4_pd_ms_table_state_t *state,
                                    uint32_t dev_id);
void p4_pd_ms_destroy_txn_state_for_dev(uint32_t dev_id);

p4_pd_status_t p4_pd_ms_new_mbr(p4_pd_sess_hdl_t sess_hdl,
                                p4_pd_ms_table_state_t *state,
                                uint8_t dev_id,
                                p4_pd_mbr_hdl_t mbr_hdl);

p4_pd_status_t p4_pd_ms_del_mbr(p4_pd_sess_hdl_t sess_hdl,
                                p4_pd_ms_table_state_t *state,
                                uint8_t dev_id,
                                p4_pd_mbr_hdl_t mbr_hdl);

p4_pd_status_t p4_pd_ms_add_mbr_to_grp(p4_pd_sess_hdl_t sess_hdl,
                                       p4_pd_ms_table_state_t *state,
                                       uint8_t dev_id,
                                       p4_pd_mbr_hdl_t mbr_hdl,
                                       p4_pd_grp_hdl_t grp_hdl);

p4_pd_status_t p4_pd_ms_del_mbr_from_grp(p4_pd_sess_hdl_t sess_hdl,
                                         p4_pd_ms_table_state_t *state,
                                         uint8_t dev_id,
                                         p4_pd_mbr_hdl_t mbr_hdl,
                                         p4_pd_grp_hdl_t grp_hdl);

p4_pd_status_t p4_pd_ms_mbr_apply_to_grps(p4_pd_ms_table_state_t *state,
                                          uint8_t dev_id,
                                          p4_pd_mbr_hdl_t mbr_hdl,
                                          PDMSGrpFn grp_fn,
                                          void *aux);

p4_pd_status_t p4_pd_ms_get_mbr_act(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_mbr_hdl_t mbr_hdl,
                                    p4_pd_act_hdl_t *act_hdl);

p4_pd_status_t p4_pd_ms_set_mbr_act(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_mbr_hdl_t mbr_hdl,
                                    p4_pd_act_hdl_t act_hdl);

p4_pd_status_t p4_pd_ms_get_grp_act(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_grp_hdl_t grp_hdl,
                                    p4_pd_act_hdl_t *act_hdl);

p4_pd_status_t p4_pd_ms_set_grp_act(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_grp_hdl_t grp_hdl,
                                    p4_pd_act_hdl_t act_hdl);

p4_pd_status_t p4_pd_ms_del_grp(p4_pd_sess_hdl_t sess_hdl,
                                p4_pd_ms_table_state_t *state,
                                uint8_t dev_id,
                                p4_pd_grp_hdl_t grp_hdl);

p4_pd_status_t p4_pd_ms_new_grp(p4_pd_sess_hdl_t sess_hdl,
                                p4_pd_ms_table_state_t *state,
                                uint8_t dev_id,
                                p4_pd_grp_hdl_t grp_hdl);

p4_pd_status_t p4_pd_ms_grp_get_mbrs(p4_pd_ms_table_state_t *state,
                                     uint8_t dev_id,
                                     p4_pd_grp_hdl_t grp_hdl,
                                     p4_pd_mbr_hdl_t *mbr_hdls,
                                     int *num_mbrs);

p4_pd_status_t p4_pd_ms_mbr_add_res(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_mbr_hdl_t mbr_hdl,
                                    pd_res_spec_t *res_spec);

p4_pd_status_t p4_pd_ms_mbr_get_res(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_mbr_hdl_t mbr_hdl,
                                    int *count,
                                    pd_res_spec_t **res_specs);

p4_pd_status_t p4_pd_ms_grp_update_res(uint8_t dev_id,
                                       p4_pd_mbr_hdl_t mbr_hdl,
                                       p4_pd_grp_hdl_t grp_hdl,
                                       void *aux);

p4_pd_status_t p4_pd_ms_grp_get_res(p4_pd_ms_table_state_t *state,
                                    uint8_t dev_id,
                                    p4_pd_grp_hdl_t grp_hdl,
                                    int *count,
                                    pd_res_spec_t **res_specs);

p4_pd_status_t p4_pd_ms_begin_txn(p4_pd_sess_hdl_t sess_hdl);

p4_pd_status_t p4_pd_ms_commit_txn(p4_pd_sess_hdl_t sess_hdl);

p4_pd_status_t p4_pd_ms_abort_txn(p4_pd_sess_hdl_t sess_hdl);

void p4_pd_ms_log_state(uint8_t dev_id,
                        p4_pd_ms_table_state_t *state,
                        cJSON *prof);

void p4_pd_ms_restore_state(uint8_t dev_id,
                            p4_pd_ms_table_state_t *state,
                            cJSON *prof);

#endif
