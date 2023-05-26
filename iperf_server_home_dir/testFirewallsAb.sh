#!/bin/bash
. sharedFirewallTestConfig.sh

# Testcases
FILES=(1kb 10kb 100kb 1mb 10mb 100mb 250mb)
CONNECTIONS=(1 2 4 8 64 256)
RUNS_PER_CASE=5

# Other constants
RULE_FILE_NAME="abRules.csv"

used_result_dir="${RESULT_DIR}ab/"
mkdir -p ${used_result_dir}

iperf_ssh "rm ab.csv"

echo "-> Staring varnish server"
iperf_ssh "sudo killall varnishd"
sleep 5
iperf_ssh "sudo ip netns exec ns_server /usr/sbin/varnishd -j unix,user=vcache -F -a :80 -T 10.0.1.1:6082 -f /etc/varnish/default.vcl -S /etc/varnish/secret -s malloc,512m" &
sleep 5

setup_firewall_test

scp $RULE_FILE_NAME "${FIREWALL_CLIENT}:/home/fwtestbed/rules.csv"

for ((i=0;i<${RUNS_PER_CASE};i++))
do
    for  file in "${FILES[@]}"
    do
        for connections in "${CONNECTIONS[@]}"
        do
            for firewall in "${FIREWALLS[@]}"
            do
                save_id="${firewall}_${file}_${connections}"
                run_id="${save_id}_${i}"
                save_dir="${used_result_dir}${save_id}"
                log_run_path="${FIREWALL_DIRECTORY}${run_id}"

                echo "-> Running testcase: ${run_id}"
                mkdir -p ${save_dir}

                iperf_ssh "sudo killall ab"

                set_cpu_affinity firewall

                start_firewall
                sleep 3

                echo "-> Running Ab"
                iperf_ssh "sudo ip netns exec ns_client ab -e ab.csv -c ${connections} -n 1280 10.0.1.1:80/${file}.html" > "${save_dir}/ab${i}.txt"

                echo "-> Clean up / Copy results"
                stop_firewall
                iperf_ssh "sudo killall ab"
                copy_firewall_results

                # must be removed, because ab does not override it
                scp "${IPERF_CLIENT}:ab.csv" "${save_dir}/ab${i}.csv"
                iperf_ssh "rm ab.csv"
            done
        done
    done
done

iperf_ssh "sudo killall varnishd"
