#ifndef PARTICLE_H
#define PARTICLE_H

#include <time.h>
#include <stdlib.h>

#include "vec.h"
#include "opts.h"

typedef struct
{
    vec3f position;
    vec3f momentum;

    float mass;
    float radius;
} particle;

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static inline float frand_min_max(float const min, float const max)
{
    return frand() * (max - min) + min;
}

static void particle_init(particle * * const p, opts_t const * const opts)
{
    off_t i;

    srand(time(NULL));

    p[0] = (particle*)malloc(sizeof(particle) * opts->particle_count);

    for (i = 0; i < opts->particle_count; i++)
    {
        p[0][i].position.x = (rand() % 50) - 25;
        p[0][i].position.y = (rand() % 50) - 25;
        p[0][i].position.z = 0;

        p[0][i].momentum.x = frand() / 100;
        p[0][i].momentum.y = frand() / 100;
        p[0][i].momentum.z = 0;

        p[0][i].mass = frand_min_max(opts->mass_min, opts->mass_max);
    }
}

#endif
