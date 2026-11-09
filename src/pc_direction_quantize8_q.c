#include "pc_direction_quantize8_q.h"
#include <stddef.h>

bool pc_direction_quantize8_q(uint32_t phase_turns_q0_32, uint8_t *out)
{
    if (out == NULL) return false;
    *out = (uint8_t)((phase_turns_q0_32 + UINT32_C(0x10000000)) >> 29);
    return true;
}
