#ifndef RM_RPM_TO_RADPS_Q_H
#define RM_RPM_TO_RADPS_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Convert signed Q16.16 RPM to signed Q16.16 radians per second.
 * Uses nearest-even rounding with a Q30 pi constant; null output fails. */
bool rm_rpm_to_radps_q(int32_t rpm_q16, int32_t *radps_q16);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_rpm_to_radps_q
#define pc_rpm_to_radps_q rm_rpm_to_radps_q
#endif
#ifndef pc_rpm_to_radps_q
#define pc_rpm_to_radps_q rm_rpm_to_radps_q
#endif
#ifndef PC_RPM_TO_RADPS_Q_H
#define PC_RPM_TO_RADPS_Q_H RM_RPM_TO_RADPS_Q_H
#endif

