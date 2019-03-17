#pragma once

/* Copyright © 2018-2019 N. Van Bossuyt.                                               */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <skift/generic.h>

void serial_setup();

char serial_getc();
void serial_putc(char c);

int serial_read(char *buffer, uint size);
int serial_write(const char *buffer, uint size);
int serial_writeln(const char *str);