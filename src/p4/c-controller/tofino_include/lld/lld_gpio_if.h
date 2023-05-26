/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2019 Barefoot Networks, Inc.

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
/*!
 *  * @file lld_gpio_if.h
 *   * @date
 *    *
 *     */

#ifndef __LLD_GPIO_IF_H_
#define __LLD_GPIO_IF_H_

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

#define BF_IO_STATEOUT_BUF_SIZE 256 /* 2K bit stateout buffer */
#define BF_IO_STATEIN_BUF_SIZE 32   /* 256 bit statein buffer */
#define BF_IO_NUM_PIN_PAIR 12

/* Macros for Tofino-1 */
#define GPIO_PAIR_OFFSET_BR_TOF1(idx, reg) \
  (offsetof(Tofino, ethgpiobr.gpio_pair_regs[idx].reg))

#define GPIO_PAIR_OFFSET_TL_TOF1(idx, reg) \
  (offsetof(Tofino, ethgpiotl.gpio_pair_regs[idx].reg))

#define GPIO_COMM_OFFSET_BR_TOF1(reg) \
  (offsetof(Tofino, ethgpiobr.gpio_common_regs.reg))

#define GPIO_COMM_OFFSET_TL_TOF1(reg) \
  (offsetof(Tofino, ethgpiotl.gpio_common_regs.reg))

#define GPIO_PAIR_OFFSET_TOF1(gpio_pin_pair, gpio_reg)                      \
  ((gpio_pin_pair >= (BF_IO_NUM_PIN_PAIR / 2))                              \
       ? GPIO_PAIR_OFFSET_BR_TOF1(gpio_pin_pair - (BF_IO_NUM_PIN_PAIR / 2), \
                                  gpio_reg)                                 \
       : GPIO_PAIR_OFFSET_TL_TOF1(gpio_pin_pair, gpio_reg))

#define GPIO_COMM_OFFSET_TOF1(gpio_pin_pair, gpio_reg) \
  ((gpio_pin_pair >= (BF_IO_NUM_PIN_PAIR / 2))         \
       ? GPIO_COMM_OFFSET_BR_TOF1(gpio_reg)            \
       : GPIO_COMM_OFFSET_TL_TOF1(gpio_reg))

/* Macros for Tofino-2 */
#define GPIO_PAIR_OFFSET_BR_TOF2(idx, reg) \
  (offsetof(tof2_reg, ethgpiobr.gpio_regs.gpio_pair_regs[idx].reg))

#define GPIO_PAIR_OFFSET_TL_TOF2(idx, reg) \
  (offsetof(tof2_reg, ethgpiotl.gpio_regs.gpio_pair_regs[idx].reg))

#define GPIO_COMM_OFFSET_BR_TOF2(reg) \
  (offsetof(tof2_reg, ethgpiobr.gpio_regs.gpio_common_regs.reg))

#define GPIO_COMM_OFFSET_TL_TOF2(reg) \
  (offsetof(tof2_reg, ethgpiotl.gpio_regs.gpio_common_regs.reg))

#define GPIO_PAIR_OFFSET_TOF2(gpio_pin_pair, gpio_reg)                      \
  ((gpio_pin_pair >= (BF_IO_NUM_PIN_PAIR / 2))                              \
       ? GPIO_PAIR_OFFSET_BR_TOF2(gpio_pin_pair - (BF_IO_NUM_PIN_PAIR / 2), \
                                  gpio_reg)                                 \
       : GPIO_PAIR_OFFSET_TL_TOF2(gpio_pin_pair, gpio_reg))

#define GPIO_COMM_OFFSET_TOF2(gpio_pin_pair, gpio_reg) \
  ((gpio_pin_pair >= (BF_IO_NUM_PIN_PAIR / 2))         \
       ? GPIO_COMM_OFFSET_BR_TOF2(gpio_reg)            \
       : GPIO_COMM_OFFSET_TL_TOF2(gpio_reg))

#define GPIO_COMM_OFFSET(dev_id, pin_pair, reg)                       \
  ((lld_dev_is_tofino(dev_id)) ? GPIO_COMM_OFFSET_TOF1(pin_pair, reg) \
                               : GPIO_COMM_OFFSET_TOF2(pin_pair, reg))

#define GPIO_PAIR_OFFSET(dev_id, pin_pair, reg)                       \
  ((lld_dev_is_tofino(dev_id)) ? GPIO_PAIR_OFFSET_TOF1(pin_pair, reg) \
                               : GPIO_PAIR_OFFSET_TOF2(pin_pair, reg))

