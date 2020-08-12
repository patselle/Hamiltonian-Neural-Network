#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "particle.h"
#include "vec.h"
#include "graphics.h"

#define DIMENSIONS 2
#define PARTICLES 3
#define TIME_MAX 10
#define TIME_STEP 0.1
#define MASS 1
#define G 1

static particle particles[PARTICLES];

static void particle_init2()
{
    /* use particle_init() from particle.h */
    int i;

    printf("Initialize particles...\n");

    srand(time(NULL));

    particles[0].position.x = 5;
    particles[0].position.y = -2;
    particles[0].position.z = 0;

    particles[1].position.x = 3;
    particles[1].position.y = 6;
    particles[1].position.z = 0;

    particles[2].position.x = -1;
    particles[2].position.y = 4;
    particles[2].position.z = 0;
}

static void particle_move()
{
    int i, j;
    vec3f force, distance, norm;
    particle *pi, *pj;

    while (1)
    {
        // here compute particle movement

        for (i = 0; i < PARTICLES; i++)
        {
            pi = particles + i;

            // set forces to zero
            memset(&pi->force, 0, sizeof(vec3f));
            memset(&force, 0, sizeof(vec3f));

            for (j = 0; j < i; j++)
            {
                pj = particles + j;

                vec3f_sub(&distance, &pi->position, &pj->position);

                printf("(%f,%f) - (%f,%f) = (%f,%f)\n", pi->position.x, pi->position.y, pj->position.x, pi->position.y, distance.x, distance.y);

                printf("vec3f_quadist: %f\n", vec3f_quadist(&pi->position, &pj->position));

                // float scalar =  G * pi->mass * pj->mass / vec3f_quadist(&pi->position, &pj->position);
                float scalar = 1.0 / vec3f_quadist(&pi->position, &pj->position);

                printf("scalar: %f\n", scalar);

 

                vec3f_norm(&norm, &distance);

                

                printf("norm: (%f, %f)\n", norm.x, norm.y);

                vec3f_scalar(&norm, &norm, scalar);
                vec3f_add(&force, &force, &norm);

                printf("force: (%f, %f)\n", force.x, force.y);

                printf("###########################\n");

                return;
            }
        }

        //graphics_draw(particles, PARTICLES);

        // 13 milliseconds
        //usleep(13 * 1000);
        // usleep(5 * 1000000);
    }
}

int main()
{

    printf("Starting 3-Body Simulation...\n");
    particle_init2();
    particle_move();
    // pthread_t thread;

    // particle_init();

    // pthread_create(&thread, NULL, particle_move, NULL);

    // graphics_init();
    // graphics_loop();

    // pthread_cancel(thread);
    // pthread_join(thread, NULL);
}
