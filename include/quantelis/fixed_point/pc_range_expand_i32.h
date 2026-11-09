#ifndef PRIMITIVECORE_RANGE_EXPAND_I32_H
#define PRIMITIVECORE_RANGE_EXPAND_I32_H
#include <stdbool.h>
#include <stdint.h>
/* Symmetrically expand a closed range by amount. Invalid bounds, overflow,
 * null outputs, or aliased output pointers fail without writes. */
bool rm_range_expand_i32(int32_t lower, int32_t upper, uint32_t amount,
                         int32_t *expanded_lower, int32_t *expanded_upper);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_range_expand_i32
#define pc_range_expand_i32 rm_range_expand_i32
#endif
#ifndef pc_range_expand_i32
#define pc_range_expand_i32 rm_range_expand_i32
#endif
#ifndef PC_PRIMITIVECORE_RANGE_EXPAND_I32_H
#define PC_PRIMITIVECORE_RANGE_EXPAND_I32_H PRIMITIVECORE_RANGE_EXPAND_I32_H
#endif

