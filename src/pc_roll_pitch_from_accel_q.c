#include "pc_roll_pitch_from_accel_q.h"
#include "pc_bearing2_q.h"
#include "pc_q_hypot3.h"

#include <stddef.h>

#define PC_ONE_Q1_30 INT32_C(1073741824)

static int32_t pc_signed_phase_q0_32(uint32_t phase)
{
    return phase <= INT32_MAX ? (int32_t)phase
        : (int32_t)((int64_t)phase - INT64_C(4294967296));
}

bool pc_roll_pitch_from_accel_q(const int32_t accel_q1_30[3],
                                int32_t *roll_turns_q0_32,
                                int32_t *pitch_turns_q0_32)
{
    int32_t scaled[3], yz_magnitude_q1_30;
    uint32_t roll_phase_q0_32, pitch_phase_q0_32;
    int32_t roll, pitch;
    uint64_t largest = 0u;
    unsigned scale_bits = 0u;

    if (accel_q1_30 == NULL || roll_turns_q0_32 == NULL ||
        pitch_turns_q0_32 == NULL) return false;

    for (unsigned i = 0u; i < 3u; ++i) {
        uint64_t magnitude;
        if (accel_q1_30[i] < -PC_ONE_Q1_30 ||
            accel_q1_30[i] > PC_ONE_Q1_30) return false;
        magnitude = accel_q1_30[i] < 0
            ? (uint64_t)(-(int64_t)accel_q1_30[i])
            : (uint64_t)accel_q1_30[i];
        if (magnitude > largest) largest = magnitude;
    }
    if (largest == 0u) return false;

    while (largest < UINT64_C(536870912)) {
        largest *= 2u;
        ++scale_bits;
    }
    for (unsigned i = 0u; i < 3u; ++i)
        scaled[i] = (int32_t)((int64_t)accel_q1_30[i] *
                              (INT64_C(1) << scale_bits));

    if (scaled[1] == 0 && scaled[2] == 0) {
        roll = 0;
        pitch = scaled[0] > 0 ? -INT32_C(1073741824)
                               : INT32_C(1073741824);
    } else {
        if (!pc_bearing2_q(0, 0, scaled[2], scaled[1], &roll_phase_q0_32) ||
            !pc_q_hypot3(0, scaled[1], scaled[2], &yz_magnitude_q1_30) ||
            !pc_bearing2_q(0, 0, yz_magnitude_q1_30, -scaled[0],
                           &pitch_phase_q0_32)) return false;
        roll = pc_signed_phase_q0_32(roll_phase_q0_32);
        pitch = pc_signed_phase_q0_32(pitch_phase_q0_32);
    }

    *roll_turns_q0_32 = roll;
    *pitch_turns_q0_32 = pitch;
    return true;
}
