#ifndef PARTICLE_H
#define PARTICLE_H

#include <time.h>

#include "vec.h"
#include "opts.h"

#define MASS_MIN_DEFAULT 0.5
#define MASS_MAX_DEFAULT 1

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

static void particle_init(particle * const p, size_t const count, opts_t const * const opts)
{
    off_t i;

    srand(time(NULL));

    for (i = 0; i < count; i++)
    {
        p[i].position.x = (rand() % 50) - 25;
        p[i].position.y = (rand() % 50) - 25;
        p[i].position.z = 0;

        p[i].momentum.x = frand() / 100;
        p[i].momentum.y = frand() / 100;
        p[i].momentum.z = 0;

        p[i].mass = frand_min_max(opts->mass_min ? opts->mass_min : MASS_MIN_DEFAULT, opts->mass_max ? opts->mass_max : MASS_MAX_DEFAULT);
    }
}

#endif
