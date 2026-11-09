#include "pc_trilinear_interp_q.h"
#include <stddef.h>

bool pc_trilinear_interp_q(
    int16_t v000_q15, int16_t v100_q15, int16_t v010_q15, int16_t v110_q15,
    int16_t v001_q15, int16_t v101_q15, int16_t v011_q15, int16_t v111_q15,
    uint32_t fx_q0_16, uint32_t fy_q0_16, uint32_t fz_q0_16,
    int16_t *value_q15)
{
    const uint64_t scale = UINT64_C(65536);
    const uint64_t denominator = UINT64_C(281474976710656);
    uint64_t x0, y0, z0, magnitude;
    int64_t weighted, quotient, remainder;
    if (value_q15 == NULL || fx_q0_16 > scale || fy_q0_16 > scale || fz_q0_16 > scale)
        return false;
    x0 = scale - fx_q0_16;
    y0 = scale - fy_q0_16;
    z0 = scale - fz_q0_16;
    weighted = (int64_t)v000_q15 * (int64_t)(x0 * y0 * z0) +
               (int64_t)v100_q15 * (int64_t)((uint64_t)fx_q0_16 * y0 * z0) +
               (int64_t)v010_q15 * (int64_t)(x0 * (uint64_t)fy_q0_16 * z0) +
               (int64_t)v110_q15 * (int64_t)((uint64_t)fx_q0_16 * fy_q0_16 * z0) +
               (int64_t)v001_q15 * (int64_t)(x0 * y0 * (uint64_t)fz_q0_16) +
               (int64_t)v101_q15 * (int64_t)((uint64_t)fx_q0_16 * y0 * fz_q0_16) +
               (int64_t)v011_q15 * (int64_t)(x0 * (uint64_t)fy_q0_16 * fz_q0_16) +
               (int64_t)v111_q15 * (int64_t)((uint64_t)fx_q0_16 * fy_q0_16 * fz_q0_16);
    quotient = weighted / (int64_t)denominator;
    remainder = weighted % (int64_t)denominator;
    magnitude = (uint64_t)(remainder < 0 ? -remainder : remainder);
    if (magnitude > denominator - magnitude ||
        (magnitude == denominator - magnitude && quotient % 2 != 0))
        quotient += weighted < 0 ? -1 : 1;
    *value_q15 = (int16_t)quotient;
    return true;
}
