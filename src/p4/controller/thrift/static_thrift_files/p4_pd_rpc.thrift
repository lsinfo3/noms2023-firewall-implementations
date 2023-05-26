# BFN Thrift RPC Input

include "res.thrift"


namespace py p4_pd_rpc
namespace cpp p4_pd_rpc
namespace c_glib p4_pd_rpc

typedef i32 EntryHandle_t
typedef i32 MemberHandle_t
typedef i32 GroupHandle_t
typedef binary MacAddr_t
typedef binary IPv6_t
typedef i32 SnapshotHandle_t
typedef i32 PvsHandle_t

struct main_counter_value_t {
  1: required i64 packets;
  2: required i64 bytes;
}

struct main_packets_meter_spec_t {
  1: required i64 cir_pps;
  2: required i64 cburst_pkts;
  3: required i64 pir_pps;
  4: required i64 pburst_pkts;
  5: required bool color_aware;
  6: optional bool is_set = 1;
}

struct main_bytes_meter_spec_t {
  1: required i64 cir_kbps;
  2: required i64 cburst_kbits;
  3: required i64 pir_kbps;
  4: required i64 pburst_kbits;
  5: required bool color_aware;
  6: optional bool is_set = 1;
}

enum main_lpf_type {
  TYPE_RATE = 0,
  TYPE_SAMPLE = 1
}

struct main_lpf_spec_t {
  1: required bool gain_decay_separate_time_constant;
  2: required double gain_time_constant;
  3: required double decay_time_constant;
  4: required double time_constant;
  5: required i32 output_scale_down_factor;
  6: required main_lpf_type lpf_type;
  7: optional bool is_set = 1;
}

struct main_wred_spec_t {
  1: required double time_constant;
  2: required i32 red_min_threshold;
  3: required i32 red_max_threshold;
  4: required double max_probability;
  5: optional bool is_set = 1;
}


enum main_idle_time_mode {
  POLL_MODE = 0,
  NOTIFY_MODE = 1,
  INVALID_MODE = 2
}

enum main_idle_time_hit_state {
  ENTRY_IDLE = 0,
  ENTRY_ACTIVE = 1
}

struct main_idle_time_params_t {
  1: required main_idle_time_mode mode;
  2: optional i32 ttl_query_interval;
  3: optional i32 max_ttl;
  4: optional i32 min_ttl;
  5: optional i32 cookie;
}

struct main_idle_tmo_expired_t {
  1: required i32 dev_id;
  2: required EntryHandle_t entry;
  3: required i32 cookie;
}

struct main_sel_update_t {
  1: required res.SessionHandle_t  sess_hdl;
  2: required res.DevTarget_t      dev_tgt;
  3: required i32                  cookie;
  4: required i32                  grp_hdl;
  5: required i32                  mbr_hdl;
  6: required i32                  index;
  7: required bool                 is_add;
}

enum main_grp_mbr_state {
  MBR_ACTIVE = 0,
  MBR_INACTIVE = 1
}


enum tbl_property_t
{
   TBL_PROP_TBL_ENTRY_SCOPE = 1,
   TBL_PROP_TERN_TABLE_ENTRY_PLACEMENT = 2,
   TBL_PROP_DUPLICATE_ENTRY_CHECK = 3,
   TBL_PROP_IDLETIME_REPEATED_NOTIFICATION = 4
}

enum tbl_property_value_t
{
   ENTRY_SCOPE_ALL_PIPELINES=0,
   ENTRY_SCOPE_SINGLE_PIPELINE=1,
   ENTRY_SCOPE_USER_DEFINED=2,
   TERN_ENTRY_PLACEMENT_DRV_MANAGED=0,
   TERN_ENTRY_PLACEMENT_APP_MANAGED=1,
   DUPLICATE_ENTRY_CHECK_DISABLE=0,
   DUPLICATE_ENTRY_CHECK_ENABLE=1,
   IDLETIME_REPEATED_NOTIFICATION_DISABLE = 0,
   IDLETIME_REPEATED_NOTIFICATION_ENABLE = 1
}

