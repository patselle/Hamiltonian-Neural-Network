#ifndef OPTS_H
#define OPTS_H

#include <getopt.h>

#define VERSION "1.0.0"

enum
{
    OPT_NONE = 0,
    OPT_NO_GUI = 1
};

typedef struct
{
    char *trace_file;
    int flags;
} opts_t;

extern void opts_parse(opts_t * const opts, size_t const argc, char ** const argv);

#endif
