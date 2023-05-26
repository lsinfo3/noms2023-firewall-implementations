import logging

from .switch_api import SwitchAPI
from .tcp_utils import TcpState, TcpFlags, Direction, get_new_state, get_new_rules, tcp_flags_to_switch_tcp_match
from ..util import FiveTuple, reverse_five_tuple
from typing import Dict, List

logger = logging.getLogger(__name__)


class Flow:
    def __init__(self, five_tuple: FiveTuple):
        if five_tuple.is_original_direction():
            self.fiveTupleOriginal = five_tuple
            self.fiveTupleReply = reverse_five_tuple(five_tuple)
        else:
            self.fiveTupleOriginal = reverse_five_tuple(five_tuple)
            self.fiveTupleReply = five_tuple
        self.tcpState = TcpState.NONE


class StatefulFirewall:
    """
    Controller-side representation of the TCP state checking.
    """

    def __init__(self, switch: SwitchAPI):
        self.switch = switch

        self.flows: Dict[int, Flow] = dict()

    def add(self, five_tuple: FiveTuple):
        """
        Add a 5-tuple to the tcp state checking
        """
        tuple_hash = five_tuple.direction_independent_hash()

        if tuple_hash not in self.flows:
            new_flow = Flow(five_tuple)
            self.flows[tuple_hash] = new_flow
            self._add_rules(new_flow, new_flow.tcpState)
        elif five_tuple.is_original_direction():
            logger.warning("got a hash collision that should not happen")

    def _add_rules(self, flow: Flow, tcp_state: TcpState):
        original_dir_rules_stay, original_dir_rules_controller = get_new_rules(tcp_state, Direction.ORIGINAL)
        self._insert_rules(flow.fiveTupleOriginal, original_dir_rules_stay, original_dir_rules_controller)

        reply_dir_rules_stay, reply_dir_rules_to_controller = get_new_rules(tcp_state, Direction.REPLY)
        self._insert_rules(flow.fiveTupleReply, reply_dir_rules_stay, reply_dir_rules_to_controller)

    def _insert_rules(self, five_tuple: FiveTuple, stay_in_flags: List[TcpFlags], to_controller_flags: List[TcpFlags]):
        logger.debug(f"Inserting rules for {five_tuple}: {stay_in_flags}, {to_controller_flags}")
        for tcp_flag in stay_in_flags:
            match = tcp_flags_to_switch_tcp_match(tcp_flag)
            self.switch.insert_stateful_entry_forward(five_tuple, match)
        for tcp_flag in to_controller_flags:
            match = tcp_flags_to_switch_tcp_match(tcp_flag)
            self.switch.insert_stateful_entry_to_controller(five_tuple, match)

    def _remove_rules(self, flow: Flow, tcp_state: TcpState):
        original_dir_rules_stay, original_dir_rules_controller = get_new_rules(tcp_state, Direction.ORIGINAL)
        self._clear_rules(flow.fiveTupleOriginal, original_dir_rules_stay, original_dir_rules_controller)

        reply_dir_rules_stay, reply_dir_rules_to_controller = get_new_rules(tcp_state, Direction.REPLY)
        self._clear_rules(flow.fiveTupleReply, reply_dir_rules_stay, reply_dir_rules_to_controller)

    def _clear_rules(self, five_tuple: FiveTuple, stay_in_flags: List[TcpFlags], to_controller_flags: List[TcpFlags]):
        for tcp_flag in stay_in_flags:
            match = tcp_flags_to_switch_tcp_match(tcp_flag)
            self.switch.remove_stateful_entries(five_tuple, match)
        for tcp_flag in to_controller_flags:
            match = tcp_flags_to_switch_tcp_match(tcp_flag)
            self.switch.remove_stateful_entries(five_tuple, match)

    def process(self, five_tuple: FiveTuple, tcp_flags: TcpFlags):
        tuple_hash = five_tuple.direction_independent_hash()

        if tuple_hash not in self.flows:
            logger.warning(f"{five_tuple} not in flows")
            return

        flow = self.flows[tuple_hash]

        direction = Direction.ORIGINAL if five_tuple.is_original_direction() else Direction.REPLY
        new_state = get_new_state(flow.tcpState, direction, tcp_flags)

        if new_state == TcpState.INVALID or new_state == TcpState.IGNORE:
            #logger.warning(f"Received invalid transition: {five_tuple}, {direction}, {tcp_flags}")
            return

        if new_state == flow.tcpState:
            #logger.warning(f"Received {tcp_flags} and this should stay in state {flow.tcpState}")
            return

        self._remove_rules(flow, flow.tcpState)
        logger.debug(f"Switching to new state {new_state}")
        self._add_rules(flow, new_state)
        flow.tcpState = new_state
