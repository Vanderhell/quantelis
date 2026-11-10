#ifndef PC_PC_TIME_TO_TARGET_Q_H
#define PC_PC_TIME_TO_TARGET_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Return ceil time to target in microseconds for scalar Q16.16 position and
 * constant velocity in Q16.16 units/second. Equal position returns 0 even at
 * zero speed. A nonzero distance with zero/opposite velocity fails atomically. */
bool pc_time_to_target_q(int32_t position_q16_16, int32_t target_q16_16,
                         int32_t velocity_q16_16_per_s,
                         uint64_t *time_to_target_us);
#endif
