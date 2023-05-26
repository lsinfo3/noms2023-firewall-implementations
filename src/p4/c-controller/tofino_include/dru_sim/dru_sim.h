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
//
//  dru_sim.h
//
//  Created by Bruce McLoughlin on 7/14/14.
//

#ifndef lld_p2_dru_sim_h
#define lld_p2_dru_sim_h

#include <bfsys/bf_sal/bf_sys_dma.h>

#define dru_make_virtual(u64) ((void *)((uintptr_t)u64))
#define dru_make_wd_sz(ptr) ((uintptr_t)ptr)

// hack so we dont need to include lld/bf_dma_if.h,
// which requires lots of other stuff the model
// doesn't use
#define LLD_MAX_DR 100

typedef enum {
  FM = 0,
  RX,
  TX,
  CP,
} dr_type_e;

typedef enum {
  pcie_op_rd = 0,
  pcie_op_wr,
  pcie_op_dma_rd,
  pcie_op_dma_wr,
} pcie_op_e;

typedef struct pcie_msg_s {
  pcie_op_e typ;
  uint32_t asic;
  // Direct Access
  uint64_t addr;
  uint32_t value;
  // Indirect Access
  uint64_t ind_addr;
  // only for DMA rd/wr
  uint32_t len;
} pcie_msg_t;

typedef void (*cpu_to_pcie_wr_fn)(uint32_t asic, uint32_t addr, uint32_t value);
typedef uint32_t (*cpu_to_pcie_rd_fn)(uint32_t asic, uint32_t addr);
typedef void (*cpu_to_pcie_ind_wr_fn)(uint32_t asic,
                                      uint64_t addr,
                                      uint64_t data0,
                                      uint64_t data1);
typedef uint32_t (*cpu_to_pcie_ind_rd_fn)(uint32_t asic,
                                          uint64_t addr,
                                          uint64_t *data0,
                                          uint64_t *data1);
typedef void (*dru_to_pcie_dma_wr_fn)(uint32_t asic,
                                      uint64_t addr,
                                      uint8_t *buf,
                                      uint32_t n);
typedef void (*dru_to_pcie_dma_rd_fn)(uint32_t asic,
                                      uint64_t addr,
                                      uint8_t *buf,
                                      uint32_t n);
typedef void (*dru_rtn_pcie_rd_data_fn)(pcie_msg_t *msg, uint32_t value);
typedef pcie_msg_t *(*dru_next_pcie_msg_fn)(void);

typedef void (*dru_write_dma_chnl_fn)(uint8_t *buf, int len);
typedef int (*dru_read_dma_chnl_fn)(uint8_t *buf, int len);
typedef void (*dru_write_vpi_link_fn)(pcie_msg_t *msg);
typedef unsigned int (*dru_push_to_dru_fn)(pcie_msg_t *msg, int len);
typedef uint32_t (*dru_push_to_model_fn)(int typ,
                                         unsigned int asic,
                                         uint64_t reg,
                                         uint64_t data);

typedef struct dru_intf_t {
  cpu_to_pcie_wr_fn cpu_to_pcie_wr;
  cpu_to_pcie_rd_fn cpu_to_pcie_rd;
  cpu_to_pcie_ind_wr_fn cpu_to_pcie_ind_wr;
  cpu_to_pcie_ind_rd_fn cpu_to_pcie_ind_rd;
  dru_to_pcie_dma_wr_fn dru_to_pcie_dma_wr;
  dru_to_pcie_dma_rd_fn dru_to_pcie_dma_rd;
  dru_rtn_pcie_rd_data_fn dru_rtn_pcie_rd_data;
  dru_next_pcie_msg_fn dru_next_pcie_msg;
} dru_intf_t;

extern void dru_sim_cpu_to_pcie_wr(uint32_t asic,
                                   uint32_t addr,
                                   uint32_t value);
extern uint32_t dru_sim_cpu_to_pcie_rd(uint32_t asic, uint32_t addr);

extern void dru_init(int emu_integ, int parallel_mode);
extern void dru_create_service_thread(void);

typedef void *(*dru_sim_dma2virt_dbg_callback_fn)(bf_dma_addr_t dma_addr);

typedef void *(*dru_sim_dma2virt_dbg_callback_fn_fifo)(uint32_t asic,
                                                       bf_dma_addr_t dma_addr);

extern void dru_init_fifo(int debug_mode,
                          int emu_integ,
                          int parallel_mode,
                          dru_write_dma_chnl_fn wr_dma_fn,
                          dru_read_dma_chnl_fn rd_dma_fn,
                          dru_write_vpi_link_fn wr_vpi_fn,
                          dru_push_to_dru_fn push_to_dru_fn,
                          dru_push_to_model_fn push_to_model_fn,
                          dru_sim_dma2virt_dbg_callback_fn_fifo dma2virt_fn);

extern void dru_init_tcp(int debug_mode,
                         int emu_integ,
                         int parallel_mode,
                         dru_write_dma_chnl_fn wr_dma_fn,
                         dru_read_dma_chnl_fn rd_dma_fn,
                         dru_write_vpi_link_fn wr_vpi_fn,
                         dru_push_to_dru_fn push_to_dru_fn,
                         dru_push_to_model_fn push_model_fn,
                         dru_sim_dma2virt_dbg_callback_fn dma2virt_fn);
#ifdef DRU_INTF_SHM
extern void dru_init_shm(dru_intf_t *dru_intf);
#endif

extern int dru_init_mti(void);

int dru_sim_init(int tcp_port_base, dru_sim_dma2virt_dbg_callback_fn fn);
void *dru_pcie_dma_service_thread_entry(void *arg);

#endif
