#include "pc_radps_to_rpm_q.h"
#include <limits.h>

bool rm_radps_to_rpm_q(int32_t radps_q16, int32_t *rpm_q16)
{
    const uint64_t pi_q30 = UINT64_C(3373259427);
    const uint64_t multiplier = UINT64_C(30) << 30;
    const uint64_t max_input = ((uint64_t)INT32_MAX * pi_q30) / multiplier;
    int64_t signed_input = radps_q16;
    uint64_t magnitude = signed_input < 0 ? (uint64_t)(-signed_input) :
                                             (uint64_t)signed_input;
    uint64_t numerator;
    uint64_t quotient;
    uint64_t remainder;
    int64_t result;

    if (rpm_q16 == 0 || magnitude > max_input) return false;
    numerator = magnitude * multiplier;
    quotient = numerator / pi_q30;
    remainder = numerator % pi_q30;
    if (remainder > pi_q30 - remainder ||
        (remainder == pi_q30 - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    result = (int64_t)quotient;
    if (radps_q16 < 0) result = -result;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *rpm_q16 = (int32_t)result;
    return true;
}
