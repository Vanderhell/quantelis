#ifndef PC_RADPS_TO_RPM_Q_H
#define PC_RADPS_TO_RPM_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Convert signed Q16.16 radians per second to signed Q16.16 RPM.
 * Uses nearest-even rounding with a Q30 pi constant.
 * False on null output or unrepresentable result; output is preserved. */
bool pc_radps_to_rpm_q(int32_t radps_q16, int32_t *rpm_q16);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_radps_to_rpm_q
#define pc_radps_to_rpm_q pc_radps_to_rpm_q
#endif
#ifndef pc_radps_to_rpm_q
#define pc_radps_to_rpm_q pc_radps_to_rpm_q
#endif
#ifndef PC_RADPS_TO_RPM_Q_H
#define PC_RADPS_TO_RPM_Q_H PC_RADPS_TO_RPM_Q_H
#endif

