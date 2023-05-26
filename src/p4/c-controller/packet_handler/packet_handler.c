#include <string.h>
#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "packet_handler.h"
#include "../config.h"
#include "../datastructures/structs.h"
#include "../datastructures/flow_hashtable.h"
#include "../tcp.h"
#include "../dataplane/dp_api.h"

#ifdef MOCK_PACKETS
#include "../mock_packets.h"
#endif

#define MAX_PKT_LEN 2048
#define ETHERTYPE_IPV4_BE 0x0008

pcap_t *send_descr = NULL;

/*
 * Helper function to print packet hexdumps
 */
void hexDump(const char *desc, const void *addr, const int len) {
	int i;
	unsigned char buff[17];
	const unsigned char *pc = (const unsigned char *) addr;

	// Output description if given.

	if (desc != NULL) {
		printf("%s:\n", desc);
	}

	// Length checks.
	if (len == 0) {
		printf("  ZERO LENGTH\n");
		return;
	}
	else {
		if (len < 0) {
			printf("  NEGATIVE LENGTH: %d\n", len);
			return;
		}
	}

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).
		if ((i % 16) == 0) {
			// Don't print ASCII buffer for the "zeroth" line.
			if (i != 0) {
				printf("  %s\n", buff);
			}
			// Output the offset.
			printf("  %04x ", i);
		}

		// Now the hex code for the specific character.
		printf(" %02x", pc[i]);

		// And buffer a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e)) { // isprint() may be better.
			buff[i % 16] = '.';
		}
		else {
			buff[i % 16] = pc[i];
		}
		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
		printf("   ");
		i++;
	}
	// And print the final ASCII buffer.
	printf("  %s\n", buff);
}

static void print_five_tuple(five_tuple_t five_tuple, char *buf) {
	char src[INET_ADDRSTRLEN], dst[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &five_tuple.src_ipv4, src, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &five_tuple.dst_ipv4, dst, INET_ADDRSTRLEN);
	sprintf(buf, "%s:%d -> %s:%d", src, five_tuple.src_port, dst, five_tuple.dst_port);
}

/*
 * Process a single TCP packet
 * Returns True if successful
 */
bool process_packet(five_tuple_t five_tuple, tcp_flags_t tcp_flags) {
	// We save direction independent 5-tuples in the hashtable to ensure have one state
	// for each flow and not one state for each subflow
	five_tuple_t direction_ind_five_tuple = direction_independent_five_tuple(five_tuple);
	flow_hashtable_value_t old_state;

	char buf[256];
	print_five_tuple(five_tuple, buf);
	VERBOSE_LOG("Received packet %s", buf);

	if (flow_hashtable_get(&direction_ind_five_tuple, &old_state) != 0) {
		ERROR_LOG("Fivetuple not in flows!!")
		return false;
	}

	direction_t direction = get_direction(five_tuple);

	tcp_state_t new_state = transitions[direction][tcp_flags][old_state];

	VERBOSE_LOG("State transition in direction %s from %s to %s", direction_to_str[direction], state_to_str[old_state], state_to_str[new_state])

	if (new_state == INVALID || new_state == IGNORE) {
		ERROR_LOG("Received invalid transition: %s, %s, %s", buf, direction_to_str[direction], state_to_str[new_state])
		return false;
	}

	if (new_state == old_state) {
		ERROR_LOG("Received %s and this should stay in state %s", flag_to_str[tcp_flags], state_to_str[new_state])
		return false;
	}

	// Update the data plane rules
	remove_rules(five_tuple, old_state);
	add_rules(five_tuple, new_state);
	// Update flow state in the hashtable
	flow_hashtable_change(&direction_ind_five_tuple, new_state);
	return true;
}

/*
 * Extract the TCP flags and map them to tcp_flags_t
 */
