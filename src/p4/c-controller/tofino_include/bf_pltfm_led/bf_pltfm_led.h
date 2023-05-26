/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2016 Barefoot Networks, Inc.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of
 * Barefoot Networks, Inc. and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Barefoot Networks,
 * Inc.
 * and its suppliers and may be covered by U.S. and Foreign Patents, patents in
 * process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material is
 * strictly forbidden unless prior written permission is obtained from
 * Barefoot Networks, Inc.
 *
 * No warranty, explicit or implicit is provided, unless granted under a
 * written agreement with Barefoot Networks, Inc.
 *
 * $Id: $
 *
 ******************************************************************************/

#ifndef _BF_PLTFM_LED_H
#define _BF_PLTFM_LED_H
#ifdef INC_PLTFM_UCLI
#include <bfutils/uCli/ucli.h>
#endif

/* Allow the use in C++ code. */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  LED_NONE = 0,
  LED_RED,
  LED_GREEN,
  LED_BLUE,
  LED_PURPLE,
  LED_WHITE,
} bf_pltfm_led_color_t;

/* LED colors can be bit-wise ORed */
#define BF_DNI_PORT_LED_OFF 0x0
#define BF_DNI_PORT_LED_AMBER 0x4
#define BF_DNI_PORT_LED_GREEN 0x2
#define BF_DNI_PORT_LED_BLUE 0x1
#define BF_DNI_PORT_LED_PURPLE 0x5
#define BF_DNI_PORT_LED_WHITE 0x7
#define BF_DNI_PORT_LED_BLINK 0x8

typedef enum { LED_NO_BLINK = 0, LED_BLINK } bf_pltfm_led_blink_t;

/* display port led  by directly writing into sysCPLD */
int bf_pltfm_port_led_by_cpld_set(int chip_id,
                                  bf_pltfm_port_info_t *port_info,
                                  int led_col,
                                  bf_pltfm_led_blink_t led_blink);

int bf_pltfm_led_init(int chip_id);

#ifdef INC_PLTFM_UCLI
ucli_node_t *bf_pltfm_led_ucli_node_create(ucli_node_t *m);
#endif

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _BF_PLTFM_LED_H */
