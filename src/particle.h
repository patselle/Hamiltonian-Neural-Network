#ifndef PARTICLE_H
#define PARTICLE_H

#include <time.h>

#include "vec.h"

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

static void particle_init(particle * const p, size_t const count, float const mass)
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

        p[i].mass = mass;
    }
}

#endif
