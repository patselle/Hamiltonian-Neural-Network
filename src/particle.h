#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct
{
    float x,y,z;
    float px,py,pz;
    float mass;
    float radius;

    //(float)malloc(DIMENSION)
}particle;

#endif