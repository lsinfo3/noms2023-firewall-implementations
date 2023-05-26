sudo ethtool -L ens2f0  combined 2
sudo ethtool -L ens2f1  combined 2

cd /sys/class/net/ens2f0/queues

echo 01 | sudo tee rx-0/rps_cpus
echo 00 | sudo tee rx-1/rps_cpus

echo 00 | sudo tee tx-0/xps_cpus
echo 01 | sudo tee tx-1/xps_cpus

cd /sys/class/net/ens2f1/queues
echo 04 | sudo tee rx-0/rps_cpus
echo 00 | sudo tee rx-1/rps_cpus

echo 00 | sudo tee tx-0/xps_cpus
echo 04 | sudo tee tx-1/xps_cpus



nr=$(cat /proc/interrupts | grep "ens2f0-0" | head -n1 | cut -d ":" -f1 | cut -d " " -f3)
echo 01 | sudo tee /proc/irq/$nr/smp_affinity
nr=$(cat /proc/interrupts | grep "ens2f0-1" | cut -d ":" -f1 | cut -d " " -f3)
echo 01 | sudo tee /proc/irq/$nr/smp_affinity

nr=$(cat /proc/interrupts | grep "ens2f1-0" | cut -d ":" -f1 | cut -d " " -f3)
echo 04 | sudo tee /proc/irq/$nr/smp_affinity
nr=$(cat /proc/interrupts | grep "ens2f1-1" | cut -d ":" -f1 | cut -d " " -f3)
echo 04 | sudo tee /proc/irq/$nr/smp_affinity
