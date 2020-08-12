#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "particle.h"
#include "vec.h"
#include "graphics.h"
#include "trace.h"

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

static inline void particle_force(particle const * const pi, particle const * const pj, vec3f * const f_i, vec3f * const f_j)
{
    vec3f force, distance, norm;

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
    vec3f_add(f_i, f_i, &force);

    // update force p_j
    vec3f_sub(f_j, f_j, &force);
}

static void particle_move()
{
    off_t i, j, c;

    vec3f tmp, r_new, p_new;
    vec3f forces[PARTICLES];

    particle *pi, *pj;

    for (c = 0; c < 1000000; c++)
    {
        // reset forces
        memset(forces, 0, sizeof(vec3f) * PARTICLES);

        for (i = 0; i < PARTICLES; i++)
        {
            for (j = 0; j < i; j++)
            {
                particle_force(particles + i, particles + j, forces + i, forces + j);
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

        for (i = 0; i < PARTICLES; i++)
        {
            pi = particles + i;
            
            // scalar multiplication: F *TIME_STEP
            vec3f_scalar(&tmp, forces + i, TIME_STEP);
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

        // trace particle positions
        trace(particles);

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
    trace_init("trace", PARTICLES);

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

    trace_end();
}
