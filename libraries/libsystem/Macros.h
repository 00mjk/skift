#pragma once

/* Copyright © 2018-2020 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#define __packed __attribute__((packed))

#define __aligned(__align) __attribute__((aligned(__align)))

#define __unused(__stuff) (void)(__stuff)

#define __create(__type) ((__type *)calloc(1, sizeof(__type)))

#define __swap(__type, __x, __y) \
    ({                           \
        __type __tmp = __x;      \
        __x = __y;               \
        __y = __tmp;             \
    })

#define __cleanup(__function) __attribute__((__cleanup__(__function)))
#define __cleanup_malloc __attribute__((__cleanup__(malloc_cleanup)))

// Align the nearest _lower_ aligned address
// ex: 8 with align = 8 -> 8
// ex: 9 with align = 8 -> 16
// ex: 7 with align = 8 -> 0
#define __align_down(__addr, __align) ((__addr) & ~((__align)-1))

// Align the nearest _upper_ aligned address
// ex: 8 with align = 8 -> 8
// ex: 9 with align = 8 -> 16
// ex: 7 with align = 8 -> 8
#define __align_up(__addr, __align) (((__addr) + (__align)-1) & ~((__align)-1))