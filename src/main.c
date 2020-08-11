#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "particle.h"
#include "graphics.h"

#define N 10

static particle particles[N];

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static void particle_init()
{
    int i;

    srand(time(NULL));

    for (i = 0; i < N; i++)
    {
        particles[i].x = (rand() % 50) - 25;
        particles[i].y = (rand() % 50) - 25;
        particles[i].px = frand() / 100;
        particles[i].py = frand() / 100;
    }    
}

static void *particle_move(void *args)
{
    int i;

    while (1)
    {
        // here compute particle movement

        for (i = 0; i < N; i++)
        {
            particles[i].x += particles[i].px;
            particles[i].y += particles[i].py;
        }

        graphics_draw(particles, N);

        // 13 milliseconds
        usleep(13 * 1000);
    }
}

int main()
{
    pthread_t thread;

    particle_init();

    pthread_create(&thread, NULL, particle_move, NULL);

    graphics_init();    
    graphics_loop();

    pthread_cancel(thread);
    pthread_join(thread, NULL);
}
