#ifndef PRIMITIVECORE_Q_MUL_ROUND_EVEN_H
#define PRIMITIVECORE_Q_MUL_ROUND_EVEN_H
#include <stdbool.h>
#include <stdint.h>
/* Multiply two signed int32 Q values with f fractional bits, nearest-even. */
bool rm_q_mul_round_even(int32_t a, int32_t b, unsigned fractional_bits,
                         int32_t *product);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_q_mul_round_even
#define pc_q_mul_round_even rm_q_mul_round_even
#endif
#ifndef pc_q_mul_round_even
#define pc_q_mul_round_even rm_q_mul_round_even
#endif
#ifndef PC_PRIMITIVECORE_Q_MUL_ROUND_EVEN_H
#define PC_PRIMITIVECORE_Q_MUL_ROUND_EVEN_H PRIMITIVECORE_Q_MUL_ROUND_EVEN_H
#endif

