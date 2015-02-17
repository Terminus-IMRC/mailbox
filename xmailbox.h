#ifndef _XMAILBOX_H_INCLUDED_
#define _XMAILBOX_H_INCLUDED_

	void *xmapmem_cpu(unsigned base, unsigned size);
	unsigned xmem_alloc(int file_desc, unsigned size, unsigned align, unsigned flags);
	unsigned xmem_free(int file_desc, unsigned handle);
	unsigned xmem_lock(int file_desc, unsigned handle);
	unsigned xmem_unlock(int file_desc, unsigned handle);
	int xmbox_open();
	void xmbox_close(int file_desc);

#endif /* _XMAILBOX_H_INCLUDED_ */
