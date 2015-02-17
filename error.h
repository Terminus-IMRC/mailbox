#ifndef _ERROR_H_INCLUDED_
#define _ERROR_H_INCLUDED_

#include <stdio.h>

#define error(str, ...) fprintf(stderr, "%s:%d: error: "str, __FILE__, __LINE__, ## __VA_ARGS__)

#endif /* _ERROR_H_INCLUDED_ */
