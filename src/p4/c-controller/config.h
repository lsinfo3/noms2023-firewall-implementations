#ifndef C_CONTROLLER_CONFIG_H
#define C_CONTROLLER_CONFIG_H

/*
 * Hashtable size
 */
#define FLOW_HASHTABLE_SIZE (1 << 20)

/*
 * Seed for the murmur hash function for the hashtable
 */
#define MURMUR_SEED 0xDEADBEEF

/*
 * Interface to receive packets from
 */
#define DP_IFACE "enp1s0"

/*
 * P4 CPU Port
 */
#define CPU_PORT 320

/*
 * Enable verbose logging (logs stuff per packet!!)
 */
#define VERBOSE


/*
 * DO NOT MODIFY BEYOND THIS LINE!!
 */

#ifndef NDEBUG
#define DEBUG
#endif

#ifdef DEBUG
#ifdef BENCH
#define ENABLE_BENCH
#endif

#ifdef VERBOSE
#define ENABLE_VERBOSE
#endif
#endif

#ifdef DEBUG
#include "time.h"
#define DEBUG_LOG(str, ...) {                                                                   \
    time_t __debug_time = time(NULL);                                                           \
    printf("%.24s "__FILE__"@%d " str "\n", ctime(&__debug_time), __LINE__, ## __VA_ARGS__);    \
    }
#else
#define DEBUG_LOG(...)
#endif

#ifdef ENABLE_BENCH
#define BENCH_PREPARE(name) struct timeval _bench_##name##_start, _bench_##name##_end, _bench_##name##_diff;
#define BENCH_START(name) gettimeofday(&_bench_##name##_start, NULL);
#define BENCH_END(name, str) \
	gettimeofday(&_bench_##name##_end, NULL); \
	timersub(&_bench_##name##_end, &_bench_##name##_start, &_bench_##name##_diff); \
	printf(str ": %ld.%06lds\n", _bench_##name##_diff.tv_sec, _bench_##name##_diff.tv_usec);
#else
#define BENCH_PREPARE(name)
#define BENCH_START(name)
#define BENCH_END(name, str)
#endif

#ifdef ENABLE_VERBOSE
#define VERBOSE_LOG(...) DEBUG_LOG(__VA_ARGS__)
#else
#define VERBOSE_LOG(...)
#endif

#define ERROR_LOG(str, ...) printf("ERROR: "__FILE__"@%d " str "\n", __LINE__, ## __VA_ARGS__);


#endif //C_CONTROLLER_CONFIG_H
