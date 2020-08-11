#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#include "particle.h"
#include "vecops.h"
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


static void particle_init()
{
    int i;

    printf("Initialite particles...\n");

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

    for (i = 0; i < PARTICLES; i++)
    {
        // particles[i].position.x = (rand() % 50) - 25;
        // particles[i].position.y = (rand() % 50) - 25;
        // particles[i].position.z = 0;

        // particles[i].momentum.x = frand() / 100;
        // particles[i].momentum.y = frand() / 100;
        // particles[i].momentum.z = 0;

        particles[i].mass = MASS;

        printf("particle %i: \n", i);
        printf("pos: (%f, %f)\n", particles[i].position.x, particles[i].position.y);
        //printf("mom: (%f, %f)\n", particles[i].momentum.x, particles[i].momentum.y);
    }



}

static void particle_move()
{
    printf("\n");
    int i, j;
    vec3d vecforce, diffposition, vecnorm;

    int count = 0;

    while (1)
    {
        if (count == 1)
        {
            break;  
        }
        // here compute particle movement

        for (i = 0; i < PARTICLES; i++)
        {
            // set sum of forces to zero
            particles[i].force.x = 0;
            particles[i].force.y = 0;
            particles[i].force.z = 0;

            vecforce.x = 0;
            vecforce.y = 0;

            for (j = 0; j < i; j++)
            {
                diffposition = vecsub(&particles[i].position, &particles[j].position);

                printf("i: %d, j: %d\n", i, j);
                printf("(%f, %f) - (%f, %f) = (%f, %f)\n", particles[i].position.x,  particles[i].position.y, particles[j].position.x,  particles[j].position.y, diffposition.x, diffposition.y);

                printf("vecquadraticdistance: %f\n", vecquadraticdistance(&particles[i].position, &particles[j].position));

                // float scalar =  G * particles[i].mass * particles[j].mass / vecquadraticdistance(&particles[i].position, &particles[j].position);
                float scalar = 1.0 / vecquadraticdistance(&particles[i].position, &particles[j].position);

                printf("scalar: %f\n", scalar);

 

                vecnorm = normvec(&diffposition);

                

                printf("vecnorm: (%f, %f)\n", vecnorm.x, vecnorm.y);

                printf("vecforce: (%f, %f)\n", vecforce.x, vecforce.y);

                vecforce = vecsum(&vecforce, scalmul(scalar, vecnorm));

                printf("vecforce: (%f, %f)\n", vecforce.x, vecforce.y);

                printf("= (%f, %f)\n", vecforce.x,  vecforce.y);

                printf("###########################\n");

            }
        }

        count += 1;

        //graphics_draw(particles, PARTICLES);

        // 13 milliseconds
        //usleep(13 * 1000);
        // usleep(5 * 1000000);
    }
}

int main()
{

    printf("Starting 3-Body Simulation...\n");
    particle_init();
    particle_move();
    // pthread_t thread;

    // particle_init();

    // pthread_create(&thread, NULL, particle_move, NULL);

    // graphics_init();
    // graphics_loop();

    // pthread_cancel(thread);
    // pthread_join(thread, NULL);
}
