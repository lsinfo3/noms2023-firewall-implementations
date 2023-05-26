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

#include "bpf/libbpf.h"
#include <bpf/bpf.h>

char *ifname1, *ifname2;

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
	const char *prog_name = "xdpDurchreichen";
	struct bpf_program *prog;
	char filename[PATH_MAX];
	struct bpf_object *obj;
	int i, err;
	int prog_fd, map_fd;
	int intf1, intf2;
	ifname1 = "ens2f0";
	ifname2 = "ens2f1";

	if (argc != 1 && argc != 3) {
		printf("Wrong amount of arguments\n");
		return -1;
	}

	if (argc == 3) {
		ifname1 = argv[1];
		ifname2 = argv[2];
	}

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
	map_fd = bpf_map__fd(bpf_object__find_map_by_name(obj, "tx_port"));
	if (map_fd < 0) {
		printf("map not found: %s\n", strerror(map_fd));
		return 1;
	}

	for (i = 1; i < 64; ++i)
		bpf_map_update_elem(map_fd, &i, &i, 0);


	intf1 = if_nametoindex(ifname1);
	intf2 = if_nametoindex(ifname2);


	err = do_attach(intf1, prog_fd, ifname1);
	if (err)
		return err;

	err = do_attach(intf2, prog_fd, ifname2);
	if (err) {
		do_detach(intf1, ifname1);
		return err;
	}


	bpf_map_update_elem(map_fd,&intf1,&intf2,BPF_ANY);
	bpf_map_update_elem(map_fd,&intf2,&intf1,BPF_ANY);

/*
	int ukey, uvalue, retu =0;
    for(ukey = 0;ukey <64;ukey++){
        retu = bpf_map_lookup_elem(map_fd, &ukey, &uvalue);
        if(retu==0){
            printf("Value for Key: (%i) = %i\n",ukey,uvalue);
        } else{
            //printf("%s (%i)\n",strerror(errno),errno);
        }
    }
    */

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);
	while(1){
        sleep(1);
	}

    return 0;
}
