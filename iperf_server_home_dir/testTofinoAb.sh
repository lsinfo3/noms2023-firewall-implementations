#!/bin/bash
. sharedFirewallTestConfig.sh

# override firewall client to tofino
FIREWALL_CLIENT="manuel@172.16.35.101"
FIREWALL_DIRECTORY="/home/manuel/controllerenv/"

#FIREWALL_TYPE="PYTHON"
FIREWALL_TYPE="C"

# Testcases
FILES=(1kb 10kb 100kb 1mb 10mb 100mb 250mb)
CONNECTIONS=(1 2 4 8 64 256)
RUNS_PER_CASE=5

# Other constants
RULE_FILE_NAME="abRules.csv"

used_result_dir="${RESULT_DIR}ab/"
mkdir -p ${used_result_dir}

iperf_ssh "rm ab.csv"

firewall_ssh "sudo killall -p bf_switchd"

setup_firewall_test_iperf_only
delete_old_bandwidth_limits
firewall_ssh "sudo killall -q python"
firewall_ssh "sudo killall -q python3"

echo "-> Staring varnish server"
iperf_ssh "sudo killall varnishd"
sleep 5
iperf_ssh "sudo ip netns exec ns_server /usr/sbin/varnishd -j unix,user=vcache -F -a :80 -T 10.0.1.1:6082 -f /etc/varnish/default.vcl -S /etc/varnish/secret -s malloc,512m" &
sleep 5

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

scp $RULE_FILE_NAME "${FIREWALL_CLIENT}:${FIREWALL_DIRECTORY}rules.csv"

for ((i=0;i<${RUNS_PER_CASE};i++))
do
    for  file in "${FILES[@]}"
    do
        for connections in "${CONNECTIONS[@]}"
        do
            save_id="${CORE_SAVE_NAME}_${file}_${connections}"
            run_id="${save_id}_${i}"
            save_dir="${used_result_dir}${save_id}"
            log_run_path="${FIREWALL_DIRECTORY}${run_id}"

            echo "-> Running testcase: ${run_id}"
            mkdir -p ${save_dir}

            iperf_ssh "sudo killall ab"

            echo "-> Starting state meassurement and firewall"
            firewall_ssh "cd ${FIREWALL_DIRECTORY}; python measureCPUstats.py ${run_id} 360" &
            sleep 2

            if [ "$FIREWALL_TYPE" = "C" ]; then
                echo "-> Starting switch"
                firewall_ssh "source bf-sde-8.9.2/set_sde.bash; cd bf-sde-8.9.2; ./run_switchd.sh -p main" &
                sleep 40
            elif [ "$FIREWALL_TYPE" = "PYTHON" ]; then
                firewall_ssh "cd ${FIREWALL_DIRECTORY}; source bin/activate; sudo python3 controller.py" &
                sleep 50
            fi

            echo "-> Running Ab"
            iperf_ssh "sudo ip netns exec ns_client ab -e ab.csv -c ${connections} -n 1280 10.0.1.1:80/${file}.html" > "${save_dir}/ab${i}.txt"

            echo "-> Clean up / Copy results"
            firewall_ssh "sudo killall -q python"
            firewall_ssh "sudo killall -2 python3"

            if [ "$FIREWALL_TYPE" = "C" ]; then
                echo "-> Stopping switch"
                firewall_ssh "sudo killall -p bf_switchd"
            fi

            copy_firewall_results
            iperf_ssh "sudo killall ab"


            # must be removed, because ab does not override it
            scp "${IPERF_CLIENT}:ab.csv" "${save_dir}/ab${i}.csv"
            iperf_ssh "rm ab.csv"
        done
    done
done

iperf_ssh "sudo killall varnishd"
firewall_ssh "sudo killall -p bf_switchd"
