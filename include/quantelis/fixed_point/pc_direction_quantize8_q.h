#ifndef PRIMITIVECORE_RM_DIRECTION_QUANTIZE8_Q_H
#define PRIMITIVECORE_RM_DIRECTION_QUANTIZE8_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Quantize unsigned Q0.32 turns to nearest of 8 compass sectors (E through
 * SE counterclockwise), codes 0..7. Exact halfway values round CCW. */
bool rm_direction_quantize8_q(uint32_t phase_turns_q0_32, uint8_t *out);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_direction_quantize8_q
#define pc_direction_quantize8_q rm_direction_quantize8_q
#endif
#ifndef pc_direction_quantize8_q
#define pc_direction_quantize8_q rm_direction_quantize8_q
#endif
#ifndef PC_PRIMITIVECORE_RM_DIRECTION_QUANTIZE8_Q_H
#define PC_PRIMITIVECORE_RM_DIRECTION_QUANTIZE8_Q_H PRIMITIVECORE_RM_DIRECTION_QUANTIZE8_Q_H
#endif

