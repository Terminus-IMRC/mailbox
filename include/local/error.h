/*
 * Copyright (c) 2018 Idein Inc. ( http://idein.jp/ )
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#ifndef LOCAL_ERROR_H_
#define LOCAL_ERROR_H_

#include <stdio.h>

#define print_error(fmt, ...) \
        do { \
            fprintf(stderr, "%s:%u:%s: error: " fmt, \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        } while (0)

#endif /* LOCAL_ERROR_H_ */
