#include "pc_ratio_round_even_u32.h"
#include <stddef.h>

bool rm_ratio_round_even_u32(uint32_t numerator, uint32_t denominator,
                             uint32_t *rounded)
{
    uint32_t q, r;
    uint64_t twice_remainder;
    if (rounded == NULL || denominator == 0u) return false;
    q = numerator / denominator;
    r = numerator % denominator;
    twice_remainder = (uint64_t)r * 2u;
    if (twice_remainder > denominator ||
        (twice_remainder == denominator && (q & 1u) != 0u)) ++q;
    *rounded = q;
    return true;
}
