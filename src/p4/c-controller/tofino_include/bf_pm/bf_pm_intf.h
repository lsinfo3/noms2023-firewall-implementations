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
#ifndef _BF_PAL_PM_INTF_H
#define _BF_PAL_PM_INTF_H

// File includes
#include <tofino/bf_pal/bf_pal_types.h>
#include <port_mgr/bf_port_if.h>

// Public Functions

/**
 * @brief Mark a port ready for bringup
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param is_ready Flag to indicate if a port is ready or not
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_pltfm_front_port_ready_for_bringup(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl, bool is_ready);

/**
 * @brief Mark a port eligible for autonegotiation
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param is_eligible Flag to indicate if a port can autoneg while bring up or
 * not
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_pltfm_front_port_eligible_for_autoneg(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl, bool is_eligible);

/**
 * @brief Get the number of MAC lanes consumed by an existing port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param num_lanes Number of lanes consumed
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_pltfm_front_port_num_lanes_get(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl, int *num_lanes);

/**
 * @brief Given a dev port, get the corresponding front panel port number
 *
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_dev_port_to_front_panel_port_get(
    bf_dev_id_t dev_id,
    bf_dev_port_t dev_port,
    bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Given a front panel port number, get the corresponding dev port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param dev_port Device port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_front_panel_port_to_dev_port_get(
    bf_dev_id_t dev_id,
    bf_pal_front_port_handle_t *port_hdl,
    bf_dev_port_t *dev_port);

/**
 * @brief Get the first front panel port number
 *
 * @param dev_id Device id
 * @param first_port_hdl First front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_front_panel_port_get_first(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *first_port_hdl);

/**
 * @brief Given a front panel port number, get the next front panel port number
 * curr_port_hdl == NULL -> next_port_hdl is the first port
 * return == BF_OBJECT_NOT_FOUND -> curr_port_hdl is the last port
 *
 * @param dev_id Device id
 * @param curr_port_hdl Current front panel port number
 * @param next_port_hdl Next front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_front_panel_port_get_next(
    bf_dev_id_t dev_id,
    bf_pal_front_port_handle_t *curr_port_hdl,
    bf_pal_front_port_handle_t *next_port_hdl);

/**
 * @brief Get the port handle corresponding to the string
 *
 * @param dev_id Device id
 * @param port_str String describing the port
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_str_to_hdl_get(bf_dev_id_t dev_id,
                                      const char *port_str,
                                      bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Add a port with a given speed and fec
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param speed Speed in which the port is to be added
 * @param fec FEC in which the port is to be added
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_add(bf_dev_id_t dev_id,
                           bf_pal_front_port_handle_t *port_hdl,
                           bf_port_speed_t speed,
                           bf_fec_type_t fec);

/**
 * @brief Add a port with a given speed, lane number, and fec
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param speed Speed in which the port is to be added
 * @param n_lanes Lane number in which the port is to be added
 * @param fec FEC in which the port is to be added
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_add_with_lanes(bf_dev_id_t dev_id,
                                      bf_pal_front_port_handle_t *port_hdl,
                                      bf_port_speed_t speed,
                                      uint32_t n_lanes,
                                      bf_fec_type_t fec);

/**
 * @brief Add all ports with a given speed and fec
 *
 * @param dev_id Device id
 * @param speed Speed in which the port is to be added
 * @param fec FEC in which the port is to be added
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_add_all(bf_dev_id_t dev_id,
                               bf_port_speed_t speed,
                               bf_fec_type_t fec);

/**
 * @brief Add all ports with a given speed, lane number,and fec
 *
 * @param dev_id Device id
 * @param speed Speed in which the port is to be added
 * @param n_lanes Lane number in which the port is to be added
 * @param fec FEC in which the port is to be added
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_add_all_with_lanes(bf_dev_id_t dev_id,
                                          bf_port_speed_t speed,
                                          uint32_t n_lanes,
                                          bf_fec_type_t fec);
/**
 * @brief Delete a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_delete(bf_dev_id_t dev_id,
                              bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Delete all ports
 *
 * @param dev_id Device id
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_delete_all(bf_dev_id_t dev_id);

/**
 * @brief Enable a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_enable(bf_dev_id_t dev_id,
                              bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Enable all ports
 *
 * @param dev_id Device id
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_enable_all(bf_dev_id_t dev_id);

/**
 * @brief Disable a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_disable(bf_dev_id_t dev_id,
                               bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Enable/Disable Auto-negotiation for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param an_policy AN policy for the port
 *        (PM_AN_DEFAULT, PM_AN_FORCE_ENABLE, PM_AN_FORCE_DISABLE)
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_autoneg_set(bf_dev_id_t dev_id,
                                   bf_pal_front_port_handle_t *port_hdl,
                                   bf_pm_port_autoneg_policy_e an_policy);

/**
 * @brief Get Enable/Disable of Auto-negotiation for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param an_policy AN policy for the port
 *        (PM_AN_DEFAULT, PM_AN_FORCE_ENABLE, PM_AN_FORCE_DISABLE)
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_autoneg_get(bf_dev_id_t dev_id,
                                   bf_pal_front_port_handle_t *port_hdl,
                                   bf_pm_port_autoneg_policy_e *an_policy);
/**
 * @brief Enable/Disable Auto-negotiation for all ports
 *
 * @param dev_id Device id
 * @param an_policy AN policy for the port
 *        (PM_AN_DEFAULT, PM_AN_FORCE_ENABLE, PM_AN_FORCE_DISABLE)
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_autoneg_set_all(bf_dev_id_t dev_id,
                                       bf_pm_port_autoneg_policy_e an_policy);

/**
 * @brief Setup PRBS on multiple ports. This sets the PRBS on all the ports
 * in the list
 *
 * @param dev_id Device id
 * @param port_hdl_list Front panel port number list
 * @param len Number of ports in the list
 * @param prbs_speed Speed of the PRBS test
 * @param prbs_mode Mode of the PRBS test
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_prbs_set(bf_dev_id_t dev_id,
                                bf_pal_front_port_handle_t *port_hdl_list,
                                uint32_t len,
                                bf_port_prbs_speed_t prbs_speed,
                                bf_port_prbs_mode_t prbs_mode);

/**
 * @brief Cleanup PRBS on multiple ports. This cleans up the PRBS only on all
 * the ports in the list
 *
 * @param dev_id Device id
 * @param port_hdl_list Front panel port number list
 * @param len Number of ports in the list
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_prbs_cleanup(bf_dev_id_t dev_id,
                                    bf_pal_front_port_handle_t *port_hdl_list,
                                    uint32_t len);

/**
 * @brief Get the PRBS stats on multiple ports
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param q_stats prbs stats
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_prbs_stats_get(bf_dev_id_t dev_id,
                                      bf_pal_front_port_handle_t *port_hdl,
                                      bf_sds_debug_stats_t *stats);

/**
 * @brief Get the oper status of a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param oper_status Operational status of the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_oper_status_get(bf_dev_id_t dev_id,
                                       bf_pal_front_port_handle_t *port_hdl,
                                       bool *oper_status);

/**
 * @brief Get the speed of a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param speed Speed of the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_speed_get(bf_dev_id_t dev_id,
                                 bf_pal_front_port_handle_t *port_hdl,
                                 bf_port_speed_t *speed);

/**
 * @brief Set the speed of a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param speed Speed of the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_speed_set(bf_dev_id_t dev_id,
                                 bf_pal_front_port_handle_t *port_hdl,
                                 bf_port_speed_t speed);

/**
 * @brief Set the speed and lane number of a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param speed Speed of the port
 * @param n_lanes Lane number of the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_speed_set_with_lanes(
    bf_dev_id_t dev_id,
    bf_pal_front_port_handle_t *port_hdl,
    bf_port_speed_t speed,
    uint32_t n_lanes);

/**
 * @brief Get the FEC type for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param fec_type FEC type set for the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_fec_get(bf_dev_id_t dev_id,
                               bf_pal_front_port_handle_t *port_hdl,
                               bf_fec_type_t *fec_type);

/**
 * @brief Set the FEC type for a port. If the fec type being set is different
 * than the existing one, then the port will be deleted and re-added
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param fec_type FEC type to be set
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_fec_set(bf_dev_id_t dev_id,
                               bf_pal_front_port_handle_t *port_hdl,
                               bf_fec_type_t fec_type);

/**
 * @brief Get the loopback mode of a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param mode Loopback mode
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_loopback_mode_get(bf_dev_id_t dev_id,
                                         bf_pal_front_port_handle_t *port_hdl,
                                         bf_loopback_mode_e *mode);

/**
 * @brief Set a port in loopback
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param mode Loopback mode
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_loopback_mode_set(bf_dev_id_t dev_id,
                                         bf_pal_front_port_handle_t *port_hdl,
                                         bf_loopback_mode_e mode);

/**
 * @brief Start the timer to periodically update stats for all the ports
 * after the given polling interval
 *
 * @param dev_id Device id
 * @param poll_intv_ms Polling interval
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_stats_poll_start(bf_dev_id_t dev_id,
                                        uint32_t poll_intv_ms);

/**
 * @brief Get a particular stat counter for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param ctr_type Counter id
 * @param stat_val Value of the counter
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_this_stat_get(bf_dev_id_t dev_id,
                                     bf_pal_front_port_handle_t *port_hdl,
                                     bf_rmon_counter_t ctr_type,
                                     uint64_t *stat_val);

/**
 * @brief Get all stat counters for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param stats Array of all the counter values
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_all_stats_get(bf_dev_id_t dev_id,
                                     bf_pal_front_port_handle_t *port_hdl,
                                     uint64_t stats[BF_NUM_RMON_COUNTERS]);

/**
 * @brief Clear a particular stat counter for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param ctr_type Counter id
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_this_stat_clear(bf_dev_id_t dev_id,
                                       bf_pal_front_port_handle_t *port_hdl,
                                       bf_rmon_counter_t ctr_type);

/**
 * @brief Clear all stat counters for a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_all_stats_clear(bf_dev_id_t dev_id,
                                       bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Read all the stats asynchronously from the hardware and update the
 * local cache
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_all_stats_update(bf_dev_id_t dev_id,
                                        bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Read all the stats asynchronously from the hardware and update the
 * local cache
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param stats Array of all the counter values
 * @param timestamp Time stamp of the last stats update, struct timespec:sec and
 *nsec
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_all_pure_stats_get_with_timestamp(
    bf_dev_id_t dev_id,
    bf_pal_front_port_handle_t *port_hdl,
    uint64_t stats[BF_NUM_RMON_COUNTERS],
    int64_t *timestamp_s,
    int64_t *timestamp_ns);

/**
 * @brief Read all the stats synchronously from the hardware and update the
 * cache
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_all_stats_update_sync(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Get the media type connected to the port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param media_type Media type connected to the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_media_type_get(bf_dev_id_t dev_id,
                                      bf_pal_front_port_handle_t *port_hdl,
                                      bf_media_type_t *media_type);

/**
 * @brief Get the number of ports on the chip depending on the efuse.
 *        Includes front and internal ports on the chip.
 * @param dev_id Device id
 * @param num_ports Number of ports on the chip
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_num_max_ports_get(bf_dev_id_t dev_id, uint32_t *num_ports);

/**
 * @brief Get the number of ports on the chip depending on the efuse,
 *        excluding the internal ports.
 *
 * @param dev_id Device id
 * @param num_ports Number of ports on the chip
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_num_front_ports_get(bf_dev_id_t dev_id, uint32_t *num_ports);

/**
 * @brief Get the dev port corresponding to the front port index
 *
 * @param dev_id Device id
 * @param fp_idx Front port index
 * @param dev_port Device port number corresponding to the front port index
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_front_port_index_to_dev_port_get(bf_dev_id_t dev_id,
                                                   uint32_t fp_idx,
                                                   bf_dev_port_t *dev_port);

/**
 * @brief Get the range of the available recirculation ports on the system
 *
 * @param dev_id Device id
 * @param start_recirc_port First recirc port index
 * @param end_recirc_port Last recirc port index
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_recirc_port_range_get(bf_dev_id_t dev_id,
                                        uint32_t *start_recirc_port,
                                        uint32_t *end_recirc_port);

/**
 * @brief Get the dev port corresponding to the recirculation port index
 *
 * @param dev_id Device id
 * @param recirc_port Recirculation port index
 * @param dev_port Device port number corresponding to the recirc port index
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_recirc_port_to_dev_port_get(bf_dev_id_t dev_id,
                                              uint32_t recirc_port,
                                              bf_dev_port_t *dev_port);

/**
 * @brief Set the serdes Tx Equalization Pre parameter
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param tx_pre Serdes Tx Pre Emphasis param
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_serdes_tx_eq_pre_set(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl, int tx_pre);

/**
 * @brief Set the serdes Tx Equalization Post parameter
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param tx_post Serdes Tx Post Emphasis param
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_serdes_tx_eq_post_set(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl, int tx_post);

/**
 * @brief Set the serdes Tx Equalization Main parameter
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param tx_pre Serdes Tx Attenuation param
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_serdes_tx_eq_main_set(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl, int tx_attn);

/**
 * @brief Add a port FSM as a scheduled tasklet to bring up the port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_fsm_init(bf_dev_id_t dev_id,
                                bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Run the FSM tasklet. This should be periodically called by the
 * application
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_tasklet_scheduler();

/**
 * @brief Initialize the bf PM module
 *
 * @param void
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_init(void);

bf_status_t bf_pm_interrupt_based_link_monitoring_set(bf_dev_id_t dev_id,
                                                      bool en);

/**
 * @brief Add and set all the internal ports in MAC lpbk for eligible SKU parts
 *
 * @param dev_id Device id
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_internal_ports_init(bf_dev_id_t dev_id);

/**
 * @brief Return if a particular port is internal (doesn't have serdes)
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param is_internal Indicates if the port internal or not
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_is_port_internal(bf_dev_id_t dev_id,
                                   bf_pal_front_port_handle_t *port_hdl,
                                   bool *is_internal);

/**
 * @brief Set default configuration (passed in by the platforms module) for a
 * serdes slice correponding to a port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_serdes_cfg_set(bf_dev_id_t dev_id,
                                      bf_pal_front_port_handle_t *port_hdl);

bf_status_t bf_pm_port_traffic_status_get(bf_dev_id_t dev_id,
                                          bf_pal_front_port_handle_t *port_hdl,
                                          bool *there_is_traffic);
/**@set up the rate function
 *
 */
