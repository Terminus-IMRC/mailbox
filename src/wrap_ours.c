/*
 * Copyright (c) 2018 Idein Inc. ( http://idein.jp/ )
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#include "mailbox.h"
#include <stdint.h>

int mailbox_get_firmware_revision(const int fd,
        uint32_t *firmware_revision)
{
    union {
        struct {
        } in;
        struct {
            uint32_t firmware_revision;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_FIRMWARE_REVISION, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *firmware_revision = msg.out.firmware_revision;
    return 0;
}

int mailbox_get_board_model(const int fd, uint32_t *board_model)
{
    union {
        struct {
            uint32_t aa;
        } in;
        struct {
            uint32_t board_model;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_BOARD_MODEL, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *board_model = msg.out.board_model;
    return 0;
}

int mailbox_get_board_revision(const int fd, uint32_t *board_revision)
{
    union {
        struct {
        } in;
        struct {
            uint32_t board_revision;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_BOARD_REVISION, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *board_revision = msg.out.board_revision;
    return 0;
}

int mailbox_get_board_mac_address(const int fd, uint64_t *mac_address)
{
    union {
        struct {
            uint64_t dummy;
        } in;
        struct {
            uint8_t v0, v1, v2, v3, v4, v5;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_BOARD_MAC_ADDRESS, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *mac_address =
              ((uint64_t) msg.out.v5) <<  0
            | ((uint64_t) msg.out.v4) <<  8
            | ((uint64_t) msg.out.v3) << 16
            | ((uint64_t) msg.out.v2) << 24
            | ((uint64_t) msg.out.v1) << 32
            | ((uint64_t) msg.out.v0) << 40;
    return 0;
}

int mailbox_get_board_serial(const int fd, uint64_t *board_serial)
{
    union {
        struct {
        } in;
        struct {
            uint64_t board_serial;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_BOARD_SERIAL, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *board_serial = msg.out.board_serial;
    return 0;
}

int mailbox_get_arm_memory(const int fd, uint32_t *base, uint32_t *size)
{
    union {
        struct {
        } in;
        struct {
            uint32_t base, size;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_ARM_MEMORY, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *base = msg.out.base;
    *size = msg.out.size;
    return 0;
}

int mailbox_get_vc_memory(const int fd, uint32_t *base, uint32_t *size)
{
    union {
        struct {
        } in;
        struct {
            uint32_t base, size;
        } out;
    } msg = {
        .in = {
        }
    };
    int err;

    err = rpi_firmware_property(fd, RPI_FIRMWARE_GET_VC_MEMORY, &msg,
            sizeof(msg), sizeof(msg.out));
    if (err)
        return err;

    *base = msg.out.base;
    *size = msg.out.size;
    return 0;
}
