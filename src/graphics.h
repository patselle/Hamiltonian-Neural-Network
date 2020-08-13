#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "particle.h"

extern void graphics_init(int const flags);
extern void graphics_loop();
extern void graphics_draw(particle *p, unsigned int const c);

#endif
