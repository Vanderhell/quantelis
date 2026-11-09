#ifndef PC_TIME_RATIO_INTERNAL_H
#define PC_TIME_RATIO_INTERNAL_H
#include <stdbool.h>
#include <stdint.h>
/* Private shared primitive. Computes floor(value*numerator/denominator) and
 * its remainder exactly. False on invalid pointers/denominator or quotient
 * overflow; outputs remain unchanged on failure. */
bool pc_time_ratio_mul_divmod_u64(uint64_t value, uint64_t numerator,
                                  uint64_t denominator, uint64_t *quotient,
                                  uint64_t *remainder);
#endif
