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
#ifndef _BF_PAL_PORT_INTF_H
#define _BF_PAL_PORT_INTF_H

#include <bf_types/bf_types.h>
#include <port_mgr/bf_port_if.h>
#include <tofino/bf_pal/bf_pal_types.h>

/**
 * @brief Callback function pointer to be registered for port status
 * notifications
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param up Port Status
 * @param cookie Registered data returned back
 * @return Status of the API call
 */
typedef bf_status_t (*port_status_chg_cb)(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          bool up,
                                          void *cookie);

/**
 * @brief Get the max number of ports on the target
 * @param dev_id Device id
 * @param ports Max number of ports on the target
 * @return Status of the API call
 */
bf_status_t bf_pal_max_ports_get(bf_dev_id_t dev_id, uint32_t *ports);

/**
 * @brief Map the front port index to the dev port on the target
 * @param dev_id Device id
 * @param fp_idx Front port index
 * @param dev_port Dev port corresponding to the front port index
 * @return Status of the API call
 */
bf_status_t bf_pal_fp_idx_to_dev_port_map(bf_dev_id_t dev_id,
                                          uint32_t fp_idx,
                                          bf_dev_port_t *dev_port);

/**
 * @brief Get the first (MAC) port on a given device
 * @param dev_id Device id
 * @param dev_port First dev port on the device
 * @return Status of the API call
 */
bf_status_t bf_pal_port_get_first(bf_dev_id_t dev_id, bf_dev_port_t *dev_port);

/**
 * @brief Get the next (MAC) port on a given device
 * @param dev_id Device id
 * @param curr_dev_port Current dev port on the device
 * @param next_dev_port Next dev port on the device
 * next_dev_port == -1, current dev_port is the last port on the device
 * @return Status of the API call
 */
bf_status_t bf_pal_port_get_next(bf_dev_id_t dev_id,
                                 bf_dev_port_t curr_dev_port,
                                 bf_dev_port_t *next_dev_port);

/**
 * @brief Get the range of the recirculation ports on the target
 * @param dev_id Device id
 * @param start_recirc_port Start of the range of the recirculation ports on the
 * target
 * @param end_recirc_port End of the range of the recirculation ports on the
 * target
 * @return Status of the API call
 */
bf_status_t bf_pal_recirc_port_range_get(bf_dev_id_t dev_id,
                                         uint32_t *start_recirc_port,
                                         uint32_t *end_recirc_port);

/**
 * @brief Map a given recirculation port to dev port on the target
 * @param dev_id Device id
 * @param recirc_port Recirculation port id
 * @param dev_port Dev port corresponding to the front port index
 * @return Status of the API call
 */
bf_status_t bf_pal_recirc_port_to_dev_port_map(bf_dev_id_t dev_id,
                                               uint32_t recirc_port,
                                               bf_dev_port_t *dev_port);

/**
 * @brief Port add function
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param speed Enum type describing the speed of the port
 * @param fec_type Enum type describing the FEC type of the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_add(bf_dev_id_t dev_id,
                            bf_dev_port_t dev_port,
                            bf_port_speed_t speed,
                            bf_fec_type_t fec_type);

/**
 * @brief Port add function, specify lane number
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param speed Enum type describing the speed of the port
 * @param n_lanes describing lane number of the port
 * @param fec_type Enum type describing the FEC type of the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_add_with_lanes(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       bf_port_speed_t speed,
                                       uint32_t n_lanes,
                                       bf_fec_type_t fec_type);

/**
 * @brief Port add function for all ports
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param speed Enum type describing the speed of the port
 * @param fec_type Enum type describing the FEC type of the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_add_all(bf_dev_id_t dev_id,
                                bf_port_speed_t speed,
                                bf_fec_type_t fec_type);

/**
 * @brief Port delete function
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_del(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

/**
 * @brief All ports delete function
 * @param dev_id Device id
 * @return Status of the API call
 */
bf_status_t bf_pal_port_del_all(bf_dev_id_t dev_id);

