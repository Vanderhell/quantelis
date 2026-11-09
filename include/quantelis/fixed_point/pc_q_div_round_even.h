#ifndef PRIMITIVECORE_Q_DIV_ROUND_EVEN_H
#define PRIMITIVECORE_Q_DIV_ROUND_EVEN_H
#include <stdbool.h>
#include <stdint.h>
/* Compute (a*2^f)/b to int32, nearest-even; f=0..31 and b!=0. */
bool rm_q_div_round_even(int32_t a, int32_t b, unsigned fractional_bits,
                         int32_t *quotient);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_q_div_round_even
#define pc_q_div_round_even rm_q_div_round_even
#endif
#ifndef pc_q_div_round_even
#define pc_q_div_round_even rm_q_div_round_even
#endif
#ifndef PC_PRIMITIVECORE_Q_DIV_ROUND_EVEN_H
#define PC_PRIMITIVECORE_Q_DIV_ROUND_EVEN_H PRIMITIVECORE_Q_DIV_ROUND_EVEN_H
#endif

