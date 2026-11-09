#include "pc_table_inverse_index_q.h"

bool rm_table_inverse_index_q(const int32_t *values, size_t count,
                              int32_t sample, int32_t *index_q16_16)
{
    size_t lo, hi;
    uint32_t offset, gap;
    uint64_t numerator, q, rem;
    uint32_t result;
    if (values == NULL || count < 2u || count > 32768u || index_q16_16 == NULL)
        return false;
    if (sample <= values[0]) {
        *index_q16_16 = 0;
        return true;
    }
    if (sample >= values[count - 1u]) {
        *index_q16_16 = (int32_t)((uint32_t)(count - 1u) << 16);
        return true;
    }
    lo = 0u;
    hi = count;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2u;
        if (values[mid] < sample) lo = mid + 1u;
        else hi = mid;
    }
    if (values[lo] == sample) {
        *index_q16_16 = (int32_t)((uint32_t)lo << 16);
        return true;
    }
    offset = (uint32_t)sample - (uint32_t)values[lo - 1u];
    gap = (uint32_t)values[lo] - (uint32_t)values[lo - 1u];
    numerator = (uint64_t)offset << 16;
    q = numerator / gap;
    rem = numerator % gap;
    if (rem > (uint64_t)gap - rem ||
        (rem == (uint64_t)gap - rem && (q & 1u) != 0u)) ++q;
    result = ((uint32_t)(lo - 1u) << 16) + (uint32_t)q;
    *index_q16_16 = (int32_t)result;
    return true;
}
