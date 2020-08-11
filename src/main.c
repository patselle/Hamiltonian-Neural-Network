#include <stdlib.h>
#include <stdio.h>

#include "particle.h"
#include "graphics.h"

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static void particle_init(particle *p, int c)
{
    int i;

    srand(time(NULL));

    for (i = 0; i < c; i++)
    {
        p[i].x = (rand() % 50) - 25;
        p[i].y = (rand() % 50) - 25;
    }    
}

int main()
{
    particle p[10];

    particle_init(p, 10);

    graphics_init();
    graphics_draw(p, 10);
    graphics_loop();
}
