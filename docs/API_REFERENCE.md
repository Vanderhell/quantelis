# Quantelis API reference

Complete public-header inventory generated from the current source tree. Headers remain authoritative.

## include/quantelis/fixed_point/pc_bearing2_q.h

Public API: pc_bearing2_q

Contract: CORDIC estimate of bearing from an int32 origin to target as unsigned Q0.32 turns CCW from +X. Equal points return zero. Coordinates need not share a specific Q scale. Differential tests observed <= 16 phase-code error; this empirical limit is not a formal global bound.

Header path: include/quantelis/fixed_point/pc_bearing2_q.h

## include/quantelis/fixed_point/pc_bilinear_interp_q.h

Public API: pc_bilinear_interp_q

Contract: Single-round bilinear interpolation of signed-Q15 corners. fx/fy are unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even.

Header path: include/quantelis/fixed_point/pc_bilinear_interp_q.h

## include/quantelis/fixed_point/pc_constant_velocity_predict_q.h

Public API: pc_constant_velocity_predict_q

Contract: Predict scalar Q16.16 position after dt_us at constant velocity in Q16.16 units/second. Delta is rounded nearest-even. Returns false if the result is outside int32; output is unchanged on failure. dt_us may be any uint32 value.

Header path: include/quantelis/fixed_point/pc_constant_velocity_predict_q.h

## include/quantelis/fixed_point/pc_decay_factor_from_halflife_q.h

Public API: pc_decay_factor_from_halflife_q

Contract: Compute the per-step retention factor 2^(-1/half_life_steps) in unsigned Q0.16, rounded to nearest-even. The result ranges from 32768 through 65536; 65536 represents exact unity. half_life_steps must be positive. On zero half-life or null output, return false without modifying the output.

Header path: include/quantelis/fixed_point/pc_decay_factor_from_halflife_q.h

## include/quantelis/fixed_point/pc_decay_factor_from_tau_q.h

Public API: pc_decay_factor_from_tau_q

Contract: Return exp(-1/tau_steps) as nearest-even unsigned Q0.16 retention. tau_steps must be positive; 65536 represents unity.

Header path: include/quantelis/fixed_point/pc_decay_factor_from_tau_q.h

## include/quantelis/fixed_point/pc_deg_to_rad_q.h

Public API: pc_deg_to_rad_q

Contract: Convert signed Q16.16 degrees to signed Q16.16 radians. Uses round-to-nearest, ties-to-even with a Q30 pi constant. Returns false for a null output pointer and leaves output unchanged.

Header path: include/quantelis/fixed_point/pc_deg_to_rad_q.h

## include/quantelis/fixed_point/pc_direction_quantize16_q.h

Public API: pc_direction_quantize16_q

Contract: Quantize unsigned Q0.32 turns to nearest of 16 equally spaced directions, codes 0..15 counterclockwise from +X. Halfway values round CCW.

Header path: include/quantelis/fixed_point/pc_direction_quantize16_q.h

## include/quantelis/fixed_point/pc_direction_quantize8_q.h

Public API: pc_direction_quantize8_q

Contract: Quantize unsigned Q0.32 turns to nearest of 8 compass sectors (E through SE counterclockwise), codes 0..7. Exact halfway values round CCW.

Header path: include/quantelis/fixed_point/pc_direction_quantize8_q.h

## include/quantelis/fixed_point/pc_one_pole_smoother_q.h

Public API: pc_one_pole_smoother_q

Contract: Update caller-owned state toward input by Q16 alpha: state += round-nearest-even((input-state)*alpha_q16/65536). alpha_q16 must be in [0,65536]. Invalid input leaves state unchanged. Per-sample coefficient: effective bandwidth depends on sample cadence.

Header path: include/quantelis/fixed_point/pc_one_pole_smoother_q.h

## include/quantelis/fixed_point/pc_packet_loss_rate_q.h

Public API: pc_packet_loss_rate_q

Contract: Compute round-nearest-even((lost_packets * 2^fractional_bits) / sent_packets). Requires sent_packets > 0, lost_packets <= sent_packets, fractional_bits <= 31, and non-null rate_q. Failure leaves *rate_q unchanged.

Header path: include/quantelis/fixed_point/pc_packet_loss_rate_q.h

## include/quantelis/fixed_point/pc_q_div_round_even.h

Public API: pc_q_div_round_even

Contract: Compute (a*2^f)/b to int32, nearest-even; f=0..31 and b!=0.

Header path: include/quantelis/fixed_point/pc_q_div_round_even.h

## include/quantelis/fixed_point/pc_q_hypot2.h

Public API: pc_q_hypot2

Contract: Nearest-even Euclidean norm of same-scale signed Q raw values. False on null output or int32 result overflow; failure preserves *out.

Header path: include/quantelis/fixed_point/pc_q_hypot2.h

## include/quantelis/fixed_point/pc_q_hypot3.h

Public API: pc_q_hypot3

Contract: Nearest-even Euclidean norm of three same-scale signed Q raw values. False on null output or int32 overflow; failure preserves *out.

Header path: include/quantelis/fixed_point/pc_q_hypot3.h

## include/quantelis/fixed_point/pc_q_mul_add_sat.h

Public API: pc_q_mul_add_sat

Contract: sat32(round_even(a*b/2^f)+c), f=0..31.

Header path: include/quantelis/fixed_point/pc_q_mul_add_sat.h

## include/quantelis/fixed_point/pc_q_mul_round_even.h

Public API: pc_q_mul_round_even

