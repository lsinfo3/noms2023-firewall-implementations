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

/*
 * This file describes  APIs for Traffic Manager application
 * to program Traffic Manager block to desired QoS behaviour.
 */

#ifndef __TRAFFIC_MGR_PPG_INTF_H__
#define __TRAFFIC_MGR_PPG_INTF_H__

#include <traffic_mgr/traffic_mgr_types.h>

/**
 * @file traffic_mgr_ppg_intf.h
 * \brief This file contains APIs for Traffic Manager application to
 *        program PPGs meant to implement part of QoS behaviour based on
 *        traffic character and arrival port.
 */

/**
 * @addtogroup tm-ingress
 * @{
 * Description of APIs for Traffic Manager application to manage
 * ingress buffer and PPGs meant to desired QoS based on
 * traffic behaviour and arrival port.
 */

/**
 * Allocate an unused PPG. The new PPG can be used to implement part of QoS
 * behaviour at ingress TM. If PPGs are exhausted, the API fails.
 *
 * Related APIs: bf_tm_ppg_free(), bf_tm_ppg_defaultppg_get()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param ppg        ppg handle is allocated if available.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_allocate(bf_dev_id_t dev,
                               bf_dev_port_t port,
                               bf_tm_ppg_hdl *ppg);

/**
 * Free PPG back to free pool.
 *
 * Related APIs: bf_tm_ppg_allocate()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg handle to free. PPG handle specifies
 *                   pipe to which PPG belongs to. PPG resource
 *                   will be returned to that pipe.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_free(bf_dev_id_t dev, bf_tm_ppg_hdl ppg);

/**
 * Get default PPG associated with port. The default PPG handle can be used to
 * configure PPG limit. One or many iCoS (iCoS = ig_intr_md.ingress_cos)
 * traffic is mapped to default PPG. At the start all iCoS traffic on a port
 * is mapped to default PPG. By using API bf_tm_ppg_icos_mapping_set(), all or
 * subset of iCoS traffic can be moved to a PPG of their own.
 *
 * Related APIs: bf_tm_ppg_allocate()
 *
 * @param dev        ASIC device identifier.
 * @param port       port handle.
 * @param ppg        ppg handle associated with port
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_defaultppg_get(bf_dev_id_t dev,
                                     bf_dev_port_t port,
                                     bf_tm_ppg_hdl *ppg);

/**
 * This API will assign iCoS (iCoS = ig_intr_md.ingress_cos) traffic on port
 * that PPG is attached to. PPG handle can be default ppg, non-default ppg.
 * If its default ppg, then all the icos mapped traffic is treated lossy. If
 * not, then depending on whether lossless treatment is attached to ppg using
 * bf_tm_ppg_lossless_treatment_enable() or not, all the icos traffic
 * specified using icos_bmap will be treated accordingly.
 *
 * Default : When PPG is allocated, no icos is mapped. User has to explicit
 *           assign one or more iCoS to the PPG.
 *
 * Related APIs: bf_tm_q_pfc_mapping_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg handle
 * @param icos_bmap  Bit map of iCoS (iCoS = ig_intr_md.ingress_cos).
 *                   Bit 7 is interpreted as iCoS 7.
 * @return           Status of API call.
 *
 */
bf_status_t bf_tm_ppg_icos_mapping_set(bf_dev_id_t dev,
                                       bf_tm_ppg_hdl ppg,
                                       uint8_t icos_bmap);

/**
 * Enable lossless treatment for PPG. The PPG handle to use is
 * obtained using bf_tm_ppg_allocate(). All traffic mapped to the PPG is
 * considered as lossless traffic.
 *
 * Default : Default property of PPG is to treat traffic as lossy.
 *
 * Related APIs: bf_tm_ppg_lossless_treatment_disable()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg handle
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_lossless_treatment_enable(bf_dev_id_t dev,
                                                bf_tm_ppg_hdl ppg);

/**
 * Disable lossless treatment for PPG. The PPG handle that is obtained using
 * bf_tm_ppg_allocate() can be used for lossy traffic.
 *
 * Related APIs: bf_tm_ppg_lossless_treatment_enable()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg handle
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_lossless_treatment_disable(bf_dev_id_t dev,
                                                 bf_tm_ppg_hdl ppg);

/**
 * A non deafult PPG can be optionally assigned to any application pool.
 * When assigned to application pool, static or dynamic shared limit
 * can be set. This API aids to achieve that. If it is desired to not
 * assign PPG to any pool, then this API need not be invoked.
 *
 * Default: PPG is not assigned to any application pool.
 *
 * Related APIs: bf_tm_disable_ppg_app_pool_usage(),
 *               bf_tm_ppg_app_pool_usage_get()
 *
 * @param dev             ASIC device identifier.
 * @param ppg             ppg handle.
 * @param pool            Application pool to which PPG is assigned to.
 * @param base_use_limit  Limit to which PPG can grow inside application
 *                        pool. Limit is specified in terms of cells.
 *                        Once this limit is crossed, if PPG burst
 *                        absroption factor (BAF) is non zero, depending
 *                        availability of buffer, PPG is allowed to
 *                        use buffer upto BAF limit. If BAF limit is zero,
 *                        PPG is treated as static and no dynamic thresholding.
 * @param dynamic_baf     One of the values listed in bf_tm_ppg_baf_t
 *                        When BF_TM_PPG_BAF_DISABLE is used, PPG uses static
 *                        limit.
 * @param hysteresis      Hysteresis value in cells. Hardware supports limited
 *                        number of different hysteresis values that can be
 *                        set on PPGs/Pools. When this limit is execeed
 *                        API returns error.
 * @return                Status of API call.
 */
