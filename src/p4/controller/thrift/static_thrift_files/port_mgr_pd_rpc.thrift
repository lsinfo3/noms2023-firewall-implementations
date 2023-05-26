include "res.thrift"

namespace py port_mgr_pd_rpc
namespace cpp port_mgr_pd_rpc
namespace c_glib port_mgr_pd_rpc

exception InvalidPortMgrOperation {
  1:i32 code
}

service port_mgr {
  # Port Mgr APIs
  void port_mgr_mtu_set(1: i32 dev_id, 2: i32 port_id, 3: i32 tx_mtu, 4: i32 rx_mtu) throws (1:InvalidPortMgrOperation ouch);
}
