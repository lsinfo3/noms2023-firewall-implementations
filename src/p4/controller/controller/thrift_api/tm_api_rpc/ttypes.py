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

from thrift.transport import TTransport
all_structs = []


class InvalidTmOperation(TException):
    """
    Attributes:
     - code

    """


    def __init__(self, code=None,):
        super(InvalidTmOperation, self).__setattr__('code', code)

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
        oprot.writeStructBegin('InvalidTmOperation')
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


class tm_pfc_cos_map_t(object):
    """
    Attributes:
     - CoS0_to_iCos
     - CoS1_to_iCos
     - CoS2_to_iCos
     - CoS3_to_iCos
     - CoS4_to_iCos
     - CoS5_to_iCos
     - CoS6_to_iCos
     - CoS7_to_iCos

    """


    def __init__(self, CoS0_to_iCos=None, CoS1_to_iCos=None, CoS2_to_iCos=None, CoS3_to_iCos=None, CoS4_to_iCos=None, CoS5_to_iCos=None, CoS6_to_iCos=None, CoS7_to_iCos=None,):
        self.CoS0_to_iCos = CoS0_to_iCos
        self.CoS1_to_iCos = CoS1_to_iCos
        self.CoS2_to_iCos = CoS2_to_iCos
        self.CoS3_to_iCos = CoS3_to_iCos
        self.CoS4_to_iCos = CoS4_to_iCos
        self.CoS5_to_iCos = CoS5_to_iCos
        self.CoS6_to_iCos = CoS6_to_iCos
        self.CoS7_to_iCos = CoS7_to_iCos

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
                    self.CoS0_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.CoS1_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.CoS2_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.I32:
                    self.CoS3_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 5:
                if ftype == TType.I32:
                    self.CoS4_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 6:
                if ftype == TType.I32:
                    self.CoS5_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 7:
                if ftype == TType.I32:
                    self.CoS6_to_iCos = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 8:
                if ftype == TType.I32:
                    self.CoS7_to_iCos = iprot.readI32()
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
        oprot.writeStructBegin('tm_pfc_cos_map_t')
        if self.CoS0_to_iCos is not None:
            oprot.writeFieldBegin('CoS0_to_iCos', TType.I32, 1)
            oprot.writeI32(self.CoS0_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS1_to_iCos is not None:
            oprot.writeFieldBegin('CoS1_to_iCos', TType.I32, 2)
            oprot.writeI32(self.CoS1_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS2_to_iCos is not None:
            oprot.writeFieldBegin('CoS2_to_iCos', TType.I32, 3)
            oprot.writeI32(self.CoS2_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS3_to_iCos is not None:
            oprot.writeFieldBegin('CoS3_to_iCos', TType.I32, 4)
            oprot.writeI32(self.CoS3_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS4_to_iCos is not None:
            oprot.writeFieldBegin('CoS4_to_iCos', TType.I32, 5)
            oprot.writeI32(self.CoS4_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS5_to_iCos is not None:
            oprot.writeFieldBegin('CoS5_to_iCos', TType.I32, 6)
            oprot.writeI32(self.CoS5_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS6_to_iCos is not None:
            oprot.writeFieldBegin('CoS6_to_iCos', TType.I32, 7)
            oprot.writeI32(self.CoS6_to_iCos)
            oprot.writeFieldEnd()
        if self.CoS7_to_iCos is not None:
            oprot.writeFieldBegin('CoS7_to_iCos', TType.I32, 8)
            oprot.writeI32(self.CoS7_to_iCos)
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


class tm_q_map_t(object):
    """
    Attributes:
     - md_qid0_to_tm_q
     - md_qid1_to_tm_q
     - md_qid2_to_tm_q
     - md_qid3_to_tm_q
     - md_qid4_to_tm_q
     - md_qid5_to_tm_q
     - md_qid6_to_tm_q
     - md_qid7_to_tm_q
     - md_qid8_to_tm_q
     - md_qid9_to_tm_q
     - md_qid10_to_tm_q
     - md_qid11_to_tm_q
     - md_qid12_to_tm_q
     - md_qid13_to_tm_q
     - md_qid14_to_tm_q
     - md_qid15_to_tm_q
     - md_qid16_to_tm_q
     - md_qid17_to_tm_q
     - md_qid18_to_tm_q
     - md_qid19_to_tm_q
     - md_qid20_to_tm_q
     - md_qid21_to_tm_q
     - md_qid22_to_tm_q
     - md_qid23_to_tm_q
     - md_qid24_to_tm_q
     - md_qid25_to_tm_q
     - md_qid26_to_tm_q
     - md_qid27_to_tm_q
     - md_qid28_to_tm_q
     - md_qid29_to_tm_q
     - md_qid30_to_tm_q
     - md_qid31_to_tm_q
     - q_count

    """


    def __init__(self, md_qid0_to_tm_q=None, md_qid1_to_tm_q=None, md_qid2_to_tm_q=None, md_qid3_to_tm_q=None, md_qid4_to_tm_q=None, md_qid5_to_tm_q=None, md_qid6_to_tm_q=None, md_qid7_to_tm_q=None, md_qid8_to_tm_q=None, md_qid9_to_tm_q=None, md_qid10_to_tm_q=None, md_qid11_to_tm_q=None, md_qid12_to_tm_q=None, md_qid13_to_tm_q=None, md_qid14_to_tm_q=None, md_qid15_to_tm_q=None, md_qid16_to_tm_q=None, md_qid17_to_tm_q=None, md_qid18_to_tm_q=None, md_qid19_to_tm_q=None, md_qid20_to_tm_q=None, md_qid21_to_tm_q=None, md_qid22_to_tm_q=None, md_qid23_to_tm_q=None, md_qid24_to_tm_q=None, md_qid25_to_tm_q=None, md_qid26_to_tm_q=None, md_qid27_to_tm_q=None, md_qid28_to_tm_q=None, md_qid29_to_tm_q=None, md_qid30_to_tm_q=None, md_qid31_to_tm_q=None, q_count=None,):
        self.md_qid0_to_tm_q = md_qid0_to_tm_q
        self.md_qid1_to_tm_q = md_qid1_to_tm_q
        self.md_qid2_to_tm_q = md_qid2_to_tm_q
        self.md_qid3_to_tm_q = md_qid3_to_tm_q
        self.md_qid4_to_tm_q = md_qid4_to_tm_q
        self.md_qid5_to_tm_q = md_qid5_to_tm_q
        self.md_qid6_to_tm_q = md_qid6_to_tm_q
        self.md_qid7_to_tm_q = md_qid7_to_tm_q
        self.md_qid8_to_tm_q = md_qid8_to_tm_q
        self.md_qid9_to_tm_q = md_qid9_to_tm_q
        self.md_qid10_to_tm_q = md_qid10_to_tm_q
        self.md_qid11_to_tm_q = md_qid11_to_tm_q
        self.md_qid12_to_tm_q = md_qid12_to_tm_q
        self.md_qid13_to_tm_q = md_qid13_to_tm_q
        self.md_qid14_to_tm_q = md_qid14_to_tm_q
        self.md_qid15_to_tm_q = md_qid15_to_tm_q
        self.md_qid16_to_tm_q = md_qid16_to_tm_q
        self.md_qid17_to_tm_q = md_qid17_to_tm_q
        self.md_qid18_to_tm_q = md_qid18_to_tm_q
        self.md_qid19_to_tm_q = md_qid19_to_tm_q
        self.md_qid20_to_tm_q = md_qid20_to_tm_q
        self.md_qid21_to_tm_q = md_qid21_to_tm_q
        self.md_qid22_to_tm_q = md_qid22_to_tm_q
        self.md_qid23_to_tm_q = md_qid23_to_tm_q
        self.md_qid24_to_tm_q = md_qid24_to_tm_q
        self.md_qid25_to_tm_q = md_qid25_to_tm_q
        self.md_qid26_to_tm_q = md_qid26_to_tm_q
        self.md_qid27_to_tm_q = md_qid27_to_tm_q
        self.md_qid28_to_tm_q = md_qid28_to_tm_q
        self.md_qid29_to_tm_q = md_qid29_to_tm_q
        self.md_qid30_to_tm_q = md_qid30_to_tm_q
        self.md_qid31_to_tm_q = md_qid31_to_tm_q
        self.q_count = q_count

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
                    self.md_qid0_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.md_qid1_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.md_qid2_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.I32:
                    self.md_qid3_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 5:
                if ftype == TType.I32:
                    self.md_qid4_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 6:
                if ftype == TType.I32:
                    self.md_qid5_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 7:
                if ftype == TType.I32:
                    self.md_qid6_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 8:
                if ftype == TType.I32:
                    self.md_qid7_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 9:
                if ftype == TType.I32:
                    self.md_qid8_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 10:
                if ftype == TType.I32:
                    self.md_qid9_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 11:
                if ftype == TType.I32:
                    self.md_qid10_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 12:
                if ftype == TType.I32:
                    self.md_qid11_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 13:
                if ftype == TType.I32:
                    self.md_qid12_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 14:
                if ftype == TType.I32:
                    self.md_qid13_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 15:
                if ftype == TType.I32:
                    self.md_qid14_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 16:
                if ftype == TType.I32:
                    self.md_qid15_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 17:
                if ftype == TType.I32:
                    self.md_qid16_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 18:
                if ftype == TType.I32:
                    self.md_qid17_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 19:
                if ftype == TType.I32:
                    self.md_qid18_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 20:
                if ftype == TType.I32:
                    self.md_qid19_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 21:
                if ftype == TType.I32:
                    self.md_qid20_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 22:
                if ftype == TType.I32:
                    self.md_qid21_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 23:
                if ftype == TType.I32:
                    self.md_qid22_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 24:
                if ftype == TType.I32:
                    self.md_qid23_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 25:
                if ftype == TType.I32:
                    self.md_qid24_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 26:
                if ftype == TType.I32:
                    self.md_qid25_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 27:
                if ftype == TType.I32:
                    self.md_qid26_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 28:
                if ftype == TType.I32:
                    self.md_qid27_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 29:
                if ftype == TType.I32:
                    self.md_qid28_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 30:
                if ftype == TType.I32:
                    self.md_qid29_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 31:
                if ftype == TType.I32:
                    self.md_qid30_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 32:
                if ftype == TType.I32:
                    self.md_qid31_to_tm_q = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 33:
                if ftype == TType.I32:
                    self.q_count = iprot.readI32()
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
        oprot.writeStructBegin('tm_q_map_t')
        if self.md_qid0_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid0_to_tm_q', TType.I32, 1)
            oprot.writeI32(self.md_qid0_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid1_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid1_to_tm_q', TType.I32, 2)
            oprot.writeI32(self.md_qid1_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid2_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid2_to_tm_q', TType.I32, 3)
            oprot.writeI32(self.md_qid2_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid3_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid3_to_tm_q', TType.I32, 4)
            oprot.writeI32(self.md_qid3_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid4_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid4_to_tm_q', TType.I32, 5)
            oprot.writeI32(self.md_qid4_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid5_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid5_to_tm_q', TType.I32, 6)
            oprot.writeI32(self.md_qid5_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid6_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid6_to_tm_q', TType.I32, 7)
            oprot.writeI32(self.md_qid6_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid7_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid7_to_tm_q', TType.I32, 8)
            oprot.writeI32(self.md_qid7_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid8_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid8_to_tm_q', TType.I32, 9)
            oprot.writeI32(self.md_qid8_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid9_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid9_to_tm_q', TType.I32, 10)
            oprot.writeI32(self.md_qid9_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid10_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid10_to_tm_q', TType.I32, 11)
            oprot.writeI32(self.md_qid10_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid11_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid11_to_tm_q', TType.I32, 12)
            oprot.writeI32(self.md_qid11_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid12_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid12_to_tm_q', TType.I32, 13)
            oprot.writeI32(self.md_qid12_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid13_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid13_to_tm_q', TType.I32, 14)
            oprot.writeI32(self.md_qid13_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid14_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid14_to_tm_q', TType.I32, 15)
            oprot.writeI32(self.md_qid14_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid15_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid15_to_tm_q', TType.I32, 16)
            oprot.writeI32(self.md_qid15_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid16_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid16_to_tm_q', TType.I32, 17)
            oprot.writeI32(self.md_qid16_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid17_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid17_to_tm_q', TType.I32, 18)
            oprot.writeI32(self.md_qid17_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid18_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid18_to_tm_q', TType.I32, 19)
            oprot.writeI32(self.md_qid18_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid19_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid19_to_tm_q', TType.I32, 20)
            oprot.writeI32(self.md_qid19_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid20_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid20_to_tm_q', TType.I32, 21)
            oprot.writeI32(self.md_qid20_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid21_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid21_to_tm_q', TType.I32, 22)
            oprot.writeI32(self.md_qid21_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid22_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid22_to_tm_q', TType.I32, 23)
            oprot.writeI32(self.md_qid22_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid23_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid23_to_tm_q', TType.I32, 24)
            oprot.writeI32(self.md_qid23_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid24_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid24_to_tm_q', TType.I32, 25)
            oprot.writeI32(self.md_qid24_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid25_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid25_to_tm_q', TType.I32, 26)
            oprot.writeI32(self.md_qid25_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid26_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid26_to_tm_q', TType.I32, 27)
            oprot.writeI32(self.md_qid26_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid27_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid27_to_tm_q', TType.I32, 28)
            oprot.writeI32(self.md_qid27_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid28_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid28_to_tm_q', TType.I32, 29)
            oprot.writeI32(self.md_qid28_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid29_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid29_to_tm_q', TType.I32, 30)
            oprot.writeI32(self.md_qid29_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid30_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid30_to_tm_q', TType.I32, 31)
            oprot.writeI32(self.md_qid30_to_tm_q)
            oprot.writeFieldEnd()
        if self.md_qid31_to_tm_q is not None:
            oprot.writeFieldBegin('md_qid31_to_tm_q', TType.I32, 32)
            oprot.writeI32(self.md_qid31_to_tm_q)
            oprot.writeFieldEnd()
        if self.q_count is not None:
            oprot.writeFieldBegin('q_count', TType.I32, 33)
            oprot.writeI32(self.q_count)
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


class tm_shaper_rate_t(object):
    """
    Attributes:
     - pps
     - burst_size
     - rate

    """


    def __init__(self, pps=None, burst_size=None, rate=None,):
        self.pps = pps
        self.burst_size = burst_size
        self.rate = rate

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
                if ftype == TType.BOOL:
                    self.pps = iprot.readBool()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.burst_size = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.rate = iprot.readI32()
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
        oprot.writeStructBegin('tm_shaper_rate_t')
        if self.pps is not None:
            oprot.writeFieldBegin('pps', TType.BOOL, 1)
            oprot.writeBool(self.pps)
            oprot.writeFieldEnd()
        if self.burst_size is not None:
            oprot.writeFieldBegin('burst_size', TType.I32, 2)
            oprot.writeI32(self.burst_size)
            oprot.writeFieldEnd()
        if self.rate is not None:
            oprot.writeFieldBegin('rate', TType.I32, 3)
            oprot.writeI32(self.rate)
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


class tm_pool_usage_t(object):
    """
    Attributes:
     - pool
     - base_use_limit
     - dynamic_baf
     - hysteresis

    """


    def __init__(self, pool=None, base_use_limit=None, dynamic_baf=None, hysteresis=None,):
        self.pool = pool
        self.base_use_limit = base_use_limit
        self.dynamic_baf = dynamic_baf
        self.hysteresis = hysteresis

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
                    self.pool = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.base_use_limit = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.dynamic_baf = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.I32:
                    self.hysteresis = iprot.readI32()
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
        oprot.writeStructBegin('tm_pool_usage_t')
        if self.pool is not None:
            oprot.writeFieldBegin('pool', TType.I32, 1)
            oprot.writeI32(self.pool)
            oprot.writeFieldEnd()
        if self.base_use_limit is not None:
            oprot.writeFieldBegin('base_use_limit', TType.I32, 2)
            oprot.writeI32(self.base_use_limit)
            oprot.writeFieldEnd()
        if self.dynamic_baf is not None:
            oprot.writeFieldBegin('dynamic_baf', TType.I32, 3)
            oprot.writeI32(self.dynamic_baf)
            oprot.writeFieldEnd()
        if self.hysteresis is not None:
            oprot.writeFieldBegin('hysteresis', TType.I32, 4)
            oprot.writeI32(self.hysteresis)
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


class tm_ppg_usage_t(object):
    """
    Attributes:
     - gmin_count
     - shared_count
     - skid_count
     - wm

    """


    def __init__(self, gmin_count=None, shared_count=None, skid_count=None, wm=None,):
        self.gmin_count = gmin_count
        self.shared_count = shared_count
        self.skid_count = skid_count
        self.wm = wm

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
                    self.gmin_count = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.shared_count = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.skid_count = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.I32:
                    self.wm = iprot.readI32()
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
        oprot.writeStructBegin('tm_ppg_usage_t')
        if self.gmin_count is not None:
            oprot.writeFieldBegin('gmin_count', TType.I32, 1)
            oprot.writeI32(self.gmin_count)
            oprot.writeFieldEnd()
        if self.shared_count is not None:
            oprot.writeFieldBegin('shared_count', TType.I32, 2)
            oprot.writeI32(self.shared_count)
            oprot.writeFieldEnd()
        if self.skid_count is not None:
            oprot.writeFieldBegin('skid_count', TType.I32, 3)
            oprot.writeI32(self.skid_count)
            oprot.writeFieldEnd()
        if self.wm is not None:
            oprot.writeFieldBegin('wm', TType.I32, 4)
            oprot.writeI32(self.wm)
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


class tm_usage_t(object):
    """
    Attributes:
     - count
     - wm

    """


    def __init__(self, count=None, wm=None,):
        self.count = count
        self.wm = wm

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
                    self.count = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.wm = iprot.readI32()
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
        oprot.writeStructBegin('tm_usage_t')
        if self.count is not None:
            oprot.writeFieldBegin('count', TType.I32, 1)
            oprot.writeI32(self.count)
            oprot.writeFieldEnd()
        if self.wm is not None:
            oprot.writeFieldBegin('wm', TType.I32, 2)
            oprot.writeI32(self.wm)
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
all_structs.append(InvalidTmOperation)
InvalidTmOperation.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'code', None, None, ),  # 1
)
all_structs.append(tm_pfc_cos_map_t)
tm_pfc_cos_map_t.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'CoS0_to_iCos', None, None, ),  # 1
    (2, TType.I32, 'CoS1_to_iCos', None, None, ),  # 2
    (3, TType.I32, 'CoS2_to_iCos', None, None, ),  # 3
    (4, TType.I32, 'CoS3_to_iCos', None, None, ),  # 4
    (5, TType.I32, 'CoS4_to_iCos', None, None, ),  # 5
    (6, TType.I32, 'CoS5_to_iCos', None, None, ),  # 6
    (7, TType.I32, 'CoS6_to_iCos', None, None, ),  # 7
    (8, TType.I32, 'CoS7_to_iCos', None, None, ),  # 8
)
all_structs.append(tm_q_map_t)
tm_q_map_t.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'md_qid0_to_tm_q', None, None, ),  # 1
    (2, TType.I32, 'md_qid1_to_tm_q', None, None, ),  # 2
    (3, TType.I32, 'md_qid2_to_tm_q', None, None, ),  # 3
    (4, TType.I32, 'md_qid3_to_tm_q', None, None, ),  # 4
    (5, TType.I32, 'md_qid4_to_tm_q', None, None, ),  # 5
    (6, TType.I32, 'md_qid5_to_tm_q', None, None, ),  # 6
    (7, TType.I32, 'md_qid6_to_tm_q', None, None, ),  # 7
    (8, TType.I32, 'md_qid7_to_tm_q', None, None, ),  # 8
    (9, TType.I32, 'md_qid8_to_tm_q', None, None, ),  # 9
    (10, TType.I32, 'md_qid9_to_tm_q', None, None, ),  # 10
    (11, TType.I32, 'md_qid10_to_tm_q', None, None, ),  # 11
    (12, TType.I32, 'md_qid11_to_tm_q', None, None, ),  # 12
    (13, TType.I32, 'md_qid12_to_tm_q', None, None, ),  # 13
    (14, TType.I32, 'md_qid13_to_tm_q', None, None, ),  # 14
    (15, TType.I32, 'md_qid14_to_tm_q', None, None, ),  # 15
    (16, TType.I32, 'md_qid15_to_tm_q', None, None, ),  # 16
    (17, TType.I32, 'md_qid16_to_tm_q', None, None, ),  # 17
    (18, TType.I32, 'md_qid17_to_tm_q', None, None, ),  # 18
    (19, TType.I32, 'md_qid18_to_tm_q', None, None, ),  # 19
    (20, TType.I32, 'md_qid19_to_tm_q', None, None, ),  # 20
    (21, TType.I32, 'md_qid20_to_tm_q', None, None, ),  # 21
    (22, TType.I32, 'md_qid21_to_tm_q', None, None, ),  # 22
    (23, TType.I32, 'md_qid22_to_tm_q', None, None, ),  # 23
    (24, TType.I32, 'md_qid23_to_tm_q', None, None, ),  # 24
    (25, TType.I32, 'md_qid24_to_tm_q', None, None, ),  # 25
    (26, TType.I32, 'md_qid25_to_tm_q', None, None, ),  # 26
    (27, TType.I32, 'md_qid26_to_tm_q', None, None, ),  # 27
    (28, TType.I32, 'md_qid27_to_tm_q', None, None, ),  # 28
    (29, TType.I32, 'md_qid28_to_tm_q', None, None, ),  # 29
    (30, TType.I32, 'md_qid29_to_tm_q', None, None, ),  # 30
    (31, TType.I32, 'md_qid30_to_tm_q', None, None, ),  # 31
    (32, TType.I32, 'md_qid31_to_tm_q', None, None, ),  # 32
    (33, TType.I32, 'q_count', None, None, ),  # 33
)
all_structs.append(tm_shaper_rate_t)
tm_shaper_rate_t.thrift_spec = (
    None,  # 0
    (1, TType.BOOL, 'pps', None, None, ),  # 1
    (2, TType.I32, 'burst_size', None, None, ),  # 2
    (3, TType.I32, 'rate', None, None, ),  # 3
)
all_structs.append(tm_pool_usage_t)
tm_pool_usage_t.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'pool', None, None, ),  # 1
    (2, TType.I32, 'base_use_limit', None, None, ),  # 2
    (3, TType.I32, 'dynamic_baf', None, None, ),  # 3
    (4, TType.I32, 'hysteresis', None, None, ),  # 4
)
all_structs.append(tm_ppg_usage_t)
tm_ppg_usage_t.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'gmin_count', None, None, ),  # 1
    (2, TType.I32, 'shared_count', None, None, ),  # 2
    (3, TType.I32, 'skid_count', None, None, ),  # 3
    (4, TType.I32, 'wm', None, None, ),  # 4
)
all_structs.append(tm_usage_t)
tm_usage_t.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'count', None, None, ),  # 1
    (2, TType.I32, 'wm', None, None, ),  # 2
)
fix_spec(all_structs)
del all_structs
