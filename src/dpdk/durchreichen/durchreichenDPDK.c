/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2015 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <inttypes.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_ip.h>

#define DPDK_INTERFACE1 "0000:61:00.0"
#define DPDK_INTERFACE2 "0000:61:00.1"

#define RX_RING_SIZE 128
#define TX_RING_SIZE 512
#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32


static const struct rte_eth_conf port_conf_default = {
        .rxmode = { .max_rx_pkt_len = RTE_ETHER_MAX_LEN }
};
// basicfwd.c: Basic DPDK skeleton forwarding example.

/*
 * Initializes a given port using global settings and with the RX buffers
 * coming from the mbuf_pool passed as a parameter.
 */
static inline int
port_init(uint16_t port, struct rte_mempool *mbuf_pool)
{
    struct rte_eth_conf port_conf = port_conf_default;
    const uint16_t rx_rings = 1, tx_rings = 1;
    int retval;
    uint16_t q;
    char name[RTE_ETH_NAME_MAX_LEN];

    if (port >= rte_eth_dev_count_avail())
        return -1;
    // Configure the Ethernet device.
    retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
    if (retval != 0)
        return retval;


    retval = rte_eth_dev_get_name_by_port(port, name);
    if (retval < 0)
        return retval;
    printf("Name: %s\n",name);

    // Allocate and set up 1 RX queue per Ethernet port.
    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(port, q, RX_RING_SIZE,
                                        rte_eth_dev_socket_id(port), NULL, mbuf_pool);
        if (retval < 0)
            return retval;
    }
    // Allocate and set up 1 TX queue per Ethernet port.
    for (q = 0; q < tx_rings; q++) {
        retval = rte_eth_tx_queue_setup(port, q, TX_RING_SIZE,
                                        rte_eth_dev_socket_id(port), NULL);
        if (retval < 0)
            return retval;
    }
    // Start the Ethernet port.
    retval = rte_eth_dev_start(port);
    if (retval < 0)
        return retval;
    // Display the port MAC address.
    struct rte_ether_addr addr;
    rte_eth_macaddr_get(port, &addr);
    printf("Port %u MAC: %02" PRIx8 " %02" PRIx8 " %02" PRIx8
           " %02" PRIx8 " %02" PRIx8 " %02" PRIx8 "\n",
           (unsigned)port,
           addr.addr_bytes[0], addr.addr_bytes[1],
           addr.addr_bytes[2], addr.addr_bytes[3],
           addr.addr_bytes[4], addr.addr_bytes[5]);
    // Enable RX in promiscuous mode for the Ethernet device.
    rte_eth_promiscuous_enable(port);
    return 0;
}

static uint16_t receive(uint16_t port, struct rte_mbuf *bufs[32]) {


    return  rte_eth_rx_burst(port, 0,
                                bufs, BURST_SIZE);

}

static void forward(uint16_t port, struct rte_mbuf *bufs[32], const uint16_t rx) {
    // Send burst of TX packets, to second port of pair.
    const uint16_t nb_tx = rte_eth_tx_burst(port , 0, bufs, rx);
    // Free any unsent packets.
    if (unlikely(nb_tx < rx)) {
        uint16_t buf;
        for (buf = nb_tx; buf < rx; buf++){
            rte_pktmbuf_free(bufs[buf]);
        }
    }
}

static __attribute__((noreturn)) void
lcore_main(void)
{
    const uint16_t nb_ports = rte_eth_dev_count_avail();
    uint16_t port;
    /*
     * Check that the port is on the same NUMA node as the polling thread
     * for best performance.
     */
    for (port = 0; port < nb_ports; port++) {
        if (rte_eth_dev_socket_id(port) > 0 && rte_eth_dev_socket_id(port) != (int)rte_socket_id()) {

            printf("\nCore %u forwarding packets. [Ctrl+C to quit]\n", rte_lcore_id());
            printf("WARNING, port %u is on remote NUMA node to "
                                   "polling thread.\n\tPerformance will "
                                   "not be optimal.\n", port);
        }
    }
    // Run until the application is quit or killed.
    while (1) {
        /*
         * Receive packets on a port and forward them on the paired
         * port. The mapping is 0 -> 1, 1 -> 0, 2 -> 3, 3 -> 2, etc.
         */
        for (port = 0; port < nb_ports; port++) {
            // Get burst of RX packets, from first port of pair.
            struct rte_mbuf *bufs[BURST_SIZE];
            const uint16_t nb_rx = receive(port, bufs);

            if (unlikely(nb_rx == 0)) {
                continue;
            }


            forward(port ^ 1, bufs, nb_rx);
        }
    }
}
/*
 * The main function, which does initialization and calls the per-lcore
 * functions.
 */
int
main(int argc, char *argv[])
{
    struct rte_mempool *mbuf_pool;
    //unsigned nb_ports;
    uint16_t portid0, portid1;
    // Initialize the Environment Abstraction Layer (EAL).
    int ret = rte_eal_init(argc, argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");
    argc -= ret;
    argv += ret;

    if(rte_eth_dev_get_port_by_name(DPDK_INTERFACE1, &portid0)!=0)
        rte_exit(EXIT_FAILURE, "Cannot find device %s \n",
                 DPDK_INTERFACE1);


    if(rte_eth_dev_get_port_by_name(DPDK_INTERFACE2, &portid1)!=0)
        rte_exit(EXIT_FAILURE, "Cannot find device %s \n",
                 DPDK_INTERFACE2);

    // Creates a new mempool in memory to hold the mbufs.
    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * 2,
                                        MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");
    // Initialize all ports.
    if (port_init(portid0, mbuf_pool) != 0)
        rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu8 "\n",
                portid0);
    if (port_init(portid1, mbuf_pool) != 0)
        rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu8 "\n",
                portid1);
    if (rte_lcore_count() > 1)
        printf("\nWARNING: Too many lcores enabled. Only 1 used.\n");
    // Call lcore_main on the master core only.
    lcore_main();
    return 0;
}
