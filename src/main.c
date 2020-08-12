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
    particles[0].mass = MASS;

    particles[1].position.x = 3;
    particles[1].position.y = 6;
    particles[1].position.z = 0;
    particles[1].mass = MASS;

    particles[2].position.x = -1;
    particles[2].position.y = 4;
    particles[2].position.z = 0;
    particles[2].mass = MASS;
}

static inline void particle_force_reset()
{
    off_t i;
    
    for (i = 0; i < PARTICLES; i++)
    {
        memset(&particles[i].force, 0, sizeof(vec3f));
    }
}

static inline void particle_force(particle * const pi, particle * const pj)
{
    vec3f force, distance, norm, tmp;

    memset(&force, 0, sizeof(vec3f));

    // compute distance
    vec3f_sub(&distance, &pi->position, &pj->position);

    // compute normalized distance vector
    vec3f_scalar(&norm, &distance, 1.0 / vec3f_euclidian(&distance));

    // compute normalized distance
    float scalar = G * pi->mass * pj->mass * 1.0 / (vec3f_euclidian(&distance) * vec3f_euclidian(&distance));

    // vec3f_mul(&tmp, &distance, &distance);
    // float scalar = 1.0 / (sqrt(vec3f_sum(&tmp)));
    // vec3f_scalar(&norm, &distance, scalar);

    // compute force
    vec3f_scalar(&force, &norm, scalar);

    printf("force: ");
    vec3f_print(&force);

    // update force p_i
    vec3f_add(&pi->force, &pi->force, &force);

    // update force p_j
    vec3f_sub(&pj->force, &pj->force, &force);
}

static void particle_move()
{
    off_t i, j;
    
    particle *pi, *pj, *pk;

    while (1)
    {
        particle_force_reset();

        for (i = 0; i < PARTICLES; i++)
        {
            pi = particles + i; 



            for (j = 0; j < i; j++)
            {

                pj = particles + j;

                printf("##########################################\n");
                for (int k = 0; k < PARTICLES; k++)
                {
                    pk = particles + k;
                    printf("particle %d\n", k);
                    printf("(%f, %f)\n", pk->force.x, pk->force.y);
                }
                printf("##########################################\n");



                particle_force(pi, pj);
            }
        }

        printf("##########################################\n");
        for (int k = 0; k < PARTICLES; k++)
        {
            pk = particles + k;
            printf("particle %d\n", k);
            printf("(%f, %f)\n", pk->force.x, pk->force.y);
        }
        printf("##########################################\n");



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
