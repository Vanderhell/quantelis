#ifndef PRIMITIVECORE_ONE_POLE_SMOOTHER_Q_H
#define PRIMITIVECORE_ONE_POLE_SMOOTHER_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Update caller-owned state toward input by Q16 alpha:
 * state += round-nearest-even((input-state)*alpha_q16/65536).
 * alpha_q16 must be in [0,65536]. Invalid input leaves state unchanged.
 * Per-sample coefficient: effective bandwidth depends on sample cadence. */
bool rm_one_pole_smoother_q(int32_t input, uint32_t alpha_q16, int32_t *state);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_one_pole_smoother_q
#define pc_one_pole_smoother_q rm_one_pole_smoother_q
#endif
#ifndef pc_one_pole_smoother_q
#define pc_one_pole_smoother_q rm_one_pole_smoother_q
#endif
#ifndef PC_PRIMITIVECORE_ONE_POLE_SMOOTHER_Q_H
#define PC_PRIMITIVECORE_ONE_POLE_SMOOTHER_Q_H PRIMITIVECORE_ONE_POLE_SMOOTHER_Q_H
#endif

