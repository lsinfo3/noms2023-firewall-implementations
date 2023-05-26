#!/bin/bash

cd "$(dirname "$(readlink -f "$0")")" || exit

mkdir -p executables/{ebpf,raw,dpdk}

#echo "Compiling raw"
#cd raw
#gcc durchreichen.c -pthread -o durchreichen
#gcc firewallRaw.c -pthread -o firewall
#gcc firewallMultiWorker.c -pthread -o multiWorkerFire
#gcc firewallDualThreaded.c -pthread -o threadedFirewal
#gcc firewallWorker.c -pthread -o workerFirewall
#cd ..


#cd ..

#echo "PLS READ HOWTO: this is not that easy"
#cd ebpf
#cd ..


echo "Compiling dpdk"
cd dpdk

cd durchreichen
make
cd ..

cd threadedFirewall
make
cd ..

cd firewall
make
cd ..

cd workerFirewall
make
cd ..

cd multiWorker
make
cd ..

cd ..

