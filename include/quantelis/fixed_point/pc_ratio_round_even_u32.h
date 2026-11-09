#ifndef PRIMITIVECORE_RATIO_ROUND_EVEN_U32_H
#define PRIMITIVECORE_RATIO_ROUND_EVEN_U32_H
#include <stdbool.h>
#include <stdint.h>
/* Round numerator/denominator to nearest integer, ties to even. */
bool rm_ratio_round_even_u32(uint32_t numerator, uint32_t denominator,
                             uint32_t *rounded);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_ratio_round_even_u32
#define pc_ratio_round_even_u32 rm_ratio_round_even_u32
#endif
#ifndef pc_ratio_round_even_u32
#define pc_ratio_round_even_u32 rm_ratio_round_even_u32
#endif
#ifndef PC_PRIMITIVECORE_RATIO_ROUND_EVEN_U32_H
#define PC_PRIMITIVECORE_RATIO_ROUND_EVEN_U32_H PRIMITIVECORE_RATIO_ROUND_EVEN_U32_H
#endif

