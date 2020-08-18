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

extern void particle_init(particle * * const p, opts_t const * const opts);
extern void particle_init_file(particle * * const p, size_t * const n, char const * const path);

#endif
