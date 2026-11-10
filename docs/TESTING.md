# Testing and audit status

The suite contains 21 C test programs. It directly exercises all 30 callable declarations, including the shared time-ratio primitive; see the API reference for an operation-to-test index. Assertions in the legacy tests have been made active under `NDEBUG` so Release runs retain their checks.

## Executed validation

| Configuration | Result | Notes |
|---|---:|---|
| GCC 13.3, Ubuntu 24.04, Release, strict warnings | PASS 21/21 | `-Wall -Wextra -Wpedantic -Werror` |
| Clang 18.1.3, Ubuntu 24.04, Release, strict warnings | PASS 21/21 | Same warning policy |
| GCC 13.3, Ubuntu 24.04, ASan + UBSan, Debug | PASS 21/21 | No sanitizer findings |
| GCC 16.1, Windows, Release, strict warnings | PASS 21/21 | MinGW-w64 toolchain |
| MSVC 19.42, Windows, Debug | PASS 21/21 | Exact integer trilinear reference oracle |
| MSVC 19.42, Windows, Release | PASS 21/21 | Exact integer trilinear reference oracle |
| ESP32-S3 smoke run, v0.2 at 240 MHz | PASS 30/30 | Captured `QUANTELIS_ALL30_PASS passed=30 failed_index=0`; this is one known-value check per callable declaration, not the host differential suite |
| GitHub Actions for audit commit `636bde0` | PASS | [Run 42902910872](https://github.com/Vanderhell/quantelis/actions/runs/42902910872): GCC/Clang Debug+Release, GCC ASan/UBSan, MSVC Debug+Release |

The Clang Release build also serves as a strict portability check; it identified missing final newlines that were corrected. The trilinear oracle uses floor division and a nonnegative remainder with exact tie-to-even handling, so it does not depend on extended floating-point precision. No confirmed production algorithm defect was found in this validation pass. This is not a formal proof for all inputs.

## Differential coverage

`tests/test_021_remaining_api.c` uses a fixed-seed generator and independent `atan2`, `hypot`, `exp`, and integer-rational references. It checks 100,000 cases each for bearing, direction quantization, 2D/3D norms, half-life decay, constant-velocity prediction, time-to-target, rounded ratios, and the private exact multiply/divide helper where the compiler provides a 128-bit reference type. Cardinal bearings and `int32_t` boundaries are also covered. The maximum observed bearing error was 6 codes in the seeded and boundary corpus, where one code is 1/2^32 turn; the test accepts at most 32 codes. This observed maximum is empirical, not a global error bound.

The existing interpolation and arithmetic programs retain their independent oracles, deterministic boundary cases, and invariants. The suite checks invalid pointers/parameters and output preservation where those properties are declared by the API. There is no blanket guarantee of buffer overlap unless an individual function contract says so.

## Reproduce host tests

```sh
cmake -S . -B build -DQUANTELIS_BUILD_TESTS=ON -DQUANTELIS_STRICT_WARNINGS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure -C Release
```

GCC sanitizer run on a supported platform:

```sh
cmake -S . -B build-sanitize -DQUANTELIS_BUILD_TESTS=ON -DQUANTELIS_STRICT_WARNINGS=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build build-sanitize --parallel
ctest --test-dir build-sanitize --output-on-failure
```

The CI workflow runs GCC and Clang Debug/Release, GCC ASan+UBSan, and MSVC Debug/Release. The production library remains C99; `__int128` is used only for an optional independent test oracle when supported.
