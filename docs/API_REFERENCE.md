# Quantelis API reference

This reference explains every public header in the Quantelis product. It is generated from the current headers and test sources; the header remains authoritative when a detail conflicts.

## Reading the entries
Each entry states the public symbol, implementation unit, contract, edge/failure behavior and a call extracted from the validating test source. The examples are evidence-oriented; adapt buffer ownership and numeric units to the application.

## include/quantelis/fixed_point/pc_bearing2_q.h

**Public symbol:** pc_bearing2_q

**Implementation unit:** src/pc_bearing2_q.c

**Purpose and contract:** CORDIC estimate of bearing from an int32 origin to target as unsigned Q0.32 turns CCW from +X. Equal points return zero. Coordinates need not share a specific Q scale. The seeded 100,000-case and boundary differential corpus observed maximum error 6 phase codes; the test permits 32, and this is not a formal global bound.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_bilinear_interp_q.h

**Public symbol:** pc_bilinear_interp_q

**Implementation unit:** src/pc_bilinear_interp_q.c

**Purpose and contract:** Single-round bilinear interpolation of signed-Q15 corners. fx/fy are unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even.

**Direct validation:** [`test_001_bilinear_interp_q.c`](tests/test_001_bilinear_interp_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_constant_velocity_predict_q.h

**Public symbol:** pc_constant_velocity_predict_q

**Implementation unit:** src/pc_constant_velocity_predict_q.c

**Purpose and contract:** Predict scalar Q16.16 position after dt_us at constant velocity in Q16.16 units/second. Delta is rounded nearest-even. Returns false if the result is outside int32; output is unchanged on failure. dt_us may be any uint32 value.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_decay_factor_from_halflife_q.h

**Public symbol:** pc_decay_factor_from_halflife_q

**Implementation unit:** src/pc_decay_factor_from_halflife_q.c

**Purpose and contract:** Compute the per-step retention factor 2^(-1/half_life_steps) in unsigned Q0.16, rounded to nearest-even. The result ranges from 32768 through 65536; 65536 represents exact unity. half_life_steps must be positive. On zero half-life or null output, return false without modifying the output.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_decay_factor_from_tau_q.h

**Public symbol:** pc_decay_factor_from_tau_q

**Implementation unit:** src/pc_decay_factor_from_tau_q.c

**Purpose and contract:** Return exp(-1/tau_steps) as nearest-even unsigned Q0.16 retention. tau_steps must be positive; 65536 represents unity.

**Direct validation:** [`test_002_decay_factor_from_tau_q.c`](tests/test_002_decay_factor_from_tau_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_deg_to_rad_q.h

**Public symbol:** pc_deg_to_rad_q

**Implementation unit:** src/pc_deg_to_rad_q.c

**Purpose and contract:** Convert signed Q16.16 degrees to signed Q16.16 radians. Uses round-to-nearest, ties-to-even with a Q30 pi constant. Returns false for a null output pointer and leaves output unchanged.

**Direct validation:** [`test_003_deg_to_rad_q.c`](tests/test_003_deg_to_rad_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_direction_quantize16_q.h

**Public symbol:** pc_direction_quantize16_q

**Implementation unit:** src/pc_direction_quantize16_q.c

**Purpose and contract:** Quantize unsigned Q0.32 turns to nearest of 16 equally spaced directions, codes 0..15 counterclockwise from +X. Halfway values round CCW.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_direction_quantize8_q.h

**Public symbol:** pc_direction_quantize8_q

**Implementation unit:** src/pc_direction_quantize8_q.c

**Purpose and contract:** Quantize unsigned Q0.32 turns to nearest of 8 compass sectors (E through SE counterclockwise), codes 0..7. Exact halfway values round CCW.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_one_pole_smoother_q.h

**Public symbol:** pc_one_pole_smoother_q

**Implementation unit:** src/pc_one_pole_smoother_q.c

**Purpose and contract:** Update caller-owned state toward input by Q16 alpha: state += round-nearest-even((input-state)*alpha_q16/65536). alpha_q16 must be in [0,65536]. Invalid input leaves state unchanged. Per-sample coefficient: effective bandwidth depends on sample cadence.

**Direct validation:** [`test_004_one_pole_smoother_q.c`](tests/test_004_one_pole_smoother_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_packet_loss_rate_q.h

**Public symbol:** pc_packet_loss_rate_q

**Implementation unit:** src/pc_packet_loss_rate_q.c

**Purpose and contract:** Compute round-nearest-even((lost_packets * 2^fractional_bits) / sent_packets). Requires sent_packets > 0, lost_packets <= sent_packets, fractional_bits <= 31, and non-null rate_q. Failure leaves *rate_q unchanged.

**Direct validation:** [`test_005_packet_loss_rate_q.c`](tests/test_005_packet_loss_rate_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q_div_round_even.h

**Public symbol:** pc_q_div_round_even

**Implementation unit:** src/pc_q_div_round_even.c

**Purpose and contract:** Compute (a*2^f)/b to int32, nearest-even; f=0..31 and b!=0.

**Direct validation:** [`test_005_packet_loss_rate_q.c`](tests/test_005_packet_loss_rate_q.c), [`test_006_q_div_round_even.c`](tests/test_006_q_div_round_even.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q_hypot2.h

**Public symbol:** pc_q_hypot2

**Implementation unit:** src/pc_q_hypot2.c

**Purpose and contract:** Nearest-even Euclidean norm of same-scale signed Q raw values. False on null output or int32 result overflow; failure preserves *out.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q_hypot3.h

**Public symbol:** pc_q_hypot3

**Implementation unit:** src/pc_q_hypot3.c

**Purpose and contract:** Nearest-even Euclidean norm of three same-scale signed Q raw values. False on null output or int32 overflow; failure preserves *out.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q_mul_add_sat.h

**Public symbol:** pc_q_mul_add_sat

**Implementation unit:** src/pc_q_mul_add_sat.c

**Purpose and contract:** sat32(round_even(a*b/2^f)+c), f=0..31.

**Direct validation:** [`test_007_q_mul_add_sat.c`](tests/test_007_q_mul_add_sat.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q_mul_round_even.h

**Public symbol:** pc_q_mul_round_even

**Implementation unit:** src/pc_q_mul_round_even.c

**Purpose and contract:** Multiply two signed int32 Q values with f fractional bits, nearest-even.

**Direct validation:** [`test_008_q_mul_round_even.c`](tests/test_008_q_mul_round_even.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q_to_i32_round.h

**Public symbol:** pc_q_to_i32_round

**Implementation unit:** src/pc_q_to_i32_round.c

**Purpose and contract:** Convert signed int32 Q raw value to integer, nearest-even; f is 0..31.

**Direct validation:** [`test_009_q_to_i32_round.c`](tests/test_009_q_to_i32_round.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q64_clamp.h

**Public symbol:** pc_q64_clamp

**Implementation unit:** src/pc_q64_clamp.c

**Purpose and contract:** Clamp a same-scale signed Q value to inclusive [lower, upper]. Invalid bounds or null result return false and leave *result unchanged.

**Direct validation:** [`test_010_q64_clamp.c`](tests/test_010_q64_clamp.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_q64_lerp.h

**Public symbol:** pc_q64_lerp

**Implementation unit:** src/pc_q64_lerp.c

**Purpose and contract:** Convex same-scale signed int64 interpolation at numerator/denominator. Requires denominator>0 and numerator<=denominator. The exact final value rounds nearest-even. Invalid inputs fail without modifying *result.

**Direct validation:** [`test_011_q64_lerp.c`](tests/test_011_q64_lerp.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_rad_to_deg_q.h

**Public symbol:** pc_rad_to_deg_q

**Implementation unit:** src/pc_rad_to_deg_q.c

**Purpose and contract:** Convert signed Q16.16 radians to signed Q16.16 degrees. Returns false for null output or unrepresentable result and preserves output.

**Direct validation:** [`test_012_rad_to_deg_q.c`](tests/test_012_rad_to_deg_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_radps_to_rpm_q.h

**Public symbol:** pc_radps_to_rpm_q

**Implementation unit:** src/pc_radps_to_rpm_q.c

**Purpose and contract:** Convert signed Q16.16 radians per second to signed Q16.16 RPM. Uses nearest-even rounding with a Q30 pi constant. False on null output or unrepresentable result; output is preserved.

**Direct validation:** [`test_013_radps_to_rpm_q.c`](tests/test_013_radps_to_rpm_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_range_expand_i32.h

**Public symbol:** pc_range_expand_i32

**Implementation unit:** src/pc_range_expand_i32.c

**Purpose and contract:** Symmetrically expand a closed range by amount. Invalid bounds, overflow, null outputs, or aliased output pointers fail without writes.

**Direct validation:** [`test_014_range_expand_i32.c`](tests/test_014_range_expand_i32.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_ratio_round_even_u32.h

**Public symbol:** pc_ratio_round_even_u32

**Implementation unit:** src/pc_ratio_round_even_u32.c

**Purpose and contract:** Round numerator/denominator to nearest integer, ties to even.

**Direct validation:** [`test_009_q_to_i32_round.c`](tests/test_009_q_to_i32_round.c), [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_roll_pitch_from_accel_q.h

**Public symbol:** pc_roll_pitch_from_accel_q

**Implementation unit:** src/pc_roll_pitch_from_accel_q.c

**Purpose and contract:** Estimate static-gravity tilt from a bounded Q1.30 accelerometer vector. Roll = atan2(y,z); pitch = atan2(-x,sqrt(y*y+z*z)). Angles are signed Q0.32 turns; the +half-turn roll boundary is represented as -half-turn. The all-zero vector and out-of-range inputs fail without changing outputs.

**Direct validation:** [`test_015_roll_pitch_from_accel_q.c`](tests/test_015_roll_pitch_from_accel_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_rpm_to_radps_q.h

**Public symbol:** pc_rpm_to_radps_q

**Implementation unit:** src/pc_rpm_to_radps_q.c

**Purpose and contract:** Convert signed Q16.16 RPM to signed Q16.16 radians per second. Uses nearest-even rounding with a Q30 pi constant; null output fails.

**Direct validation:** [`test_016_rpm_to_radps_q.c`](tests/test_016_rpm_to_radps_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_strain_ratio_q.h

**Public symbol:** pc_strain_ratio_q

**Implementation unit:** src/pc_strain_ratio_q.c

**Purpose and contract:** Convert a signed resistance change to strain using GF = (deltaR/R)/strain. Inputs: delta resistance in milliohms, nominal resistance in ohms, gauge factor UQ16.16. Output is signed microstrain, nearest-even.

**Direct validation:** [`test_017_strain_ratio_q.c`](tests/test_017_strain_ratio_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_table_inverse_index_q.h

**Public symbol:** pc_table_inverse_index_q

**Implementation unit:** src/pc_table_inverse_index_q.c

**Purpose and contract:** Map a sample through a strictly increasing implicit-index table to a clamped Q16.16 fractional index. Count is 2..32768. Interior fractions round to nearest, ties-to-even. The table's strict ordering is a precondition.

**Direct validation:** [`test_018_table_inverse_index_q.c`](tests/test_018_table_inverse_index_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_time_ratio_internal.h

**Public symbol:** pc_time_ratio_mul_divmod_u64

**Implementation unit:** src/pc_time_ratio_internal.c

**Purpose and contract:** Private shared primitive. Computes floor(value*numerator/denominator) and its remainder exactly. False on invalid pointers/denominator or quotient overflow; outputs remain unchanged on failure.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_time_to_target_q.h

**Public symbol:** pc_time_to_target_q

**Implementation unit:** src/pc_time_to_target_q.c

**Purpose and contract:** Return ceil time to target in microseconds for scalar Q16.16 position and constant velocity in Q16.16 units/second. Equal position returns 0 even at zero speed. A nonzero distance with zero/opposite velocity fails atomically.

**Direct validation:** [`test_021_remaining_api.c`](tests/test_021_remaining_api.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_trilinear_interp_q.h

**Public symbol:** pc_trilinear_interp_q

**Implementation unit:** src/pc_trilinear_interp_q.c

**Purpose and contract:** Single-round trilinear interpolation of signed-Q15 corners. fx/fy/fz are unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even.

**Direct validation:** [`test_019_trilinear_interp_q.c`](tests/test_019_trilinear_interp_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.

## include/quantelis/fixed_point/pc_voltage_divider_q.h

**Public symbol:** pc_voltage_divider_q

**Implementation unit:** src/pc_voltage_divider_q.c

**Purpose and contract:** The public header contains the authoritative signature and input/output contract.

**Direct validation:** [`test_020_voltage_divider_q.c`](tests/test_020_voltage_divider_q.c)


**Integration notes:** use the exact fixed-width types and units shown in the declaration; check the boolean/status return before consuming an output pointer; do not assume overlap, rounding or overflow behavior beyond the contract above.