/**
 * @addtogroup lld-gpio-api
 * @{
 */

/* enums defining pairs of  pins */
typedef enum {
  BF_IO_PIN_PAIR_0_1 = 0,
  BF_IO_PIN_PAIR_2_3 = 1,
  BF_IO_PIN_PAIR_4_5 = 2,
  BF_IO_PIN_PAIR_6_7 = 3,
  BF_IO_PIN_PAIR_8_9 = 4,
  BF_IO_PIN_PAIR_10_11 = 5,
  BF_IO_PIN_PAIR_12_13 = 6,
  BF_IO_PIN_PAIR_14_15 = 7,
  BF_IO_PIN_PAIR_16_17 = 8,
  BF_IO_PIN_PAIR_18_19 = 9,
  BF_IO_PIN_PAIR_20_21 = 10,
  BF_IO_PIN_PAIR_22_23 = 11,

  BF_IO_PIN_PAIR_MAX = 11 /* keep this the last */
} bf_io_pin_pair_t;

typedef enum {
  /* enums defining individual GPIO pins */
  /* enums defining individual GPIO pins */
  BF_GPIO_PIN_0 = 0,
  BF_GPIO_PIN_1 = 1,
  BF_GPIO_PIN_2 = 2,
  BF_GPIO_PIN_3 = 3,
  BF_GPIO_PIN_4 = 4,
  BF_GPIO_PIN_5 = 5,
  BF_GPIO_PIN_6 = 6,
  BF_GPIO_PIN_7 = 7,
  BF_GPIO_PIN_8 = 8,
  BF_GPIO_PIN_9 = 9,
  BF_GPIO_PIN_10 = 10,
  BF_GPIO_PIN_11 = 11,
  BF_GPIO_PIN_12 = 12,
  BF_GPIO_PIN_13 = 13,
  BF_GPIO_PIN_14 = 14,
  BF_GPIO_PIN_15 = 15,
  BF_GPIO_PIN_16 = 16,
  BF_GPIO_PIN_17 = 17,
  BF_GPIO_PIN_18 = 18,
  BF_GPIO_PIN_19 = 19,
  BF_GPIO_PIN_20 = 20,
  BF_GPIO_PIN_21 = 21,
  BF_GPIO_PIN_22 = 22,
  BF_GPIO_PIN_23 = 23,
  BF_GPIO_PIN_MAX = 23 /* keep this the last */
} bf_gpio_pin_t;

#define BF_GPIO_NUM_PIN 24

/* mode selection */
typedef enum {
  BF_IO_MODE_GPIO = 0,
  BF_IO_MODE_I2C = 1,
  BF_IO_MODE_MDIO = 2,
} bf_io_mode_t;

typedef enum { BF_GPIO_IN = 0, BF_GPIO_OUT = 1 } bf_gpio_dir_t;

typedef enum {
  BF_GPIO_PULL_DOWN = 0, /* activate pull down resistor on o/p */
  BF_GPIO_PULL_UP = 1    /* activate pull up resistor on o/p */
} bf_gpio_pull_dir_t;

typedef enum {
  BF_GPIO_OUT_Z = 1, /* level is high impedance */
  BF_GPIO_OUT_L = 2, /* level is logic 0 */
  BF_GPIO_OUT_H = 3  /* level is logic high */
} bf_gpio_output_level_t;

typedef enum {
  BF_GPIO_LEVEL = 0,     /* particular level on GPIO causes a trigger event */
  BF_GPIO_ANY_EDGE = 1,  /* an edge on gpio pin causes a trigger event */
  BF_GPIO_EDGE_RISE = 2, /* rising edge on gpio pin causes a trigger event */
  BF_GPIO_EDGE_FALL = 3  /* falling edge on gpio pin causes a trigger event */
} bf_gpio_trigger_mode_t;

typedef enum {
  BF_GPIO_DRIVE_4MA = 0,  /* 4mA drive */
  BF_GPIO_DRIVE_6MA = 1,  /* 6mA drive */
  BF_GPIO_DRIVE_8MA = 2,  /* 8mA drive */
  BF_GPIO_DRIVE_12MA = 3, /* 12mA drive */
} bf_gpio_drive_t;

