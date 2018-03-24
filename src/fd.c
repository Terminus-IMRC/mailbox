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
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

int mailbox_open(void)
{
    int fd;

    fd = open(VCIO_FILE_NAME, O_NONBLOCK);
    if (fd == -1) {
        print_error("open: %s: %s\n", VCIO_FILE_NAME, strerror(errno));
        return -1;
    }

    return fd;
}

int mailbox_close(const int fd)
{
    int err;

    err = close(fd);
    if (err) {
        print_error("close: %s\n", strerror(errno));
        return err;
    }

    return 0;
}

int mailbox_property(const int fd, void *buf)
{
    int err;

    err = ioctl(fd, IOCTL_MBOX_PROPERTY, buf);
    if (err) {
        print_error("ioctl: IOCTL_MBOX_PROPERTY: %s\n", strerror(errno));
        return err;
    }

    return 0;
}
