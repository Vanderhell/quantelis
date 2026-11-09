#ifndef PC_PC_Q64_CLAMP_H
#define PC_PC_Q64_CLAMP_H
#include <stdbool.h>
#include <stdint.h>
/* Clamp a same-scale signed Q value to inclusive [lower, upper]. Invalid
 * bounds or null result return false and leave *result unchanged. */
bool pc_q64_clamp(int64_t value, int64_t lower, int64_t upper,
                  int64_t *result);
#endif
