import functools
import typing


def ipv42int(ip):
    ip = ip.split('.')
    return 2 ** 24 * int(ip[0]) + 2 ** 16 * int(ip[1]) + 2 ** 8 * int(ip[2]) + int(ip[3])


basetwo = functools.partial(int, base=2)


def i8(val):
    if -128 <= val <= 127:
        return val
    if 128 <= val <= 255:
        return val - 256
    raise ValueError(f"{val} not a valid i8")


def u8(val):
    if -128 <= val <= -1:
        return 256 + val
    if 0 <= val <= 255:
        return val
    raise ValueError(f"{val} not a valid u8")


def i16(val):
    if -32768 <= val <= 32767:
        return val
    if 32768 <= val <= 65535:
        return val - 65536
    raise ValueError(f"{val} not a valid i16")


def u16(val):
    if -32768 <= val <= -1:
        return 65536 + val
    if 0 <= val <= 65535:
        return val
    raise ValueError(f"{val} not a valid u16")


def i32(val):
    if -2147483648 <= val <= 2147483647:
        return val
    if 2147483648 <= val <= 4294967295:
        return val - 4294967296
    raise ValueError(f"{val} not a valid i32")


def u32(val):
    if -2147483648 <= val <= -1:
        return 4294967296 + val
    if 0 <= val <= 4294967295:
        return val
    raise ValueError(f"{val} not a valid u32")


def to_pipe_port(dev_port: int) -> typing.Tuple[int, int]:
    return dev_port >> 7, dev_port & 0x7f


def to_pipe_id(dev_port: int) -> int:
    return to_pipe_port(dev_port)[0]
