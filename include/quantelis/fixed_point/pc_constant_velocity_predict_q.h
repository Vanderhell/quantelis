#ifndef PRIMITIVECORE_PC_CONSTANT_VELOCITY_PREDICT_Q_H
#define PRIMITIVECORE_PC_CONSTANT_VELOCITY_PREDICT_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Predict scalar Q16.16 position after dt_us at constant velocity in
 * Q16.16 units/second. Delta is rounded nearest-even. Returns false if the
 * result is outside int32; output is unchanged on failure. dt_us may be any
 * uint32 value. */
bool pc_constant_velocity_predict_q(int32_t position_q16_16,
                                    int32_t velocity_q16_16_per_s,
                                    uint32_t dt_us,
                                    int32_t *predicted_q16_16);
#endif