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
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/param.h> /* for MAX() */

int rpi_firmware_property_list(const int fd, void *data, uint32_t tag_size)
{
    int err;
    uint32_t *buf;
    const uint32_t size = sizeof(*buf)*2 + tag_size + sizeof(*buf)*1;

    buf = malloc(size);
    if (buf == NULL) {
        print_error("malloc: %s\n", strerror(errno));
        return 1;
    }

    buf[0] = size;
    buf[1] = RPI_FIRMWARE_STATUS_REQUEST;
    memcpy(buf + 2, data, tag_size);
    buf[size/4 - 1] = RPI_FIRMWARE_PROPERTY_END;

    err = mailbox_property(fd, buf);
    if (err) {
        goto out;
    }
    if (buf[1] != RPI_FIRMWARE_STATUS_SUCCESS) {
        print_error("Request failed: 0x%08" PRIx32 "\n", buf[1]);
        err = 1;
        goto out;
    }

    memcpy(data, buf + 2, tag_size);

out:
    free(buf);
    return err;
}

int rpi_firmware_property(const int fd, const uint32_t tag, void *tag_data,
        const uint32_t buf_size, const uint32_t req_resp_size)
{
    int err;
    const unsigned data_size =
            sizeof(struct rpi_firmware_property_tag_header) + buf_size;
    void *data = alloca(data_size);
    struct rpi_firmware_property_tag_header *header =
            (struct rpi_firmware_property_tag_header*) data;

    if (buf_size < req_resp_size) {
        print_error("buf_size < req_resp_size\n");
        return 1;
    }

    header->tag = tag;
    header->buf_size = buf_size;
    header->req_resp_size = req_resp_size;
    memcpy(data + sizeof(*header), tag_data, buf_size);

    err = rpi_firmware_property_list(fd, data, data_size);
    if (err)
        return err;
    if (!(header->req_resp_size & (1UL<<31))) {
        print_error("header->req_resp_size[31] was not set by firmware\n");
        return 1;
    }
    header->req_resp_size &= ~(1UL<<31);
    if (header->req_resp_size != req_resp_size) {
        print_error("Firmware requires %" PRIu32 " bytes for response buffer "
                "while you think it is %" PRIu32 " bytes\n",
                header->req_resp_size, req_resp_size);
        print_error("Note: req_resp_size seems not to be used in the firmware "
                "for now, but we require users to set this to proper value\n");
        return 1;
    }
    if (header->req_resp_size > buf_size) {
        print_error("Firmware requires %" PRIu32 " bytes for response buffer "
                "while the supplied buffer is only %" PRIu32 " bytes\n",
                header->req_resp_size, buf_size);
        return 1;
    }

    memcpy(tag_data, data + sizeof(*header), req_resp_size);

    return 0;
}
