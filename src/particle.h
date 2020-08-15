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

#endif
