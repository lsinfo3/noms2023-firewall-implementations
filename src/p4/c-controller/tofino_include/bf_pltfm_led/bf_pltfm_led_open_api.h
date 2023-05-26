#ifndef _BF_PLTFM_LED_OPEN_API_H
#define _BF_PLTFM_LED_OPEN_API_H


/* Allow the use in C++ code. */
#ifdef __cplusplus
extern "C" {
#endif

int bf_pltfm_i2c_led_dni_set(int chip_id, int color, int led_blink);

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _BF_PLTFM_LED_OPEN_API_H */