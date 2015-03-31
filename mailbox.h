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

#ifndef _MAILBOX_H_INCLUDED_
#define _MAILBOX_H_INCLUDED_

	void mb_get_firmware_revision(unsigned p[], int file_desc);
	void mb_get_board_model(unsigned p[], int file_desc);
	void mb_get_board_revision(unsigned p[], int file_desc);
	void mb_get_board_mac_address(unsigned p[], int file_desc);
	void mb_get_board_serial(unsigned p[], int file_desc);
	void mb_get_arm_memory(unsigned p[], int file_desc);
	void mb_get_vc_memory(unsigned p[], int file_desc);
	void mb_set_allocate_mem(unsigned p[], int file_desc, unsigned size, unsigned align, unsigned flags);
	void mb_set_lock_mem(unsigned p[], int file_desc, unsigned handle);
	void mb_set_unlock_mem(unsigned p[], int file_desc, unsigned handle);
	void mb_set_release_mem(unsigned p[], int file_desc, unsigned handle);
	void mb_set_execute_code(unsigned p[], int file_desc, unsigned code, unsigned r0, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned r5);
	void mb_set_execute_qpu(unsigned p[], int file_desc, unsigned num_qpus, unsigned control, unsigned noflush, unsigned timeout);
	void mb_set_enable_qpu(unsigned p[], int file_desc, unsigned enable);

#include "mapmem.h"
#include "mbfd.h"
#include "mb_frontend.h"

#endif /* _MAILBOX_H_INCLUDED_ */
