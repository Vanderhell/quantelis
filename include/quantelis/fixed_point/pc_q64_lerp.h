#ifndef PRIMITIVECORE_PC_Q64_LERP_H
#define PRIMITIVECORE_PC_Q64_LERP_H
#include <stdbool.h>
#include <stdint.h>
/* Convex same-scale signed int64 interpolation at numerator/denominator.
 * Requires denominator>0 and numerator<=denominator. The exact final value
 * rounds nearest-even. Invalid inputs fail without modifying *result. */
bool pc_q64_lerp(int64_t a, int64_t b, uint64_t numerator,
                 uint64_t denominator, int64_t *result);
#endif
