import functools
import logging
import typing

from .thrift_wrapper import ThriftWrapper
from .util import i32, to_pipe_port, u32
from ..thrift_api.pal_rpc import pal, ttypes

logger = logging.getLogger(__name__)
PortType = typing.Union[tuple, list, int]


class PortManager:
    """
    Wrapper for easy switch port manipulation and querying
    """
    PORT_SPEEDS = {
        10: ttypes.pal_port_speed_t.BF_SPEED_10G,
        25: ttypes.pal_port_speed_t.BF_SPEED_25G,
        40: ttypes.pal_port_speed_t.BF_SPEED_40G,
        100: ttypes.pal_port_speed_t.BF_SPEED_100G,
    }
    PORT_FEC = {
        'FC': ttypes.pal_fec_type_t.BF_FEC_TYP_FIRECODE,
        'RS': ttypes.pal_fec_type_t.BF_FEC_TYP_REED_SOLOMON,
        'None': ttypes.pal_fec_type_t.BF_FEC_TYP_NONE,
        None: ttypes.pal_fec_type_t.BF_FEC_TYP_NONE,
    }

    client: pal.Iface

    def __init__(self, thrift: ThriftWrapper):
        self.thrift = thrift
        self.client = pal.Iface()

    def connect(self):
        self.client = self.thrift.connect(pal)

    def get_clean_port(self, port: PortType) -> int:
        """
        port: [int, int] => front device port, lane
        port: int => devport

        converts the first port representation into the devport repr.
        checks if port is internal and raises ValueError if it is the case.
        """
        if isinstance(port, (tuple, list)) and len(port) == 2:
            port, lane = port
            dev_port = self.front_panel_to_dev_port(port, lane)
        elif isinstance(port, int):
            dev_port = port
        else:
            raise ValueError(f"{port} is not a valid port description")

        if self.client.pal_is_port_internal(0, dev_port):
            raise ValueError(f"{port} describes an internal port, cannot configure")

        return dev_port

    def add_port(self, port: PortType, speed: int, fec: str):
        """
        Add a port the switch, equivalent to `ucli pm port-add` on the console
        """
        dev_port = self.get_clean_port(port)
        logger.debug("Adding port %d", port)
        self.client.pal_port_add(
            0, dev_port,
            self.PORT_SPEEDS[speed],
            self.PORT_FEC[fec],
        )

    def enable_port(self, port: PortType):
        """
        Enable a port, equivalent to `ucli pm port-enb` on the console
        """
        logger.debug("Enabling port %d", port)
        dev_port = self.get_clean_port(port)
        self.client.pal_port_enable(0, dev_port)

    def add_enable_port(self, port: PortType, speed: int, fec: str):
        """
        Shortcut for add_port, enable_port
        """
        dev_port = self.get_clean_port(port)
        self.add_port(dev_port, speed, fec)
        self.enable_port(dev_port)

    def clear_ports(self):
        """
        Disable and remove all ports
        """
        self.client.pal_port_del_all(0)

    @functools.lru_cache(maxsize=512)
    def front_panel_to_dev_port(self, port: int, lane: int) -> int:
        """
        Convert a (front port, lane) port description into the internal devport one
        """
        logger.debug("Translating %d/%d to dev_port", port, lane)
        dev_port = u32(self.client.pal_port_front_panel_port_to_dev_port_get(
            0, i32(port), i32(lane)
        ))
        logger.debug("Dev_port of %d/%d is %d on pipe %d/%d",
                     port, lane, dev_port, *to_pipe_port(dev_port))
        return dev_port