typedef struct bf_host_gpio_pad_ctrl_s {
  bf_gpio_pull_dir_t pull_dir;
  bool pull_en;
  bf_gpio_drive_t drv;
} bf_host_gpio_pad_ctrl_t;

/* Mode Setting */

bf_status_t bf_io_set_mode_i2c(bf_dev_id_t dev_id, bf_io_pin_pair_t pin_pair);

bf_status_t bf_io_set_mode_mdio(bf_dev_id_t dev_id, bf_io_pin_pair_t pin_pair);

/* if a pair of pins are configured as GPIO, then, we program the output levels
 * before we (later on) set the direction as output type */
bf_status_t bf_io_set_mode_gpio(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                bf_gpio_output_level_t level_pin0,
                                bf_gpio_output_level_t level_pin1);

bf_status_t bf_io_get_mode(bf_dev_id_t dev_id,
                           bf_io_pin_pair_t index,
                           bf_io_mode_t *mode);

/* GPIO APIs */
/* gpio_pin in below APIs run 0 thru BF_GPIO_PIN_23 */

bf_status_t bf_gpio_set_dir(bf_dev_id_t dev_id,
                            bf_gpio_pin_t gpio_pin,
                            bf_gpio_dir_t dir,
                            bf_gpio_output_level_t level);

bf_status_t bf_gpio_set_level(bf_dev_id_t dev_id,
                              bf_gpio_pin_t gpio_pin,
                              bf_gpio_output_level_t level);

bf_status_t bf_gpio_get_level(bf_dev_id_t dev_id,
                              bf_gpio_pin_t gpio_pin,
                              bool *level);

bf_status_t bf_gpio_set_pullup(bf_dev_id_t dev_id,
                               bf_gpio_pin_t gpio_pin,
                               bf_gpio_pull_dir_t pull_dir,
                               bool en);

bf_status_t bf_gpio_get_pullup(bf_dev_id_t dev_id,
                               bf_gpio_pin_t gpio_pin,
                               bf_gpio_pull_dir_t *pull_dir,
                               bool *en);

/* period is in “num_10_nano_seconds” */
bf_status_t bf_gpio_set_debounce_time(bf_dev_id_t dev_id,
                                      bf_gpio_pin_t gpio_pin,
                                      uint8_t period);

bf_status_t bf_gpio_set_trigger_mode(bf_dev_id_t dev_id,
                                     bf_gpio_pin_t gpio_pin,
                                     bf_gpio_trigger_mode_t mode);

/* GPIO APIs */

bf_status_t bf_mdio_set_clk(bf_dev_id_t dev_id,
                            bf_io_pin_pair_t pin_pair,
                            uint8_t clock_period);
/*
 *   Following MDIO APIs are non-blocking. Caller can initiate an mdio
 *   transaction and get back later to check the result. After initiating an
 *   mdio operation, if  the status (for write type operation) or result
 *   (for read type operation) is not checked before initiating next mdio
 *   transaction, then, the status or result of the previous transaction would
 *   be unrecoverably erased. If the previous transaction is incomplete when
 *   initiating  the next transaction, the later one would return with
 *   appropriate error code.
 */
/* Issue MDIO operation */
/* write address to MDIO device */
bf_status_t bf_mdio_issue_addr(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               uint8_t phy_addr,
                               uint8_t dev_type,
                               uint16_t address);

/* write data to MDIO device */
bf_status_t bf_mdio_issue_wr(bf_dev_id_t dev_id,
                             bf_io_pin_pair_t pin_pair,
                             uint8_t phy_addr,
                             uint8_t dev_type,
                             uint16_t data);

/* read data from MDIO device */
bf_status_t bf_mdio_issue_rd(bf_dev_id_t dev_id,
                             bf_io_pin_pair_t pin_pair,
                             uint8_t phy_addr,
                             uint8_t dev_type);

/* read data and post address increment from MDIO device */
bf_status_t bf_mdio_issue_rd_and_incr_addr(bf_dev_id_t dev_id,
                                           bf_io_pin_pair_t pin_pair,
                                           uint8_t phy_addr,
                                           uint8_t dev_type);

/* legacy clause-22 devices */
bf_status_t bf_mdio22_issue_wr(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               uint8_t phy_addr,
                               uint8_t reg_addr,
                               uint16_t data);

bf_status_t bf_mdio22_issue_rd(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               uint8_t phy_addr,
                               uint8_t reg_addr);

