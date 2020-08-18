#include <stdio.h>
#include <stdlib.h>

#include "particle.h"

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static inline float frand_min_max(float const min, float const max)
{
    return frand() * (max - min) + min;
}

void particle_init(particle * * const p, opts_t const * const opts)
{
    off_t i;

    srand(time(NULL));

    p[0] = (particle*)malloc(sizeof(particle) * opts->particle_count);

    for (i = 0; i < opts->particle_count; i++)
    {
        p[0][i].position.x = (rand() % 50) - 25;
        p[0][i].position.y = (rand() % 50) - 25;
        p[0][i].position.z = 0;

        p[0][i].momentum.x = frand_min_max(opts->mom_min, opts->mom_max) * (frand() < 0.5f ? 1 : -1);
        p[0][i].momentum.y = frand_min_max(opts->mom_min, opts->mom_max) * (frand() < 0.5f ? 1 : -1);
        p[0][i].momentum.z = 0;

        p[0][i].mass = frand_min_max(opts->mass_min, opts->mass_max);
    }
}

void particle_init_file(particle * * const p, size_t * const n, char const * const path)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

       *n = 0;

        fp = fopen(path, "r");
        if (fp == NULL)
        {
                fprintf(stderr, "failed to open file\n");
                exit(1);
        }

        while ((read = getline(&line, &len, fp)) != -1) (*n)++;

        fseek(fp, 0, SEEK_SET);

        *p = (particle*)malloc(n[0] * sizeof(particle));
        *n = 0;

        while ((read = getline(&line, &len, fp)) != -1) {
                sscanf(line, "%f;%f;%f;%f;%f;%f;%f", &p[0][*n].position.x, &p[0][*n].position.y, &p[0][*n].position.z, &p[0][*n].momentum.x, &p[0][*n].momentum.y, &p[0][*n].momentum.z, &p[0][*n].mass);
                (*n)++;
        }


        fclose(fp);

        if (line)
        {
                free(line);
        }
}
