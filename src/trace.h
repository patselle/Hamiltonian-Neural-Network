#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "particle.h"

#define FLOAT_MAX_CHARS (3 + FLT_MANT_DIG - FLT_MIN_EXP)

static FILE *trace_fp = NULL;
static size_t trace_n;
static char *trace_line;

static inline void trace_init(char const * const file, size_t const n)
{
    if (file)
    {
        trace_n = n;
        trace_line = (char*)malloc(sizeof(char) * n * (FLOAT_MAX_CHARS + 7));
        trace_fp = fopen(file, "a");
    }
}

static inline void trace(particle * const particles)
{
    off_t i;

    char str[FLOAT_MAX_CHARS + 7];

    particle *p;

    if (!trace_fp)
        return;

    trace_line[0] = '\0';

    for (i = 0; i < trace_n; i++)
    {
	p = particles + i;

        sprintf(str, "%f;%f;%f;%f;%f;%f;",p->position.x, p->position.y, p->position.z, p->momentum.x, p->momentum.y, p->momentum.z);
        strcat(trace_line, str);
    }

    fprintf(trace_fp, "%s\n", trace_line);
}

static inline void trace_end()
{
    if (trace_fp)
    {
        fclose(trace_fp);
        free(trace_line);
    }
}

#endif
