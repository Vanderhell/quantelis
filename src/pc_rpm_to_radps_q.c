#include "pc_rpm_to_radps_q.h"
#include <limits.h>

bool pc_rpm_to_radps_q(int32_t rpm_q16, int32_t *radps_q16)
{
    const uint64_t pi_q30 = UINT64_C(3373259427);
    const uint64_t denominator = UINT64_C(30) << 30;
    int64_t signed_input = rpm_q16;
    uint64_t magnitude = signed_input < 0 ? (uint64_t)(-signed_input) :
                                             (uint64_t)signed_input;
    uint64_t numerator;
    uint64_t quotient;
    uint64_t remainder;
    int64_t result;

    if (radps_q16 == 0) return false;
    numerator = magnitude * pi_q30;
    quotient = numerator / denominator;
    remainder = numerator % denominator;
    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    result = (int64_t)quotient;
    if (rpm_q16 < 0) result = -result;
    if (result < INT32_MIN || result > INT32_MAX) return false;
    *radps_q16 = (int32_t)result;
    return true;
}
