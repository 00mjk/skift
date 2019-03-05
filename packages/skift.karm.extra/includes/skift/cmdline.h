#pragma once

/* Copyright © 2018-2019 MAKER.                                               */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <skift/generic.h>

struct s_cmdline;
struct s_cmdline_option;

typedef void cmdline_callback_t(
    struct s_cmdline *cmdline,
    struct s_cmdline_option *opt);

typedef enum
{
    CMDLINE_BOOLEAN,
    CMDLINE_STRING,
    CMDLINE_INTEGER,
    CMDLINE_ACTION,
    CMDLINE_END
} cmdline_option_type_t;

typedef struct s_cmdline_option
{
    cmdline_option_type_t type;

    void *value;
    const char *long_name;
    const char short_name;

    cmdline_callback_t *callback;

    const char *help;
} cmdline_option_t;

typedef struct s_cmdline
{
    const char *const *usages;
    const char *prologue;
    cmdline_option_t *options;
    const char *epiloge;
} cmdline_t;

#define CMDLINE_NEWLINE "\n\t"

#define CMDLINE_OPT_HELP                            \
    {                                               \
        .type = CMDLINE_BOOLEAN,                    \
        .value = NULL,                              \
        .long_name = "help",                        \
        .short_name = 'h',                          \
        .callback = cmdline_callback_help,          \
        .help = "Show this help message and exit.", \
    }

#define CMDLINE_OPT_END      \
    {                        \
        .type = CMDLINE_END, \
    }

#define CMDLINE(__usages, __options, __prologue, __epiloge) \
    {                                                       \
        .usages = __usages,                                 \
        .prologue = __prologue,                             \
        .options = __options,                               \
        .epiloge = __epiloge                                \
    }

void cmdline_callback_help(cmdline_t *cmdline, cmdline_option_t *option);
int cmdline_parse(cmdline_t *cmdline, int argc, char **argv);