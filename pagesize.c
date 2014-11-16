#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

long get_pagesize();

long get_pagesize()
{
	long pagesize;

	if((pagesize=sysconf(_SC_PAGESIZE))==-1){
		fprintf(stderr, "%s:%d: error: sysconf(3): _SC_PAGESIZE: %s\n", __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	return pagesize;
}
