#ifndef _BF_KNET_IF_H_
#define _BF_KNET_IF_H_

#include <stdint.h>
#include <netinet/in.h>
#include <knet_mgr/bf_knet_ioctl.h>
#include <bf_types/bf_types.h>

bf_status_t bf_knet_cpuif_ndev_add(const char *cpuif_netdev_name,
                                   char *cpuif_knetdev_name,
                                   bf_knet_cpuif_t *knet_cpuif_id);
bf_status_t bf_knet_cpuif_ndev_delete(const bf_knet_cpuif_t knet_cpuif_id);
bf_status_t bf_knet_hostif_kndev_add(const bf_knet_cpuif_t knet_cpuif_id,
                                     bf_knet_hostif_knetdev_t *hostif_knetdev);
bf_status_t bf_knet_hostif_kndev_delete(const bf_knet_cpuif_t knet_cpuif_id,
                                        const bf_knet_hostif_t knet_hostif_id);
bf_status_t bf_knet_rx_filter_add(const bf_knet_cpuif_t knet_cpuif_id,
                                  bf_knet_rx_filter_t *rx_filter);
bf_status_t bf_knet_rx_filter_delete(const bf_knet_cpuif_t knet_cpuif_id,
                                     const bf_knet_filter_t filter_id);
bf_status_t bf_knet_rx_filter_get(const bf_knet_cpuif_t knet_cpuif_id,
                                  const bf_knet_filter_t filter_id,
                                  bf_knet_rx_filter_t *rx_filter,
                                  bf_knet_count_t rx_mutation_count);
bf_status_t bf_knet_tx_action_add(const bf_knet_cpuif_t knet_cpuif_id,
                                  const bf_knet_hostif_t knet_hostif_id,
                                  bf_knet_tx_action_t *const tx_action);
bf_status_t bf_knet_tx_action_delete(const bf_knet_cpuif_t knet_cpuif_id,
                                     const bf_knet_hostif_t knet_hostif_id);
bf_status_t bf_knet_get_cpuif_cnt(bf_knet_count_t *const obj_count);
bf_status_t bf_knet_get_hostif_cnt(const bf_knet_cpuif_t knet_cpuif_id,
                                   bf_knet_count_t *const obj_count);
bf_status_t bf_knet_get_rx_filter_cnt(const bf_knet_cpuif_t knet_cpuif_id,
                                      bf_knet_count_t *const obj_count);
bf_status_t bf_knet_get_rx_mutation_cnt(const bf_knet_cpuif_t knet_cpuif_id,
                                        const bf_knet_filter_t filter_id,
                                        bf_knet_count_t *const obj_count);
bf_status_t bf_knet_get_tx_mutation_cnt(const bf_knet_cpuif_t knet_cpuif_id,
                                        const bf_knet_hostif_t hostif_id,
                                        bf_knet_count_t *const obj_count);
bf_status_t bf_knet_rx_filter_list_get(const bf_knet_cpuif_t knet_cpuif_id,
                                       bf_knet_filter_t *const filter_list,
                                       bf_knet_count_t *const filter_count);
bf_status_t bf_knet_cpuif_list_get(bf_knet_cpuif_list_t *const cpuif_list,
                                   bf_knet_count_t *const cpuif_count);
bf_status_t bf_knet_hostif_list_get(bf_knet_cpuif_t knet_cpuif_id,
                                    bf_knet_hostif_list_t *const hostif_list,
                                    bf_knet_count_t *const hostif_count);
bf_status_t bf_knet_tx_action_get(const bf_knet_cpuif_t knet_cpuif_id,
                                  const bf_knet_hostif_t knet_hostif_id,
                                  bf_knet_tx_action_t *tx_action,
                                  bf_knet_count_t tx_mutation_count);
bool bf_knet_module_is_inited();
#endif
