/*
 * Copyright (c) 2018 Idein Inc. ( http://idein.jp/ )
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#include "mailbox.h"
#include "local/error.h"
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t mailbox_mem_alloc(const int fd, const uint32_t size,
        const uint32_t align, const uint32_t flags)
{
    union {
        struct {
            uint32_t size, align, flags;
        } in;
        struct {
            uint32_t handle;
        } out;
    } msg = {
        .in = {
            .size = size,
            .align = align,
            .flags = flags
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_ALLOCATE_MEMORY, &msg,
            sizeof(msg.in), sizeof(msg.out));
    if (err)
        return 0;

    return msg.out.handle;
}

int mailbox_mem_free(const int fd, const uint32_t handle)
{
    union {
        struct {
            uint32_t handle;
        } in;
        struct {
            uint32_t status;
        } out;
    } msg = {
        .in = {
            .handle = handle
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_RELEASE_MEMORY, &msg,
            sizeof(msg.in), sizeof(msg.out));
    if (err)
        return err;
    else if (msg.out.status) {
        print_error("status=0x%08" PRIx32 "\n", msg.out.status);
        return msg.out.status;
    }

    return 0;
}

uint32_t mailbox_mem_lock(const int fd, const uint32_t handle)
{
    union {
        struct {
            uint32_t handle;
        } in;
        struct {
            uint32_t busaddr;
        } out;
    } msg = {
        .in = {
            .handle = handle
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_LOCK_MEMORY, &msg,
            sizeof(msg.in), sizeof(msg.out));
    if (err)
        return 0;

    return msg.out.busaddr;
}

int mailbox_mem_unlock(const int fd, const uint32_t busaddr)
{
    union {
        struct {
            uint32_t busaddr;
        } in;
        struct {
            uint32_t status;
        } out;
    } msg = {
        .in = {
            .busaddr = busaddr
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_UNLOCK_MEMORY, &msg,
            sizeof(msg.in), sizeof(msg.out));
    if (err)
        return err;
    else if (msg.out.status) {
        print_error("status=0x%08" PRIx32 "\n", msg.out.status);
        return msg.out.status;
    }

    return 0;
}

int mailbox_qpu_execute(const int fd, const uint32_t num_qpus,
        const uint32_t control, const uint32_t noflush,
        const uint32_t timeout)
{
    union {
        struct {
            uint32_t num_qpus, control, noflush, timeout;
        } in;
        struct {
            uint32_t status;
        } out;
    } msg = {
        .in = {
            .num_qpus = num_qpus,
            .control = control,
            .noflush = noflush,
            .timeout = timeout
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_EXECUTE_QPU, &msg,
            sizeof(msg.in), sizeof(msg.out));
    if (err)
        return err;
    else if (msg.out.status) {
        if (msg.out.status == 0x80000000)
            print_error("Execution timeout (timeout=%" PRIu32 "ms)\n",
                    timeout);
        else
            print_error("Unknown status: 0x%08" PRIx32 "\n",
                    msg.out.status);
        return msg.out.status;
    }

    return 0;
}

int mailbox_qpu_enable(const int fd, const uint32_t enable)
{
    union {
        struct {
            uint32_t enable;
        } in;
        struct {
            uint32_t status;
        } out;
    } msg = {
        .in = {
            .enable = enable
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_SET_ENABLE_QPU, &msg,
            sizeof(msg.in), sizeof(msg.out));
    if (err)
        return err;
    else if (msg.out.status) {
        print_error("status=0x%08" PRIx32 "\n", msg.out.status);
        return msg.out.status;
    }

    return 0;
}
