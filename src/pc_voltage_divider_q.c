#include "pc_voltage_divider_q.h"
#include <stddef.h>
bool rm_voltage_divider_q(uint32_t input_q16, uint32_t resistance_top,
                          uint32_t resistance_bottom, uint32_t *output_q16)
{
    if (output_q16 == NULL) return false;
    uint64_t denominator = (uint64_t)resistance_top + resistance_bottom;
    if (denominator == 0u) return false;
    uint64_t numerator = (uint64_t)input_q16 * resistance_bottom;
    uint64_t quotient = numerator / denominator;
    uint64_t remainder = numerator % denominator;
    if (remainder > denominator / 2u ||
        ((denominator & 1u) == 0u && remainder == denominator / 2u &&
         (quotient & 1u) != 0u)) ++quotient;
    *output_q16 = (uint32_t)quotient;
    return true;
}
