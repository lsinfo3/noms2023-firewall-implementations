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
#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <uapi/linux/tcp.h>
#include <uapi/linux/udp.h>


#include "bpf_helpers.h"

#define TH_ACK TCP_FLAG_ACK
#define TH_FIN TCP_FLAG_FIN
#define TH_SYN TCP_FLAG_SYN
#define TH_RST TCP_FLAG_RST

#define MAX_TCP_PKT_SIZE 1448
#define TCP_WINDOW_SCALING 1024 //(this is a Window Scale option value of 10)

#define SEQ_GT(a,b) ((int)((a)-(b)) > 0)
#define SEQ_LT(a,b) ((int)((a)-(b)) < 0)
#define SEQ_GEQ(a,b) ((int)((a)-(b)) >= 0)
#define SEQ_LEQ(a,b) ((int)((a)-(b)) <= 0)


union byte4 {
	char byte[4];
	int numint;
	float numfloat;
};

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


struct bpf_map_def SEC("maps") tx_port = {
	.type = BPF_MAP_TYPE_DEVMAP,
	.key_size = sizeof(int),
	.value_size = sizeof(int),
	.max_entries = 64,
};

struct bpf_map_def SEC("maps") rules = {
		.type = BPF_MAP_TYPE_HASH,
		.key_size = sizeof(int),
		.value_size = sizeof(tcpState),
		.max_entries = 28250,
};

static __always_inline int ntohl_alt(int a) {
	union byte4 sw;
	int i;
    sw.numint = a;

	char h = sw.byte[0];
    sw.byte[0] = sw.byte[3];
    sw.byte[3] = h;
	h = sw.byte[1];
    sw.byte[1] = sw.byte[2];
    sw.byte[2] = h;

	return sw.numint;
}

static __always_inline int hash(const __u8 *proto, const unsigned long *s_addr, const u_int16_t *s_port, const unsigned long *c_addr,
		 const uint16_t *c_port) {
    int erg = (int) ((*s_addr ^ *s_port) ^ (*c_addr ^ *c_port) ^ *proto);
	return erg;
}


