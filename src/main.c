#include <stdlib.h>
#include <stdio.h>

#include "particle.h"
#include "graphics.h"

#define N 10

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static void particle_init(particle *p)
{
    int i;

    srand(time(NULL));

    for (i = 0; i < N; i++)
    {
        p[i].x = (rand() % 50) - 25;
        p[i].y = (rand() % 50) - 25;
    }    
}

int main()
{
    particle p[N];

    particle_init(p);

    graphics_init();
    graphics_draw(p, N);
    graphics_loop();
}
