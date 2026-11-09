#ifndef PC_DEG_TO_RAD_Q_H
#define PC_DEG_TO_RAD_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Convert signed Q16.16 degrees to signed Q16.16 radians.
 * Uses round-to-nearest, ties-to-even with a Q30 pi constant.
 * Returns false for a null output pointer and leaves output unchanged. */
bool pc_deg_to_rad_q(int32_t degrees_q16, int32_t *radians_q16);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_deg_to_rad_q
#define pc_deg_to_rad_q pc_deg_to_rad_q
#endif
#ifndef pc_deg_to_rad_q
#define pc_deg_to_rad_q pc_deg_to_rad_q
#endif
#ifndef PC_DEG_TO_RAD_Q_H
#define PC_DEG_TO_RAD_Q_H PC_DEG_TO_RAD_Q_H
#endif

