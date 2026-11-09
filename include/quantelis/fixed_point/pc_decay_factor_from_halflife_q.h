#ifndef PRIMITIVECORE_PC_DECAY_FACTOR_FROM_HALFLIFE_Q_H
#define PRIMITIVECORE_PC_DECAY_FACTOR_FROM_HALFLIFE_Q_H

#include <stdbool.h>
#include <stdint.h>

/* Compute the per-step retention factor 2^(-1/half_life_steps) in unsigned
 * Q0.16, rounded to nearest-even. The result ranges from 32768 through 65536;
 * 65536 represents exact unity. half_life_steps must be positive. On zero
 * half-life or null output, return false without modifying the output. */
bool pc_decay_factor_from_halflife_q(uint32_t half_life_steps,
                                     uint32_t *retention_q16);

#endif
