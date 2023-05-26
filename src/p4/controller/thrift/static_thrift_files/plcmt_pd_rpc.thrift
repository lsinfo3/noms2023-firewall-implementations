include "res.thrift"

namespace py plcmt_pd_rpc
namespace cpp plcmt_pd_rpc
namespace c_glib plcmt_pd_rpc

exception InvalidPlcmtOperation {
  1:i32 code
}


//:: if gen_md_pd:
enum mat_update_type {
  MAT_UPDATE_ADD = 0,
  MAT_UPDATE_ADD_MULTI = 1,
  MAT_UPDATE_SET_DFLT = 2,
  MAT_UPDATE_CLR_DFLT = 3,
  MAT_UPDATE_DEL = 4,
  MAT_UPDATE_MOD = 5,
  MAT_UPDATE_MOV = 6,
  MAT_UPDATE_MOV_MULTI = 7
}

struct multi_index {
  1: required i32  base_index;
  2: required i32  index_count;
}
struct mat_update_set_dflt_params {
  1: required i32    entry_hdl;
  2: required i32    action_profile_mbr;
  3: required i32    action_index;
  4: required bool   action_profile_mbr_exists;
  5: required i32    sel_grp_hdl;
  6: required i32    selection_index;
  7: required i32    num_selector_indices;
  8: required bool   sel_grp_exists;
  9: required binary drv_data;
}
struct mat_update_clr_dflt_params {
  1: required i32    entry_hdl;
}
struct mat_update_add_params {
  1: required i32    entry_hdl;
  2: required i32    priority;
  3: required i32    entry_index;
  4: required i32    action_profile_mbr;
  5: required i32    action_index;
  6: required bool   action_profile_mbr_exists;
  7: required i32    sel_grp_hdl;
  8: required i32    selection_index;
  9: required i32    num_selector_indices;
 10: required bool   sel_grp_exists;
 11: required binary drv_data;
}
struct mat_update_add_multi_params {
  1: required i32    entry_hdl;
  2: required i32    priority;
  3: required i32    action_profile_mbr;
  4: required i32    action_index;
  5: required bool   action_profile_mbr_exists;
  6: required i32    sel_grp_hdl;
  7: required i32    selection_index;
  8: required i32    num_selector_indices;
  9: required bool   sel_grp_exists;
 10: required list<multi_index> locations;
 11: required binary drv_data;
}
struct mat_update_mov_multi_params {
  1: required i32    entry_hdl;
  2: required i32    action_profile_mbr;
  3: required i32    action_index;
  4: required bool   action_profile_mbr_exists;
  5: required i32    sel_grp_hdl;
  6: required i32    selection_index;
  7: required i32    num_selector_indices;
  8: required bool   sel_grp_exists;
  9: required list<multi_index> locations;
 10: required binary drv_data;
}
struct mat_update_del_params {
  1: required i32    entry_hdl;
}
struct mat_update_mod_params {
  1: required i32    entry_hdl;
  2: required i32    action_profile_mbr;
  3: required i32    action_index;
  4: required bool   action_profile_mbr_exists;
  5: required i32    sel_grp_hdl;
  6: required i32    selection_index;
  7: required i32    num_selector_indices;
  8: required bool   sel_grp_exists;
  9: required binary drv_data;
}
struct mat_update_mov_params {
  1: required i32    entry_hdl;
  2: required i32    entry_index;
  3: required i32    action_profile_mbr;
  4: required i32    action_index;
  5: required bool   action_profile_mbr_exists;
  6: required i32    sel_grp_hdl;
  7: required i32    selection_index;
  8: required i32    num_selector_indices;
  9: required bool   sel_grp_exists;
 10: required binary drv_data;
}

union mat_update_params {
  1: mat_update_set_dflt_params  set_dflt;
  2: mat_update_clr_dflt_params  clr_dflt;
  3: mat_update_add_params       add;
  4: mat_update_del_params       remove;
  5: mat_update_mod_params       mod;
  6: mat_update_mov_params       mov;
  7: mat_update_add_multi_params add_multi;
  8: mat_update_mov_multi_params mov_multi;
}

