from aenum import Enum, unique
from typing import Tuple, List

@unique
class TcpState(Enum):
    NONE = 0
    SYN_SENT = 1
    SYN_RECV = 2
    ESTABLISHED = 3
    FIN_WAIT = 4
    CLOSE_WAIT = 5
    LAST_ACK = 6
    TIME_WAIT = 7
    CLOSE = 8
    SYN_SENT2 = 9
    IGNORE = 10
    INVALID = 11


class SwitchTcpMatch:
    def __init__(self, ack, rst, syn, fin):
        self.ack: bool = ack
        self.rst: bool = rst
        self.syn: bool = syn
        self.fin: bool = fin

@unique
class TcpFlags(Enum):
    SYN_SET = 0
    SYNACK_SET = 1
    FIN_SET = 2
    ACK_SET = 3
    RST_SET = 4
    NONE_SET = 5
    FINACK_SET = 6


def tcp_flags_from_str(flags: str):
    if 'R' in flags:
        return TcpFlags.RST_SET
    elif 'S' in flags:
        if 'A' in flags:
            return TcpFlags.SYNACK_SET
        else:
            return TcpFlags.SYN_SET
    elif 'F' in flags:
        if 'A' in flags:
            return TcpFlags.FINACK_SET
        else:
            return TcpFlags.FIN_SET
    elif 'A' in flags:
        return TcpFlags.ACK_SET

    return TcpFlags.NONE_SET


def tcp_flags_to_switch_tcp_match(tcp_flags: TcpFlags) -> SwitchTcpMatch:
    if tcp_flags == TcpFlags.SYN_SET:
        return SwitchTcpMatch(False, False, True, False)
    elif tcp_flags == TcpFlags.SYNACK_SET:
        return SwitchTcpMatch(True, False, True, False)
    # allow both fin and fin/ack
    elif tcp_flags == TcpFlags.FIN_SET:
        return SwitchTcpMatch(False, False, False, True)
    elif tcp_flags == TcpFlags.ACK_SET:
        return SwitchTcpMatch(True, False, False, False)
    elif tcp_flags == TcpFlags.RST_SET:
        return SwitchTcpMatch(False, True, False, False)
    elif tcp_flags == TcpFlags.FINACK_SET:
        return SwitchTcpMatch(True, False, False, True)
    else:
        return SwitchTcpMatch(False, False, False, False)


@unique
class Direction(Enum):
    ORIGINAL = 0
    REPLY = 1


transitions: List[List[List[int]]] = [
    [
        # Direction: ORIGINAL
        # State.NONE, State.SYN_SENT, State.SYN_RECV, State.ESTABLISHED, State.FIN_WAIT, State.CLOSE_WAIT, State.LAST_ACK, State.TIME_WAIT, State.CLOSE, State.SYN_SENT2
        [TcpState.SYN_SENT, TcpState.SYN_SENT, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.SYN_SENT, TcpState.SYN_SENT, TcpState.SYN_SENT2],
        [TcpState.INVALID, TcpState.INVALID, TcpState.SYN_RECV, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.SYN_RECV],
        [TcpState.INVALID, TcpState.INVALID, TcpState.FIN_WAIT, TcpState.FIN_WAIT, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.TIME_WAIT, TcpState.CLOSE, TcpState.INVALID],
        [TcpState.ESTABLISHED, TcpState.INVALID, TcpState.ESTABLISHED, TcpState.ESTABLISHED, TcpState.CLOSE_WAIT, TcpState.CLOSE_WAIT, TcpState.TIME_WAIT, TcpState.TIME_WAIT, TcpState.CLOSE, TcpState.INVALID],
        [TcpState.INVALID, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE],
        [TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID],
        # copy from fin set to fin/ack set
        [TcpState.INVALID, TcpState.INVALID, TcpState.FIN_WAIT, TcpState.FIN_WAIT, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.TIME_WAIT, TcpState.CLOSE, TcpState.INVALID]
    ],
    [
        # Direction: REPLY
        # State.NONE, State.SYN_SENT, State.SYN_RECV, State.ESTABLISHED, State.FIN_WAIT, State.CLOSE_WAIT, State.LAST_ACK, State.TIME_WAIT, State.CLOSE, State.SYN_SENT2
        [TcpState.INVALID, TcpState.SYN_SENT2, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.SYN_SENT, TcpState.INVALID, TcpState.SYN_SENT2],
        [TcpState.INVALID, TcpState.SYN_RECV, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.IGNORE, TcpState.SYN_RECV],
        [TcpState.INVALID, TcpState.INVALID, TcpState.FIN_WAIT, TcpState.FIN_WAIT, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.TIME_WAIT, TcpState.CLOSE, TcpState.INVALID],
        [TcpState.INVALID, TcpState.IGNORE, TcpState.SYN_RECV, TcpState.ESTABLISHED, TcpState.CLOSE_WAIT, TcpState.CLOSE_WAIT, TcpState.TIME_WAIT, TcpState.TIME_WAIT, TcpState.CLOSE, TcpState.IGNORE],
        [TcpState.INVALID, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE, TcpState.CLOSE],
        [TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID, TcpState.INVALID],
        # copy from fin set to fin/ack set
        [TcpState.INVALID, TcpState.INVALID, TcpState.FIN_WAIT, TcpState.FIN_WAIT, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.LAST_ACK, TcpState.TIME_WAIT, TcpState.CLOSE, TcpState.INVALID]
    ]
]


def get_new_state(old_state: TcpState, direction: Direction, flags: TcpFlags) -> TcpState:
    return TcpState(transitions[direction.value][flags.value][old_state.value])


# Generate lookup tables for legal flags
stay_in_state_flags = [[[] for j in range(len(TcpState))] for i in range(len(Direction))]
to_controller_flags = [[[] for j in range(len(TcpState))] for i in range(len(Direction))]
for direction in Direction:
    for state in TcpState:
        if state == TcpState.INVALID or state == TcpState.IGNORE:
            continue

        for flag in TcpFlags:
            new_state = get_new_state(state, direction, flag)
            if new_state == state or new_state == TcpState.IGNORE:
                stay_in_state_flags[direction.value][state.value].append(flag)
            elif new_state != TcpState.INVALID:
                to_controller_flags[direction.value][state.value].append(flag)


def get_new_rules(state: TcpState, direction: Direction) -> Tuple[List[TcpFlags], List[TcpFlags]]:
    """Returns Tuple of ([Flags_To_Stay_In_State], [Flags_To_Send_To_Controller])"""
    return stay_in_state_flags[direction.value][state.value], to_controller_flags[direction.value][state.value]