#ifndef VECOPS_H
#define VECOPS_H

#include <math.h>

#include "particle.h"

static vec3d vecsub(vec3d *pos1, vec3d *pos2)
{
    vec3d sum;
    sum.x = pos1->x - pos2->x;
    sum.y = pos1->y - pos2->y;
    sum.z = pos1->z - pos2->z;

    return sum;
}

static vec3d vecsum(vec3d *pos1, vec3d pos2)
{
    vec3d sum;
    sum.x = pos1->x + pos2.x;
    sum.y = pos1->y + pos2.y;
    sum.z = pos1->z + pos2.z;

    return sum;
}

static float vecquadraticdistance(vec3d *vec1, vec3d *vec2)
{
    float distance = (vec1->x - vec2->x) * (vec1->x - vec2->x)+ (vec1->y - vec2->y) * (vec1->y - vec2->y) + (vec1->z - vec2->z) * (vec1->z - vec2->z);
    return distance;
}

static vec3d scalmul(float scalar, vec3d vec)
{
    vec3d scalvec;

    // scalvec.x = *scalar * vec->x;
    // scalvec.y = *scalar * vec->y;
    // scalvec.z = *scalar * vec->z;

    scalvec.x = scalar * vec.x;
    scalvec.y = scalar * vec.y;
    scalvec.z = scalar * vec.z;

    return scalvec;
}

static float euclidiannorm(vec3d *vec)
{
    return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

static vec3d normvec(vec3d *vec)
{
    return scalmul(1.0 / euclidiannorm(vec), *vec);
}



#endif


