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
#include "opts.h"

#define DIMENSIONS 2
#define PARTICLES 5
#define TIME_MAX 10
#define TIME_STEP 0.1
#define MASS 1
#define G 0.5

static particle particles[PARTICLES];

static void particle_init2()
{
    /* use particle_init() from particle.h */

    srand(time(NULL));

    particle_init(particles, PARTICLES, 1);

    // particles[0].position.x = 5;
    // particles[0].position.y = -2;
    // particles[0].position.z = 0;
    // particles[0].mass = 0.1;

    // particles[1].position.x = 3;
    // particles[1].position.y = 6;
    // particles[1].position.z = 0;
    // particles[1].mass = 0.5;

    // particles[2].position.x = -1;
    // particles[2].position.y = 4;
    // particles[2].position.z = 0;
    // particles[2].mass = 0.01;
}

static inline void particle_force(particle const * const pi, particle const * const pj, vec3f * const f_i, vec3f * const f_j)
{
    vec3f force, distance, norm;

    // compute distance
    vec3f_sub(&distance, &pi->position, &pj->position);

    float euclidian = vec3f_euclidian(&distance);

    // compute normalized distance vector
    vec3f_scalar(&norm, &distance, 1.0 / euclidian);

    // compute normalized distance (NOTE the minus sign is due the inverted direction between F_ij and r_ij)
    float scalar = - G * pi->mass * pj->mass / (euclidian * euclidian);

    // compute force
    vec3f_scalar(&force, &norm, scalar);

    // update force p_i
    vec3f_add(f_i, f_i, &force);

    // update force p_j
    vec3f_sub(f_j, f_j, &force);
}

static void *particle_move(void *args)
{
    off_t i, j, c;

    vec3f tmp, r_new, p_new;
    vec3f forces[PARTICLES];

    particle *pi, *pj;

    for (c = 0; c < 1000; c++)
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
        graphics_draw(particles, PARTICLES);

        // sleep 13 milliseconds = 60 fps
        usleep(13 * 1000);
    }
}

int main(int argc, char **argv)
{
    pthread_t thread;
    opts_t opts;

    opts_parse(&opts, argc, argv);

    trace_init(opts.trace_file, PARTICLES);
    graphics_init(opts.flags);

    particle_init2();
    
    pthread_create(&thread, NULL, particle_move, NULL);

    graphics_loop();

    pthread_cancel(thread);
    pthread_join(thread, NULL);

    trace_end();
}
