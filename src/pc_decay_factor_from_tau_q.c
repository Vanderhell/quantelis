#include "pc_decay_factor_from_tau_q.h"
#include <stddef.h>

#define PC_Q32_ONE UINT64_C(4294967296)

static uint64_t round_even_u64(uint64_t numerator, uint64_t denominator)
{
    uint64_t quotient = numerator / denominator;
    const uint64_t remainder = numerator % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    return quotient;
}

bool pc_decay_factor_from_tau_q(uint32_t tau_steps, uint32_t *retention_q16)
{
    uint64_t x_q32, term_q32 = PC_Q32_ONE;
    int64_t sum_q32 = (int64_t)PC_Q32_ONE;
    uint32_t n;

    if (tau_steps == 0u || retention_q16 == NULL) return false;
    if (tau_steps == 1u) {
        *retention_q16 = UINT32_C(24109);
        return true;
    }
    /* The exact Q16 transition is 131071 -> 65535, 131072 -> unity.
     * Q32 input rounding cannot resolve the near-tie at 131071. */
    if (tau_steps == UINT32_C(131071)) {
        *retention_q16 = UINT32_C(65535);
        return true;
    }
    if (tau_steps >= UINT32_C(131072)) {
        *retention_q16 = UINT32_C(65536);
        return true;
    }
    x_q32 = round_even_u64(PC_Q32_ONE, tau_steps);
    for (n = 1u; n <= 20u; ++n) {
        const uint64_t denominator = (uint64_t)n * PC_Q32_ONE;
        term_q32 = round_even_u64(term_q32 * x_q32, denominator);
        if (term_q32 == 0u) break;
        if ((n & 1u) != 0u) sum_q32 -= (int64_t)term_q32;
        else sum_q32 += (int64_t)term_q32;
    }
    if (sum_q32 < 0) return false;
    {
        const uint64_t rounded = round_even_u64((uint64_t)sum_q32, UINT64_C(65536));
        if (rounded > UINT32_C(65536)) return false;
        *retention_q16 = (uint32_t)rounded;
    }
    return true;
}
