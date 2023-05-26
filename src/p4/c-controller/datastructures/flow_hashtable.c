#include "flow_hashtable.h"

#include <string.h>

#include "hashes/MurmurHash3.h"

flow_hashtable_t flow_hashtable;

#if (FLOW_HASHTABLE_SIZE & (FLOW_HASHTABLE_SIZE - 1)) == 0
#define POSITIVE_MODULO(x) ((x) & (FLOW_HASHTABLE_SIZE - 1))
#else
#warning "Using suboptimal operators, as MAX_FLOWS, NUM_PIPES, or FLOW_HASHTABLE_MULTIPLIER is not a power of 2"
int32_t modulo(int32_t x) {
	x %= FLOW_HASHTABLE_SIZE;
	if (x < 0) {
		x += FLOW_HASHTABLE_SIZE;
	}
	return x;
}
#define POSITIVE_MODULO(x) modulo(x)
#endif

#define HASH2INDEX(hash) POSITIVE_MODULO(hash)


/*
 * Initialize the hashtable struct
 */
void flow_hashtable_init() {
	flow_hashtable.num_entries = 0;
	memset(flow_hashtable.entries, 0, sizeof(flow_hashtable_entry_t) * FLOW_HASHTABLE_SIZE);
}

static inline void flow_hashtable_hash_key(const five_tuple_t *key, uint32_t *hash) {
	MurmurHash3_x86_32(key, sizeof(five_tuple_t), MURMUR_SEED, hash);
}

/*
 * Add five tuple with flow id to hashtable, return 0 on success and 1 if hashtable is full
 */
int flow_hashtable_add(const five_tuple_t *key, const flow_hashtable_value_t value) {
	if (flow_hashtable.num_entries == FLOW_HASHTABLE_SIZE) {
		return 1;
	}
	int ret = 0;
	uint32_t hash;
	flow_hashtable_hash_key(key, &hash);

	int32_t index = HASH2INDEX(hash);
	while (flow_hashtable.entries[index].occupied) {
		if (flow_hashtable.entries[index].hash == hash) {
			if (memcmp(&flow_hashtable.entries[index].key, key, sizeof(five_tuple_t)) == 0) {
				ret = 1;
				break;
			}
		}
		index = (index + 1) % (FLOW_HASHTABLE_SIZE);
	}
	if (ret == 0) {
		flow_hashtable.entries[index].key = *key;
		flow_hashtable.entries[index].value = value;
		flow_hashtable.entries[index].hash = hash;
		flow_hashtable.num_entries++;
		flow_hashtable.entries[index].occupied = true;
	}
	return ret;
}


/*
 * Helper function to find the index for a given key, searches for the first free index in
 * the hashtable. Returns 1 if key is not in the hashtable.
 * Hashtable MUST be locked!
 */
static inline int get_hashtable_index(const five_tuple_t *key, const uint32_t hash, int32_t *index) {
	*index = HASH2INDEX(hash);

	do {
		// If this entry is not occupied, the key is not in this table
		if (!flow_hashtable.entries[*index].occupied)
			return 1;
		// If occupied and hash matches
		if (flow_hashtable.entries[*index].hash == hash) {
			// check if the key also matches
			if (memcmp(&flow_hashtable.entries[*index].key, key, sizeof(five_tuple_t)) == 0) {
				return 0;
			}
		}
		// otherwise, search the next entry
		*index = (*index + 1) % (FLOW_HASHTABLE_SIZE);
	} while (1);
}

int flow_hashtable_change(const five_tuple_t *key, flow_hashtable_value_t new_value) {
	int32_t index;
	uint32_t hash;
	int ret;
	flow_hashtable_hash_key(key, &hash);
	if ((ret = get_hashtable_index(key, hash, &index)) != 0) {
		return ret;
	}
	flow_hashtable.entries[index].value = new_value;
	return 0;
}

/*
 * Get the value for a given key. Return 0 if key is in hashtable, 1 otherwise.
 * Value can be NULL if it should be ignored.
 */
int flow_hashtable_get(const five_tuple_t *key, flow_hashtable_value_t *value) {
	int32_t index;
	uint32_t hash;
	flow_hashtable_hash_key(key, &hash);
	int ret = get_hashtable_index(key, hash, &index);
	if (value != NULL && ret == 0) {
		*value = flow_hashtable.entries[index].value;
	}
	return ret;
}

