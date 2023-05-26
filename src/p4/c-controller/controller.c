#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "datastructures/flow_hashtable.h"
#include "dataplane/dp_api.h"
#include "packet_handler/packet_handler.h"
#include <tofino/pdfixed/pd_tm.h>


const char *getfield(char *line, int num) {
	const char *tok;
	for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
		if (!--num) {
			return tok;
		}
	}
	return NULL;
}

/*
 * Read a rules file and insert all firewall rules into the data plane
 */
void read_rules(char *filename) {
	printf("Reading rules from %s\n", filename);

	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("Error reading rules file %s\n", filename);
		exit(1);
	}

	char line[256];
	char *tmp;

	while (fgets(line, 256, file)) {
		tmp = strdup(line);
		const char *src_ip_str = getfield(tmp, 2);
		uint32_t src_ip;
		inet_pton(AF_INET, src_ip_str, (void *) &src_ip);
		free(tmp);

		tmp = strdup(line);
		port_t src_port = atoi(getfield(tmp, 3));
		free(tmp);

		tmp = strdup(line);
		const char *dst_ip_str = getfield(tmp, 4);
		uint32_t dst_ip;
		inet_pton(AF_INET, dst_ip_str, (void *) &dst_ip);
		free(tmp);

		tmp = strdup(line);
		port_t dst_port = atoi(getfield(tmp, 5));
		free(tmp);

		five_tuple_t five_tuple = {
				.src_ipv4 = src_ip,
				.dst_ipv4 = dst_ip,
				.src_port = src_port,
				.dst_port = dst_port
		};

		tcp_state_t init_state = NONE;

		five_tuple_t direction_independent_ft = direction_independent_five_tuple(five_tuple);

		if (flow_hashtable_add(&direction_independent_ft, init_state) != 0) {
			ERROR_LOG("Error when adding flow to hashtable!")
			exit(1);
		}

		add_rules(five_tuple, init_state);
		add_firewall_rule(five_tuple);
		add_firewall_rule(reverse_five_tuple(five_tuple));
        insert_forwarding_rules_ip(five_tuple);
	}
}

/*
 * Prepares data plane and starts packet loop
 */
void low_level_controller() {
	DEBUG_LOG("Initializing data structures")
	flow_hashtable_init();
	switch_connect();

	p4_pd_tm_set_cpuport(0, CPU_PORT);
	read_rules("/home/manuel/controllerenv/rules.csv");  // TODO
	insert_forwarding_rules();

	packet_thread();
}
