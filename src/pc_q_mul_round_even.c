#include "pc_q_mul_round_even.h"
#include <stddef.h>

bool pc_q_mul_round_even(int32_t a, int32_t b, unsigned fractional_bits,
                         int32_t *product)
{
    int64_t wide_product, result;
    uint64_t magnitude, denominator, quotient, remainder;

    if (product == NULL || fractional_bits > 31u) return false;
    wide_product = (int64_t)a * b;
    magnitude = wide_product < 0 ? (uint64_t)(-wide_product)
                                 : (uint64_t)wide_product;
    denominator = UINT64_C(1) << fractional_bits;
    quotient = magnitude / denominator;
    remainder = magnitude % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    result = wide_product < 0 ? -(int64_t)quotient : (int64_t)quotient;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *product = (int32_t)result;
    return true;
}
