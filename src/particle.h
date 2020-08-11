#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct
{
    float x,y,z;
} vec3d;

typedef struct
{
    vec3d position;
    vec3d momentum;
    vec3d force;

    float mass;
    float radius;
} particle;

#endif
