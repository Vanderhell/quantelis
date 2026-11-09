#include "pc_rad_to_deg_q.h"
#include <limits.h>

bool rm_rad_to_deg_q(int32_t radians_q16, int32_t *degrees_q16)
{
    const uint64_t pi_q30 = UINT64_C(3373259427);
    const uint64_t multiplier = UINT64_C(180) << 30;
    const uint64_t max_input = ((uint64_t)INT32_MAX * pi_q30) / multiplier;
    int64_t signed_input = radians_q16;
    uint64_t magnitude = signed_input < 0 ? (uint64_t)(-signed_input) :
                                             (uint64_t)signed_input;
    uint64_t numerator;
    uint64_t quotient;
    uint64_t remainder;
    int64_t signed_result;

    if (degrees_q16 == 0 || magnitude > max_input) {
        return false;
    }
    numerator = magnitude * multiplier;
    quotient = numerator / pi_q30;
    remainder = numerator % pi_q30;
    if (remainder > pi_q30 - remainder ||
        (remainder == pi_q30 - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    signed_result = (int64_t)quotient;
    if (radians_q16 < 0) {
        signed_result = -signed_result;
    }
    if (signed_result < INT32_MIN || signed_result > INT32_MAX) {
        return false;
    }
    *degrees_q16 = (int32_t)signed_result;
    return true;
}
