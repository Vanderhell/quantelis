#include "pc_direction_quantize16_q.h"
#include <stddef.h>

bool pc_direction_quantize16_q(uint32_t phase_turns_q0_32, uint8_t *out)
{
    if (out == NULL) return false;
    *out = (uint8_t)((phase_turns_q0_32 + UINT32_C(0x08000000)) >> 28);
    return true;
}
