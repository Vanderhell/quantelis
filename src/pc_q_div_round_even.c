#include "pc_q_div_round_even.h"
#include <stddef.h>

bool pc_q_div_round_even(int32_t a, int32_t b, unsigned fractional_bits,
                        int32_t *quotient)
{
    int64_t numerator, result;
    uint64_t magnitude, denominator, q, remainder;
    bool negative;

    if (quotient == NULL || b == 0 || fractional_bits > 31u) return false;
    numerator = (int64_t)a * (INT64_C(1) << fractional_bits);
    negative = (numerator < 0) != (b < 0);
    magnitude = numerator < 0 ? (uint64_t)(-numerator)
                              : (uint64_t)numerator;
    denominator = b < 0 ? (uint64_t)(-(int64_t)b) : (uint64_t)b;
    q = magnitude / denominator;
    remainder = magnitude % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (q & 1u) != 0u)) {
        ++q;
    }
    result = negative ? -(int64_t)q : (int64_t)q;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *quotient = (int32_t)result;
    return true;
}