struct tbl_property_value_args_t
{
  1: required tbl_property_value_t value;
  2: required i32                  scope_args;
}

enum pvs_gress_t
{
   PVS_GRESS_INGRESS = 0,
   PVS_GRESS_EGRESS = 1,
   PVS_GRESS_ALL = 0xff
}

enum pvs_property_t {
  PVS_PROP_NONE = 0,
  PVS_GRESS_SCOPE,
  PVS_PIPE_SCOPE,
  PVS_PARSER_SCOPE
}

enum pvs_property_value_t {
  PVS_SCOPE_ALL_GRESS = 0,
  PVS_SCOPE_SINGLE_GRESS = 1,
  PVS_SCOPE_ALL_PIPELINES = 0,
  PVS_SCOPE_SINGLE_PIPELINE = 1,
  PVS_SCOPE_ALL_PARSERS = 0,
  PVS_SCOPE_SINGLE_PARSER = 1
}  

enum tbl_dbg_counter_type_t {
  TBL_DBG_CNTR_DISABLED = 0,
  TBL_DBG_CNTR_LOG_TBL_MISS,
  TBL_DBG_CNTR_LOG_TBL_HIT,
  TBL_DBG_CNTR_GW_TBL_MISS,
  TBL_DBG_CNTR_GW_TBL_HIT,
  TBL_DBG_CNTR_GW_TBL_INHIBIT,
  TBL_DBG_CNTR_MAX
}

struct PVSSpec_t {
  1: required i32 parser_value;
  2: required i32 parser_value_mask;
}

struct TblCntrInfo_t {
  1: required tbl_dbg_counter_type_t type;
  2: required i32 value;
}

struct TblDbgStageInfo_t {
  1: required i32 num_counters;
  2: required list<string> tbl_name;
  3: required list<tbl_dbg_counter_type_t> type;
  4: required list<i32> value;
}

# not very space efficient but convenient
struct main_counter_flags_t {
  1: required bool read_hw_sync;
}

struct main_register_flags_t {
  1: required bool read_hw_sync;
}

struct main_snapshot_trig_spec_t {
  1: required string field_name;
  2: required i64 field_value;
  3: required i64 field_mask;
}

struct main_snapshot_tbl_data_t {
  1: required bool hit;
  2: required bool inhibited;
  3: required bool executed;
  4: required i32 hit_entry_handle;
}


enum main_input_field_attr_type_t {
  INPUT_FIELD_ATTR_TYPE_MASK,
  INPUT_FIELD_ATTR_TYPE_VALUE
}

enum main_input_field_attr_value_mask_t {
  INPUT_FIELD_EXCLUDED = 0,
  INPUT_FIELD_INCLUDED
}



# Match structs

struct main_firewall_table_match_spec_t {
  1: required i32 ipv4_srcAddr;
  2: required i32 ipv4_dstAddr;
  3: required i16 tcp_udp_srcPort;
  4: required i16 tcp_udp_dstPort;
}

struct main_forward_table_match_spec_t {
  1: required i16 ig_intr_md_ingress_port;
}

struct main_forward_table_by_dst_ip_match_spec_t {
  1: required i32 ipv4_dstAddr;
}

struct main_state_check_table_match_spec_t {
  1: required i32 ipv4_srcAddr;
  2: required i32 ipv4_dstAddr;
  3: required i16 tcp_udp_srcPort;
  4: required i16 tcp_udp_dstPort;
  5: required byte tcp_ack;
  6: required byte tcp_rst;
  7: required byte tcp_syn;
  8: required byte tcp_fin;
}


# Match struct for Dynamic Key Mask Exm Table.


# Action structs

struct main_forward_hit_action_spec_t {
  1: required i16 action_port;
}

struct main_forward_ip_hit_action_spec_t {
  1: required i16 action_port;
}

