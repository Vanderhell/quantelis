# Architecture

Quantelis is a stateless static C99 library. Each fixed-point operation is
compiled from its own source unit, with explicit integer widths and no hidden
runtime state.


CMake builds a standalone static archive from `src/*.c`. Set `QUANTELIS_BUILD_TESTS=OFF` to omit host tests or `QUANTELIS_STRICT_WARNINGS=ON` to enable `/W4 /WX` on MSVC and `-Wall -Wextra -Wpedantic -Werror` on GCC/Clang. The public build include paths expose both `include/` and the fixed-point header directory. No operating-system service, heap allocation or third-party library is required by the production archive; test programs link the host math library where needed.
