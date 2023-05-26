ip netns add ns_server
ip netns add ns_client

ip link set ens2f0 netns ns_server
ip netns exec ns_server ip addr add dev ens2f0 10.0.1.1/24
ip netns exec ns_server ip link set dev ens2f0 up
ip link set ens2f1 netns ns_client
ip netns exec ns_client ip addr add dev ens2f1 10.0.2.1/24
ip netns exec ns_client ip link set dev ens2f1 up

ip netns exec ns_server route add -host 10.0.2.1 dev ens2f0
ip netns exec ns_client route add -host 10.0.1.1 dev ens2f1

ip netns exec ns_server ip link set dev lo up
