#include <stdlib.h>
#include <stdio.h>

#include "particle.h"

#define N 3


static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

int main()
{
    printf("Hello from main\n");

    printf("Create some particles\n");

    particle a;
    particle b;
    particle c;

    a.x = 3.0;

    static particle particles[N];

    printf("random number in [0,1) %f\n", frand());

    for (int a = 0; a < N; a++)
    {
        printf("it %d\n", N);

        // init position
        particles[a].x = frand();
        particles[a].y = frand();
        particles[a].z = frand();

        // init momentum
        particles[a].px = frand();
        particles[a].py = frand();
        particles[a].pz = frand();
    }
}
