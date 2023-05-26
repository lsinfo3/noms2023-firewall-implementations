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
import controller.thrift_api.res_pd_rpc.ttypes

from thrift.transport import TTransport
all_structs = []


class pkt_pkt_data(object):
    """
    Attributes:
     - rx_ring
     - size
     - buf

    """


    def __init__(self, rx_ring=None, size=None, buf=None,):
        self.rx_ring = rx_ring
        self.size = size
        self.buf = buf

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
                    self.rx_ring = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.size = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.STRING:
                    self.buf = iprot.readBinary()
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
        oprot.writeStructBegin('pkt_pkt_data')
        if self.rx_ring is not None:
            oprot.writeFieldBegin('rx_ring', TType.I32, 1)
            oprot.writeI32(self.rx_ring)
            oprot.writeFieldEnd()
        if self.size is not None:
            oprot.writeFieldBegin('size', TType.I32, 2)
            oprot.writeI32(self.size)
            oprot.writeFieldEnd()
        if self.buf is not None:
            oprot.writeFieldBegin('buf', TType.STRING, 3)
            oprot.writeBinary(self.buf)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        if self.rx_ring is None:
            raise TProtocolException(message='Required field rx_ring is unset!')
        if self.size is None:
            raise TProtocolException(message='Required field size is unset!')
        if self.buf is None:
            raise TProtocolException(message='Required field buf is unset!')
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class InvalidPktOperation(TException):
    """
    Attributes:
     - code

    """


    def __init__(self, code=None,):
        super(InvalidPktOperation, self).__setattr__('code', code)

    def __setattr__(self, *args):
        raise TypeError("can't modify immutable instance")

    def __delattr__(self, *args):
        raise TypeError("can't modify immutable instance")

    def __hash__(self):
        return hash(self.__class__) ^ hash((self.code, ))

    @classmethod
    def read(cls, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and cls.thrift_spec is not None:
            return iprot._fast_decode(None, iprot, [cls, cls.thrift_spec])
        iprot.readStructBegin()
        code = None
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    code = iprot.readI32()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()
        return cls(
            code=code,
        )

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('InvalidPktOperation')
        if self.code is not None:
            oprot.writeFieldBegin('code', TType.I32, 1)
            oprot.writeI32(self.code)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __str__(self):
        return repr(self)

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
all_structs.append(pkt_pkt_data)
pkt_pkt_data.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'rx_ring', None, None, ),  # 1
    (2, TType.I32, 'size', None, None, ),  # 2
    (3, TType.STRING, 'buf', 'BINARY', None, ),  # 3
)
all_structs.append(InvalidPktOperation)
InvalidPktOperation.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'code', None, None, ),  # 1
)
fix_spec(all_structs)
del all_structs
