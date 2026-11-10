# Quantelis family guide

## What this family solves

**Fixed-point mathematics.** Fixed-point scaling, interpolation, angle conversion, smoothing and bounded numerical transforms.

This guide describes the complete public family as an independent embedded-C product. Each primitive remains separately linkable; select only the headers and source units required by the application.

## When to use this family

Use Quantelis when the application needs the operations listed below and requires deterministic behavior, explicit caller-owned memory, and no mandatory operating-system services.

## Family at a glance

```mermaid
flowchart LR
    A[Application input] --> B[Validate representation and bounds]
    B --> C[Select one public primitive]
    C --> D[Check status or output contract]
    D --> E[Use result with documented units]
```

## Primitive map

| Public header | Symbol | Purpose and contract | Validation source |
|---|---|---|---|
| `include/quantelis/fixed_point/pc_bearing2_q.h` | `pc_bearing2_q` | CORDIC estimate of bearing from an int32 origin to target as unsigned Q0.32 turns CCW from +X. Equal points return zero. Coordinates need not share a specific Q scale. The seeded 100,000-case and boundary differential corpus observed maximum error 6 phase codes; the test permits 32 and the measured value is not a formal global bound. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_bilinear_interp_q.h` | `pc_bilinear_interp_q` | Single-round bilinear interpolation of signed-Q15 corners. fx/fy are unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even. | tests/test_001_bilinear_interp_q.c |
| `include/quantelis/fixed_point/pc_constant_velocity_predict_q.h` | `pc_constant_velocity_predict_q` | Predict scalar Q16.16 position after dt_us at constant velocity in Q16.16 units/second. Delta is rounded nearest-even. Returns false if the result is outside int32; output is unchanged on failure. dt_us may be any uint32 value. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_decay_factor_from_halflife_q.h` | `pc_decay_factor_from_halflife_q` | Compute the per-step retention factor 2^(-1/half_life_steps) in unsigned Q0.16, rounded to nearest-even. The result ranges from 32768 through 65536; 65536 represents exact unity. half_life_steps must be positive. On zero half-life or null output, return false without modifying the output. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_decay_factor_from_tau_q.h` | `pc_decay_factor_from_tau_q` | Return exp(-1/tau_steps) as nearest-even unsigned Q0.16 retention. tau_steps must be positive; 65536 represents unity. | tests/test_002_decay_factor_from_tau_q.c |
| `include/quantelis/fixed_point/pc_deg_to_rad_q.h` | `pc_deg_to_rad_q` | Convert signed Q16.16 degrees to signed Q16.16 radians. Uses round-to-nearest, ties-to-even with a Q30 pi constant. Returns false for a null output pointer and leaves output unchanged. | tests/test_003_deg_to_rad_q.c |
| `include/quantelis/fixed_point/pc_direction_quantize16_q.h` | `pc_direction_quantize16_q` | Quantize unsigned Q0.32 turns to nearest of 16 equally spaced directions, codes 0..15 counterclockwise from +X. Halfway values round CCW. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_direction_quantize8_q.h` | `pc_direction_quantize8_q` | Quantize unsigned Q0.32 turns to nearest of 8 compass sectors (E through SE counterclockwise), codes 0..7. Exact halfway values round CCW. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_one_pole_smoother_q.h` | `pc_one_pole_smoother_q` | Update caller-owned state toward input by Q16 alpha: state += round-nearest-even((input-state)*alpha_q16/65536). alpha_q16 must be in [0,65536]. Invalid input leaves state unchanged. Per-sample coefficient: effective bandwidth depends on sample cadence. | tests/test_004_one_pole_smoother_q.c |
| `include/quantelis/fixed_point/pc_packet_loss_rate_q.h` | `pc_packet_loss_rate_q` | Compute round-nearest-even((lost_packets * 2^fractional_bits) / sent_packets). Requires sent_packets > 0, lost_packets <= sent_packets, fractional_bits <= 31, and non-null rate_q. Failure leaves *rate_q unchanged. | tests/test_005_packet_loss_rate_q.c |
| `include/quantelis/fixed_point/pc_q_div_round_even.h` | `pc_q_div_round_even` | Compute (a*2^f)/b to int32, nearest-even; f=0..31 and b!=0. | tests/test_005_packet_loss_rate_q.c |
| `include/quantelis/fixed_point/pc_q_hypot2.h` | `pc_q_hypot2` | Nearest-even Euclidean norm of same-scale signed Q raw values. False on null output or int32 result overflow; failure preserves *out. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_q_hypot3.h` | `pc_q_hypot3` | Nearest-even Euclidean norm of three same-scale signed Q raw values. False on null output or int32 overflow; failure preserves *out. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_q_mul_add_sat.h` | `pc_q_mul_add_sat` | sat32(round_even(a*b/2^f)+c), f=0..31. | tests/test_007_q_mul_add_sat.c |
| `include/quantelis/fixed_point/pc_q_mul_round_even.h` | `pc_q_mul_round_even` | Multiply two signed int32 Q values with f fractional bits, nearest-even. | tests/test_008_q_mul_round_even.c |
| `include/quantelis/fixed_point/pc_q_to_i32_round.h` | `pc_q_to_i32_round` | Convert signed int32 Q raw value to integer, nearest-even; f is 0..31. | tests/test_009_q_to_i32_round.c |
| `include/quantelis/fixed_point/pc_q64_clamp.h` | `pc_q64_clamp` | Clamp a same-scale signed Q value to inclusive [lower, upper]. Invalid bounds or null result return false and leave *result unchanged. | tests/test_010_q64_clamp.c |
| `include/quantelis/fixed_point/pc_q64_lerp.h` | `pc_q64_lerp` | Convex same-scale signed int64 interpolation at numerator/denominator. Requires denominator>0 and numerator<=denominator. The exact final value rounds nearest-even. Invalid inputs fail without modifying *result. | tests/test_011_q64_lerp.c |
| `include/quantelis/fixed_point/pc_rad_to_deg_q.h` | `pc_rad_to_deg_q` | Convert signed Q16.16 radians to signed Q16.16 degrees. Returns false for null output or unrepresentable result and preserves output. | tests/test_012_rad_to_deg_q.c |
| `include/quantelis/fixed_point/pc_radps_to_rpm_q.h` | `pc_radps_to_rpm_q` | Convert signed Q16.16 radians per second to signed Q16.16 RPM. Uses nearest-even rounding with a Q30 pi constant. False on null output or unrepresentable result; output is preserved. | tests/test_013_radps_to_rpm_q.c |
| `include/quantelis/fixed_point/pc_range_expand_i32.h` | `pc_range_expand_i32` | Symmetrically expand a closed range by amount. Invalid bounds, overflow, null outputs, or aliased output pointers fail without writes. | tests/test_014_range_expand_i32.c |
| `include/quantelis/fixed_point/pc_ratio_round_even_u32.h` | `pc_ratio_round_even_u32` | Round numerator/denominator to nearest integer, ties to even. | tests/test_009_q_to_i32_round.c |
| `include/quantelis/fixed_point/pc_roll_pitch_from_accel_q.h` | `pc_roll_pitch_from_accel_q` | Estimate static-gravity tilt from a bounded Q1.30 accelerometer vector. Roll = atan2(y,z); pitch = atan2(-x,sqrt(y*y+z*z)). Angles are signed Q0.32 turns; the +half-turn roll boundary is represented as -half-turn. The all-zero vector and out-of-range inputs fail without changing outputs. | tests/test_015_roll_pitch_from_accel_q.c |
| `include/quantelis/fixed_point/pc_rpm_to_radps_q.h` | `pc_rpm_to_radps_q` | Convert signed Q16.16 RPM to signed Q16.16 radians per second. Uses nearest-even rounding with a Q30 pi constant; null output fails. | tests/test_016_rpm_to_radps_q.c |
| `include/quantelis/fixed_point/pc_strain_ratio_q.h` | `pc_strain_ratio_q` | Convert a signed resistance change to strain using GF = (deltaR/R)/strain. Inputs: delta resistance in milliohms, nominal resistance in ohms, gauge factor UQ16.16. Output is signed microstrain, nearest-even. | tests/test_017_strain_ratio_q.c |
| `include/quantelis/fixed_point/pc_table_inverse_index_q.h` | `pc_table_inverse_index_q` | Map a sample through a strictly increasing implicit-index table to a clamped Q16.16 fractional index. Count is 2..32768. Interior fractions round to nearest, ties-to-even. The table's strict ordering is a precondition. | tests/test_018_table_inverse_index_q.c |
| `include/quantelis/fixed_point/pc_time_ratio_internal.h` | `pc_time_ratio_mul_divmod_u64` | Private shared primitive. Computes floor(value*numerator/denominator) and its remainder exactly. False on invalid pointers/denominator or quotient overflow; outputs remain unchanged on failure. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_time_to_target_q.h` | `pc_time_to_target_q` | Return ceil time to target in microseconds for scalar Q16.16 position and constant velocity in Q16.16 units/second. Equal position returns 0 even at zero speed. A nonzero distance with zero/opposite velocity fails atomically. | `tests/test_021_remaining_api.c` |
| `include/quantelis/fixed_point/pc_trilinear_interp_q.h` | `pc_trilinear_interp_q` | Single-round trilinear interpolation of signed-Q15 corners. fx/fy/fz are unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even. | tests/test_019_trilinear_interp_q.c |
| `include/quantelis/fixed_point/pc_voltage_divider_q.h` | `pc_voltage_divider_q` | The public header contains the authoritative signature and input/output contract. | tests/test_020_voltage_divider_q.c |

## Selection guidance

- Choose the primitive whose width, representation, rounding, saturation, wrapping, and error contract match the application.
- Do not substitute a similarly named function without checking the public header.
- Allocate state and buffers in the caller; respect documented aliasing and output-preservation rules.
- See the per-operation validation links and [test report](TESTING.md) for coverage limits and compiler-specific exclusions.

## Integration checklist

1. Include only the required public header.
2. Compile the matching source translation unit or use the product CMake target.
3. Check every boolean/status return before consuming an output.
4. Add application-specific boundary tests for units, widths, invalid inputs, and overflow behavior.
5. Run the documented host tests before target integration.

## Complexity and footprint

The product is split into independent translation units. A six-operation ESP32-S3 benchmark is recorded in [PERFORMANCE.md](PERFORMANCE.md). These values are sample costs, not WCET or full-library footprint claims.

## Validation boundary

The API reference links each public entry to its implementation and available validation source. Hardware status is reported only when reproducible target evidence exists.
