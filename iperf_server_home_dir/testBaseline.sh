#!/bin/bash
. sharedFirewallTestConfig.sh

# Clients
IPERF_CLIENT="fwtestbed@172.16.46.111"

IPERF_CLIENT_INTERFACE="ens2f1" # most likely change to ens2f0/ens2f1 later
IPERF_SERVER_INTERFACE="ens2f0"

# Directories
RESULT_DIR="results/"

# Testcases
MTUS=(88 1500)
BANDWIDTHS=(100000) # in mbit
RUNS_PER_CASE=5

# Other constants
TEST_DURATION=30
IPERF_CLIENT_PORT_START=56000
IPERF_CLIENT_PORT_COUNT=32
NUM_PARALLEL_IPERF_INSTANCES=8

mkdir -p ${RESULT_DIR}

setup_firewall_test_iperf_only
delete_old_bandwidth_limits

iperf_client_port_index=0
for ((i=0;i<${RUNS_PER_CASE};i++))
do
    for  mtu in "${MTUS[@]}"
    do
        echo "-> Setting MTU to ${mtu}"

        iperf_ssh "sudo ip netns exec ns_client ifconfig ${IPERF_CLIENT_INTERFACE} mtu ${mtu}"
        iperf_ssh "sudo ip netns exec ns_server ifconfig ${IPERF_SERVER_INTERFACE} mtu ${mtu}"
        for bandwidth in "${BANDWIDTHS[@]}"
        do
            echo "-> Setting Bandwidth to ${bandwidth}"
            set_bandwidth $bandwidth

            save_id="Baseline_${mtu}_${bandwidth}"
            run_id="${save_id}_${i}"
            save_dir="${RESULT_DIR}${save_id}"

            echo "-> Running testcase: ${run_id}"
            mkdir -p ${save_dir}

            iperf_ssh "sudo killall -9 iperf"

            iperf_client_port=$(($IPERF_CLIENT_PORT_START + $iperf_client_port_index))
            iperf_client_port_index=$((($iperf_client_port_index + $NUM_PARALLEL_IPERF_INSTANCES) % $IPERF_CLIENT_PORT_COUNT))
            echo "-> Selecting iperf client port ${iperf_client_port}"

            echo "-> Running Iperf"
            iperf_ssh "sudo ip netns exec ns_server iperf -s -p 8081 -B 10.0.1.1 -D" &
            sleep 3
            for ((j=0;j<${NUM_PARALLEL_IPERF_INSTANCES};j++))
            do
                echo "-> Starting with port $(($iperf_client_port + $j))"
                iperf_ssh "sudo ip netns exec ns_client iperf -B 10.0.2.1:$(($iperf_client_port + $j)) -p 8081 -c 10.0.1.1 -i 1 -t ${TEST_DURATION} -w 256M -y c" > "${save_dir}/iperf${i}_${j}.csv" &
            done
            sleep $(($TEST_DURATION + 3))
            iperf_ssh "sudo killall -9 iperf"
        done
    done
done
