#include <stdlib.h>
#include <stdio.h>

#include "particle.h"


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

    printf("random number in [0,1) %f\n", frand());
}