struct mat_tbl_update_t {
  1: required res.DevTarget_t   dev_tgt;
  2: required i32               tbl_hdl;
  3: required mat_update_type   update_type;
  4: required mat_update_params update_params;
}

enum adt_update_type {
  ADT_UPDATE_ADD = 0,
  ADT_UPDATE_DEL = 1,
  ADT_UPDATE_MOD = 2
}
struct adt_update_add_params {
  1: required i32 entry_hdl;
  2: required binary drv_data;
}
struct adt_update_del_params {
  1: required i32 entry_hdl;
}
struct adt_update_mod_params {
  1: required i32 entry_hdl;
  2: required binary drv_data;
}
union adt_update_params {
  1: adt_update_add_params      add;
  2: adt_update_del_params      remove;
  3: adt_update_mod_params      mod;
}
struct adt_tbl_update_t {
  1: required res.DevTarget_t   dev_tgt;
  2: required i32               tbl_hdl;
  3: required adt_update_type   update_type;
  4: required adt_update_params update_params;
}

enum sel_update_type {
  SEL_UPDATE_GROUP_CREATE = 0,
  SEL_UPDATE_GROUP_DESTROY = 1,
  SEL_UPDATE_ADD = 2,
  SEL_UPDATE_DEL = 3,
  SEL_UPDATE_ACTIVATE = 4,
  SEL_UPDATE_DEACTIVATE = 5,
  SEL_UPDATE_SET_FALLBACK = 6,
  SEL_UPDATE_CLR_FALLBACK = 7
}
struct sel_update_group_create_params {
  1: required i32 group_hdl;
  2: required i32 num_indexes;
  3: required i32 max_members;
  4: required i32 base_logical_index;
  5: required list<multi_index> locations;
}
struct sel_update_group_destroy_params {
  1: required i32 group_hdl;
}
struct sel_update_add_params {
  1: required i32 group_hdl;
  2: required i32 entry_hdl;
  3: required i32 entry_index;
  4: required i32 entry_subindex;
  5: required binary drv_data;
}
struct sel_update_del_params {
  1: required i32 group_hdl;
  2: required i32 entry_hdl;
  3: required i32 entry_index;
  4: required i32 entry_subindex;
}
struct sel_update_activate_params {
  1: required i32 group_hdl;
  2: required i32 entry_hdl;
  3: required i32 entry_index;
  4: required i32 entry_subindex;
}
struct sel_update_deactivate_params {
  1: required i32 group_hdl;
  2: required i32 entry_hdl;
  3: required i32 entry_index;
  4: required i32 entry_subindex;
}
struct sel_update_set_fallback_params {
  1: required i32 entry_hdl;
  2: required binary drv_data;
}
union sel_update_params {
  1: sel_update_group_create_params    grp_create;
  2: sel_update_group_destroy_params   grp_destroy;
  3: sel_update_add_params             add;
  4: sel_update_del_params             remove;
  5: sel_update_activate_params        activate;
  6: sel_update_deactivate_params      deactivate;
  7: sel_update_set_fallback_params    set_fallback;
}
struct sel_tbl_update_t {
  1: required res.DevTarget_t   dev_tgt;
  2: required i32               tbl_hdl;
  3: required sel_update_type   update_type;
  4: required sel_update_params update_params;
}

enum tbl_update_type {
  MAT_UPDATE_TYPE = 0,
  ADT_UPDATE_TYPE = 1,
  SEL_UPDATE_TYPE = 2
}
union tbl_update_data {
  1: mat_tbl_update_t mat;
  2: adt_tbl_update_t adt;
  3: sel_tbl_update_t sel;
}
struct tbl_update_t {
  1: required tbl_update_type update_type;
  2: required tbl_update_data update_data;
}

//:: #endif

service plcmt {
//:: if gen_md_pd:
  void process_plcmt_data(1: res.SessionHandle_t sess_hdl, 2: byte dev_id, 3: list<tbl_update_t> updates) throws (1:InvalidPlcmtOperation ouch),
  binary replace_adt_ent_hdl(1 : binary drv_data, 2: i32 mbr_hdl),
  binary replace_sel_grp_hdl(1 : binary drv_data, 2: i32 grp_hdl),
  binary replace_ttl(1 : binary drv_data, 2: i32 ttl)
//:: #endif
}
