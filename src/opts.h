#ifndef OPTS_H
#define OPTS_H

#include <getopt.h>

#define VERSION "1.0.0"

enum
{
    OPT_NONE = 0,
    OPT_NO_GUI = 1,
    OPT_STATIC_COLOR = 2
};

typedef struct
{
    char *trace_file;
    int flags;
    char *init_file;
    size_t iterations;
    size_t particle_count;
    float mass_min;
    float mass_max;
    float mom_min;
    float mom_max;
} opts_t;

extern void opts_parse(opts_t * const opts, size_t const argc, char ** const argv);

#endif
