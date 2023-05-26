import logging

from thrift.protocol import TBinaryProtocol, TMultiplexedProtocol
from thrift.transport import TSocket, TTransport

import config

logger = logging.getLogger(__name__)


class ThriftWrapperException(Exception):
    pass


class ThriftWrapper:
    """
    Wrapper class to encapsulate the Thrift multiplexed protocol
    """
    def __init__(self):
        self._transport = None
        self._protocol = None

    def connect(self, thrift_client=None):
        if thrift_client is None:
            socket = TSocket.TSocket(config.THRIFT_HOST, config.THRIFT_PORT)
            self._transport = TTransport.TBufferedTransport(socket)
            self._transport.open()
            self._protocol = TBinaryProtocol.TBinaryProtocol(self._transport)

        elif self._transport is not None:
            name = thrift_client.__name__.split('.')[-1]
            multiplex_protocol = TMultiplexedProtocol.TMultiplexedProtocol(self._protocol, name)
            return thrift_client.Client(multiplex_protocol)

        else:
            raise ThriftWrapperException("Thrift client not connected")

    def disconnect(self):
        self._transport.close()
        self._transport = None
