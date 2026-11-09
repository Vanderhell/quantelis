#include "pc_decay_factor_from_halflife_q.h"
#include <stddef.h>

#define PC_LN2_Q32 UINT64_C(2977044472)
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

bool pc_decay_factor_from_halflife_q(uint32_t half_life_steps,
                                     uint32_t *retention_q16)
{
    uint64_t x_q32, term_q32 = PC_Q32_ONE;
    int64_t sum_q32 = (int64_t)PC_Q32_ONE;
    uint32_t n;
    uint64_t rounded;

    if (half_life_steps == 0u || retention_q16 == NULL) return false;
    /* The exact Q0.16 result is 65535 at 90851 and 65536 thereafter.
     * Q32 intermediate rounding cannot resolve the near-tie at 90851. */
    if (half_life_steps == UINT32_C(90851)) {
        *retention_q16 = UINT32_C(65535);
        return true;
    }
    if (half_life_steps >= UINT32_C(90852)) {
        *retention_q16 = UINT32_C(65536);
        return true;
    }

    x_q32 = round_even_u64(PC_LN2_Q32, half_life_steps);
    for (n = 1u; n <= 20u; ++n) {
        const uint64_t denominator = (uint64_t)n * PC_Q32_ONE;
        const uint64_t product = term_q32 * x_q32;
        term_q32 = round_even_u64(product, denominator);
        if (term_q32 == 0u) break;
        if ((n & 1u) != 0u) sum_q32 -= (int64_t)term_q32;
        else sum_q32 += (int64_t)term_q32;
    }
    if (sum_q32 < 0) return false;
    rounded = round_even_u64((uint64_t)sum_q32, UINT64_C(65536));
    if (rounded > UINT32_C(65536)) return false;
    *retention_q16 = (uint32_t)rounded;
    return true;
}
