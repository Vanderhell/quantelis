#include "pc_q64_clamp.h"
#include <stddef.h>

bool pc_q64_clamp(int64_t value, int64_t lower, int64_t upper,
                  int64_t *result)
{
    int64_t clamped;
    if (result == NULL || lower > upper) return false;
    clamped = value < lower ? lower : (value > upper ? upper : value);
    *result = clamped;
    return true;
}
