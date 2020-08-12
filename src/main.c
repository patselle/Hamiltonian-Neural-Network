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
    vec3f force, distance, norm;

    memset(&force, 0, sizeof(vec3f));

    // compute distance
    vec3f_sub(&distance, &pi->position, &pj->position);

    float euclidian = vec3f_euclidian(&distance);

    // compute normalized distance vector
    vec3f_scalar(&norm, &distance, 1.0 / euclidian);

    // compute normalized distance
    float scalar = G * pi->mass * pj->mass / (euclidian * euclidian);

    // compute force
    vec3f_scalar(&force, &norm, scalar);

    // update force p_i
    vec3f_add(&pi->force, &pi->force, &force);

    // update force p_j
    vec3f_sub(&pj->force, &pj->force, &force);

    // printf("force of particle i\n");
    // vec3f_print(&pj->force);
}

static void particle_move()
{
    off_t i, j;

    vec3f tmp, r_new, p_new;
    
    particle *pi, *pj;

    printf("position: (%f, %f)\n", particles[0].position.x, particles[0].position.y);
    printf("position: (%f, %f)\n", particles[1].position.x, particles[1].position.y);
    printf("position: (%f, %f)\n", particles[2].position.x, particles[2].position.y);

    int count = 0;
    while (1)
    {       

        if (count == 1000000)
        {
            break;
        }
        particle_force_reset();

        for (i = 0; i < PARTICLES; i++)
        {
            pi = particles + i; 

            for (j = 0; j < i; j++)
            {

                pj = particles + j;

                particle_force(pi, pj);
            }
        }

        // update position of particle i
        // derivation of the equation
        // v_new = v_old + F / m * TIME_STEP    (a = F / m)
        // p_new = p_old + F * TIME_STEP
        // with
        // r_new = r_old + v * TIME_STEP
        // r_new = r_old + p_new / m * TIME_STEP
        // insert p_new
        // r_new = r_old + TIME_STEP / m * (p_old + F * TIME_STEP)

        int k;

        for (k = 0; k < PARTICLES; k++)
        {
            pi = particles + k;
            
            // scalar multiplication: F *TIME_STEP
            vec3f_scalar(&tmp, &pi->force, TIME_STEP);
            // add p_old and F * TIME_STEP together (this is p_new)
            vec3f_add(&p_new, &pi->momentum, &tmp);
            // scalar multiplication of TIME_STEP / m * (p_old + F * TIME_STEP)
            float scalar = TIME_STEP / pi->mass;
            vec3f_scalar(&tmp, &p_new, scalar);
            // add r_old and the previous computated expression together
            vec3f_add(&r_new, &pi->position, &tmp);
            
            // update position of particle i
            pi->position = r_new;
            // update momentum of particle i
            pi->momentum = p_new;
        }

        count += 1;

        // break;

        //graphics_draw(particles, PARTICLES);

        // 13 milliseconds
        //usleep(13 * 1000);
        // usleep(5 * 1000000);
    }

    printf("#####################################################\n");
    printf("position: (%f, %f)\n", particles[0].position.x, particles[0].position.y);
    printf("position: (%f, %f)\n", particles[1].position.x, particles[1].position.y);
    printf("position: (%f, %f)\n", particles[2].position.x, particles[2].position.y);
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
