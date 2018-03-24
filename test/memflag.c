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

static int print_addr(const int mbfd, const uint32_t flags)
{
    uint32_t handle, busaddr;
    int err;

    handle = mailbox_mem_alloc(mbfd, 4096, 4096, flags);
    if (!handle)
        goto err_out;

    busaddr = mailbox_mem_lock(mbfd, handle);
    if (!busaddr)
        goto err_free;

    printf("0x%08" PRIx32 "\n", busaddr);

    err = mailbox_mem_unlock(mbfd, busaddr);
    if (err)
        goto err_free;

    err = mailbox_mem_free(mbfd, handle);
    if (err)
        goto err_out;

    return 0;

err_free:
    (void) mailbox_mem_free(mbfd, handle);
err_out:
    return 1;
}

int main(void)
{
    int mbfd;
    int err;

    mbfd = mailbox_open();
    if (mbfd == -1)
        return 1;

    printf("NORMAL:           ");
    print_addr(mbfd, MEM_FLAG_NORMAL);
    printf("DIRECT:           ");
    print_addr(mbfd, MEM_FLAG_DIRECT);
    printf("COHERENT:         ");
    print_addr(mbfd, MEM_FLAG_COHERENT);
    printf("L1_NONALLOCATING: ");
    print_addr(mbfd, MEM_FLAG_L1_NONALLOCATING);

    err = mailbox_close(mbfd);
    return err;
}
