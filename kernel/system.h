#pragma once

/* Copyright © 2018-2020 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <libsystem/logger.h>

#include "kernel/x86/Interrupts.h"
#include "kernel/x86/x86.h"

#define HANG   \
    while (1)  \
    {          \
        hlt(); \
    }

#define STOP   \
    while (1)  \
    {          \
        cli(); \
        hlt(); \
    }

void __attribute__((noreturn)) __panic(const char *file, const char *function, const int line, InterruptStackFrame *stackframe, const char *message, ...);

#define PANIC(x...) __panic(__FILE__, __FUNCTION__, __LINE__, NULL, x)

#define CPANIC(ctx, x...) __panic(__FILE__, __FUNCTION__, __LINE__, ctx, x)
