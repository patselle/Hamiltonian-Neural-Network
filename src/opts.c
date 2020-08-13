#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opts.h"

#define PARTICLE_COUNT_DEFAULT 5
#define MASS_MIN_DEFAULT 0.5f
#define MASS_MAX_DEFAULT 1.0f

static void print_usage(int const exitCode)
{
    printf("usage:\n");
    printf("main [options]\n");
    printf("\n");
    printf("options:\n");
    printf("  --trace\tOptional trace file for particle position and momentum\n");
    printf("  --no-gui\tDo not show user interface\n");
    printf("\n");
    printf("particle specific options:\n");
    printf("  --count\tParticle count (default %i)\n", PARTICLE_COUNT_DEFAULT);
    printf("  --mass-min\tMin. value of particle mass (default %f)\n", MASS_MIN_DEFAULT);
    printf("  --mass-max\tMax. value of particle mass (default %f)\n", MASS_MAX_DEFAULT);
    exit(exitCode);
}

void opts_parse(opts_t * const opts, size_t const argc, char ** const argv)
{
    int c;
    int opt_idx = 0;

    memset(opts, 0, sizeof(opts_t));
    
    struct option long_opts[] =
    {
        { "trace",    required_argument, 0, 0 },
        { "no-gui",   no_argument,       0, 0 },
        { "count",    required_argument, 0, 0 },
        { "mass-min", required_argument, 0, 0 },
        { "mass-max", required_argument, 0, 0 },
        { "help",     no_argument,       0, 'h' },
        { "version",  no_argument,       0, 'v' },
        { 0,          0,                 0, 0 }
    };

    while ((c = getopt_long(argc, argv, "hv", long_opts, &opt_idx)) >= 0)
    {
        switch (c)
        {
            case 0:
                if (opt_idx == 0)
                {
                    opts->trace_file = optarg;
                }
                else if (opt_idx == 1)
                {
                    opts->flags |= OPT_NO_GUI;
                }
                else if (opt_idx == 2)
                {
                    opts->particle_count = (float)atoi(optarg);
                    if (opts->particle_count <= 0)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 3)
                {
                    opts->mass_min = (float)atof(optarg);
                    if (opts->mass_min <= 0)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 4)
                {
                    opts->mass_max = (float)atof(optarg);
                    if (opts->mass_max <= 0)
                    {
                        print_usage(1);
                    }
                }
                break;
            case 'h':
                print_usage(0);
                break;
            case 'v':
                printf("version: %s\n", VERSION);
                exit(0);
                break;
            case '?':
                print_usage(1);
                break;
        }
    }

    // take over (default) values

    opts->particle_count = opts->particle_count ? opts->particle_count : PARTICLE_COUNT_DEFAULT;
    opts->mass_min = opts->mass_min ? opts->mass_min : MASS_MIN_DEFAULT;
    opts->mass_max = opts->mass_max ? opts->mass_max : MASS_MAX_DEFAULT;

    // plausibility check

    if (opts->mass_min > opts->mass_max)
    {
        fprintf(stderr, "mass min is bigger than mass max\n");
        exit(1);
    }
}