/**
 * @brief Port Enable function
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_enable(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

/**
 * @brief Port Enable function for all ports
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_enable_all(bf_dev_id_t dev_id);

/**
 * @brief Port Disable function
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_disable(bf_dev_id_t dev_id, bf_dev_port_t dev_port);

/**
 * @brief Get all the stats of a port (User must ensure that that sufficient
 * space fot stats array has been allocated
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param stats Array to hold all the stats read from hardware
 * @return Status of the API call
 */
bf_status_t bf_pal_port_all_stats_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      uint64_t stats[BF_NUM_RMON_COUNTERS]);

/**
 * @brief Get a particular stat of a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param ctr_type Enum type to hold the id of the stats counter
 * @param stat_val Counter value
 * @return Status of the API call
 */
bf_status_t bf_pal_port_this_stat_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      bf_rmon_counter_t ctr_type,
                                      uint64_t *stat_val);

/**
 * @brief Map the Port Stats id to its corresponding description
 * @param ctr_type Enum type to hold the id of the stats counter
 * @param str Corresponding description of the counter type
 * @return Status of the API call
 */
bf_status_t bf_pal_port_this_stat_id_to_str(bf_rmon_counter_t ctr_type,
                                            char **str);

/**
 * @brief Clear a particular stats counter for a particular port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param ctr_type Enum type to hold the id of the stats counter
 * @return Status of the API call
 */
bf_status_t bf_pal_port_this_stat_clear(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        bf_rmon_counter_t ctr_type);

/**
 * @brief Clear all the stats of a particular port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_all_stats_clear(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port);

/**
 * @brief Set polling interval for collecting Port stats
 * @param dev_id Device id
 * @param poll_intv_ms Polling interval in milliseconds
 * @return Status of the API call
 */
bf_status_t bf_pal_port_stats_poll_intvl_set(bf_dev_id_t dev_id,
                                             uint32_t poll_intvl_ms);
/**
 * @brief Get polling interval for collecting Port stats
 * @param dev_id Device id
 * @param poll_intv_ms Polling interval in milliseconds
 * @return Status of the API call
 */
bf_status_t bf_pal_port_stats_poll_intvl_get(bf_dev_id_t dev_id,
                                             uint32_t *poll_intvl_ms);
/**
 * @brief Register for a port status change callback
 * @param cb_fn Callback function which is called when the port status changes
 * @param cookie Data to be given back in callback fn
 * @return Status of the API call
 */
bf_status_t bf_pal_port_status_notif_reg(port_status_chg_cb cb_fn,
                                         void *cookie);

/**
 * @brief Set a port in loopback mode
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param mode Loopback mode to be set on the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_loopback_mode_set(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          bf_loopback_mode_e mode);

/**
 * @brief Get loopback mode of a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param mode Loopback mode on the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_loopback_mode_get(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          bf_loopback_mode_e *mode);
/**
 * @brief Set the Autoneg policy for the port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param an_policy Autoneg policy for the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_autoneg_policy_set(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           int an_policy);

/**
 * @brief Get the Autoneg policy of the port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param an_policy Autoneg policy of the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_autoneg_policy_get(
    bf_dev_id_t dev_id,
    bf_dev_port_t dev_port,
    bf_pm_port_autoneg_policy_e *an_policy);
/**
 * @brief Set the Autoneg policy for all ports
 * @param dev_id Device id
 * @param an_policy Autoneg policy for the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_autoneg_policy_set_all(bf_dev_id_t dev_id,
                                               int an_policy);

/**
 * @brief Read and update all the stats for a port from hardware
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_all_stats_update(bf_dev_id_t dev_id,
                                         bf_dev_port_t dev_port);

/**
 * @brief Get all the stats of a port (User must ensure that that sufficient
 * space for stats array has been allocated
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param stats Array to hold all the stats read from hardware
 * @param timestamp Time stamp of the stats update, sec and nsec
 * @return Status of the API call
 */
