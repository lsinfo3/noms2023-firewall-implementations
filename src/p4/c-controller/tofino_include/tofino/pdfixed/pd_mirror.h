#ifndef _TOFINO_PDFIXED_PD_MIRROR_H
#define _TOFINO_PDFIXED_PD_MIRROR_H

#include <tofino/pdfixed/pd_common.h>
#include <tofino/pdfixed/pd_tm.h>

typedef struct p4_pd_mirror_session_info_s {
  p4_pd_mirror_type_e type;
  p4_pd_direction_t dir;
  p4_pd_mirror_id_t id;
  uint16_t egr_port;
  bool egr_port_v;
  p4_pd_tm_queue_t egr_port_queue;
  p4_pd_color_t packet_color;
  uint16_t mcast_grp_a;
  bool mcast_grp_a_v;
  uint16_t mcast_grp_b;
  bool mcast_grp_b_v;
  uint16_t max_pkt_len;
  uint32_t level1_mcast_hash;
  uint32_t level2_mcast_hash;
  uint16_t mcast_l1_xid;
  uint16_t mcast_l2_xid;
  uint16_t mcast_rid;
  uint8_t cos;
  bool c2c;
  uint16_t extract_len;
  uint32_t timeout_usec;
  uint32_t *int_hdr;  // coalesce mirroring header data, ignore for normal
                      // mirroring
  uint8_t int_hdr_len;
} p4_pd_mirror_session_info_t;

p4_pd_status_t p4_pd_mirror_session_create(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_mirror_session_info_t *mirr_sess_info);

p4_pd_status_t p4_pd_mirror_session_update(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_mirror_session_info_t *mirr_sess_info,
    bool enable);

p4_pd_status_t p4_pd_mirror_session_delete(p4_pd_sess_hdl_t shdl,
                                           p4_pd_dev_target_t dev_tgt,
                                           p4_pd_mirror_id_t id);

p4_pd_status_t p4_pd_mirror_session_disable(p4_pd_sess_hdl_t shdl,
                                            p4_pd_direction_t dir,
                                            p4_pd_dev_target_t dev_tgt,
                                            p4_pd_mirror_id_t id);

p4_pd_status_t p4_pd_mirror_session_enable(p4_pd_sess_hdl_t shdl,
                                           p4_pd_direction_t dir,
                                           p4_pd_dev_target_t dev_tgt,
                                           p4_pd_mirror_id_t id);

p4_pd_status_t p4_pd_mirror_session_pipe_vector_set(p4_pd_sess_hdl_t shdl,
                                                    p4_pd_dev_target_t dev_tgt,
                                                    p4_pd_mirror_id_t id,
                                                    int logical_pipe_vector);

p4_pd_status_t p4_pd_mirror_session_pipe_vector_get(p4_pd_sess_hdl_t shdl,
                                                    p4_pd_dev_target_t dev_tgt,
                                                    p4_pd_mirror_id_t id,
                                                    int *logical_pipe_vector);

p4_pd_status_t p4_pd_mirror_session_meta_flag_update(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_mirror_id_t id,
    p4_pd_mirror_meta_flag_e flag,
    bool value);
p4_pd_status_t p4_pd_mirror_session_priority_update(p4_pd_sess_hdl_t shdl,
                                                    p4_pd_dev_target_t dev_tgt,
                                                    p4_pd_mirror_id_t id,
                                                    bool value);
p4_pd_status_t p4_pd_mirror_session_coal_mode_update(p4_pd_sess_hdl_t shdl,
                                                     p4_pd_dev_target_t dev_tgt,
                                                     p4_pd_mirror_id_t id,
                                                     bool value);
p4_pd_status_t p4_pd_mirror_session_get_first(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_mirror_session_info_t *first_mirr_sess_info,
    uint16_t *first_mirr_sess_pipe_id);
p4_pd_status_t p4_pd_mirror_session_get_next(
    p4_pd_sess_hdl_t shdl,
    p4_pd_dev_target_t dev_tgt,
    p4_pd_mirror_id_t current_mirr_id,
    uint16_t current_mirr_sess_pipe_id,
    p4_pd_mirror_session_info_t *next_mirr_sess_info,
    uint16_t *next_mirr_sess_pipe_id);
p4_pd_status_t p4_pd_mirror_session_max_session_id_get(
    p4_pd_sess_hdl_t shdl,
    int device_id,
    p4_pd_mirror_type_e mir_type,
    p4_pd_mirror_id_t *id);
p4_pd_status_t p4_pd_mirror_session_base_session_id_get(
    p4_pd_sess_hdl_t shdl,
    int device_id,
    p4_pd_mirror_type_e mir_type,
    p4_pd_mirror_id_t *id);
#endif
