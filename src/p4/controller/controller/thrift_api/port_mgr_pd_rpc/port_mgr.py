#
# Autogenerated by Thrift Compiler (0.14.1)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py:package_prefix=controller.thrift_api.
#

from thrift.Thrift import TType, TMessageType, TFrozenDict, TException, TApplicationException
from thrift.protocol.TProtocol import TProtocolException
from thrift.TRecursive import fix_spec

import sys
import logging
from .ttypes import *
from thrift.Thrift import TProcessor
from thrift.transport import TTransport
all_structs = []


class Iface(object):
    def port_mgr_mtu_set(self, dev_id, port_id, tx_mtu, rx_mtu):
        """
        Parameters:
         - dev_id
         - port_id
         - tx_mtu
         - rx_mtu

        """
        pass


class Client(Iface):
    def __init__(self, iprot, oprot=None):
        self._iprot = self._oprot = iprot
        if oprot is not None:
            self._oprot = oprot
        self._seqid = 0

    def port_mgr_mtu_set(self, dev_id, port_id, tx_mtu, rx_mtu):
        """
        Parameters:
         - dev_id
         - port_id
         - tx_mtu
         - rx_mtu

        """
        self.send_port_mgr_mtu_set(dev_id, port_id, tx_mtu, rx_mtu)
        self.recv_port_mgr_mtu_set()

    def send_port_mgr_mtu_set(self, dev_id, port_id, tx_mtu, rx_mtu):
        self._oprot.writeMessageBegin('port_mgr_mtu_set', TMessageType.CALL, self._seqid)
        args = port_mgr_mtu_set_args()
        args.dev_id = dev_id
        args.port_id = port_id
        args.tx_mtu = tx_mtu
        args.rx_mtu = rx_mtu
        args.write(self._oprot)
        self._oprot.writeMessageEnd()
        self._oprot.trans.flush()

    def recv_port_mgr_mtu_set(self):
        iprot = self._iprot
        (fname, mtype, rseqid) = iprot.readMessageBegin()
        if mtype == TMessageType.EXCEPTION:
            x = TApplicationException()
            x.read(iprot)
            iprot.readMessageEnd()
            raise x
        result = port_mgr_mtu_set_result()
        result.read(iprot)
        iprot.readMessageEnd()
        if result.ouch is not None:
            raise result.ouch
        return


class Processor(Iface, TProcessor):
    def __init__(self, handler):
        self._handler = handler
        self._processMap = {}
        self._processMap["port_mgr_mtu_set"] = Processor.process_port_mgr_mtu_set
        self._on_message_begin = None

    def on_message_begin(self, func):
        self._on_message_begin = func

    def process(self, iprot, oprot):
        (name, type, seqid) = iprot.readMessageBegin()
        if self._on_message_begin:
            self._on_message_begin(name, type, seqid)
        if name not in self._processMap:
            iprot.skip(TType.STRUCT)
            iprot.readMessageEnd()
            x = TApplicationException(TApplicationException.UNKNOWN_METHOD, 'Unknown function %s' % (name))
            oprot.writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
            x.write(oprot)
            oprot.writeMessageEnd()
            oprot.trans.flush()
            return
        else:
            self._processMap[name](self, seqid, iprot, oprot)
        return True

    def process_port_mgr_mtu_set(self, seqid, iprot, oprot):
        args = port_mgr_mtu_set_args()
        args.read(iprot)
        iprot.readMessageEnd()
        result = port_mgr_mtu_set_result()
        try:
            self._handler.port_mgr_mtu_set(args.dev_id, args.port_id, args.tx_mtu, args.rx_mtu)
            msg_type = TMessageType.REPLY
        except TTransport.TTransportException:
            raise
        except InvalidPortMgrOperation as ouch:
            msg_type = TMessageType.REPLY
            result.ouch = ouch
        except TApplicationException as ex:
            logging.exception('TApplication exception in handler')
            msg_type = TMessageType.EXCEPTION
            result = ex
        except Exception:
            logging.exception('Unexpected exception in handler')
            msg_type = TMessageType.EXCEPTION
            result = TApplicationException(TApplicationException.INTERNAL_ERROR, 'Internal error')
        oprot.writeMessageBegin("port_mgr_mtu_set", msg_type, seqid)
        result.write(oprot)
        oprot.writeMessageEnd()
        oprot.trans.flush()

# HELPER FUNCTIONS AND STRUCTURES


class port_mgr_mtu_set_args(object):
    """
    Attributes:
     - dev_id
     - port_id
     - tx_mtu
     - rx_mtu

    """


    def __init__(self, dev_id=None, port_id=None, tx_mtu=None, rx_mtu=None,):
        self.dev_id = dev_id
        self.port_id = port_id
        self.tx_mtu = tx_mtu
        self.rx_mtu = rx_mtu

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    self.dev_id = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.port_id = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.tx_mtu = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.I32:
                    self.rx_mtu = iprot.readI32()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('port_mgr_mtu_set_args')
        if self.dev_id is not None:
            oprot.writeFieldBegin('dev_id', TType.I32, 1)
            oprot.writeI32(self.dev_id)
            oprot.writeFieldEnd()
        if self.port_id is not None:
            oprot.writeFieldBegin('port_id', TType.I32, 2)
            oprot.writeI32(self.port_id)
            oprot.writeFieldEnd()
        if self.tx_mtu is not None:
            oprot.writeFieldBegin('tx_mtu', TType.I32, 3)
            oprot.writeI32(self.tx_mtu)
            oprot.writeFieldEnd()
        if self.rx_mtu is not None:
            oprot.writeFieldBegin('rx_mtu', TType.I32, 4)
            oprot.writeI32(self.rx_mtu)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
all_structs.append(port_mgr_mtu_set_args)
port_mgr_mtu_set_args.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'dev_id', None, None, ),  # 1
    (2, TType.I32, 'port_id', None, None, ),  # 2
    (3, TType.I32, 'tx_mtu', None, None, ),  # 3
    (4, TType.I32, 'rx_mtu', None, None, ),  # 4
)


class port_mgr_mtu_set_result(object):
    """
    Attributes:
     - ouch

    """


    def __init__(self, ouch=None,):
        self.ouch = ouch

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.STRUCT:
                    self.ouch = InvalidPortMgrOperation.read(iprot)
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('port_mgr_mtu_set_result')
        if self.ouch is not None:
            oprot.writeFieldBegin('ouch', TType.STRUCT, 1)
            self.ouch.write(oprot)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
all_structs.append(port_mgr_mtu_set_result)
port_mgr_mtu_set_result.thrift_spec = (
    None,  # 0
    (1, TType.STRUCT, 'ouch', [InvalidPortMgrOperation, None], None, ),  # 1
)
fix_spec(all_structs)
del all_structs
