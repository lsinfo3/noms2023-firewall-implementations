// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2017-18 David Ahern <dsahern@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 */

#include <linux/bpf.h>
#include <linux/if_link.h>
#include <linux/limits.h>
#include <net/if.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <signal.h>
#include <linux/ip.h> //ip header
#include <arpa/inet.h> //inet_ntop
#include <linux/tcp.h>
#include <linux/udp.h>

#include "bpf/libbpf.h"
#include <bpf/bpf.h>

char ifname1[IFNAMSIZ], ifname2[IFNAMSIZ];

enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT,
	TCP_SYN_RECV,
	TCP_FIN_WAIT1,
	TCP_FIN_WAIT2,
	TCP_TIME_WAIT,
	TCP_CLOSE,
	TCP_CLOSE_WAIT,
	TCP_LAST_ACK,
	TCP_LISTEN,
	TCP_CLOSING,	/* Now a valid state */

	TCP_MAX_STATES	/* Leave at the end! */
};

typedef struct { //s_ip < c_ip
	uint32_t srv_seq;
	uint32_t cli_seq;
	uint8_t srv_state;
	uint8_t cli_state;
    uint32_t srv_window;
    uint32_t cli_window;
} tcpState;


int hash(const __u8 *proto, const unsigned long *s_addr, const u_int16_t *s_port, const unsigned long *c_addr,
		 const uint16_t *c_port) {
    int erg = (int) ((*s_addr ^ *s_port) ^ (*c_addr ^ *c_port) ^ *proto);
	return erg;
}

void addConnection(int rule_map_fd, int *key,  tcpState *s) {

	if(bpf_map_update_elem(rule_map_fd,key,s,BPF_ANY)<0){
		printf("Failed to set rule\n");
	}
}

void readRules(const char *file, int rule_map_fd) {
	char buffer[1024], ip1[INET_ADDRSTRLEN], ip2[INET_ADDRSTRLEN];
	int i, j, rulehash;
	uint16_t port1, port2;
	uint8_t proto;
	unsigned long netip1, netip2;
	struct in_addr inp;
	FILE *fp;
	fp = fopen(file, "r");


	while (fgets(buffer, 1024, fp) != NULL) {
		if (buffer[0] != '#') {
			tcpState s;
			i = 0;
			for (proto = 0; buffer[i] != ','; i = i + 1) {
				proto = (uint8_t) ((10 * proto) + (buffer[i] - '0'));
			}
			i = i + 1;
			for (j = 0; buffer[i] != ','; i = i + 1) {
				ip1[j] = buffer[i];
				j = j + 1;
			}
			ip1[j] = '\0';
			i = i + 1;
			for (port1 = 0; buffer[i] != ','; i = i + 1) {
				port1 = (uint16_t) (port1 * 10 + (buffer[i] - '0'));
			}
			port1 = htons(port1);
			i = i + 1;
			for (j = 0; buffer[i] != ','; i = i + 1) {
				ip2[j] = buffer[i];
				j = j + 1;
			}
			ip2[j] = '\0';
			i = i + 1;
			for (port2 = 0; buffer[i] != '\n'; i = i + 1) {
				port2 = (uint16_t) (port2 * 10 + (buffer[i] - '0'));
			}
			port2 = htons(port2);
			if (inet_aton(ip1, &inp) == 0) {
				printf("Invalid adress %s in line \n%s\n", ip1, buffer);
				printf("Error: %s\n", strerror(errno));
			}
			netip1 = inp.s_addr;
			if (inet_aton(ip2, &inp) == 0) {
				printf("Invalid adress %s in line \n%s\n", ip2, buffer);
				printf("Error: %s\n", strerror(errno));
			}
			netip2 = inp.s_addr;

			s.cli_state = TCP_CLOSE;
            s.cli_seq = 0;
            s.cli_window = 0;
            s.srv_seq = 0;
            s.srv_window = 0;
            s.srv_state = TCP_CLOSE;

			rulehash = hash(&proto, &netip1, &port1, &netip2, &port2);

			addConnection(rule_map_fd, &rulehash, &s);
		}
	}

}

static int do_attach(int idx, int fd, const char *name)
{
	int err;

	err = bpf_set_link_xdp_fd(idx, fd, 0);
	if (err < 0)
		printf("ERROR: failed to attach program to %s\n", name);

	return err;
}

static int do_detach(int idx, const char *name)
{
	int err;

	err = bpf_set_link_xdp_fd(idx, -1, 0);
	if (err < 0)
		printf("ERROR: failed to detach program from %s\n", name);

	return err;
}

static void int_exit(int sig)
{
	int intf1 = if_nametoindex(ifname1);
	int intf2 = if_nametoindex(ifname2);
	do_detach(intf1,ifname1);
	do_detach(intf2,ifname2);
	exit(0);
}

int main(int argc, char **argv)
{
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	const char *prog_name = "xdpFirewall";
	struct bpf_program *prog;
	char filename[PATH_MAX];
	struct bpf_object *obj;
	int i, err;
	int prog_fd, tx_port_fd, rules_fd;
	int intf1, intf2;


	sprintf(ifname1, "ens2f0");
	sprintf(ifname2, "ens2f1");

	if (argc != 1 && argc != 3) {
		printf("Wrong amount of arguments\n");
		return -1;
	}


	if (argc == 3) {
		sprintf(ifname1, "%s", argv[1]);
		sprintf(ifname2, "%s", argv[2]);
	}

	intf1 = if_nametoindex(ifname1);
	intf2 = if_nametoindex(ifname2);

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;


	if (access(filename, O_RDONLY) < 0) {
		printf("error accessing file %s: %s\n", filename, strerror(errno));
		return 1;
	}

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	prog = bpf_object__find_program_by_title(obj, prog_name);
	prog_fd = bpf_program__fd(prog);
	if (prog_fd < 0) {
		printf("program not found: %s\n", strerror(prog_fd));
		return 1;
	}


	tx_port_fd = bpf_map__fd(bpf_object__find_map_by_name(obj, "tx_port"));
	if (tx_port_fd < 0) {
		printf("map not found: %s\n", strerror(tx_port_fd));
		return 1;
	}

	for (i = 1; i < 64; ++i)
		bpf_map_update_elem(tx_port_fd, &i, &i, 0);

	bpf_map_update_elem(tx_port_fd,&intf1,&intf2,BPF_ANY);
	bpf_map_update_elem(tx_port_fd,&intf2,&intf1,BPF_ANY);


	rules_fd = bpf_map__fd(bpf_object__find_map_by_name(obj, "rules"));
	if (rules_fd < 0) {
		printf("map not found: %s\n", strerror(rules_fd));
		return 1;
	}




	readRules("../rules.csv",rules_fd);



	err = do_attach(intf1, prog_fd, ifname1);
	if (err)
		return err;

	err = do_attach(intf2, prog_fd, ifname2);
	if (err) {
		do_detach(intf1, ifname1);
		return err;
	}



	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);
	while(1){
	    sleep(1);
	}

    return 0;
}