bf_status_t bf_pal_port_all_pure_stats_get_with_timestamp(
    bf_dev_id_t dev_id,
    bf_dev_port_t dev_port,
    uint64_t stats[BF_NUM_RMON_COUNTERS],
    int64_t *timestamp_s,
    int64_t *timestamp_ns);

/**
 * @brief Get the number of lanes consumed by a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param num_lanes Number of lanes used up by the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_num_lanes_get(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      int *num_lanes);

/**
 * @brief Set MTU on a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param tx_mtu Tx Maximum transfer unit length (0-65535)
 * @param rx_mtu Rx Maximum transfer unit length (0-65535)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_mtu_set(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                uint32_t tx_mtu,
                                uint32_t rx_mtu);

/**
 * @brief Get MTU of a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param tx_mtu Tx Maximum transfer unit length (0-65535)
 * @param rx_mtu Rx Maximum transfer unit length (0-65535)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_mtu_get(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                uint32_t *tx_mtu,
                                uint32_t *rx_mtu);

/**
 * @brief Enable or Disable Per-COS Tx/Rx pause on a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param tx_en_map per-COS bitmap of state to set Tx (0=disable, 1=enable)
 * @param rx_en_map per-COS bitmap of state to set Rx (0=disable, 1=enable)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_flow_control_pfc_set(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             uint32_t tx_en_map,
                                             uint32_t rx_en_map);
/**
 * @brief Get Enable or Disable Per-COS Tx/Rx pause configured on the port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param tx_en_map per-COS bitmap of state to set Tx (0=disable, 1=enable)
 * @param rx_en_map per-COS bitmap of state to set Rx (0=disable, 1=enable)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_flow_control_pfc_get(bf_dev_id_t dev_id,
                                             bf_dev_port_t dev_port,
                                             uint32_t *tx_en_map,
                                             uint32_t *rx_en_map);
/**
 * @brief Enable or Disable link Tx and Rx link pause on a Tofino port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param tx_en state to set (False=disable, True=enable)
 * @param rx_en state to set (False=disable, True=enable)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_flow_control_link_pause_set(bf_dev_id_t dev_id,
                                                    bf_dev_port_t dev_port,
                                                    bool tx_en,
                                                    bool rx_en);
/**
 * @brief Get Enable or Disable link Tx and Rx link pause configured on the port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param tx_en state to set (False=disable, True=enable)
 * @param rx_en state to set (False=disable, True=enable)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_flow_control_link_pause_get(bf_dev_id_t dev_id,
                                                    bf_dev_port_t dev_port,
                                                    bool *tx_en,
                                                    bool *rx_en);

/**
 * @brief Get the oper state of a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param state Oper state of the port (0=Down, 1=Up)
 * @return Status of the API call
 */
bf_status_t bf_pal_port_oper_state_get(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       int *state);

/**
 * @brief Check if port is valid
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_is_valid(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
/**
 * @brief Set the FEC type of an already existing port
 * Note: This API will cause the port to be deleted and re-added if the new
 * fec type is not the same as the existing fec type for the port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param fec_type Fec type to be set for the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_fec_set(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                bf_fec_type_t fec_type);

/**
 * @brief Get the FEC type of an already existing port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param fec_type Fec type be set on the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_fec_get(bf_dev_id_t dev_id,
                                bf_dev_port_t dev_port,
                                bf_fec_type_t *fec_type);

/**
 * @brief Get the media type detected for a port
 * Note: If no QSFP is inserted on a port, then the media type reported is
 * UNKNOWN
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param media_type Media type detected on the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_media_type_get(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       bf_media_type_t *media_type);

/**
 * @brief Enable cut-through switching for a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_cut_through_enable(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port);

/**
 * @brief Disable cut-through switching for a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @return Status of the API call
 */
bf_status_t bf_pal_port_cut_through_disable(bf_dev_id_t dev_id,
                                            bf_dev_port_t dev_port);

/**
 * @brief Get cut-through enable status for a port
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param ct_enabled Pointer to current cut-through enable status
 * @return Status of the API call
 */
