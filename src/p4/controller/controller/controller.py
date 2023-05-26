import logging
import threading
import time
import typing

from scapy.layers.inet import IP, TCP, UDP
from scapy.layers.inet6 import IPv6
from scapy.layers.l2 import Ether
from scapy.sendrecv import sniff
import scapy.config as scapy_conf

import config
from .switch.stateful_firewall import StatefulFirewall
from .switch.switch_api import SwitchAPI
from .switch.tcp_utils import tcp_flags_from_str
from .util import FiveTuple, FlowType, L4Proto, Packet

logger = logging.getLogger(__name__)


class Controller:
    _ROUTING_TABLE = {}

    def __init__(self):
        # 2gb buffer
        scapy_conf.conf.bufsize = 2**21
        scapy_conf.conf.layers.filter([IP, TCP])
        self.send_socket = scapy_conf.conf.L2socket(iface=config.CONTROLLER_INTERFACE)
        self.switch = SwitchAPI()
        self.stateful_firewall = StatefulFirewall(self.switch)
        self.running = True
        self.last_age = time.monotonic()
        self.lock = threading.RLock()

    def connect(self):
        self.switch.connect()
        self.clear()
        # self.switch.init_tables()
        self.add_ports_from_config()
        self.add_firewall_five_tuples()

    def clear(self):
        logger.info("Clearing ports")
        self.switch.port_manager.clear_ports()
        logger.info("Clearing forward table")
        self.switch.clear_forward_table()
        logger.info("Clearing forward ip table")
        self.switch.clear_forward_ip_table()
        logger.info("Clearing firewall table")
        self.switch.clear_firewall_table()
        logger.info("Clearing state check table")
        self.switch.clear_stateful_firewall_table()

    def add_ports_from_config(self):
        for port, speed, fec in config.PORTS:
            self.switch.port_manager.add_enable_port(port, speed, fec)

        self._ROUTING_TABLE = {}
        for src_port, dst_port in config.ROUTING:
            src_port, dst_port = self.switch.insert_forward_entry(src_port, dst_port)
            self._ROUTING_TABLE[src_port] = dst_port

    def add_firewall_five_tuples(self):
        logger.info("Adding firewall FiveTuples")
        firewall_rules = config.load_firewall_config()

        if len(firewall_rules) == 0:
            logger.warning("rules.csv seems to be empty. This will fail.")
            return

        # CAREFUL this is a hack because only two ips are used
        dir1_dst_port = config.ROUTING[0][1]
        dir2_dst_port = config.ROUTING[1][1]
        used_tuple = firewall_rules[0]
        self.switch.insert_forward_ip_entry(used_tuple.src_ip, dir1_dst_port)
        self.switch.insert_forward_ip_entry(used_tuple.dst_ip, dir2_dst_port)

        with self.switch.batch(True):
            for five_tuple in firewall_rules:
                self.switch.insert_firewall_entry(five_tuple)
                self.stateful_firewall.add(five_tuple)

    def get_forward_port(self, dev_port: int) -> int:
        return self._ROUTING_TABLE[dev_port]

    @staticmethod
    def get_five_tuple(l3: typing.Union[IP, IPv6], l4: typing.Union[TCP, UDP]):
        return FiveTuple(
            src_ip=l3.src,
            dst_ip=l3.dst,
            sport=l4.sport,
            dport=l4.dport,
            protocol=L4Proto.TCP if isinstance(l4, TCP) else L4Proto.UDP,
        )

    def process(self, packet: Ether):
        start = time.monotonic()
        if logger.isEnabledFor(logging.DEBUG):
            logger.debug("Processing packet\n%s", packet.summary())

        #if not packet.haslayer(IP):
        #    logger.warning("Packet has not IPv4")
        #    return
        #if packet.haslayer(IPv6):
        #    logger.warning("IPv6 received but not enabled")
        #    return

        ip = packet.getlayer(IP)

        #if not packet.haslayer(TCP):
        #    logger.warning("Packet does not contain TCP:\n%s", packet.summary())
        #    return

        tcp = packet.getlayer(TCP)

        logger.debug(f"Current tcp flags: {tcp.flags}")

        self.stateful_firewall.process(self.get_five_tuple(ip, tcp), tcp_flags_from_str(tcp.flags))

        self._finish(start)

        # send packet back to dataplane, to forward without processing
        self.send_socket.send(packet)
        # this seems to open a socket for every send
        # sendp(packet, iface=config.CONTROLLER_INTERFACE, verbose=False)
        return

    def _finish(self, start):
        """
        Log timings when a packet has been processed
        """
        if logger.isEnabledFor(logging.DEBUG):
            logger.debug("Packet processing time: %f", time.monotonic() - start)

    def start(self):
        logger.info("Listening on %s", config.CONTROLLER_INTERFACE)

        # Start sniffing, only stops on SIGINT or SIGTERM
        sniff(iface=config.CONTROLLER_INTERFACE, filter="inbound && ip && tcp", store=False, quiet=True, prn=self.process)

        self.running = False
        self.switch.disconnect()
