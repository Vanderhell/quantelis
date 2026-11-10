# Quantelis
![CI](https://github.com/Vanderhell/quantelis/actions/workflows/ci.yml/badge.svg) ![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg) ![Language](https://img.shields.io/badge/language-C99-informational.svg)

![Quantelis banner](docs/banner.svg)

Fixed-point scaling, interpolation, angle conversion, smoothing and bounded numerical transforms.

## Why it exists

MCU firmware needs predictable numeric calculations where floating-point is unavailable or undesirable.

## What is included

- Portable C99-oriented implementation.
- Deterministic integer or fixed-point behavior documented at function level.
- No mandatory heap, threads or operating-system services.
- Separate translation units for selective linking.

## Quick start

```sh
cmake -S . -B build -DQUANTELIS_BUILD_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

For a minimal integration, include only the required public header and compile the matching source unit. The library does not require the rest of PrimitiveCore.

## Documentation

| Need | Read |
|---|---|
| Choose a primitive | [Family guide](docs/FAMILY_GUIDE.md) |
| Check every function and contract | [API reference](docs/API_REFERENCE.md) |
| Reproduce tests and see validation limits | [Testing report](docs/TESTING.md) |
| Review design and dependencies | [Architecture](docs/ARCHITECTURE.md) |
| See measured or pending performance data | [Performance](docs/PERFORMANCE.md) |

## At a glance

The include tree contains 30 callable declarations: 29 product operations and the shared time-ratio helper. Each has an implementation unit. Tests are in tests/. State, buffers and output ownership are explicit in each header contract.

The CMake test option is QUANTELIS_BUILD_TESTS. The library has no mandatory third-party dependency. Platform-specific link requirements are documented in CMake and the affected API header.

## Validation status

Executed checks: GCC 21/21, Clang 21/21, GCC ASan+UBSan 21/21, and MSVC Debug/Release 21/21 each. The trilinear test now uses an exact integer oracle on MSVC. An ESP32-S3 runtime smoke test passed all 30 callable declarations at 240 MHz. See [Testing](docs/TESTING.md) and [Performance](docs/PERFORMANCE.md).

Detailed overflow, rounding, invalid-input, memory-ownership and state rules are defined by the public headers and API reference. Do not infer them from the product name alone.

## License

Apache License 2.0, copyright Vanderhell. See [LICENSE](LICENSE) and [NOTICE](NOTICE).

## Origin

A standalone embedded-C library extracted from the PrimitiveCore product catalog. It is independently buildable and linkable.
