# Testing

| Test category | Count | Platform | Result | Evidence |
|---|---:|---|---|---|
| Migrated unit tests | 20 source programs; 19 MSVC executables | Windows host, MSVC 19.42.34444, Release | PASS 19/19; trilinear oracle skipped because MSVC long double has 53-bit precision | `tests/`, CTest |
| Hardware validation | 0 | ESP32-S3 | HW NOT VERIFIED | No firmware run yet |
| Sanitizers | 0 | Host | NOT TESTED | Toolchain setup pending |

```sh
cmake -S . -B build -DQUANTELIS_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```
