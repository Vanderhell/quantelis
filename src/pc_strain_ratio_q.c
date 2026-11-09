#include "pc_strain_ratio_q.h"
#include <stddef.h>

bool pc_strain_ratio_q(int32_t delta_resistance_milliohm,
                       uint16_t nominal_resistance_ohm,
                       uint32_t gauge_factor_q16_16,
                       int32_t *strain_microstrain)
{
    const uint64_t scale = UINT64_C(65536000);
    int64_t numerator, result;
    uint64_t magnitude, denominator, quotient, remainder;
    bool negative;
    if (strain_microstrain == NULL || nominal_resistance_ohm == 0u ||
        gauge_factor_q16_16 == 0u) return false;
    numerator = (int64_t)delta_resistance_milliohm * (int64_t)scale;
    negative = numerator < 0;
    magnitude = negative ? (uint64_t)(-numerator) : (uint64_t)numerator;
    denominator = (uint64_t)nominal_resistance_ohm * gauge_factor_q16_16;
    quotient = magnitude / denominator;
    remainder = magnitude % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & UINT64_C(1)) != 0u)) {
        ++quotient;
    }
    result = negative ? -(int64_t)quotient : (int64_t)quotient;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *strain_microstrain = (int32_t)result;
    return true;
}