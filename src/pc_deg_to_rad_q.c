#include "pc_deg_to_rad_q.h"
#include <limits.h>

bool rm_deg_to_rad_q(int32_t degrees_q16, int32_t *radians_q16)
{
    const uint64_t pi_q30 = UINT64_C(3373259427);
    const uint64_t denominator = UINT64_C(180) << 30;
    int64_t signed_input = degrees_q16;
    uint64_t magnitude = signed_input < 0 ? (uint64_t)(-signed_input) :
                                             (uint64_t)signed_input;
    uint64_t numerator;
    uint64_t quotient;
    uint64_t remainder;
    int64_t signed_result;

    if (radians_q16 == 0) {
        return false;
    }
    numerator = magnitude * pi_q30;
    quotient = numerator / denominator;
    remainder = numerator % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    signed_result = (int64_t)quotient;
    if (degrees_q16 < 0) {
        signed_result = -signed_result;
    }
    if (signed_result < INT32_MIN || signed_result > INT32_MAX) {
        return false;
    }
    *radians_q16 = (int32_t)signed_result;
    return true;
}
