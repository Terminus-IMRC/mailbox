/*
Copyright (c) 2012, Broadcom Europe Ltd.
Copyright (c) 2014-2015, Sugizaki Yukimasa
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <errno.h>

#include "vcio.h"
#include "mailbox.h"
#include "error.h"

unsigned mem_alloc(int file_desc, unsigned size, unsigned align, unsigned flags)
{
	unsigned p[32];

	mb_set_allocate_mem(p, file_desc, size, align, flags);

	return p[5];
}

unsigned mem_free(int file_desc, unsigned handle)
{
	unsigned p[32];

	mb_set_release_mem(p, file_desc, handle);

	return p[5];
}

unsigned mem_lock(int file_desc, unsigned handle)
{
	unsigned p[32];

	mb_set_lock_mem(p, file_desc, handle);

	return p[5];
}

unsigned mem_unlock(int file_desc, unsigned handle)
{
	unsigned p[32];

	mb_set_unlock_mem(p, file_desc, handle);

	return p[5];
}

unsigned execute_code(int file_desc, unsigned code, unsigned r0, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned r5)
{
	unsigned p[32];

	mb_set_execute_code(p, file_desc, code, r0, r1, r2, r3, r4, r5);

	return p[5];
}

unsigned qpu_enable(int file_desc, unsigned enable)
{
	unsigned p[32];

	mb_set_enable_qpu(p, file_desc, enable);

	return p[5];
}

unsigned execute_qpu(int file_desc, unsigned num_qpus, unsigned control, unsigned noflush, unsigned timeout)
{
	unsigned p[32];

	mb_set_execute_qpu(p, file_desc, num_qpus, control, noflush, timeout);

	return p[5];
}
