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
#include "mb_send.h"
#include "error.h"

#define CHECK_PR_VALIDITY(p) \
{ \
	switch (p[1]) { \
		case VCMSG_REQUEST_SUCCESSFUL: \
			break; \
		case VCMSG_REQUEST_FAILED: \
			error("process request failed\n"); \
			exit(EXIT_FAILURE); \
		default: \
			error("unknown return code on process request: 0x%08x\n", p[1]); \
			exit(EXIT_FAILURE); \
	} \
}

void mb_get_firmware_revision(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_FIRMWARE_REVISION;
	p[i++] = 4;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_get_board_model(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_BOARD_MODEL;
	p[i++] = 4;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_get_board_revision(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_BOARD_REVISION;
	p[i++] = 4;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_get_board_mac_address(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_BOARD_MAC_ADDRESS;
	p[i++] = 6;
	p[i++] = 0;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_get_board_serial(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_BOARD_SERIAL;
	p[i++] = 8;
	p[i++] = 0;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_get_arm_memory(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_ARM_MEMORY;
	p[i++] = 8;
	p[i++] = 0;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_get_vc_memory(unsigned p[], int file_desc)
{
	int i = 0;

	p[i++] = 0;
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_GET_VC_MEMORY;
	p[i++] = 8;
	p[i++] = 0;
	p[i++] = 0;
	p[i++] = 0;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]);

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_allocate_mem(unsigned p[], int file_desc, unsigned size, unsigned align, unsigned flags)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_ALLOCATE_MEM; // (the tag id)
	p[i++] = 12; // (size of the buffer)
	p[i++] = 12; // (size of the data)
	p[i++] = size; // (num bytes? or pages?)
	p[i++] = align; // (alignment)
	p[i++] = flags; // (MEM_FLAG_L1_NONALLOCATING)

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_lock_mem(unsigned p[], int file_desc, unsigned handle)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_LOCK_MEM; // (the tag id)
	p[i++] = 4; // (size of the buffer)
	p[i++] = 4; // (size of the data)
	p[i++] = handle;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_unlock_mem(unsigned p[], int file_desc, unsigned handle)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_UNLOCK_MEM; // (the tag id)
	p[i++] = 4; // (size of the buffer)
	p[i++] = 4; // (size of the data)
	p[i++] = handle;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_release_mem(unsigned p[], int file_desc, unsigned handle)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_RELEASE_MEM; // (the tag id)
	p[i++] = 4; // (size of the buffer)
	p[i++] = 4; // (size of the data)
	p[i++] = handle;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_execute_code(unsigned p[], int file_desc, unsigned code, unsigned r0, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned r5)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_EXECUTE_CODE; // (the tag id)
	p[i++] = 28; // (size of the buffer)
	p[i++] = 28; // (size of the data)
	p[i++] = code;
	p[i++] = r0;
	p[i++] = r1;
	p[i++] = r2;
	p[i++] = r3;
	p[i++] = r4;
	p[i++] = r5;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_execute_qpu(unsigned p[], int file_desc, unsigned num_qpus, unsigned control, unsigned noflush, unsigned timeout)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_EXECUTE_QPU; // (the tag id)
	p[i++] = 16; // (size of the buffer)
	p[i++] = 16; // (size of the data)
	p[i++] = num_qpus;
	p[i++] = control;
	p[i++] = noflush;
	p[i++] = timeout; // ms

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}

void mb_set_enable_qpu(unsigned p[], int file_desc, unsigned enable)
{
	int i = 0;

	p[i++] = 0; // size
	p[i++] = VCMSG_PROCESS_REQUEST;

	p[i++] = VCMSG_SET_ENABLE_QPU; // (the tag id)
	p[i++] = 4; // (size of the buffer)
	p[i++] = 4; // (size of the data)
	p[i++] = enable;

	p[i++] = VCMSG_PROPERTY_END;
	p[0] = i * sizeof(p[0]); // actual size

	mbox_property(file_desc, p);

	CHECK_PR_VALIDITY(p);
}
