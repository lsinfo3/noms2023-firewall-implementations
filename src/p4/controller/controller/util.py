import enum
import json
import socket
import typing

from scapy.layers.inet import IP, TCP, UDP
from scapy.layers.inet6 import IPv6

from controller.switch.util import ipv42int


class L4Proto(enum.Enum):
    TCP = enum.auto()
    UDP = enum.auto()


class L3Proto(enum.Enum):
    IPv4 = socket.AF_INET
    IPv6 = socket.AF_INET6


class FlowType(enum.Enum):
    UNKNOWN = enum.auto()
    GENERIC_TCP = enum.auto()
    GENERIC_UDP = enum.auto()
    DNS = enum.auto()


class ExtendedJSONEncoder(json.JSONEncoder):
    def default(self, o):
        if o == L3Proto.IPv6:
            return "IPv6"
        elif o == L3Proto.IPv4:
            return "IPv4"
        elif o == L4Proto.TCP:
            return "TCP"
        elif o == L4Proto.UDP:
            return "UDP"
        else:
            return super().default(o)


class FiveTuple(typing.NamedTuple):
    src_ip: str
    dst_ip: str
    sport: int
    dport: int
    protocol: L4Proto

    def __str__(self):
        return f"{self.src_ip}:{self.sport} - {self.dst_ip}:{self.dport} " \
               f"{'TCP' if self.protocol == L4Proto.TCP else 'UDP'}"

    def direction_independent_hash(self) -> int:
        """
        Hash a five tuple, so a reversed direction five tuple has the same hash value
        """
        ip1 = ipv42int(self.src_ip)
        ip2 = ipv42int(self.dst_ip)
        return hash((ip1, ip2, self.sport, self.dport)) if self.is_original_direction() else hash((ip2, ip1, self.dport, self.sport))

    def is_original_direction(self) -> bool:
        return self.src_ip > self.dst_ip


class Packet(typing.NamedTuple):
    five_tuple: FiveTuple
    l3: typing.Union[IP, IPv6]
    l4: typing.Union[TCP, UDP]

    def __str__(self):
        return str(self.five_tuple)


def reverse_five_tuple(five_tuple: FiveTuple) -> FiveTuple:
    return FiveTuple(
        src_ip=five_tuple.dst_ip,
        dst_ip=five_tuple.src_ip,
        sport=five_tuple.dport,
        dport=five_tuple.sport,
        protocol=five_tuple.protocol,
    )
