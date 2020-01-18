#pragma once

/* Copyright © 2018-2019 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <libsystem/runtime.h>

typedef uint32_t Codepoint;

bool codepoint_is_digit(Codepoint codepoint);

bool codepoint_is_alpha(Codepoint codepoint);

int codepoint_numeric_value(Codepoint codepoint);

char codepoint_to_cp437(Codepoint codepoint);
