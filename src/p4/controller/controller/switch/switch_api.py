import atexit
import collections
import functools
import logging
import threading
from contextlib import contextmanager

from .port_manager import PortManager
from .tcp_utils import SwitchTcpMatch
from .thrift_wrapper import ThriftWrapper
from .util import i16, i32, ipv42int
from ..thrift_api.conn_mgr_pd_rpc import conn_mgr
from ..thrift_api.p4_pd_rpc import main, ttypes
from ..thrift_api.res_pd_rpc.ttypes import DevTarget_t
from ..thrift_api.tm_api_rpc import tm
from ..util import FiveTuple

logger = logging.getLogger(__name__)

RegSelect = collections.namedtuple("SingleRange", ('single', 'range', 'write', 'clear_all'))

# Global switch API lock
LOCK = threading.RLock()


def _with_lock(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        with LOCK:
            return func(*args, **kwargs)

    return wrapper


class SwitchException(Exception):
    pass


class SwitchAPI:
    MAX_PACKET_LEN = 1500  # Maximum supported MTU

    client: main.Iface

    def __init__(self):

        self.hw_sync_flag = ttypes.main_register_flags_t(read_hw_sync=True)
        self.all_pipes = DevTarget_t(0, i16(0xFFFF))

        # Identifiers for every single pipe.
        self.pipes = [
            DevTarget_t(0, i16(0)),
            DevTarget_t(0, i16(1)),
            DevTarget_t(0, i16(2)),
            DevTarget_t(0, i16(3)),
        ]

        self.client = main.Iface()
        self.conn_manager = conn_mgr.Iface()
        self.traffic_manager = tm.Iface()
        self.thrift = ThriftWrapper()
        self.port_manager = PortManager(self.thrift)

        self.sess_hdl = None

        self._already_batching = False

    def connect(self):
        logger.debug("Connecting to Thrift services")
        self.thrift.connect()
        self.client = self.thrift.connect(main)
        self.conn_manager = self.thrift.connect(conn_mgr)
        self.traffic_manager = self.thrift.connect(tm)
        self.port_manager.connect()

        self.sess_hdl = self.conn_manager.client_init()
        atexit.register(self.disconnect)

        self.traffic_manager: tm.Iface
        self.traffic_manager.tm_set_cpuport(0, 320)

    def disconnect(self):
        logger.debug("Disconnecting from thrift")
        atexit.unregister(self.disconnect)

        if self._already_batching:
            self.conn_manager.end_batch(self.sess_hdl, False)

        self.conn_manager.client_cleanup(self.sess_hdl)
        self.sess_hdl = None
        self.thrift.disconnect()

    @contextmanager
    def batch(self, hw_sync: bool = True):
        """
        A contextmanager to batch multiple API calls. Can be nested
        """
        with LOCK:
            if self._already_batching:
                yield
            else:
                try:
                    self._already_batching = True
                    self.conn_manager.begin_batch(self.sess_hdl)
                    yield
                    self.conn_manager.end_batch(self.sess_hdl, hw_sync)
                    self.conn_manager.complete_operations(self.sess_hdl)
                finally:
                    self._already_batching = False

    @_with_lock
    def _clear_table(self, table: str, symmetric: bool = True):
        """
        Helper function to clear a data plane table
        """
        if symmetric:
            pipes = [self.all_pipes]
        else:
            pipes = self.pipes

        for pipe in pipes:
            count = getattr(self.client, f'{table}_get_entry_count')(self.sess_hdl, pipe)
            if count == 0:
                return

            entries = [
                getattr(self.client, f'{table}_get_first_entry_handle')(self.sess_hdl, pipe)
            ]

            if count > 1:
                entries.extend(
                    getattr(self.client, f'{table}_get_next_entry_handles')(
                        self.sess_hdl,
                        pipe,
                        entries[0], count - 1
                    )
                )

            for entry in entries:
                with self.batch(True):
                    getattr(self.client, f'{table}_table_delete')(self.sess_hdl, 0, entry)
            getattr(self.client, f'{table}_table_reset_default_entry')(self.sess_hdl, pipe)

    def clear_forward_ip_table(self):
        self._clear_table('forward_table_by_dst_ip')

    def clear_forward_table(self):
        self._clear_table('forward_table')

    def clear_firewall_table(self):
        self._clear_table('firewall_table')

    def clear_stateful_firewall_table(self):
        self._clear_table('state_check_table')

    @_with_lock
    def insert_forward_entry(self, src_port: int, dst_port: int):
        src_port = self.port_manager.get_clean_port(src_port)
        dst_port = self.port_manager.get_clean_port(dst_port)
        logger.debug("Adding forward entry from port %d to port %d", src_port, dst_port)

        self.client.forward_table_table_add_with_forward_hit(
            self.sess_hdl, self.all_pipes,
            ttypes.main_forward_table_match_spec_t(i16(src_port)),
            ttypes.main_forward_hit_action_spec_t(i16(dst_port))
        )
        return src_port, dst_port

    @_with_lock
    def insert_forward_ip_entry(self, dst_ip: str, dst_port: int):
        dst_port = self.port_manager.get_clean_port(dst_port)
        logger.debug("Adding forward entry from ip %s to port %d", dst_ip, dst_port)

        self.client.forward_table_by_dst_ip_table_add_with_forward_ip_hit(
            self.sess_hdl, self.all_pipes,
            ttypes.main_forward_table_by_dst_ip_match_spec_t(i32(ipv42int(dst_ip))),
            ttypes.main_forward_ip_hit_action_spec_t(i16(dst_port))
        )

    @_with_lock
    def insert_firewall_entry(self, five_tuple: FiveTuple) -> None:
        self.client.firewall_table_table_add_with_firewall_allow_action(
            self.sess_hdl, self.all_pipes,
            ttypes.main_firewall_table_match_spec_t(i32(ipv42int(five_tuple.src_ip)),
                                                    i32(ipv42int(five_tuple.dst_ip)),
                                                    i16(five_tuple.sport),
                                                    i16(five_tuple.dport))
        )

    @_with_lock
    def remove_stateful_entries(self, five_tuple: FiveTuple, tcp_match: SwitchTcpMatch):
        self.client.state_check_table_table_delete_by_match_spec(
            self.sess_hdl, self.all_pipes,
            ttypes.main_state_check_table_match_spec_t(i32(ipv42int(five_tuple.src_ip)),
                                                       i32(ipv42int(five_tuple.dst_ip)),
                                                       i16(five_tuple.sport),
                                                       i16(five_tuple.dport),
                                                       int(tcp_match.ack),
                                                       int(tcp_match.rst),
                                                       int(tcp_match.syn),
                                                       int(tcp_match.fin))
            )

    @_with_lock
    def insert_stateful_entry_to_controller(self, five_tuple: FiveTuple, tcp_match: SwitchTcpMatch) -> None:
        self.client.state_check_table_table_add_with_state_check_to_controller_action(
            self.sess_hdl, self.all_pipes,
            ttypes.main_state_check_table_match_spec_t(i32(ipv42int(five_tuple.src_ip)),
                                                       i32(ipv42int(five_tuple.dst_ip)),
                                                       i16(five_tuple.sport),
                                                       i16(five_tuple.dport),
                                                       int(tcp_match.ack),
                                                       int(tcp_match.rst),
                                                       int(tcp_match.syn),
                                                       int(tcp_match.fin))
        )

    @_with_lock
    def insert_stateful_entry_forward(self, five_tuple: FiveTuple, tcp_match: SwitchTcpMatch) -> None:
        self.client.state_check_table_table_add_with_state_check_allow_action(
            self.sess_hdl, self.all_pipes,
            ttypes.main_state_check_table_match_spec_t(i32(ipv42int(five_tuple.src_ip)),
                                                       i32(ipv42int(five_tuple.dst_ip)),
                                                       i16(five_tuple.sport),
                                                       i16(five_tuple.dport),
                                                       int(tcp_match.ack),
                                                       int(tcp_match.rst),
                                                       int(tcp_match.syn),
                                                       int(tcp_match.fin))
        )
