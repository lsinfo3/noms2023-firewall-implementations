//
// Created by joshua on 2/28/21.
//

#ifndef LOW_LEVEL_LIB_PACKET_HANDLER_H
#define LOW_LEVEL_LIB_PACKET_HANDLER_H

#include <pcap.h>

// this descriptor is required for sending packets
extern pcap_t *send_descr;

void packet_thread();

#endif //LOW_LEVEL_LIB_PACKET_HANDLER_H
