#ifndef PC_Q_HYPOT3_H
#define PC_Q_HYPOT3_H
#include <stdbool.h>
#include <stdint.h>
/* Nearest-even Euclidean norm of three same-scale signed Q raw values.
 * False on null output or int32 overflow; failure preserves *out. */
bool pc_q_hypot3(int32_t x, int32_t y, int32_t z, int32_t *out);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_q_hypot3
#define pc_q_hypot3 pc_q_hypot3
#endif
#ifndef pc_q_hypot3
#define pc_q_hypot3 pc_q_hypot3
#endif
#ifndef PC_PC_Q_HYPOT3_H
#define PC_PC_Q_HYPOT3_H PC_Q_HYPOT3_H
#endif

