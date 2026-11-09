#ifndef PC_PC_DIRECTION_QUANTIZE16_Q_H
#define PC_PC_DIRECTION_QUANTIZE16_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Quantize unsigned Q0.32 turns to nearest of 16 equally spaced directions,
 * codes 0..15 counterclockwise from +X. Halfway values round CCW. */
bool pc_direction_quantize16_q(uint32_t phase_turns_q0_32, uint8_t *out);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_direction_quantize16_q
#define pc_direction_quantize16_q pc_direction_quantize16_q
#endif
#ifndef pc_direction_quantize16_q
#define pc_direction_quantize16_q pc_direction_quantize16_q
#endif
#ifndef PC_PC_PC_DIRECTION_QUANTIZE16_Q_H
#define PC_PC_PC_DIRECTION_QUANTIZE16_Q_H PC_PC_DIRECTION_QUANTIZE16_Q_H
#endif

