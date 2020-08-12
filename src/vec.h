#ifndef VEC_H
#define VEC_H

#include <math.h>

#ifdef USE_AVX2
#include <immintrin.h>
#endif


typedef struct
{
    float x,y,z;
#ifdef USE_AVX2
    float align;
#endif
} vec3f;

static inline void vec3f_sub(vec3f * const c, vec3f const * const a, vec3f const * const b)
{
#ifdef USE_AVX2
    __m256 va = _mm256_load_ps((float*)a);
    __m256 vb = _mm256_load_ps((float*)b);
    __m256 vc = _mm256_sub_ps(va, vb);
    _mm256_store_ps((float*)c, vc);
#else
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    c->z = a->z - b->z;
#endif
}

static inline void vec3f_add(vec3f * const c, vec3f const * const a, vec3f const * const b)
{
#ifdef USE_AVX2
    __m256 va = _mm256_load_ps((float*)a);
    __m256 vb = _mm256_load_ps((float*)b);
    __m256 vc = _mm256_add_ps(va, vb);
    _mm256_store_ps((float*)c, vc);
#else
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    c->z = a->z + b->z;
#endif
}

// quadratic distance
static float vec3f_quadist(vec3f const * const a, vec3f const * const b)
{
    return (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z);
}

static inline void vec3f_scalar(vec3f * const c, vec3f const * const a, float scalar)
{
    c->x = scalar * a->x;
    c->y = scalar * a->y;
    c->z = scalar * a->z;
}

// euclidian norm
static inline float vec3f_euclid(vec3f const * const a)
{
    return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

static inline void vec3f_norm(vec3f * const b, vec3f const * const a)
{
    vec3f_scalar(b, a, 1.0 / vec3f_euclid(a));
}

#endif

