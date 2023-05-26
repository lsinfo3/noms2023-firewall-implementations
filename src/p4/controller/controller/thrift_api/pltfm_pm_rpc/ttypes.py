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


class pltfm_pm_board_type_t(object):
    BF_PLTFM_BD_ID_MAVERICKS_P0A = 564
    BF_PLTFM_BD_ID_MAVERICKS_P0B = 4660
    BF_PLTFM_BD_ID_MAVERICKS_P0C = 21044
    BF_PLTFM_BD_ID_MONTARA_P0A = 8756
    BF_PLTFM_BD_ID_MONTARA_P0B = 12852
    BF_PLTFM_BD_ID_MAVERICKS_P0B_EMU = 16948
    BF_PLTFM_BD_ID_UNKNOWN = 0
    XFFFF = 1

    _VALUES_TO_NAMES = {
        564: "BF_PLTFM_BD_ID_MAVERICKS_P0A",
        4660: "BF_PLTFM_BD_ID_MAVERICKS_P0B",
        21044: "BF_PLTFM_BD_ID_MAVERICKS_P0C",
        8756: "BF_PLTFM_BD_ID_MONTARA_P0A",
        12852: "BF_PLTFM_BD_ID_MONTARA_P0B",
        16948: "BF_PLTFM_BD_ID_MAVERICKS_P0B_EMU",
        0: "BF_PLTFM_BD_ID_UNKNOWN",
        1: "XFFFF",
    }

    _NAMES_TO_VALUES = {
        "BF_PLTFM_BD_ID_MAVERICKS_P0A": 564,
        "BF_PLTFM_BD_ID_MAVERICKS_P0B": 4660,
        "BF_PLTFM_BD_ID_MAVERICKS_P0C": 21044,
        "BF_PLTFM_BD_ID_MONTARA_P0A": 8756,
        "BF_PLTFM_BD_ID_MONTARA_P0B": 12852,
        "BF_PLTFM_BD_ID_MAVERICKS_P0B_EMU": 16948,
        "BF_PLTFM_BD_ID_UNKNOWN": 0,
        "XFFFF": 1,
    }


class InvalidPltfmPmOperation(TException):
    """
    Attributes:
     - code

    """


    def __init__(self, code=None,):
        super(InvalidPltfmPmOperation, self).__setattr__('code', code)

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
        oprot.writeStructBegin('InvalidPltfmPmOperation')
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
all_structs.append(InvalidPltfmPmOperation)
InvalidPltfmPmOperation.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'code', None, None, ),  # 1
)
fix_spec(all_structs)
del all_structs