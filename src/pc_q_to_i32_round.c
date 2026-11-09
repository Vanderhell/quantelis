#include "pc_q_to_i32_round.h"
#include <stddef.h>

bool rm_q_to_i32_round(int32_t raw, unsigned fractional_bits,
                       int32_t *integer)
{
    uint64_t magnitude, quotient, remainder, denominator;
    int64_t result;

    if (integer == NULL || fractional_bits > 31u) return false;
    magnitude = raw < 0 ? (uint64_t)(-(int64_t)raw) : (uint64_t)raw;
    denominator = UINT64_C(1) << fractional_bits;
    quotient = magnitude / denominator;
    remainder = magnitude % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    result = raw < 0 ? -(int64_t)quotient : (int64_t)quotient;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *integer = (int32_t)result;
    return true;
}