union main_action_specs_t {
  1: main_forward_hit_action_spec_t main_forward_hit;
  2: main_forward_ip_hit_action_spec_t main_forward_ip_hit;
}

struct main_action_desc_t {
  1: required string name;
  2: required main_action_specs_t data;
}


# Register values


# Entry Descriptions

struct main_firewall_table_entry_desc_t {
  1: required main_firewall_table_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_forward_table_entry_desc_t {
  1: required main_forward_table_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_forward_table_by_dst_ip_entry_desc_t {
  1: required main_forward_table_by_dst_ip_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_state_check_table_entry_desc_t {
  1: required main_state_check_table_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}




exception InvalidTableOperation {
 1:i32 code
}

exception InvalidLearnOperation {
 1:i32 code
}

exception InvalidDbgOperation {
 1:i32 code
}

exception InvalidSnapshotOperation {
 1:i32 code
}

exception InvalidCounterOperation {
 1:i32 code
}

exception InvalidRegisterOperation {
 1:i32 code
}

exception InvalidMeterOperation {
 1:i32 code
}

exception InvalidLPFOperation {
 1:i32 code
}

exception InvalidWREDOperation {
 1:i32 code
}


service main {

    # Idle time config



    EntryHandle_t firewall_table_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_firewall_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_by_dst_ip_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_by_dst_ip_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t state_check_table_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),


    # Dynamic Key Mask Exm Table.
      # set API

    # Table entry add functions

    EntryHandle_t firewall_table_table_add_with_firewall_allow_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_firewall_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t firewall_table_table_add_with_firewall_drop_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_firewall_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_table_add_with_forward_hit(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_match_spec_t match_spec, 4:main_forward_hit_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_table_add_with_forward_miss(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_by_dst_ip_table_add_with_forward_ip_hit(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_by_dst_ip_match_spec_t match_spec, 4:main_forward_ip_hit_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_by_dst_ip_table_add_with_forward_ip_miss(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_by_dst_ip_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t state_check_table_table_add_with_state_check_allow_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t state_check_table_table_add_with_state_check_to_controller_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t state_check_table_table_add_with_state_check_drop_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),

    # Table entry modify functions
    void firewall_table_table_modify_with_firewall_allow_action(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void firewall_table_table_modify_with_firewall_allow_action_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_firewall_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void firewall_table_table_modify_with_firewall_drop_action(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void firewall_table_table_modify_with_firewall_drop_action_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_firewall_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void forward_table_table_modify_with_forward_hit(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_forward_hit_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void forward_table_table_modify_with_forward_hit_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_match_spec_t match_spec, 4:main_forward_hit_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void forward_table_table_modify_with_forward_miss(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void forward_table_table_modify_with_forward_miss_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void forward_table_by_dst_ip_table_modify_with_forward_ip_hit(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_forward_ip_hit_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void forward_table_by_dst_ip_table_modify_with_forward_ip_hit_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_by_dst_ip_match_spec_t match_spec, 4:main_forward_ip_hit_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void forward_table_by_dst_ip_table_modify_with_forward_ip_miss(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void forward_table_by_dst_ip_table_modify_with_forward_ip_miss_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_by_dst_ip_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_modify_with_state_check_allow_action(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_modify_with_state_check_allow_action_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_modify_with_state_check_to_controller_action(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_modify_with_state_check_to_controller_action_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_modify_with_state_check_drop_action(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_modify_with_state_check_drop_action_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),

    # Table entry delete functions
# //::   if action_table_hdl: continue
    void firewall_table_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void firewall_table_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_firewall_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void forward_table_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void forward_table_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void forward_table_by_dst_ip_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void forward_table_by_dst_ip_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_forward_table_by_dst_ip_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void state_check_table_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void state_check_table_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_state_check_table_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),

    # Table default entry get functions
    EntryHandle_t firewall_table_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_firewall_table_entry_desc_t firewall_table_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_forward_table_entry_desc_t forward_table_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_by_dst_ip_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_forward_table_by_dst_ip_entry_desc_t forward_table_by_dst_ip_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t state_check_table_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_state_check_table_entry_desc_t state_check_table_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    # Table default entry clear functions
# //::   if action_table_hdl: continue
    void firewall_table_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void forward_table_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void forward_table_by_dst_ip_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void state_check_table_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    i32 firewall_table_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 forward_table_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 forward_table_by_dst_ip_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 state_check_table_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),


    # Get first entry handle functions
    i32 firewall_table_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<i32> firewall_table_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_firewall_table_entry_desc_t firewall_table_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    i32 forward_table_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<i32> forward_table_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_forward_table_entry_desc_t forward_table_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    i32 forward_table_by_dst_ip_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<i32> forward_table_by_dst_ip_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_forward_table_by_dst_ip_entry_desc_t forward_table_by_dst_ip_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    i32 state_check_table_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<i32> state_check_table_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_state_check_table_entry_desc_t state_check_table_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),



    # Table set default action functions

    EntryHandle_t firewall_table_set_default_action_firewall_drop_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_set_default_action_forward_miss(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t forward_table_by_dst_ip_set_default_action_forward_ip_miss(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t state_check_table_set_default_action_state_check_drop_action(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    
     # Table set/get property
# //::   if action_table_hdl: continue
    void firewall_table_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t firewall_table_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void forward_table_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t forward_table_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void forward_table_by_dst_ip_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t forward_table_by_dst_ip_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void state_check_table_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t state_check_table_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),

    # INDIRECT ACTION DATA AND MATCH SELECT






    void set_learning_timeout(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 usecs) throws (1:InvalidLearnOperation ouch),

    void tbl_dbg_counter_type_set(1:res.DevTarget_t dev_tgt, 2:string tbl_name, 3:tbl_dbg_counter_type_t type) throws (1:InvalidDbgOperation ouch),

    TblCntrInfo_t tbl_dbg_counter_get(1:res.DevTarget_t dev_tgt, 2:string tbl_name) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_clear(1:res.DevTarget_t dev_tgt, 2:string tbl_name) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_type_stage_set(1:res.DevTarget_t dev_tgt, 2:byte stage, 3:tbl_dbg_counter_type_t type) throws (1:InvalidDbgOperation ouch),

    TblDbgStageInfo_t tbl_dbg_counter_stage_get(1:res.DevTarget_t dev_tgt, 2:byte stage) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_stage_clear(1:res.DevTarget_t dev_tgt, 2: byte stage) throws (1:InvalidDbgOperation ouch),

    SnapshotHandle_t snapshot_create(1:res.DevTarget_t dev_tgt, 2:byte start_stage, 3:byte end_stage, 4:byte direction) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_delete(1:SnapshotHandle_t handle) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_state_set(1: SnapshotHandle_t handle, 2:i32 state, 3:i32 usecs) throws (1:InvalidSnapshotOperation ouch),

    i32 snapshot_state_get(1:SnapshotHandle_t handle, 2:i16 pipe) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_timer_enable(1: SnapshotHandle_t handle, 2:byte disable) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_capture_trigger_set(1: SnapshotHandle_t handle,
                2:main_snapshot_trig_spec_t trig_spec,
                3:main_snapshot_trig_spec_t trig_spec2) throws (1:InvalidSnapshotOperation ouch),

    i64 snapshot_capture_data_get(1: SnapshotHandle_t handle, 2:i16 pipe, 3:i16 stage_id, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    main_snapshot_tbl_data_t snapshot_capture_tbl_data_get(1: SnapshotHandle_t handle, 2:i16 pipe, 3:string table_name) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_capture_trigger_fields_clr(1:SnapshotHandle_t handle) throws (1:InvalidSnapshotOperation ouch),

    bool snapshot_field_in_scope(1:res.DevTarget_t dev_tgt, 2:byte stage,
                 3:byte direction, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    # counters



    # registers









} 
