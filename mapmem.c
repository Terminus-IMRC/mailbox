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
#include <errno.h>

#include "mailbox.h"
#include "error.h"

void *mapmem_cpu(unsigned base, unsigned size)
{
	int mem_fd;
	const int pagesize = 4096;

	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
		error("open: /dev/mem: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (base % pagesize != 0) {
		error("specified base pointer is not pagesize-aligned\n");
		exit(EXIT_FAILURE);
	}

	void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED /*| MAP_FIXED*/, mem_fd, base);

#ifdef DEBUG
	printf("base=0x%x, mem=%p\n", base, mem);
#endif

	if (mem == MAP_FAILED) {
		error("mmap: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	close(mem_fd);

	return mem;
}

void unmapmem_cpu(void *addr, unsigned size)
{
	int s = munmap(addr, size);
	if (s != 0) {
		error("munmap: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
