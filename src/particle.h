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

    float ptmp;
    float px = 0;
    float py = 0;

    for (i = 0; i < opts->particle_count - 1; i++)
    {
        p[0][i].position.x = (rand() % 50) - 25;
        p[0][i].position.y = (rand() % 50) - 25;
        p[0][i].position.z = 0;

        ptmp = frand_min_max(opts->mom_min, opts->mom_max) * (frand() < 0.5f ? 1 : -1);
        px += ptmp;
        p[0][i].momentum.x = ptmp;

        ptmp = frand_min_max(opts->mom_min, opts->mom_max) * (frand() < 0.5f ? 1 : -1);
        py += ptmp;

        p[0][i].momentum.y = py;
        p[0][i].momentum.z = 0;

        p[0][i].mass = frand_min_max(opts->mass_min, opts->mass_max);
    }
    p[0][opts->particle_count].position.x = (rand() % 50) - 25;
    p[0][opts->particle_count].position.y = (rand() % 50) - 25;
    p[0][opts->particle_count].position.z = 0;

    p[0][opts->particle_count].momentum.x = -px;
    p[0][opts->particle_count].momentum.y = -py;
    p[0][opts->particle_count].momentum.z = 0;

    p[0][opts->particle_count].mass = frand_min_max(opts->mass_min, opts->mass_max);

}

#endif