bf_status_t bf_pm_init_rate(bf_dev_id_t dev_id, bf_dev_port_t dev_port);
bf_status_t bf_pm_rate_timer_creat(bf_dev_id_t dev_id, uint32_t period_msecs);
bf_status_t bf_pm_rate_timer_start(bf_dev_id_t dev_id);
bf_status_t bf_pm_rate_timer_check_del(bf_dev_id_t dev_id);

/**
 * @brief Clear the FEC counters
 *
 * @param dev_id Device id
 * @param dev_port Device port number corresponding to the front port index
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_clear_the_fec_counters(bf_dev_id_t dev_id,
                                              bf_dev_port_t dev_port);

/**
 * @brief Get a particular stat counter for a port into user buffer
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param ctr_type_array Pointer to array holding Counter ids
 * @param ctr_data buffer for the counter
 * @param num_of_ctr number of counter id
 * @return Status of the API call
 */
bf_status_t bf_pm_port_stat_direct_get(bf_dev_id_t dev_id,
                                       bf_pal_front_port_handle_t *port_hdl,
                                       bf_rmon_counter_t *ctr_type_array,
                                       uint64_t *ctr_data,
                                       uint32_t num_of_ctr);
/**
 * @brief Update stats poll interval
 * @param dev_id Device id
 * @param poll_intv_ms Stats polling interval in millisec - minimum 500 msec
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_stats_poll_period_update(bf_dev_id_t dev_id,
                                                uint32_t poll_intv_ms);
/**
 * @brief get stats poll interval
 * @param dev_id Device id
 * @param poll_intv_ms Stats polling interval in millisec - minimum 500 msec
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_stats_poll_period_get(bf_dev_id_t dev_id,
                                             uint32_t *poll_intv_ms);
/**
 * @brief Set the port direction
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param port_dir Direction for the port
 *        (PM_PORT_DIR_DEFAULT, PM_PORT_DIR_TX_ONLY, PM_PORT_DIR_RX_ONLY)
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_direction_set(bf_dev_id_t dev_id,
                                     bf_pal_front_port_handle_t *port_hdl,
                                     bf_pm_port_dir_e port_dir);
/**
 * @brief Get the port direction
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param port_dir Buffer for the port direction
 *        (PM_PORT_DIR_DEFAULT, PM_PORT_DIR_TX_ONLY, PM_PORT_DIR_RX_ONLY)
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_direction_get(bf_dev_id_t dev_id,
                                     bf_pal_front_port_handle_t *port_hdl,
                                     bf_pm_port_dir_e *port_dir);

/**
 * @brief Set the media type connected to the port
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param media_type Media type connected to the port
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_media_type_set(bf_dev_id_t dev_id,
                                      bf_pal_front_port_handle_t *port_hdl,
                                      bf_media_type_t media_type);

/**
 * @brief Set the serdes param (coefficients)
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 * @param serdes_param Serdes params to be configured
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_serdes_param_set(bf_dev_id_t dev_id,
                                        bf_pal_front_port_handle_t *port_hdl,
                                        bf_pal_serdes_params_t *serdes_param);

/**
 * @brief Add a port FSM as a scheduled tasklet to wait for down event
 *
 * @param dev_id Device id
 * @param port_hdl Front panel port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_fsm_set_down_event_state(
    bf_dev_id_t dev_id, bf_pal_front_port_handle_t *port_hdl);

/**
 * @brief Get the number of internal ports on the chip depending on the efuse,
 *        excluding the front panel ports.
 * @param dev_id Device id
 * @param num_ports Number of ports on the chip
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_num_internal_ports_get(bf_dev_id_t dev_id,
                                         uint32_t *num_ports);

/**
 * @brief Given a port name, get the corresponding dev_port
 *
 * @param dev_id Device id
 * @param port_str Port Name
 * @param dev_port Device port number
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_port_str_to_dev_port_get(bf_dev_id_t dev_id,
                                           char *port_str,
                                           bf_dev_port_t *dev_port);
/**
 * @brief Given a dev port, get the corresponding port name
 *
 * @param dev_id Device id
 * @param dev_port Device port number
 * @param port_str Port Name
 *
 * @return Status of the API call
 */
bf_status_t bf_pm_dev_port_to_port_str_get(bf_dev_id_t dev_id,
                                           bf_dev_port_t dev_port,
                                           char *port_str);
#endif
