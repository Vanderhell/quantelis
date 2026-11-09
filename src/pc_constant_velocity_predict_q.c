#include "pc_constant_velocity_predict_q.h"
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
bool pc_constant_velocity_predict_q(int32_t position_q16_16,
                                    int32_t velocity_q16_16_per_s,
                                    uint32_t dt_us,
                                    int32_t *predicted_q16_16)
{
    const int64_t product = (int64_t)velocity_q16_16_per_s * (int64_t)dt_us;
    const bool negative = product < 0;
    const uint64_t magnitude = negative ? (uint64_t)(-product) : (uint64_t)product;
    uint64_t quotient = magnitude / UINT64_C(1000000);
    const uint64_t remainder = magnitude % UINT64_C(1000000);
    int64_t delta, result;
    if (predicted_q16_16 == NULL) return false;
    if (remainder > UINT64_C(500000) ||
        (remainder == UINT64_C(500000) && (quotient & UINT64_C(1)) != 0u)) ++quotient;
    delta = negative ? -(int64_t)quotient : (int64_t)quotient;
    result = (int64_t)position_q16_16 + delta;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *predicted_q16_16 = (int32_t)result;
    return true;
}
