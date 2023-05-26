#ifndef LOW_LEVEL_LIB_STRUCTS_H
#define LOW_LEVEL_LIB_STRUCTS_H

#include <stdint.h>
#include <netinet/ip6.h>
#include <pipe_mgr/pipe_mgr_intf.h>

#include <byteswap.h>

typedef uint16_t port_t;

typedef struct {
	uint32_t src_ipv4;
	uint32_t dst_ipv4;
	port_t src_port;
	port_t dst_port;
} five_tuple_t;

typedef enum {
	NONE = 0,
	SYN_SENT = 1,
	SYN_RECV = 2,
	ESTABLISHED = 3,
	FIN_WAIT = 4,
	CLOSE_WAIT = 5,
	LAST_ACK = 6,
	TIME_WAIT = 7,
	CLOSE = 8,
	SYN_SENT2 = 9,
	IGNORE = 10,
	INVALID = 11,
	NUM_STATES = 12,
} tcp_state_t;

static char *state_to_str[] = {
		"NONE",
		"SYN_SENT",
		"SYN_RECV",
		"ESTABLISHED",
		"FIN_WAIT",
		"CLOSE_WAIT",
		"LAST_ACK",
		"TIME_WAIT",
		"CLOSE",
		"SYN_SENT2",
		"IGNORE",
		"INVALID",
		"NUM_STATES",
};

typedef enum {
	SYN_SET = 0,
	SYNACK_SET = 1,
	FIN_SET = 2,
	ACK_SET = 3,
	RST_SET = 4,
	NONE_SET = 5,
	FINACK_SET = 6,
	NUM_FLAGS = 7,
} tcp_flags_t;

static char *flag_to_str[] ={
		"SYN_SET",
		"SYNACK_SET",
		"FIN_SET",
		"ACK_SET",
		"RST_SET",
		"NONE_SET",
		"FINACK_SET",
		"NUM_FLAGS",
};

typedef enum {
	ORIGINAL,
	REPLY,
	NUM_DIRECTIONS,
} direction_t;

static char *direction_to_str[] = {
	"ORIGINAL",
	"REPLY",
};

static five_tuple_t reverse_five_tuple(five_tuple_t five_tuple) {
	five_tuple_t five_tuple_reverse = {
			.src_ipv4 = five_tuple.dst_ipv4,
			.dst_ipv4 = five_tuple.src_ipv4,
			.src_port = five_tuple.dst_port,
			.dst_port = five_tuple.src_port
	};
	return five_tuple_reverse;
}

#define get_direction(five_tuple) ((five_tuple).src_ipv4 > (five_tuple).dst_ipv4 ? ORIGINAL : REPLY)

static five_tuple_t direction_independent_five_tuple(five_tuple_t five_tuple) {
	if (get_direction(five_tuple) == ORIGINAL) {
		return five_tuple;
	}
	return reverse_five_tuple(five_tuple);
}


#define SWAP_ENDIAN_16(x) bswap_16(x)

#define SWAP_ENDIAN_32(x) bswap_32(x)

#endif //LOW_LEVEL_LIB_STRUCTS_H
