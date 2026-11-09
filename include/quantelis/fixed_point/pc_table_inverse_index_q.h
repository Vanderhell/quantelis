#ifndef RM_TABLE_INVERSE_INDEX_Q_H
#define RM_TABLE_INVERSE_INDEX_Q_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Map a sample through a strictly increasing implicit-index table to a
 * clamped Q16.16 fractional index. Count is 2..32768. Interior fractions
 * round to nearest, ties-to-even. The table's strict ordering is a precondition. */
bool rm_table_inverse_index_q(const int32_t *values, size_t count,
                              int32_t sample, int32_t *index_q16_16);

#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_table_inverse_index_q
#define pc_table_inverse_index_q rm_table_inverse_index_q
#endif
#ifndef pc_table_inverse_index_q
#define pc_table_inverse_index_q rm_table_inverse_index_q
#endif
#ifndef PC_TABLE_INVERSE_INDEX_Q_H
#define PC_TABLE_INVERSE_INDEX_Q_H RM_TABLE_INVERSE_INDEX_Q_H
#endif

