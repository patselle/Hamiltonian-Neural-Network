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
#define TIME_STEP 0.5
#define G 1

static particle *particles;

static inline void particle_force(particle const * const pi, particle const * const pj, vec3f * const f_i, vec3f * const f_j)
{
    vec3f force, distance, norm;

    // compute distance
    vec3f_sub(&distance, &pi->position, &pj->position);

    float euclidian = vec3f_euclidian(&distance);

    // compute normalized distance vector
    vec3f_scalar(&norm, &distance, 1.0 / euclidian);

    // compute normalized distance (NOTE the minus sign is due the inverted direction between F_ij and r_ij)
    float scalar = - G * pi->mass * pj->mass / (euclidian);
    // float scalar = - G * pi->mass * pj->mass / (euclidian);

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

static void compute_center_of_mass(vec3f * const v, particle const * const p, size_t const c)
{
    off_t i;
    vec3f tmp;
    float total_mass = 0;

    memset(v, 0, sizeof(vec3f));

    for (i = 0; i < c; i++)
    {
        total_mass += p[i].mass;

        vec3f_scalar(&tmp, &p[i].position, p[i].mass);
        vec3f_add(v, v, &tmp);
    }

    vec3f_scalar(v, v, 1.0 / total_mass);
}

static void particle_printf(size_t const iteration, size_t const n, vec3f const * const forces)
{
    off_t i;
    particle *pi;
    vec3f const *fi;

    printf("------------ iteration %jd ------------\n", iteration);

    for (i = 0; i < n; i++)
    {
        pi = particles + i;
        fi = forces + i;

        printf("particle %jd\n", i);
        printf("\tposition %f, %f, %f\n", pi->position.x, pi->position.y, pi->position.z);
        printf("\tforce    %f, %f, %f\n", fi->x, fi->y, fi->z);
        printf("\tmomentum %f, %f, %f\n", pi->momentum.x, pi->momentum.y, pi->momentum.z);
    }
}

static void *particle_update(void *args)
{
    off_t i, j, c;
    opts_t *opts;
    vec3f *forces, center_of_mass;
    particle *pi, *pj;

    opts = (opts_t*)args;

    forces = (vec3f*)malloc(sizeof(vec3f) * opts->particle_count);

    memset(forces, 0, sizeof(vec3f) * opts->particle_count);

    for (c = 0; c < opts->iterations; c++)
    {
        // tracing and debugging

        if (opts->flags & OPT_DEBUG)
        {
            particle_printf(c, opts->particle_count, forces);
        }

        trace(particles);

        // reset forces
        memset(forces, 0, sizeof(vec3f) * opts->particle_count);

        // compute forces
        for (i = 0; i < opts->particle_count; i++)
        {
            for (j = 0; j < i; j++)
            {
                particle_force(particles + i, particles + j, forces + i, forces + j);
            }
        }

        // update particles momentum and position
        for (i = 0; i < opts->particle_count; i++)
        {
            particle_move(particles + i, forces + i);
        }

        if (!(opts->flags & OPT_NO_GUI))
        {
            // compute_center_of_mass(&center_of_mass, particles, opts->particle_count);

            graphics_update(&center_of_mass);

            // sleep 13 milliseconds
            usleep(13 * 1000);
        }
    }

    // trace again
    if (opts->flags & OPT_DEBUG)
    {
        particle_printf(c, opts->particle_count, forces);
    }

    trace(particles);

    // just exit
    exit(0);
}

int main(int argc, char **argv)
{
    pthread_t thread;
    opts_t opts;

    opts_parse(&opts, argc, argv);

    if (opts.init_file)
    {
        particle_init_file(&particles, &opts.particle_count, opts.init_file);
    }
    else
    {
        particle_init(&particles, &opts);
    }

    trace_init(opts.trace_file, opts.particle_count);
    graphics_init(particles, &opts);

    pthread_create(&thread, NULL, particle_update, &opts);

    graphics_loop();

    pthread_cancel(thread);
    pthread_join(thread, NULL);

    trace_end();
}
