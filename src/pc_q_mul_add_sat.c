#include "pc_q_mul_add_sat.h"
#include <stddef.h>

bool rm_q_mul_add_sat(int32_t a, int32_t b, int32_t c,
                      unsigned fractional_bits, int32_t *result)
{
    int64_t product, rounded, accumulated;
    uint64_t magnitude, denominator, quotient, remainder;

    if (result == NULL || fractional_bits > 31u) return false;
    product = (int64_t)a * b;
    magnitude = product < 0 ? (uint64_t)(-product) : (uint64_t)product;
    denominator = UINT64_C(1) << fractional_bits;
    quotient = magnitude / denominator;
    remainder = magnitude % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    rounded = product < 0 ? -(int64_t)quotient : (int64_t)quotient;
    accumulated = rounded + c;
    if (accumulated > INT32_MAX) accumulated = INT32_MAX;
    if (accumulated < INT32_MIN) accumulated = INT32_MIN;
    *result = (int32_t)accumulated;
    return true;
}
