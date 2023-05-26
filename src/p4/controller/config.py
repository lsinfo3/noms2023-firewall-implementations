from controller.util import FlowType, FiveTuple, L4Proto
from typing import List
import csv

# Controller configuration
LOG_CONFIG = 'logging.conf'
CONTROLLER_INTERFACE = 'enp1s0'

# Port and routing configuration
PORTS = [
    # ((Port, Lane), Speed, FEC) or (dev_port, Speed, FEC)
    # Speed in (10, 25, 40, 100)
    # FEC in (None, FC, RS)
    ((1, 0), 100, 'RS'),
    ((2, 0), 100, 'RS'),
]

ROUTING = [
    # from port to port
    # port in (dev_port, (Port, Lane))
    ((1, 0), (2, 0)),
    ((2, 0), (1, 0)),
]

THRIFT_HOST = 'localhost'
THRIFT_PORT = 9090


def load_firewall_config() -> List[FiveTuple]:
    firewall_rules: List[FiveTuple] = []
    with open('rules.csv', newline='') as csvfile:
        reader = csv.DictReader(csvfile, fieldnames=['protocol', 'ip1', 'port1', 'ip2', 'port2'])
        for row in reader:
            l4type = L4Proto.TCP if row['protocol'] == "6" else L4Proto.UDP
            firewall_rules.append(FiveTuple(row['ip1'], row['ip2'], int(row['port1']), int(row['port2']), l4type))
            firewall_rules.append(FiveTuple(row['ip2'], row['ip1'], int(row['port2']), int(row['port1']), l4type))
    return firewall_rules
