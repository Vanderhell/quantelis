#ifndef RM_RAD_TO_DEG_Q_H
#define RM_RAD_TO_DEG_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Convert signed Q16.16 radians to signed Q16.16 degrees.
 * Returns false for null output or unrepresentable result and preserves output. */
bool rm_rad_to_deg_q(int32_t radians_q16, int32_t *degrees_q16);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_rad_to_deg_q
#define pc_rad_to_deg_q rm_rad_to_deg_q
#endif
#ifndef pc_rad_to_deg_q
#define pc_rad_to_deg_q rm_rad_to_deg_q
#endif
#ifndef PC_RAD_TO_DEG_Q_H
#define PC_RAD_TO_DEG_Q_H RM_RAD_TO_DEG_Q_H
#endif

