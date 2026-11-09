#ifndef PRIMITIVECORE_Q_TO_I32_ROUND_H
#define PRIMITIVECORE_Q_TO_I32_ROUND_H
#include <stdbool.h>
#include <stdint.h>
/* Convert signed int32 Q raw value to integer, nearest-even; f is 0..31. */
bool rm_q_to_i32_round(int32_t raw, unsigned fractional_bits, int32_t *integer);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_q_to_i32_round
#define pc_q_to_i32_round rm_q_to_i32_round
#endif
#ifndef pc_q_to_i32_round
#define pc_q_to_i32_round rm_q_to_i32_round
#endif
#ifndef PC_PRIMITIVECORE_Q_TO_I32_ROUND_H
#define PC_PRIMITIVECORE_Q_TO_I32_ROUND_H PRIMITIVECORE_Q_TO_I32_ROUND_H
#endif

