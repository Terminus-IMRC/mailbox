/*
 * Copyright (c) 2018 Idein Inc. ( http://idein.jp/ )
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#include "mailbox.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

int main(void)
{
    int mbfd;
    int err;

    mbfd = mailbox_open();
    if (mbfd == -1)
        return 1;

    {
        uint32_t rev;
        time_t t;
        char s[256];
        err = mailbox_get_firmware_revision(mbfd, &rev);
        if (err)
            return err;
        t = (time_t) rev;
        strftime(s, sizeof(s), "%b %e %Y %T", gmtime(&t));
        printf("Firmware revision: %s\n", s);
    }
    {
        uint32_t model;
        err = mailbox_get_board_model(mbfd, &model);
        if (err)
            return err;
        printf("Board model: 0x%08" PRIx32 "\n", model);
    }
    {
        uint32_t rev;
        err = mailbox_get_board_revision(mbfd, &rev);
        if (err)
            return err;
        printf("Board revision: 0x%08" PRIx32 "\n", rev);
    }
    {
        uint64_t mac;
        err = mailbox_get_board_mac_address(mbfd, &mac);
        if (err)
            return err;
        printf("Board MAC address: %012" PRIx64 "\n", mac);
    }
    {
        uint64_t serial;
        err = mailbox_get_board_serial(mbfd, &serial);
        if (err)
            return err;
        printf("Board serial: 0x%" PRIx64 "\n", serial);
    }
    {
        uint32_t base, size;
        err = mailbox_get_arm_memory(mbfd, &base, &size);
        if (err)
            return err;
        printf("ARM memory: 0x%08" PRIx32 " bytes at 0x%08" PRIx32 "\n",
                size, base);
    }
    {
        uint32_t base, size;
        err = mailbox_get_vc_memory(mbfd, &base, &size);
        if (err)
            return err;
        printf("VC memory:  0x%08" PRIx32 " bytes at 0x%08" PRIx32 "\n",
                size, base);
    }

    err = mailbox_close(mbfd);
    return err;
}
