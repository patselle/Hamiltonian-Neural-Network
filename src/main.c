#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#include "particle.h"
#include "graphics.h"

#define DIMENSIONS 2
#define PARTICLES 3
#define TIME_MAX 10
#define TIME_STEP 0.1
#define MASS 1
#define G 1

static particle particles[PARTICLES];

static inline float frand()
{
    return (float)rand() / RAND_MAX;
}

static vec3d vecsub(vec3d *pos1, vec3d *pos2)
{
    vec3d sum;
    sum.x = pos1->x - pos2->x;
    sum.y = pos1->y - pos2->y;
    sum.z = pos1->z - pos2->z;

    return sum;
}

static vec3d vecsum(vec3d *pos1, vec3d pos2)
{
    vec3d sum;
    sum.x = pos1->x + pos2.x;
    sum.y = pos1->y + pos2.y;
    sum.z = pos1->z + pos2.z;

    return sum;
}

static float vecquadraticdistance(vec3d *vec1, vec3d *vec2)
{
    float distance = 0;

    distance += (vec1->x - vec2->x) * (vec1->x - vec2->x);
    distance += (vec1->y - vec2->y) * (vec1->y - vec2->y);
    distance += (vec1->z - vec2->z) * (vec1->z - vec2->z);

    return distance;
}

static vec3d scalmul(float scalar, vec3d vec)
{
    vec3d scalvec;

    // scalvec.x = *scalar * vec->x;
    // scalvec.y = *scalar * vec->y;
    // scalvec.z = *scalar * vec->z;

    scalvec.x = scalar * vec.x;
    scalvec.y = scalar * vec.y;
    scalvec.z = scalar * vec.z;

    return scalvec;
}

static vec3d normvec(vec3d *vec)
{
    vec3d vecnorm;
    float scalar = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    return scalmul(scalar, *vec);
}

static void particle_init()
{
    int i;

    srand(time(NULL));

    for (i = 0; i < PARTICLES; i++)
    {
        particles[i].position.x = (rand() % 50) - 25;
        particles[i].position.y = (rand() % 50) - 25;

        particles[i].momentum.x = frand() / 100;
        particles[i].momentum.y = frand() / 100;

        particles[i].mass = MASS;
    }    
}

static void *particle_move(void *args)
{
    int i, j;
    vec3d vecforce, subvector, vecnorm;

    while (1)
    {
        // here compute particle movement

        for (i = 0; i < PARTICLES; i++)
        {
            // set sum of forces to zero
            particles[i].force.x = 0;
            particles[i].force.y = 0;
            particles[i].force.z = 0;

            for (j = 0; j < i; j++)
            {
                printf("i: %d, j: %d\n", i, j);
                // computing gravitational force between particles i and j

                // BITTE SCHOENER MACHEN, WEI? NICHT WARUM Z.B. &scalmul(scalar, vecnorm) FUNKTIONIERT...
                // WILL EIG NUR POINTER UEBERGEBEN, ABER DA MECKERT ER
                float scalar =  G * particles[i].mass * particles[j].mass / vecquadraticdistance(&particles[i].position, &particles[j].position);
                subvector = vecsub(&particles[i].position, &particles[j].position);
                vecnorm = normvec(&subvector);
                vecforce = vecsum(&vecforce, scalmul(scalar, vecnorm));

            }
        }

        graphics_draw(particles, PARTICLES);

        // 13 milliseconds
        //usleep(13 * 1000);
        usleep(5 * 1000000);
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
