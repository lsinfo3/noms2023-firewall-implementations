#!/bin/bash
. sharedFirewallTestConfig.sh

# override firewall client to tofino
FIREWALL_CLIENT="manuel@172.16.35.101"
FIREWALL_DIRECTORY="/home/manuel/controllerenv/"

FIREWALL_TYPE="PYTHON"
#FIREWALL_TYPE="C"

# Testcases
MTUS=(88 1500)
BANDWIDTHS=(200 500 1000 2000 4000 6000 8000 10000 20000 40000 60000 80000 100000) # in mbit
RUNS_PER_CASE=5

# Other constants
TEST_DURATION=30
IPERF_CLIENT_PORT_START=56000
IPERF_CLIENT_PORT_COUNT=32
NUM_PARALLEL_IPERF_INSTANCES=8

used_result_dir="${RESULT_DIR}iperf/"
mkdir -p ${used_result_dir}

firewall_ssh "sudo killall -p bf_switchd"
iperf_ssh "sudo killall -9 iperf"

setup_firewall_test_iperf_only
delete_old_bandwidth_limits
firewall_ssh "sudo killall -q python"
firewall_ssh "sudo killall -q python3"


if [ "$FIREWALL_TYPE" = "PYTHON" ]; then
    echo "-> Starting switch"
    firewall_ssh "source bf-sde-8.9.2/set_sde.bash; ./bf-sde-8.9.2/run_switchd.sh -p main" &
    sleep 30
fi

if [ "$FIREWALL_TYPE" = "PYTHON" ]; then
    CORE_SAVE_NAME="tofino"
fi
if [ "$FIREWALL_TYPE" = "C" ]; then
    CORE_SAVE_NAME="tofinoC"
fi


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

            save_id="${CORE_SAVE_NAME}_${mtu}_${bandwidth}"
            run_id="${save_id}_${i}"
            save_dir="${used_result_dir}${save_id}"
            log_run_path="${FIREWALL_DIRECTORY}${run_id}"

            echo "-> Running testcase: ${run_id}"
            mkdir -p ${save_dir}

            iperf_client_port=$(($IPERF_CLIENT_PORT_START + $iperf_client_port_index))
            iperf_client_port_index=$((($iperf_client_port_index + $NUM_PARALLEL_IPERF_INSTANCES) % $IPERF_CLIENT_PORT_COUNT))
            echo "-> Selecting iperf client port ${iperf_client_port}"
            firewall_ssh "> ${FIREWALL_DIRECTORY}rules.csv"
            for ((j=0;j<${NUM_PARALLEL_IPERF_INSTANCES};j++))
            do
                firewall_ssh "echo '6,10.0.2.1,$(($iperf_client_port + $j)),10.0.1.1,8081' >> ${FIREWALL_DIRECTORY}rules.csv"
            done

            echo "-> Starting iperf server"
            iperf_ssh "sudo ip netns exec ns_server iperf -s -p 8081 -B 10.0.1.1 -D" &

            # start firewall
            echo "-> Starting state meassurement and firewall"
            firewall_ssh "cd ${FIREWALL_DIRECTORY}; python measureCPUstats.py ${run_id} 360" &
            sleep 2

            if [ "$FIREWALL_TYPE" = "C" ]; then
                echo "-> Starting switch"
                firewall_ssh "source bf-sde-8.9.2/set_sde.bash; cd bf-sde-8.9.2; ./run_switchd.sh -p main" &
                sleep 30
            elif [ "$FIREWALL_TYPE" = "PYTHON" ]; then
                firewall_ssh "cd ${FIREWALL_DIRECTORY}; source bin/activate; sudo python3 controller.py" &
                sleep 10
            fi

            echo "-> Running Iperf"
            for ((j=0;j<${NUM_PARALLEL_IPERF_INSTANCES};j++))
            do
                echo "-> Starting with port $(($iperf_client_port + $j))"
                iperf_ssh "sudo ip netns exec ns_client iperf -B 10.0.2.1:$(($iperf_client_port + $j)) -p 8081 -c 10.0.1.1 -i 1 -t ${TEST_DURATION} -w 256M -y c" > "${save_dir}/iperf${i}_${j}.csv" &
            done
            sleep $(($TEST_DURATION + 3))
            iperf_ssh "sudo killall -9 iperf"

            echo "-> Clean up / Copy results"
            firewall_ssh "sudo killall -q python"
            firewall_ssh "sudo killall -2 python3"
            if [ "$FIREWALL_TYPE" = "C" ]; then
                echo "-> Stopping switch"
                firewall_ssh "sudo killall -p bf_switchd"
            fi

            copy_firewall_results
        done
    done
done

iperf_ssh "sudo killall -9 iperf"
firewall_ssh "sudo killall -p bf_switchd"
