#pragma once

#define assert(expr) \
    if (!(expr)) \
        __assert_failed( #expr, __FILE__,  __FUNCTION__, __LINE__ )

extern void __assert_failed(const char * expr, const char * file, const char * function, int line);
        