#include "pc_q64_lerp.h"
#include "pc_time_ratio_internal.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

static bool apply_offset(int64_t base, uint64_t offset, bool increasing,
                         int64_t *value)
{
    if (increasing) {
        if (base >= 0) {
            const uint64_t room = (uint64_t)(INT64_MAX - base);
            if (offset > room) return false;
            *value = base + (int64_t)offset;
        } else {
            const uint64_t magnitude = UINT64_C(0) - (uint64_t)base;
            if (offset < magnitude) {
                const uint64_t negative = magnitude - offset;
                *value = negative == (UINT64_C(1) << 63u)
                             ? INT64_MIN : -(int64_t)negative;
            } else {
                const uint64_t positive = offset - magnitude;
                if (positive > (uint64_t)INT64_MAX) return false;
                *value = (int64_t)positive;
            }
        }
    } else if (base >= 0) {
        if (offset <= (uint64_t)base) {
            *value = base - (int64_t)offset;
        } else {
            const uint64_t negative = offset - (uint64_t)base;
            if (negative > (UINT64_C(1) << 63u)) return false;
            *value = negative == (UINT64_C(1) << 63u)
                         ? INT64_MIN : -(int64_t)negative;
        }
    } else {
        const uint64_t magnitude = UINT64_C(0) - (uint64_t)base;
        if (offset > (UINT64_C(1) << 63u) - magnitude) return false;
        {
            const uint64_t negative = magnitude + offset;
            *value = negative == (UINT64_C(1) << 63u)
                         ? INT64_MIN : -(int64_t)negative;
        }
    }
    return true;
}

bool pc_q64_lerp(int64_t a, int64_t b, uint64_t numerator,
                 uint64_t denominator, int64_t *result)
{
    const bool increasing = b >= a;
    const uint64_t delta = increasing ? (uint64_t)b - (uint64_t)a
                                      : (uint64_t)a - (uint64_t)b;
    uint64_t offset;
    uint64_t remainder;
    int64_t base;

    if (result == NULL || denominator == 0u || numerator > denominator) return false;
    if (a == b || numerator == 0u) {
        *result = a;
        return true;
    }
    if (numerator == denominator) {
        *result = b;
        return true;
    }
    if (!pc_time_ratio_mul_divmod_u64(delta, numerator, denominator,
                                      &offset, &remainder) ||
        !apply_offset(a, offset, increasing, &base)) return false;

    if (remainder > denominator - remainder ||
        (remainder == denominator - remainder && base % 2 != 0)) {
        if (increasing) {
            if (base == INT64_MAX) return false;
            ++base;
        } else {
            if (base == INT64_MIN) return false;
            --base;
        }
    }
    *result = base;
    return true;
}
