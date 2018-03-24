/*
 * Copyright (c) 2018 Idein Inc. ( http://idein.jp/ )
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#ifndef MAILBOX_H_
#define MAILBOX_H_

#include <mailbox/raspberrypi-firmware.h>
#include <stdint.h>

    int mailbox_open(void);
    int mailbox_close(const int fd);

    /* Raw ioctl. */
    int mailbox_property(const int fd, void *buf);

    /* Official-kernel-driver-like wrappers. */
    int rpi_firmware_property_list(const int fd, void *data, uint32_t tag_size);
    int rpi_firmware_property(const int fd, const uint32_t tag, void *tag_data,
            const uint32_t buf_size, const uint32_t req_resp_size);

    /* hello_pi/hello_fft-like userland wrappers. */
    uint32_t mailbox_mem_alloc(const int fd, const uint32_t size,
            const uint32_t align, const uint32_t flags);
    int mailbox_mem_free(const int fd, const uint32_t handle);
    uint32_t mailbox_mem_lock(const int fd, const uint32_t handle);
    int mailbox_mem_unlock(const int fd, const uint32_t busaddr);
    int mailbox_qpu_execute(const int fd, const uint32_t num_qpus,
            const uint32_t control, const uint32_t noflush,
            const uint32_t timeout);
    int mailbox_qpu_enable(const int fd, const uint32_t enable);

    /* Our original wrappers. */
    int mailbox_get_firmware_revision(const int fd,
            uint32_t *firmware_revision);
    int mailbox_get_board_model(const int fd, uint32_t *board_model);
    int mailbox_get_board_revision(const int fd, uint32_t *board_revision);
    int mailbox_get_board_mac_address(const int fd, uint64_t *mac_address);
    int mailbox_get_board_serial(const int fd, uint64_t *board_serial);
    int mailbox_get_arm_memory(const int fd, uint32_t *base, uint32_t *size);
    int mailbox_get_vc_memory(const int fd, uint32_t *base, uint32_t *size);

    /*
     * Derived from
     * https://github.com/raspberrypi/linux/blob/rpi-4.14.y/drivers/char/broadcom/vcio.c
     */
#define VCIO_IOC_MAGIC 100
#define IOCTL_MBOX_PROPERTY _IOWR(VCIO_IOC_MAGIC, 0, char *)

#define VCIO_FILE_NAME "/dev/vcio"

#define MEM_FLAG_DISCARDABLE      (1<<0)
#define MEM_FLAG_NORMAL           (0<<2)
#define MEM_FLAG_DIRECT           (1<<2)
#define MEM_FLAG_COHERENT         (1<<3)
#define MEM_FLAG_L1_NONALLOCATING (MEM_FLAG_DIRECT | MEM_FLAG_COHERENT)
#define MEM_FLAG_ZERO             (1<<4)
#define MEM_FLAG_NO_INIT          (1<<5)
#define MEM_FLAG_HINT_PERMALOCK   (1<<6)

#endif /* MAILBOX_H_ */
