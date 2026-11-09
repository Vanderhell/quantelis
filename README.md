# Quantelis

Quantelis is a portable C99 fixed-point mathematics library for deterministic
scaling, interpolation, angle conversion, smoothing and bounded numerical
transforms on embedded targets.

## Scope

The first extraction contains 27 public fixed-point functions from the
PrimitiveCore family. The preserved `pc_` API uses the representation and
rounding contracts documented in each header. No heap or operating-system
service is required.

## Build and test

```sh
cmake -S . -B build -DQUANTELIS_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

## Validation status

Host extraction tests are the current gate. ESP32-S3 validation and isolated
footprint measurements are pending; no hardware result is claimed.

## Name and origin

Quantelis combines *quantus* (quantity) with *telos* (purpose/scale), reflecting
fixed-point values used for controlled quantitative transforms. It originates
from PrimitiveCore's `fixed_point/q_format_and_numeric` family.

## License

Apache License 2.0, copyright Vanderhell. See `LICENSE` and `NOTICE`.