static __always_inline int inspectPacket(const struct iphdr *iph, const struct tcphdr *tcph, int *id) {
	uint8_t *snd_state, *rec_state;
	uint8_t futurSndState, futurRecvState;
	uint32_t seq, ack_seq;
	int ackChallenge = 0;

	tcpState *conState = bpf_map_lookup_elem(&rules, id);
	if (conState == 0) {
		return 0;
	}


	if (iph->saddr < iph->daddr) {//s_ip < c_ip
		snd_state = &(conState->srv_state);
		rec_state = &(conState->cli_state);
	} else {
		snd_state = &(conState->cli_state);
		rec_state = &(conState->srv_state);
	}


	const int flags = tcp_flag_word(tcph) & ((TH_ACK + TH_FIN) + (TH_SYN + TH_RST));
	// darf dieser state das packet schicken?

	switch (*snd_state) {
		case TCP_ESTABLISHED: //ack fin+ack
			switch (flags) {
				case TH_ACK:
					futurSndState = futurRecvState = TCP_ESTABLISHED;
					break;
				case TH_FIN + TH_ACK:
					futurSndState = TCP_FIN_WAIT1;
					futurRecvState = TCP_CLOSE_WAIT;
					break;
				case TH_ACK + TH_RST:
					futurSndState = futurRecvState = TCP_CLOSE;
					break;
				default:
					return 0;
			}
			break;
		case TCP_CLOSE://syn
			if (flags != TH_SYN) {
				return 0;
			}
			futurSndState = TCP_SYN_SENT;
			futurRecvState = TCP_SYN_RECV;
			break;
		case TCP_SYN_RECV://syn ack fin syn+ack
			switch (flags) {
				case TH_SYN + TH_ACK:
					futurSndState = *snd_state;
					futurRecvState = TCP_ESTABLISHED;
					break;
				case TH_SYN:
					futurSndState = futurRecvState = TCP_SYN_RECV;
					break;
				case TH_FIN + TH_ACK:
					futurSndState = TCP_FIN_WAIT1;
					futurRecvState = TCP_CLOSE_WAIT;
					break;
				case TH_RST + TH_ACK:
					futurSndState = futurRecvState = TCP_CLOSE;
					break;
				default:
					return 0;
			}
			break;
		case TCP_CLOSE_WAIT://fin+ack ack
			switch (flags) {
				case TH_ACK:
					futurSndState = TCP_CLOSE_WAIT;
					futurRecvState = TCP_FIN_WAIT2;
					ackChallenge = 1;
					break;
				case TH_FIN + TH_ACK:
					if (*rec_state == TCP_FIN_WAIT1) {
						futurSndState = futurRecvState = TCP_CLOSING;
						break;
					} else {
						futurSndState = TCP_LAST_ACK;
						futurRecvState = TCP_TIME_WAIT;
						break;
					}
				case TH_ACK + TH_RST:
					futurSndState = futurRecvState = TCP_CLOSE;
					break;
				default:
					return 0;
			}
			break;
		case TCP_FIN_WAIT1: //ack
		case TCP_FIN_WAIT2: // ack
			if (flags == TH_ACK) {
				futurSndState = *snd_state;
				futurRecvState = *rec_state;
				break;
			}
		case TCP_TIME_WAIT: //ack
			if (flags == TH_ACK) {
				futurSndState = futurRecvState = TCP_CLOSE;
				break;
			}
		case TCP_CLOSING:   //ack
			if ((tcp_flag_word(tcph) & (TH_ACK + TH_FIN + TH_SYN)) == TH_ACK) {
				futurSndState = TCP_CLOSE;
				if (tcph->rst)
					futurRecvState = TCP_CLOSE;
				else
					futurRecvState = *rec_state;

				break;
			}
		case TCP_SYN_SENT:
		case TCP_LAST_ACK:
		default:
			return 0;
	}


	//check seq nums
	seq = ntohl_alt(tcph->seq);
	ack_seq = ntohl_alt(tcph->ack_seq);
    uint16_t tcp_window_size = ntohs(tcph->window);

	if (iph->saddr < iph->daddr) {//=> server = sender  s_ip < c_ip
		if ((SEQ_LT(seq, conState->srv_seq) || SEQ_GEQ(seq, conState->srv_seq + conState->srv_window)) && !(tcph->syn)) {
			return 0;
		}
		if (SEQ_LT(ack_seq, conState->cli_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
			return 1;
		}
		//fin ack -> fin ack -> ack valide depending on ack seq
		if (futurSndState == TCP_CLOSING && futurRecvState == TCP_CLOSING && SEQ_GT(ack_seq, conState->cli_seq)) {
			futurSndState = TCP_CLOSE;
		}

		conState->cli_seq = ack_seq;
        conState->cli_window = tcp_window_size * TCP_WINDOW_SCALING;
		conState->srv_state = futurSndState;
		conState->cli_state = futurRecvState;


	} else {
		if ((SEQ_LT(seq, conState->cli_seq) || SEQ_GEQ(seq, conState->cli_seq + conState->cli_window)) && !(tcph->syn)) {
			return 0;
		}
		if (SEQ_LT(ack_seq, conState->srv_seq) && SEQ_LT(seq, conState->srv_seq) && ackChallenge) {
			return 1;
		}

		if (futurSndState == TCP_CLOSING && futurRecvState == TCP_CLOSING && SEQ_GT(ack_seq, conState->srv_seq)) {
			futurSndState = TCP_CLOSE;
		}
		conState->srv_seq = ack_seq;
        conState->srv_window = tcp_window_size * TCP_WINDOW_SCALING;
		conState->cli_state = futurSndState;
		conState->srv_state = futurRecvState;
	}


	if (tcph->rst || (futurSndState == TCP_CLOSE && futurRecvState == TCP_CLOSE)) {
		conState->cli_seq = 0;
		conState->srv_seq = 0;
	}

	bpf_map_update_elem(&rules, id, conState, BPF_ANY);
	return 1;
}

static __always_inline int inspectIp(struct xdp_md *ctx) {

	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	u64 nh_off = sizeof(*eth);
	int allowed = 0, id;
	struct iphdr *iph = data + nh_off;
	struct tcphdr *tcph;
	struct udphdr *udph;


	if (iph + 1 > data_end) {
		return 0;
	}
	nh_off = nh_off + sizeof(*iph);
	switch (iph->protocol) {
		case IPPROTO_TCP:
			tcph = data + nh_off;
			if (tcph + 1 > data_end) {
				return 0;
			}


			id = hash(&(iph->protocol), (const unsigned long *) &iph->saddr, &tcph->source,
					  (const unsigned long *) &iph->daddr, &tcph->dest);

			allowed = inspectPacket(iph, tcph, &id);

			break;
		case IPPROTO_UDP:
			udph = data + nh_off;
			if (udph + 1 > data_end) {
				return 0;
			}
			id = hash(&(iph->protocol), (const unsigned long *) &(iph->saddr), &(udph->source),
					  (const unsigned long *) &(iph->daddr), &(udph->dest));
			allowed = (bpf_map_lookup_elem(&rules,&id) != 0);
			break;
	}


	return allowed;
}


SEC("xdpFirewall")
int xdp_firewall_prog(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	u64 nh_off;

	nh_off = sizeof(*eth);
	if (data + nh_off > data_end)
		return XDP_DROP;

	switch (ntohs(eth->h_proto)) {
		case ETH_P_IP:
			if(!inspectIp(ctx)){
				break;
			}
		case ETH_P_ARP:
			return bpf_redirect_map(&tx_port, ctx->ingress_ifindex, 0);
	}

	return XDP_DROP;
}

char _license[] SEC("license") = "GPL";
