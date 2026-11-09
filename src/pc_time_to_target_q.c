#include "pc_time_to_target_q.h"
#include <stddef.h>
#include <stdint.h>
bool pc_time_to_target_q(int32_t position_q16_16, int32_t target_q16_16,
                         int32_t velocity_q16_16_per_s,
                         uint64_t *time_to_target_us)
{
    const int64_t difference = (int64_t)target_q16_16 - (int64_t)position_q16_16;
    uint64_t distance, speed, numerator, quotient;
    if (time_to_target_us == NULL) return false;
    if (difference == 0) { *time_to_target_us = 0u; return true; }
    if (velocity_q16_16_per_s == 0 ||
        ((difference < 0) != (velocity_q16_16_per_s < 0))) return false;
    distance = difference < 0 ? (uint64_t)(-difference) : (uint64_t)difference;
    speed = velocity_q16_16_per_s < 0 ? (uint64_t)(-(int64_t)velocity_q16_16_per_s) : (uint64_t)velocity_q16_16_per_s;
    numerator = distance * UINT64_C(1000000);
    quotient = numerator / speed;
    if (numerator % speed != 0u) ++quotient;
    *time_to_target_us = quotient;
    return true;
}
