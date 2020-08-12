#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "particle.h"

#define PARTICLE_MAX_CHARS (4 + 3 + FLT_MANT_DIG - FLT_MIN_EXP)

static FILE *trace_fp = NULL;
static size_t trace_n;
static char *trace_line;

static inline void trace_init(char const * const file, size_t const n)
{
    trace_n = n;
    trace_line = (char*)malloc(sizeof(char) * n * PARTICLE_MAX_CHARS);
    trace_fp = fopen(file, "a");
}

static inline void trace(particle const * const particles)
{
    off_t i;

    char str[PARTICLE_MAX_CHARS + 1];

    trace_line[0] = '\0';

    for (i = 0; i < trace_n; i++)
    {
        sprintf(str, "(%f,%f,%f)",particles[i].position.x, particles[i].position.y, particles[i].position.z);
        strcat(trace_line, str);
    }

    fprintf(trace_fp, "%s\n", trace_line);
}

static inline void trace_end()
{
    fclose(trace_fp);
    free(trace_line);
}

#endif
