/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2017-2018 Barefoot Networks, Inc.

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
#ifndef _BF_RT_INIT_H
#define _BF_RT_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bf_rt/bf_rt_common.h>

#ifdef __cplusplus
}
#endif

EXTERNC bf_status_t bf_rt_info_get(const bf_dev_id_t dev_id,
                                   const char *prog_name,
                                   const bf_rt_info_hdl **info_hdl_ret);

EXTERNC bf_status_t
bf_rt_num_p4_names_get(const bf_dev_id_t dev_id, int *num_names);

EXTERNC bf_status_t
bf_rt_p4_names_get(const bf_dev_id_t dev_id, const char **prog_names);

EXTERNC bf_status_t bf_rt_module_init(void);

EXTERNC bf_status_t
bf_rt_num_tables_dependent_on_this_table_get(const bf_rt_info_hdl *bf_rt,
                                             const bf_rt_id_t tbl_id,
                                             int *num_tables);

EXTERNC bf_status_t
bf_rt_tables_dependent_on_this_table_get(const bf_rt_info_hdl *bf_rt,
                                         const bf_rt_id_t tbl_id,
                                         bf_rt_id_t *table_list);

EXTERNC bf_status_t
bf_rt_num_tables_this_table_depends_on_get(const bf_rt_info_hdl *bf_rt,
                                           const bf_rt_id_t tbl_id,
                                           int *num_tables);

EXTERNC bf_status_t
bf_rt_tables_this_table_depends_on_get(const bf_rt_info_hdl *bf_rt,
                                       const bf_rt_id_t tbl_id,
                                       bf_rt_id_t *table_list);

EXTERNC bf_status_t
bf_rt_info_num_pipeline_info_get(const bf_rt_info_hdl *bf_rt, int *num);

EXTERNC bf_status_t bf_rt_info_pipeline_info_get(const bf_rt_info_hdl *bf_rt,
                                                 const char **prof_names,
                                                 bf_dev_pipe_t *pipes);

void bf_rt_python_init();

#endif  // _BF_RT_INIT_H
