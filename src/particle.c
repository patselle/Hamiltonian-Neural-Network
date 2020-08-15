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

    p[0][0].position.x = 15;
    p[0][0].position.y = 15;
    p[0][0].position.z = 0;

    p[0][0].momentum.x = 1;
    p[0][0].momentum.y = 0;
    p[0][0].momentum.z = 0;

    p[0][0].mass = 1;


    p[0][1].position.x = -15;
    p[0][1].position.y = -15;
    p[0][1].position.z = 0;

    p[0][1].momentum.x = -1;
    p[0][1].momentum.y = 0;
    p[0][1].momentum.z = 0;

    p[0][1].mass = 1;


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
