#pragma once

/* Copyright © 2018-2019 MAKER.                                               */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <skift/generic.h>
#include "kernel/shared/keyboard.h"

typedef struct
{
    char c;
    keyboard_key_t key;
} keyboard_event_t;

void keyboard_setup();