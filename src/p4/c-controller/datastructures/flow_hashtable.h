#ifndef LOW_LEVEL_LIB_FLOW_HASHTABLE_H
#define LOW_LEVEL_LIB_FLOW_HASHTABLE_H

#include <stdbool.h>

#include "./structs.h"
#include "../config.h"

typedef tcp_state_t flow_hashtable_value_t;

typedef struct {
	five_tuple_t key;
	flow_hashtable_value_t value;
	uint32_t hash;
	bool occupied;
} flow_hashtable_entry_t;

typedef struct {
	size_t num_entries;
	flow_hashtable_entry_t entries[FLOW_HASHTABLE_SIZE];
} flow_hashtable_t;

extern flow_hashtable_t flow_hashtable;

/*
 * Initialize the hashtable structure
 */
void flow_hashtable_init();

/*
 * Add a 5-tuple with its corresponding value to the hashtable (return != 0 on error)
 */
int flow_hashtable_add(const five_tuple_t *key, flow_hashtable_value_t value);

/*
 * Change the value of a specific 5-tuple (return != 0 on error/not found)
 */
int flow_hashtable_change(const five_tuple_t *key, flow_hashtable_value_t new_value);

/*
 * Retrieve the value for a specific 5-tuple (return != 0 on error/not found)
 */
int flow_hashtable_get(const five_tuple_t *key, flow_hashtable_value_t *value);

#endif //LOW_LEVEL_LIB_FLOW_HASHTABLE_H
