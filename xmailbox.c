#include <stdlib.h>
#include "mailbox.h"
#include "error.h"

unsigned xmem_alloc(int file_desc, unsigned size, unsigned align, unsigned flags)
{
	unsigned handle = mem_alloc(file_desc, size, align, flags);
	if (!handle) {
		error("mem_alloc returned an error\n");
		exit(EXIT_FAILURE);
	}
	return handle;
}

unsigned xmem_free(int file_desc, unsigned handle)
{
	unsigned p = mem_free(file_desc, handle);
	if (p) {
		error("mem_free returned an error\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

unsigned xmem_lock(int file_desc, unsigned handle)
{
	unsigned p = mem_lock(file_desc, handle);
	if (!handle) {
		error("mem_lock returned an error\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

unsigned xmem_unlock(int file_desc, unsigned handle)
{
	unsigned p = mem_unlock(file_desc, handle);
	if (!handle) {
		error("mem_free returned an error\n");
		exit(EXIT_FAILURE);
	}
	return handle;
}

int xmbox_open()
{
	return mbox_open();
}

void xmbox_close(int file_desc)
{
	mbox_close(file_desc);
}