Contract: Multiply two signed int32 Q values with f fractional bits, nearest-even.

Header path: include/quantelis/fixed_point/pc_q_mul_round_even.h

## include/quantelis/fixed_point/pc_q_to_i32_round.h

Public API: pc_q_to_i32_round

Contract: Convert signed int32 Q raw value to integer, nearest-even; f is 0..31.

Header path: include/quantelis/fixed_point/pc_q_to_i32_round.h

## include/quantelis/fixed_point/pc_q64_clamp.h

Public API: pc_q64_clamp

Contract: Clamp a same-scale signed Q value to inclusive [lower, upper]. Invalid bounds or null result return false and leave *result unchanged.

Header path: include/quantelis/fixed_point/pc_q64_clamp.h

## include/quantelis/fixed_point/pc_q64_lerp.h

Public API: pc_q64_lerp

Contract: Convex same-scale signed int64 interpolation at numerator/denominator. Requires denominator>0 and numerator<=denominator. The exact final value rounds nearest-even. Invalid inputs fail without modifying *result.

Header path: include/quantelis/fixed_point/pc_q64_lerp.h

## include/quantelis/fixed_point/pc_rad_to_deg_q.h

Public API: pc_rad_to_deg_q

Contract: Convert signed Q16.16 radians to signed Q16.16 degrees. Returns false for null output or unrepresentable result and preserves output.

Header path: include/quantelis/fixed_point/pc_rad_to_deg_q.h

## include/quantelis/fixed_point/pc_radps_to_rpm_q.h

Public API: pc_radps_to_rpm_q

Contract: Convert signed Q16.16 radians per second to signed Q16.16 RPM. Uses nearest-even rounding with a Q30 pi constant. False on null output or unrepresentable result; output is preserved.

Header path: include/quantelis/fixed_point/pc_radps_to_rpm_q.h

## include/quantelis/fixed_point/pc_range_expand_i32.h

Public API: pc_range_expand_i32

Contract: Symmetrically expand a closed range by amount. Invalid bounds, overflow, null outputs, or aliased output pointers fail without writes.

Header path: include/quantelis/fixed_point/pc_range_expand_i32.h

## include/quantelis/fixed_point/pc_ratio_round_even_u32.h

Public API: pc_ratio_round_even_u32

Contract: Round numerator/denominator to nearest integer, ties to even.

Header path: include/quantelis/fixed_point/pc_ratio_round_even_u32.h

## include/quantelis/fixed_point/pc_roll_pitch_from_accel_q.h

Public API: pc_roll_pitch_from_accel_q

Contract: Estimate static-gravity tilt from a bounded Q1.30 accelerometer vector. Roll = atan2(y,z); pitch = atan2(-x,sqrt(y*y+z*z)). Angles are signed Q0.32 turns; the +half-turn roll boundary is represented as -half-turn. The all-zero vector and out-of-range inputs fail without changing outputs.

Header path: include/quantelis/fixed_point/pc_roll_pitch_from_accel_q.h

## include/quantelis/fixed_point/pc_rpm_to_radps_q.h

Public API: pc_rpm_to_radps_q

Contract: Convert signed Q16.16 RPM to signed Q16.16 radians per second. Uses nearest-even rounding with a Q30 pi constant; null output fails.

Header path: include/quantelis/fixed_point/pc_rpm_to_radps_q.h

## include/quantelis/fixed_point/pc_strain_ratio_q.h

Public API: pc_strain_ratio_q

Contract: Convert a signed resistance change to strain using GF = (deltaR/R)/strain. Inputs: delta resistance in milliohms, nominal resistance in ohms, gauge factor UQ16.16. Output is signed microstrain, nearest-even.

Header path: include/quantelis/fixed_point/pc_strain_ratio_q.h

## include/quantelis/fixed_point/pc_table_inverse_index_q.h

Public API: pc_table_inverse_index_q

Contract: Map a sample through a strictly increasing implicit-index table to a clamped Q16.16 fractional index. Count is 2..32768. Interior fractions round to nearest, ties-to-even. The table's strict ordering is a precondition.

Header path: include/quantelis/fixed_point/pc_table_inverse_index_q.h

## include/quantelis/fixed_point/pc_time_ratio_internal.h

Public API: pc_time_ratio_mul_divmod_u64

Contract: Private shared primitive. Computes floor(value*numerator/denominator) and its remainder exactly. False on invalid pointers/denominator or quotient overflow; outputs remain unchanged on failure.

Header path: include/quantelis/fixed_point/pc_time_ratio_internal.h

## include/quantelis/fixed_point/pc_time_to_target_q.h

Public API: pc_time_to_target_q

Contract: Return ceil time to target in microseconds for scalar Q16.16 position and constant velocity in Q16.16 units/second. Equal position returns 0 even at zero speed. A nonzero distance with zero/opposite velocity fails atomically.

Header path: include/quantelis/fixed_point/pc_time_to_target_q.h

## include/quantelis/fixed_point/pc_trilinear_interp_q.h

Public API: pc_trilinear_interp_q

Contract: Single-round trilinear interpolation of signed-Q15 corners. fx/fy/fz are unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even.

Header path: include/quantelis/fixed_point/pc_trilinear_interp_q.h

## include/quantelis/fixed_point/pc_voltage_divider_q.h

Public API: pc_voltage_divider_q

Contract: The public header contains the authoritative signature and input/output contract.

Header path: include/quantelis/fixed_point/pc_voltage_divider_q.h
