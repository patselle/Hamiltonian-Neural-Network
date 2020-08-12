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
    vec3f force, distance, norm, tmp;
    particle *pi, *pj;

    while (1)
    {
        // here compute particle movement

        // set forces of all particles to zero
        for (i = 0; i < PARTICLES; i++)
        {
            pi = particles + i;
            memset(&pi->force, 0, sizeof(vec3f));
        }

        memset(&force, 0, sizeof(vec3f));

        for (i = 0; i < PARTICLES; i++)
        {
            pi = particles + i;

            for (j = 0; j < i; j++)
            {
                pj = particles + j;

                // compute distance
                vec3f_sub(&distance, &pi->position, &pj->position);

                // compute normalized distance vector
                vec3f_mul(&tmp, &distance, &distance);
                float scalar = 1.0 / sqrt(vec3f_sum(&tmp));
                vec3f_scalar(&norm, &distance, scalar);

                // compute force F_ij
                vec3f_scalar(&force, &norm, scalar);

                // add F_ij to particle i's force
                vec3f_add(&pi->force, &pi->force, &force);

                // compute force F_ji = -F_ij
                vec3f_neg(&force);
                
                // add F_ji to particle j's force
                vec3f_add(&pj->force, &pj->force, &force);
            }
        }

        break;

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