/* check for completion of MDIO operation */
bf_status_t bf_mdio_get_completion_status(bf_dev_id_t dev_id,
                                          bf_io_pin_pair_t pin_pair,
                                          bool *complete);

/* get the data back from read-type MDIO operation */
bf_status_t bf_mdio_get_rd_data(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                uint16_t *data);

bf_status_t bf_mdio22_get_rd_data(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint16_t *data);

/* Following MDIO transactions are blocking calls (sleep or busy wait).
 */

/* write address to MDIO device */
bf_status_t bf_mdio_addr_blocking(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint8_t phy_addr,
                                  uint8_t dev_type,
                                  uint16_t address);

/* write data to MDIO device */
bf_status_t bf_mdio_wr_blocking(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                uint8_t phy_addr,
                                uint8_t dev_type,
                                uint16_t data);

/* read data from MDIO device */
bf_status_t bf_mdio_rd_blocking(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                uint8_t phy_addr,
                                uint8_t dev_type,
                                uint16_t *data);

/* read data and post address increment from MDIO device */
bf_status_t bf_mdio_rd_and_incr_addr_blocking(bf_dev_id_t dev_id,
                                              bf_io_pin_pair_t pin_pair,
                                              uint8_t phy_addr,
                                              uint8_t dev_type,
                                              uint16_t *data);

/*  legacy clause-22 devices */
bf_status_t bf_mdio22_wr_blocking(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint8_t phy_addr,
                                  uint8_t reg_addr,
                                  uint16_t data);

bf_status_t bf_mdio22_rd_blocking(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint8_t phy_addr,
                                  uint8_t reg_addr,
                                  uint16_t *data);

/*  I2C APIs */
typedef enum {
  BF_I2C_MODE_REG = 0,
  BF_I2C_MODE_STATEOUT = 1,
  BF_I2C_MODE_STATEIN = 2,
  BF_I2C_MODE_RSVD = 3
} bf_i2c_mode_t;

/* clock period is in “num_10_nano_seconds” */
bf_status_t bf_i2c_set_clk(bf_dev_id_t dev_id,
                           bf_io_pin_pair_t pin_pair,
                           uint16_t clock_period);

/* set i2c access mode */
bf_status_t bf_i2c_set_submode(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               bf_i2c_mode_t mode);

/* get i2c access mode */
bf_status_t bf_i2c_get_submode(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               bf_i2c_mode_t *mode);

/* write to common 2K bit stateout buffer */
bf_status_t bf_write_stateout_buf(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint32_t offset,
                                  uint8_t *buf,
                                  int num_data_bytes);

/* read common 2K bit stateout buffer */
bf_status_t bf_read_stateout_buf(bf_dev_id_t dev_id,
                                 bf_io_pin_pair_t pin_pair,
                                 uint32_t offset,
                                 uint8_t *buf,
                                 int num_data_bytes);

/* write to common 2K bit stateout buffer */
bf_status_t bf_write_statein_buf(bf_dev_id_t dev_id,
                                 bf_io_pin_pair_t pin_pair,
                                 uint32_t offset,
                                 uint8_t *buf,
                                 int num_data_bytes);

/* read common 2K bit stateout buffer */
bf_status_t bf_read_statein_buf(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                uint32_t offset,
                                uint8_t *buf,
                                int num_data_bytes);

/* enable or disable on going statein operations */
bf_status_t bf_i2c_statein_enable(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  bool en);

/*
 * Following i2c APIs are non-blocking. Caller can initiate an i2c transaction
 * and get back later to check the result. After initiating an i2c operation,
 * if  the status (for write type operation) or result (for read type operation)
 * is not checked before initiating next i2c transaction, then, the status or
 * result of the previous transaction would be unrecoverably erased. If the
 * previous transaction is incomplete when initiating  the next transaction,
 * the later one would return with appropriate error code.
 */

/* Issue i2c operation */
bf_status_t bf_i2c_issue_wr_reg(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                uint8_t i2c_addr,
                                uint32_t reg_addr,
                                int num_addr_bytes,
                                uint8_t *buf,
                                int num_data_bytes);

bf_status_t bf_i2c_issue_rd_reg(bf_dev_id_t dev_id,
                                bf_io_pin_pair_t pin_pair,
                                uint8_t i2c_addr,
                                uint32_t reg_addr,
                                int num_addr_bytes,
                                int num_data_bytes);

