#ifndef PRIMITIVECORE_PC_ROLL_PITCH_FROM_ACCEL_Q_H
#define PRIMITIVECORE_PC_ROLL_PITCH_FROM_ACCEL_Q_H

#include <stdbool.h>
#include <stdint.h>

/* Estimate static-gravity tilt from a bounded Q1.30 accelerometer vector.
 * Roll = atan2(y,z); pitch = atan2(-x,sqrt(y*y+z*z)). Angles are signed
 * Q0.32 turns; the +half-turn roll boundary is represented as -half-turn.
 * The all-zero vector and out-of-range inputs fail without changing outputs. */
bool pc_roll_pitch_from_accel_q(const int32_t accel_q1_30[3],
                                int32_t *roll_turns_q0_32,
                                int32_t *pitch_turns_q0_32);

#endif
