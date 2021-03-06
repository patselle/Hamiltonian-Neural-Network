#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opts.h"

#define PARTICLE_COUNT_DEFAULT 5
#define MASS_MIN_DEFAULT 0.5f
#define MASS_MAX_DEFAULT 1.0f
#define MOMENTUM_MIN_DEFAULT 1.0f
#define MOMENTUM_MAX_DEFAULT 2.0f

static void print_usage(int const exitCode)
{
    printf("usage:\n");
    printf("main [options]\n");
    printf("\n");
    printf("options:\n");
    printf("  --trace\tOptional trace file for particle position and momentum\n");
    printf("  --no-gui\tDo not show user interface\n");
    printf("  --iterations\tLimit iterations\n");
    printf("  --debug\tPrint position,force,momentum of each itertion to stdout\n");
    printf("\n");
    printf("particle specific options:\n");
    printf("  --init\tOptional particle initialization file (format: posx;posy;posz;momx;momy;momz;mass)\n");
    printf("  --particles\tParticle count (default %i)\n", PARTICLE_COUNT_DEFAULT);
    printf("  --mass-min\tMin. value of particle mass (default %f)\n", MASS_MIN_DEFAULT);
    printf("  --mass-max\tMax. value of particle mass (default %f)\n", MASS_MAX_DEFAULT);
    printf("  --mom-min\tMin. value of initial particle momentum (default %f)\n", MOMENTUM_MIN_DEFAULT);
    printf("  --mom-max\tMax. value of initial particle momentum (default %f)\n", MOMENTUM_MAX_DEFAULT);

    exit(exitCode);
}

void opts_parse(opts_t * const opts, size_t const argc, char ** const argv)
{
    int c;
    int opt_idx = 0;

    memset(opts, 0, sizeof(opts_t));

    struct option long_opts[] =
    {
        { "trace",       required_argument, 0, 0 },
        { "no-gui",      no_argument,       0, 0 },
        { "particles",   required_argument, 0, 0 },
        { "iterations",  required_argument, 0, 0 },
        { "mass-min",    required_argument, 0, 0 },
        { "mass-max",    required_argument, 0, 0 },
        { "mom-min",     required_argument, 0, 0 },
        { "mom-max",     required_argument, 0, 0 },
        { "init",        required_argument, 0, 0 },
        { "debug",       no_argument,       0, 0 },
        { "help",        no_argument,       0, 'h' },
        { "version",     no_argument,       0, 'v' },
        { 0,             0,                 0, 0 }
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
                    opts->iterations = (size_t)atoi(optarg);
                    if (opts->iterations <= 0)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 4)
                {
                    opts->mass_min = (float)atof(optarg);
                    if (opts->mass_min <= 0)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 5)
                {
                    opts->mass_max = (float)atof(optarg);
                    if (opts->mass_max <= 0)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 6)
                {
                    opts->mom_min = (float)atof(optarg);
                    if (opts->mom_min <= 0)
                    {
                        print_usage(1);
                    }
                }
                else if (opt_idx == 7)
                {
                    opts->mom_max = (float)atof(optarg);
                    if (opts->mom_max <= 0)
                    {
                        print_usage(1);
                    }
                }
		        else if (opt_idx == 8)
                {
                    opts->init_file = optarg;
                }
                else if (opt_idx == 9)
                {
                    opts->flags |= OPT_DEBUG;
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

    opts->iterations = opts->iterations ? opts->iterations : (size_t)-1;
    opts->particle_count = opts->particle_count ? opts->particle_count : PARTICLE_COUNT_DEFAULT;
    opts->mass_min = opts->mass_min ? opts->mass_min : MASS_MIN_DEFAULT;
    opts->mass_max = opts->mass_max ? opts->mass_max : MASS_MAX_DEFAULT;
    opts->mom_min = opts->mom_min ? opts->mom_min : MOMENTUM_MIN_DEFAULT;
    opts->mom_max = opts->mom_max ? opts->mom_max : MOMENTUM_MAX_DEFAULT;

    // plausibility check

    if (opts->mass_min > opts->mass_max)
    {
        fprintf(stderr, "mass min is bigger than mass max\n");
        exit(1);
    }

    if (opts->mom_min > opts->mom_max)
    {
        fprintf(stderr, "momentum min is bigger than momentum max\n");
        exit(1);
    }
}