static tcp_flags_t extract_tcp_flags(struct tcphdr *tcpHeader) {
	if (tcpHeader->th_flags & TH_RST) {
		return RST_SET;
	}
	else {
		if (tcpHeader->th_flags & TH_SYN) {
			if (tcpHeader->th_flags & TH_ACK) {
				return SYNACK_SET;
			}
			else {
				return SYN_SET;
			}
		}
		else {
			if (tcpHeader->th_flags & TH_FIN) {
				if (tcpHeader->th_flags & TH_ACK) {
					return FINACK_SET;
				}
				else {
					return FIN_SET;
				}
			}
			else {
				if (tcpHeader->th_flags & TH_ACK) {
					return ACK_SET;
				}
				else {
					return NONE_SET;
				}
			}
		}
	}
}

/*
 * Extract the next header from the packet, return if the header is longer than
 * the remaining packet
 */
#define EXTRACT(dest, type)                                  \
    if ((curSize + sizeof(type)) > pkthdr->caplen) return;   \
    (dest) = (type *) (packet + curSize);                    \
    curSize += sizeof(type);

/*
 * gets called from the pcap_loop function for each received packet
 * parses the ethernet, L3 and L4 headers and calls process_packet for each relevant packet
 */
static void packet_handler(u_char *arg __attribute__((unused)),
						   const struct pcap_pkthdr *pkthdr, const u_char *packet) {
	five_tuple_t five_tuple;
	memset(&five_tuple, 0, sizeof(five_tuple_t));

	struct ether_header *etherHeader = NULL;
	struct iphdr *ipHeader = NULL;
	struct tcphdr *tcpHeader = NULL;
	tcp_flags_t tcp_flags;

	size_t curSize = 0;

	EXTRACT(etherHeader, struct ether_header)

	VERBOSE_LOG("New packet of type %d", etherHeader->ether_type)
#ifdef VERBOSE
	hexDump(NULL, etherHeader, sizeof(struct ether_header));
#endif

	if (etherHeader->ether_type != ETHERTYPE_IPV4_BE) {
		return;
	}

	EXTRACT(ipHeader, struct iphdr)

#ifdef VERBOSE
	hexDump(NULL, ipHeader, sizeof(struct iphdr));
#endif

	five_tuple.src_ipv4 = ipHeader->saddr;
	five_tuple.dst_ipv4 = ipHeader->daddr;

	if (ipHeader->protocol != IPPROTO_TCP) {
		return;
	}

	EXTRACT(tcpHeader, struct tcphdr)

#ifdef VERBOSE
	hexDump(NULL, tcpHeader, sizeof(struct tcphdr));
#endif

	five_tuple.dst_port = SWAP_ENDIAN_16(tcpHeader->dest);
	five_tuple.src_port = SWAP_ENDIAN_16(tcpHeader->source);
	tcp_flags = extract_tcp_flags(tcpHeader);

	if (process_packet(five_tuple, tcp_flags)) {
		VERBOSE_LOG("Trying to send packet");
	    if (pcap_sendpacket(send_descr, packet, (int) pkthdr->caplen) < 0) {
            ERROR_LOG("Could not send packet to switch")
            return;
        }
	}
}

/*
 * executes the pcap_loop function which listens on the interface given in args
 */
void packet_thread() {
#ifdef MOCK_PACKETS
	//	for (int i=0; i<3; i++) {mock_packets();}exit(0);
	//	while (1) { mock_packets(); }
		while (1) { mock_raw_packets(packet_handler); }
#else
	char errbuf[PCAP_ERRBUF_SIZE];
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);

	DEBUG_LOG("Opening network send interface")
	if ((send_descr = pcap_open_live(DP_IFACE, MAX_PKT_LEN, 1, 512, errbuf)) == NULL) {
		printf("%s", errbuf);
		exit(1);
	}

	pcap_t *descr = NULL;
	DEBUG_LOG("Opening network receive interface")
	if ((descr = pcap_open_live(DP_IFACE, MAX_PKT_LEN, 1, 512, errbuf)) == NULL) {
		printf("%s", errbuf);
		exit(1);
	}

	DEBUG_LOG("pcap_loop")
	pcap_loop(descr, -1, packet_handler, NULL);
#endif
}