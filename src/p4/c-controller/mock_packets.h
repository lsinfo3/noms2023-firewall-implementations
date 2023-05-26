#ifndef LOW_LEVEL_LIB_MOCK_PACKETS_H
#define LOW_LEVEL_LIB_MOCK_PACKETS_H

#include <sys/time.h>
#include <unistd.h>

typedef void (*packet_handler_t)(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet);

void mock_raw_packets(packet_handler_t handler) {
	VERBOSE_LOG("Creating raw packet")
	static u_char raw_packet[255] = \
        "\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x08\x00\x45\x00" \
        "\x00\x28\x00\x01\x00\x00\x40\x06\x7c\xcd\x7f\x00\x00\x01\x7f\x00" \
        "\x00\x01\x00\x14\x00\x50\x00\x00\x00\x00\x00\x00\x00\x00\x50\x02" \
        "\x20\x00\x91\x7c\x00\x00";
	static struct pcap_pkthdr pkthdr = {
			.caplen = 255,
			.len = 255
	};
	raw_packet[5] += 1;
	raw_packet[10] += 1;
	handler(NULL, &pkthdr, raw_packet);
	usleep(3 * 1000 * 1000);
}

#endif //LOW_LEVEL_LIB_MOCK_PACKETS_H
