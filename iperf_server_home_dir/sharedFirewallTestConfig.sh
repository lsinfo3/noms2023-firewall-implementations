#!/bin/bash

# Clients
FIREWALL_CLIENT="fwtestbed@172.16.46.101"
IPERF_CLIENT="fwtestbed@172.16.46.111"

IPERF_CLIENT_INTERFACE="ens2f1" # most likely change to ens2f0/ens2f1 later
IPERF_SERVER_INTERFACE="ens2f0"

FIREWALL_RECEIVE_INTERFACE="ens2f0"
FIREWALL_SEND_INTERFACE="ens2f1"

# Directories
RESULT_DIR="results/"
FIREWALL_DIRECTORY="/home/fwtestbed/firewall_test/"

FIREWALLS=(durchreichen firewall multiWorkerFire threadedFirewal workerFirewall multiDPDK durchDPDK firewallDPDK threadedDPDK workerDPDK xdpDurchreichen xdpFirewall)

MAXIMUM_BANDWIDTH=100000


firewall_ssh () {
    ssh ${FIREWALL_CLIENT} "$1"
}

iperf_ssh () {
    ssh ${IPERF_CLIENT} "$1"
}

# void set_bandwidth(int bandwidth)
set_bandwidth () {
    delete_old_bandwidth_limits
    iperf_ssh "sudo ip netns exec ns_client tc qdisc add dev ${IPERF_CLIENT_INTERFACE} root tbf rate $1mbit burst $1k latency 400ms"
    iperf_ssh "sudo ip netns exec ns_server tc qdisc add dev ${IPERF_SERVER_INTERFACE} root tbf rate $1mbit burst $1k latency 400ms"
}

delete_old_bandwidth_limits () {
    client=$(iperf_ssh "sudo ip netns exec ns_client tc qdisc show")
    server=$(iperf_ssh "sudo ip netns exec ns_server tc qdisc show")
    # must delete old entries if they exist
    if [[ $client == *"rate"* ]]; then
        iperf_ssh "sudo ip netns exec ns_client tc qdisc del dev ${IPERF_CLIENT_INTERFACE} root"
    fi
    if [[ $server == *"rate"* ]]; then
        iperf_ssh "sudo ip netns exec ns_server tc qdisc del dev ${IPERF_SERVER_INTERFACE} root"
    fi
}

# void set_cpu_affinity(string firewall_name)
set_cpu_affinity () {
    echo "-> Setting affinity based on firewall name"
    if [[ $1 == *"orker"* ]]; then
        firewall_ssh "sudo bash ${FIREWALL_DIRECTORY}setWorkerAffinity.sh"
    elif [[ $1 == *"thread"* ]]; then
        firewall_ssh "sudo bash ${FIREWALL_DIRECTORY}setDualThreadAffinity.sh"
    else
        firewall_ssh "sudo bash ${FIREWALL_DIRECTORY}setSingleThreadAffinity.sh"
    fi
}

setup_firewall_test_iperf_only () {
    echo "-> Setting default values for iperf server"
    iperf_ssh "sudo ip netns exec ns_client ifconfig ${IPERF_CLIENT_INTERFACE} mtu 1500"
    iperf_ssh "sudo ip netns exec ns_server ifconfig ${IPERF_SERVER_INTERFACE} mtu 1500"
}

setup_firewall_test () {
    echo "-> Setting default mtu/bandwidth settings"
    # Firewall servers MTU must be on 1500 or lower, otherwise xdp programs will fail
    firewall_ssh "sudo ifconfig ${FIREWALL_SEND_INTERFACE} mtu 1500"
    firewall_ssh "sudo ifconfig ${FIREWALL_RECEIVE_INTERFACE} mtu 1500"

    # Default values
    setup_firewall_test_iperf_only

    delete_old_bandwidth_limits
}

start_firewall () {
    # following statements run in parallel and are killed in cleanup section
    echo "-> Start Firewall"
    firewall_ssh "cd ${FIREWALL_DIRECTORY}; python measureCPUstats.py ${run_id} 360" &
    sleep 5
    firewall_ssh "cd ${FIREWALL_DIRECTORY}; sudo ./${firewall} ${FIREWALL_RECEIVE_INTERFACE} ${FIREWALL_SEND_INTERFACE}" &
}

stop_firewall () {
    firewall_ssh "sudo killall ${firewall}"
    firewall_ssh "sudo killall -q python"
}

copy_firewall_results () {
    scp "${FIREWALL_CLIENT}:${log_run_path}_cpu.log" "${save_dir}"
    scp "${FIREWALL_CLIENT}:${log_run_path}_mem.log" "${save_dir}"
    firewall_ssh "rm ${log_run_path}_cpu.log"
    firewall_ssh "rm ${log_run_path}_mem.log"
}
