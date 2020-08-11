#include <stdlib.h>
#include <stdio.h>

#include "particle.h"

#define DIMENSION 2
#define PARTICLES 3
#define TIME_MAX 10
#define TIME_STEP 0.1
#define MOMENTA_MAX 100

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static inline float prand()
{
    return (float)rand() / RAND_MAX * MOMENTA_MAX;
}

int main()
{
    printf("Hello from main\n");

    printf("Create some particles\n");

    particle a;
    particle b;
    particle c;

    a.x = 3.0;

    static particle particles[PARTICLES];

    printf("random number in [0,1) %f\n", frand());

    for (int a = 0; a < PARTICLES; a++)
    {
        printf("it %d\n", PARTICLES);
        printf("it %d\n", RAND_MAX);

        // init position
        particles[a].x = frand();
        particles[a].y = frand();
        particles[a].z = frand();

        // init momentum
        particles[a].px = prand();
        particles[a].py = prand();
        particles[a].pz = prand();
    }
}
