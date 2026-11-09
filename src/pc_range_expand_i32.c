#include "pc_range_expand_i32.h"
#include <limits.h>
#include <stddef.h>

bool pc_range_expand_i32(int32_t lower, int32_t upper, uint32_t amount,
                         int32_t *expanded_lower, int32_t *expanded_upper)
{
    int64_t new_lower, new_upper;
    if (expanded_lower == NULL || expanded_upper == NULL ||
        expanded_lower == expanded_upper || lower > upper) return false;
    new_lower = (int64_t)lower - amount;
    new_upper = (int64_t)upper + amount;
    if (new_lower < INT32_MIN || new_upper > INT32_MAX) return false;
    *expanded_lower = (int32_t)new_lower;
    *expanded_upper = (int32_t)new_upper;
    return true;
}