bf_status_t bf_tm_ppg_app_pool_usage_set(bf_dev_id_t dev,
                                         bf_tm_ppg_hdl ppg,
                                         bf_tm_app_pool_t pool,
                                         uint32_t base_use_limit,
                                         bf_tm_ppg_baf_t dynamic_baf,
                                         uint32_t hysteresis);

/**
 * This API can be used to move a PPG that is assigned to application
 * pool to default.
 *
 * Related APIs: bf_tm_ppg_app_pool_usage_set(), bf_tm_ppg_app_pool_usage_get()
 *
 * @param dev        ASIC device identifier.
 * @param pool       Pool handle. Valid pools are BF_TM_IG_POOL_0..3
 *                   and BF_TM_SKID_POOL.
 * @param ppg        ppg handle
 * @return           Status of API call.
 *
 */

bf_status_t bf_tm_ppg_app_pool_usage_disable(bf_dev_id_t dev,
                                             bf_tm_app_pool_t pool,
                                             bf_tm_ppg_hdl ppg);

/**
 * Set miminum limits of ppg. Inorder to increase min limits, that
 * many free cell should be available.
 *
 * Default : TM buffer is equally assigned to all PPGs.
 *
 * Related APIs: bf_tm_ppg_guaranteed_min_limit_get(),
 *               bf_tm_ppg_guaranteed_min_skid_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg whose limits has to be adjusted.
 * @param cells      Number of cells by which minimum ppg limit
 *                   has be increased.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_guaranteed_min_limit_set(bf_dev_id_t dev,
                                               bf_tm_ppg_hdl ppg,
                                               uint32_t cells);

/**
 * Set ppg skid limits. Cannot be set more than the  size of
 * Skid pool size. Once skit limit is reached, even lossless
 * traffic will be dropped. Before consuming skid or head room
 * buffer, PFC would be asserted for lossless flows.
 *
 * Default : Skid limits are set to zero.
 *
 * Related APIs: bf_tm_ppg_skid_limit_get(),
 *               bf_tm_ppg_guaranteed_min_skid_hysteresis_set()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg whose skid limits has to be set.
 * @param cells      Limits in terms of number of cells.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_skid_limit_set(bf_dev_id_t dev,
                                     bf_tm_ppg_hdl ppg,
                                     uint32_t cells);

/**
 * Set ppg hysteresis limits.
 * Hysterisis limits are numbers of cells the ppg usage should fall by
 * from its limit value. Once usage limits are below hysteresis, appropriate
 * condition is cleared. Example when non PFC enabled PPG's usage limit falls
 * below its allowed limit by hysteresis value, drop condition is
 * cleared. PPG's buffer usage limit depends whether it is allowed to use
 * shared pool buffers. If allowed to use shared pool buffers, then hysteresis
 * is applied on total buffer limit which is guaranteed min limit and shared
 * limit,  else hysteresis limit is applied on only guaranteed limit.
 *
 * Default: Skid hysteresis limit set to zero. No hysteresis.
 *
 * Related APIs: bf_tm_ppg_skid_limit_set(),
 *               bf_tm_ppg_guaranteed_min_skid_hysteresis_get()
 *
 * @param dev        ASIC device identifier.
 * @param ppg        ppg whose resume offset limits has to be increased.
 * @param cells      Limits in terms of number of cells
 *                   Hardware supports limited
 *                   number of different hysteresis values that can be
 *                   set on PPGs/Pools. When this limit is execeed
 *                   API returns error.
 * @return           Status of API call.
 */
bf_status_t bf_tm_ppg_guaranteed_min_skid_hysteresis_set(bf_dev_id_t dev,
                                                         bf_tm_ppg_hdl ppg,
                                                         uint32_t cells);

/* @} */

#endif
