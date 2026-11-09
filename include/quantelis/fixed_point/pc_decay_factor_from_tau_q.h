#ifndef PRIMITIVECORE_PC_DECAY_FACTOR_FROM_TAU_Q_H
#define PRIMITIVECORE_PC_DECAY_FACTOR_FROM_TAU_Q_H

#include <stdbool.h>
#include <stdint.h>

/* Return exp(-1/tau_steps) as nearest-even unsigned Q0.16 retention.
 * tau_steps must be positive; 65536 represents unity. */
bool pc_decay_factor_from_tau_q(uint32_t tau_steps, uint32_t *retention_q16);

#endif