bf_status_t bf_i2c_issue_stateout(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint8_t i2c_addr,
                                  uint32_t reg_addr,
                                  int num_addr_bytes,
                                  uint8_t statout_addr,
                                  int num_bytes);

bf_status_t bf_i2c_issue_statein(bf_dev_id_t dev_id,
                                 bf_io_pin_pair_t pin_pair,
                                 uint8_t i2c_addr,
                                 uint32_t reg_addr,
                                 int num_addr_bytes,
                                 uint8_t statin_addr,
                                 int num_bits,
                                 uint32_t trigger_mode,
                                 uint32_t period);

/* check for completion of i2c operation */
bf_status_t bf_i2c_get_completion_status(bf_dev_id_t dev_id,
                                         bf_io_pin_pair_t pin_pair,
                                         bool *complete);

/* get the data back from read-type i2c operation  */

bf_status_t bf_i2c_get_rd_data(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               uint8_t *buf,
                               int num_bytes);

bf_status_t bf_i2c_get_statein_data(bf_dev_id_t dev_id,
                                    bf_io_pin_pair_t pin_pair,
                                    uint8_t *buf,
                                    int num_bytes);

/* Following I2C transactions are the blocking versions of the calls with a
 * sleep of anticipated delay.
 */
/* reset the i2c bus */
bf_status_t bf_i2c_reset(bf_dev_id_t dev_id, bf_io_pin_pair_t pin_pair);

/* probes an end point device to quickly check its presence */
bf_status_t bf_i2c_probe_blocking(bf_dev_id_t dev_id,
                                  bf_io_pin_pair_t pin_pair,
                                  uint8_t i2c_addr);

/* read bytes from the current address */
bf_status_t bf_i2c_rd_blocking(bf_dev_id_t dev_id,
                               bf_io_pin_pair_t pin_pair,
                               uint8_t i2c_addr,
                               uint8_t *buf,
                               int rd_cnt);

/* generic reg i2c write */
bf_status_t bf_i2c_wr_reg_blocking(bf_dev_id_t dev_id,
                                   bf_io_pin_pair_t pin_pair,
                                   uint8_t i2c_addr,
                                   uint32_t reg_addr,
                                   int num_addr_bytes,
                                   uint8_t *buf,
                                   int num_data_bytes);

/* generic ireg 2c read */
bf_status_t bf_i2c_rd_reg_blocking(bf_dev_id_t dev_id,
                                   bf_io_pin_pair_t pin_pair,
                                   uint8_t i2c_addr,
                                   uint32_t reg_addr,
                                   int num_addr_bytes,
                                   uint8_t *buf,
                                   int num_data_bytes);

/* multi byte i2c operation */
/* Tofino carries out multi-byte operations using its internal temporary buffers
 * called statein and stateout buffers.  Controller takes the offset into this
 * internal memory. we can remove parameters <statein_addr> and <stateout_addr>
 * from below APIs if we do not want data to be preserved in the internal buffer
 * for any reason.  (does p4 program make use of this internal buffer
 * automatically??)
 */
bf_status_t bf_i2c_statein_blocking(bf_dev_id_t dev_id,
                                    bf_io_pin_pair_t pin_pair,
                                    uint8_t i2c_addr,
                                    uint8_t statin_addr,
                                    uint8_t *buf,
                                    int num_bits);

/* write wr_bytes from buf to internal stateout address and also
 * out on i2c bus */
bf_status_t bf_i2c_stateout_blocking(bf_dev_id_t dev_id,
                                     bf_io_pin_pair_t pin_pair,
                                     uint8_t i2c_addr,
                                     uint8_t statout_addr,
                                     uint8_t *buf,
                                     int num_bytes);

bf_status_t bf_host_gpio_set_mode_pad_ctrl(bf_dev_id_t dev_id,
                                           bf_host_gpio_pad_ctrl_t *pad_ctrl);

bf_status_t bf_host_gpio_set_i2c_pad_ctrl(bf_dev_id_t dev_id,
                                          bf_host_gpio_pad_ctrl_t *pad_ctrl);

bf_status_t bf_host_gpio_set_bare_pad_ctrl(bf_dev_id_t dev_id,
                                           bf_host_gpio_pad_ctrl_t *pad_ctrl);

bf_status_t bf_host_gpio_set_misc_pad_ctrl(bf_dev_id_t dev_id,
                                           bf_host_gpio_pad_ctrl_t *pad_ctrl);

/* @} */

#ifdef __cplusplus
}
#endif /* C++ */

#endif
