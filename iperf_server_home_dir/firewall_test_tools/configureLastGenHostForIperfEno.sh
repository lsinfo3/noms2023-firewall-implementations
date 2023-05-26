ip netns add ns_server
ip netns add ns_client

ip link set eno3 netns ns_server
ip netns exec ns_server ip addr add dev eno3 10.0.1.1/24
ip netns exec ns_server ip link set dev eno3 up
ip link set eno4 netns ns_client
ip netns exec ns_client ip addr add dev eno4 10.0.2.1/24
ip netns exec ns_client ip link set dev eno4 up

ip netns exec ns_server route add -host 10.0.2.1 dev eno3
ip netns exec ns_client route add -host 10.0.1.1 dev eno4

ip netns exec ns_server ip link set dev lo up
