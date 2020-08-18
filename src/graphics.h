#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "particle.h"

extern void graphics_init(particle * const p, opts_t const * const opts);
extern void graphics_loop();
extern void graphics_update(vec3f * const center_of_mass);

#endif
