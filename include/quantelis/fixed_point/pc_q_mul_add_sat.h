#ifndef PC_Q_MUL_ADD_SAT_H
#define PC_Q_MUL_ADD_SAT_H
#include <stdbool.h>
#include <stdint.h>
/* sat32(round_even(a*b/2^f)+c), f=0..31. */
bool pc_q_mul_add_sat(int32_t a, int32_t b, int32_t c,
                      unsigned fractional_bits, int32_t *result);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_q_mul_add_sat
#define pc_q_mul_add_sat pc_q_mul_add_sat
#endif
#ifndef pc_q_mul_add_sat
#define pc_q_mul_add_sat pc_q_mul_add_sat
#endif
#ifndef PC_PC_Q_MUL_ADD_SAT_H
#define PC_PC_Q_MUL_ADD_SAT_H PC_Q_MUL_ADD_SAT_H
#endif

