#ifndef _BF_UTILS_ALGORITHM_H_
#define _BF_UTILS_ALGORITHM_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  CRC_8,
  CRC_8_DARC,
  CRC_8_I_CODE,
  CRC_8_ITU,
  CRC_8_MAXIM,
  CRC_8_ROHC,
  CRC_8_WCDMA,
  CRC_16,
  CRC_16_BYPASS,
  CRC_16_DDS_110,
  CRC_16_DECT,
  CRC_16_DECT_R,
  CRC_16_DECT_X,
  CRC_16_DNP,
  CRC_16_EN_13757,
  CRC_16_GENIBUS,
  CRC_16_MAXIM,
  CRC_16_MCRF4XX,
  CRC_16_RIELLO,
  CRC_16_T10_DIF,
  CRC_16_TELEDISK,
  CRC_16_USB,
  X_25,
  XMODEM,
  MODBUS,
  KERMIT,
  CRC_CCITT_FALSE,
  CRC_AUG_CCITT,
  CRC_32,
  CRC_32_BZIP2,
  CRC_32C,
  CRC_32D,
  CRC_32_MPEG,
  POSIX,
  CRC_32Q,
  JAMCRC,
  XFER,
  CRC_64,
  CRC_64_GO_ISO,
  CRC_64_WE,
  CRC_64_JONES,
  CRC_INVALID
} bfn_crc_alg_t;

typedef enum {
  IDENTITY_DYN,
  CRC_DYN,
  RANDOM_DYN,
  XOR_DYN,
  INVALID_DYN
} bfn_hash_alg_type_t;

static inline bfn_hash_alg_type_t hash_alg_str_to_type(const char *alg_name) {
  if (!strcmp(alg_name, "identity")) {
    return IDENTITY_DYN;
  }
  if (!strcmp(alg_name, "crc")) {
    return CRC_DYN;
  }
  if (!strcmp(alg_name, "random")) {
    return RANDOM_DYN;
  }
  if (!strcmp(alg_name, "xor")) {
    return XOR_DYN;
  }
  return INVALID_DYN;
}

/**
 * Holds a char * value representing the required information for the standard
 * algorithms
 */
typedef struct crc_alg_info_ {
  char *crc_name;
  uint64_t poly;
  bool reverse;
  uint64_t init;
  uint64_t final_xor;
} crc_alg_info_t;

typedef struct bfn_hash_algorithm_ {
  bfn_hash_alg_type_t hash_alg;
  bool msb;
  bool extend;
  ///> All below only valid for crc algorithm
  int hash_bit_width;
  bool reverse;
  uint64_t poly;
  uint64_t init;
  uint64_t final_xor;
  uint8_t **crc_matrix;
} bfn_hash_algorithm_t;

/**
 * Verifies that the parameters of a crc algorithm are possible.  Currently
 * ensures that the polynomial is odd, and that the sizes of the init and
 * final_xor values correctly fit within the size of the polynomial
 */
bool verify_algorithm(bfn_hash_algorithm_t *alg, char **error_message);

/**
 * Given a list of parameters, this will build an algorithm to be used in a
 * hash matrix calculation
 *
 *     alg - The algorithm to be created
 *     hash_alg_type - The type of the hash algorithm.
 *     msb - whether the algorithm starts at the most significant bit
 *     extend - whether the algorithm output is repeated
 *     crc_alg - the crc algorithm type to build the crc algorithm
 */
void initialize_algorithm(bfn_hash_algorithm_t *alg,
                          bfn_hash_alg_type_t hash_alg_type,
                          bool msb,
                          bool extend,
                          bfn_crc_alg_t crc_alg);

void initialize_crc_matrix(bfn_hash_algorithm_t *alg);

void calculate_crc(bfn_hash_algorithm_t *alg,
                   uint32_t hash_output_bits,
                   uint8_t *stream,
                   uint32_t stream_len,
                   uint8_t *crc);

#ifdef __cplusplus
}
#endif

#endif /* _BF_UTILS_ALGORITHM_H_ */
