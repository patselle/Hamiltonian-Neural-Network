#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opts.h"

static void print_usage(int const exitCode)
{
    printf("usage:\n");
    printf("main [options]\n");
    printf("\n");
    printf("options:\n");
    printf("  --trace\tOptional trace file for particle position and momentum\n");
    printf("  --no-gui\tDo not show user interface\n");
    printf("\n");
    printf("partcle specific options:\n");
    printf("  --mass-min\tMin. value of particle mass\n");
    printf("  --mass-max\tMax. value of particle mass\n");
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
                    opts->mass_min = (float)atof(optarg);
                    if (!opts->mass_min)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 3)
                {
                    opts->mass_max = (float)atof(optarg);
                    if (!opts->mass_max)
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
}
