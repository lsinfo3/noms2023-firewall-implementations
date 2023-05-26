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
 * @file bf_usd.h
 * @date
 *
 *
 */

#ifndef _BF_USD_H_
#define _BF_USD_H_

/**
 * mmap bfn uio device based on its device filename
 * @param uio_name device filename (in)
 * @param v_addr virtual address pointer (out)
 * @param pci_size size of BAR0 region of the device (out)
 * @return Status 0 on Success, -1 on failure
 */
int bf_mmap_by_name(char *uio_name, void **v_addr, size_t *pci_size);

/**
 * find bfn uio device file name based on its pcie bus:fun:device
 * @param name device filename (out)
 * @param name_size size of "name" (in)
 * @param domain pcie bus domain of device
 * @param b pcie bus num of device
 * @param f pcie function of device
 * @param d pcie device num of device
 * @return Status 0 on Success, -1 on failure
 */
int bf_name_from_bfd(char *name,
                     size_t name_size,
                     uint16_t domain,
                     uint8_t b,
                     uint8_t f,
                     uint8_t d);

/**
 * unmap previously mmapped bf pci space
 * @param v_addr virtual address
 * @param len previously mmapped size
 * @return none
 */
void bf_unmmap(void *v_addr, size_t len);

/**
 * open a uio file
 * @param uio_name device filename (in)
 * @flags flags as in open() system call
 * @return file handle
 */
int bf_uio_open(char *uio_name, int flags);

/**
 * close a uio file
 * @fd file handle of uio device
 * @return 0
 */
int bf_uio_close(int fd);
#endif
