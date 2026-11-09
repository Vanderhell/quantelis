#include "pc_one_pole_smoother_q.h"
#include <stddef.h>
#include <stdint.h>
bool rm_one_pole_smoother_q(int32_t input, uint32_t alpha_q16, int32_t *state)
{
    int64_t delta, product, adjustment, next;
    uint64_t magnitude, quotient, remainder;
    if (state == NULL || alpha_q16 > 65536u) return false;
    delta = (int64_t)input - (int64_t)*state;
    product = delta * (int64_t)alpha_q16;
    magnitude = product < 0 ? (uint64_t)(-product) : (uint64_t)product;
    quotient = magnitude / 65536u;
    remainder = magnitude % 65536u;
    if (remainder > 32768u ||
        (remainder == 32768u && (quotient & 1u) != 0u)) ++quotient;
    adjustment = product < 0 ? -(int64_t)quotient : (int64_t)quotient;
    next = (int64_t)*state + adjustment;
    *state = (int32_t)next;
    return true;
}
