# Performance and footprint

## ESP32-S3 benchmark

Measured on an ESP32-S3 revision v0.2 at 240 MHz, Arduino ESP32 core 3.3.10, using the Arduino `-Os` configuration and USB CDC. Each direct-operation wrapper ran 20,000 calls in five repeats; the median integer cycles per call is reported. This is one representative input per operation and includes the wrapper/call loop; it is not a worst-case execution-time guarantee.

| Operation | Median cycles/call | Approx. time at 240 MHz |
|---|---:|---:|
| `pc_bearing2_q` | 2,996 | 12.48 µs |
| `pc_constant_velocity_predict_q` | 267 | 1.11 µs |
| `pc_decay_factor_from_halflife_q` | 851 | 3.55 µs |
| `pc_q_hypot3` | 1,226 | 5.11 µs |
| `pc_trilinear_interp_q` | 304 | 1.27 µs |
| `pc_q_mul_round_even` | 121 | 0.50 µs |

The six-operation benchmark was compiled and uploaded, and its cycle medians were captured. A separate ESP32-S3 v0.2 smoke firmware then called all 30 callable declarations and emitted `QUANTELIS_ALL30_PASS passed=30 failed_index=0` at 240 MHz. This is one deterministic known-value check per declaration, not a target port of the full host differential corpus.

## Flash and RAM

For the same Arduino integration style, the full benchmark firmware used **367,036 bytes** of application flash (28% of the 1,310,720-byte limit). It reported **54,320 bytes** of global/static RAM (16% of 327,680 bytes), leaving 273,360 bytes. These totals include the Arduino core, USB CDC, test harness, and selected Quantelis operations; they are not the isolated library footprint.

The linker map reports **1,891 bytes** across `.text` and `.literal` sections for the six selected Quantelis functions in this harness. Their source object `.data` and `.bss` sections are zero. This is only a selected-function link contribution; it excludes transitive compiler-runtime helpers and is not the footprint of all 30 callable declarations.

The task stack watermark remained unchanged within captured benchmark cycles (6,268 bytes on the first observed pass and 6,104 bytes on later passes). This is a whole-task FreeRTOS watermark with the USB/harness activity and cannot be used as a per-function stack bound.

Re-measure for a production application: results vary with compiler/core version, optimization flags, selected functions, inputs, and USB/runtime configuration. The six cycle values are samples, not WCET bounds.
