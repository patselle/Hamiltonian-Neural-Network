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

static void particle_move(particle * const p, vec3f const * const force)
{
    vec3f tmp;

    // update momentum
    vec3f_scalar(&tmp, force, TIME_STEP);
    vec3f_add(&p->momentum, &p->momentum, &tmp);

    // update position
    vec3f_scalar(&tmp, &p->momentum, TIME_STEP / p->mass);
    vec3f_add(&p->position, &p->position, &tmp);
}

static void *particle_update(void *args)
{
    off_t i, j;
    opts_t *opts;

    vec3f forces[PARTICLES];

    particle *pi, *pj;

    opts = (opts_t*)args;

    while (1)
    {
        // reset forces
        memset(forces, 0, sizeof(vec3f) * PARTICLES);

        // compute forces
        for (i = 0; i < PARTICLES; i++)
        {
            for (j = 0; j < i; j++)
            {
                particle_force(particles + i, particles + j, forces + i, forces + j);
            }
        }

        // update particles momentum and position
        for (i = 0; i < PARTICLES; i++)
        {
            particle_move(particles + i, forces + i);
        }

        // trace particle positions
        trace(particles);

        if (!(opts->flags & OPT_NO_GUI))
        {
            // update ui
            graphics_draw(particles, PARTICLES);

            // sleep 13 milliseconds
            usleep(13 * 1000);
        }
    }
}

int main(int argc, char **argv)
{
    pthread_t thread;
    opts_t opts;

    opts_parse(&opts, argc, argv);

    trace_init(opts.trace_file, PARTICLES);
    graphics_init(opts.flags);

    particle_init(particles, PARTICLES, MASS);
    
    pthread_create(&thread, NULL, particle_update, &opts);

    graphics_loop();

    pthread_cancel(thread);
    pthread_join(thread, NULL);

    trace_end();
}