bf_status_t bf_pal_port_cut_through_enable_status_get(bf_dev_id_t dev_id,
                                                      bf_dev_port_t dev_port,
                                                      bool *ct_enabled);

/**
 * @brief Get the number of pipes on a target
 * @param dev_id Device id
 * @param num_pipes Number of active pipes on the target
 * @return Status of the API call
 */
bf_status_t bf_pal_num_pipes_get(bf_dev_id_t dev_id, uint32_t *num_pipes);

/**
 * @brief Get the dev port number
 * @param dev_id Device id
 * @param port_hdl Port handle for the front port
 * @param dev_port Corresponding dev port
 * @return Status of the API call
 */
bf_status_t bf_pal_front_port_to_dev_port_get(
    bf_dev_id_t dev_id,
    bf_pal_front_port_handle_t *port_hdl,
    bf_dev_port_t *dev_port);

/**
 * @brief Get the front panel port number
 * @param dev_id Device id
 * @param dev_port Corresponding dev port
 * @param port_hdl Port handle for the front port
 * @return Status of the API call
 */
bf_status_t bf_pal_dev_port_to_front_port_get(
    bf_dev_id_t dev_id,
    bf_dev_port_t dev_port,
    bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Get the dev port number
 * @param dev_id Device id
 * @param port_str Port str, length max:MAX_PORT_HDL_STRING_LEN
 * @param dev_port Corresponding dev port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_str_to_dev_port_map(bf_dev_id_t dev_id,
                                            char *port_str,
                                            bf_dev_port_t *dev_port);

/**
 * @brief Get the dev port number
 * @param dev_id Device id
 * @param dev_port Corresponding dev port
 * @param port_str Port str, length required:MAX_PORT_HDL_STRING_LEN
 * @return Status of the API call
 */
bf_status_t bf_pal_dev_port_to_port_str_map(bf_dev_id_t dev_id,
                                            bf_dev_port_t dev_port,
                                            char *port_str);
/**
 * @brief Get a particular stat of a port via register access
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param ctr_type_array Pointer to array holding stats counter id(s)
 * @param stat_val Counter value
 * @param num_of_ctr to read number of ctr_type
 * @return Status of the API call
 */
bf_status_t bf_pal_port_stat_direct_get(bf_dev_id_t dev_id,
                                        bf_dev_port_t dev_port,
                                        bf_rmon_counter_t *ctr_type_array,
                                        uint64_t *stat_val,
                                        uint32_t num_of_ctr);

/**
 * @brief Check if the port is an internal port
 * @param dev_id Device id
 * @param dev_port Corresponding dev port
 * @param is_internal Internal port
 * @return Status of the API call
 */
bf_status_t bf_pal_is_port_internal(bf_dev_id_t dev_id,
                                    bf_dev_port_t dev_port,
                                    bool *is_internal);

/**
 * @brief Sets the port direction
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param port_dir Port Direction 0->default 1->TX only, 2->RX only
 * @return Status of the API call
 */
bf_status_t bf_pal_port_direction_set(bf_dev_id_t dev_id,
                                      bf_dev_port_t dev_port,
                                      bf_pm_port_dir_e port_dir);

/**
 * @brief Set the media type for a port.
 *        Initial configuration via in Json file will be ignored, if any.
 *        Need to be set before port-enable.
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param media_type Media type configured on the port
 * @return Status of the API call
 */
bf_status_t bf_pal_port_media_type_set(bf_dev_id_t dev_id,
                                       bf_dev_port_t dev_port,
                                       bf_media_type_t media_type);

/**
 * @brief Set the serdes parameters for a port per channel.
 *        Initial configuration via in Json file will be ignored, if any.
 *        Need to be set before port-enable.
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param serdes_param Serdes param
 * @return Status of the API call
 */
bf_status_t bf_pal_port_serdes_params_set(bf_dev_id_t dev_id,
                                          bf_dev_port_t dev_port,
                                          bf_pal_serdes_params_t *serdes_param);

#endif
