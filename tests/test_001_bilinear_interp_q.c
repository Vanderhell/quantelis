#include "pc_bilinear_interp_q.h"
#include <assert.h>
#undef assert
#define assert(condition) do { if (!(condition)) return __LINE__; } while (0)
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t rng = 0x864C1A4u;
static uint32_t next_u32(void)
{
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng;
}
static int16_t from_bits(uint16_t bits)
{
    return bits <= (uint16_t)INT16_MAX ? (int16_t)bits
                                       : (int16_t)((int32_t)bits - 65536);
}
/* Exact integer weighted numerator, rounded through binary long double. Its
 * magnitude is below 2^47, so it is exactly representable even as binary64. */
static int16_t oracle(int16_t a, int16_t b, int16_t c, int16_t d,
                      uint32_t fx, uint32_t fy)
{
    const uint64_t s = 65536u;
    uint64_t x0 = s - fx, y0 = s - fy;
    int64_t weighted = (int64_t)a * (int64_t)(x0 * y0) +
        (int64_t)b * (int64_t)((uint64_t)fx * y0) +
        (int64_t)c * (int64_t)(x0 * (uint64_t)fy) +
        (int64_t)d * (int64_t)((uint64_t)fx * fy);
    long double exact = (long double)weighted / 4294967296.0L;
    int64_t q = (int64_t)exact;
    long double frac = exact - (long double)q;
    if (frac > 0.5L || (frac == 0.5L && q % 2 != 0)) ++q;
    else if (frac < -0.5L || (frac == -0.5L && q % 2 != 0)) --q;
    return (int16_t)q;
}
static int16_t interp1d(int16_t a, int16_t b, uint32_t n)
{
    int64_t weighted = (int64_t)a * (65536u - n) + (int64_t)b * n;
    int64_t q = weighted / 65536, r = weighted % 65536;
    uint64_t mag = (uint64_t)(r < 0 ? -r : r);
    if (mag > 65536u - mag || (mag == 65536u - mag && q % 2 != 0))
        q += weighted < 0 ? -1 : 1;
    return (int16_t)q;
}

int main(void)
{
    static const int16_t values[] = {INT16_MIN, -1, 0, 1, INT16_MAX};
    static const uint32_t fractions[] = {0u, 1u, 32768u, 65535u, 65536u};
    int16_t got;
    uint32_t tested = 0u;
    size_t a, b, c, d, x, y;
    uint32_t double_round_differences = 0u;
    for (a = 0u; a < 5u; ++a) for (b = 0u; b < 5u; ++b)
        for (c = 0u; c < 5u; ++c) for (d = 0u; d < 5u; ++d)
            for (x = 0u; x < 5u; ++x) for (y = 0u; y < 5u; ++y) {
                int16_t minv = values[a], maxv = values[a];
                assert(pc_bilinear_interp_q(values[a], values[b], values[c], values[d],
                                             fractions[x], fractions[y], &got));
                if (values[b] < minv) minv = values[b];
                if (values[c] < minv) minv = values[c];
                if (values[d] < minv) minv = values[d];
                if (values[b] > maxv) maxv = values[b];
                if (values[c] > maxv) maxv = values[c];
                if (values[d] > maxv) maxv = values[d];
                assert(got == oracle(values[a], values[b], values[c], values[d],
                                     fractions[x], fractions[y]));
                assert(got >= minv && got <= maxv);
                ++tested;
            }
    for (uint32_t i = 0u; i < 200000u; ++i) {
        int16_t v00 = from_bits((uint16_t)next_u32()), v10 = from_bits((uint16_t)next_u32());
        int16_t v01 = from_bits((uint16_t)next_u32()), v11 = from_bits((uint16_t)next_u32());
        uint32_t fx = next_u32() % 65537u, fy = next_u32() % 65537u;
        assert(pc_bilinear_interp_q(v00, v10, v01, v11, fx, fy, &got));
        assert(got == oracle(v00, v10, v01, v11, fx, fy));
        assert(pc_bilinear_interp_q(v00, v01, v10, v11, fy, fx, &got));
        assert(got == oracle(v00, v10, v01, v11, fx, fy));
        ++tested;
    }
    {
        static const int16_t small[] = {-3, -2, -1, 0, 1, 2, 3};
        static const uint32_t f[] = {0u, 1u, 16384u, 32768u, 49152u, 65535u, 65536u};
        for (a = 0u; a < 7u; ++a) for (b = 0u; b < 7u; ++b)
            for (c = 0u; c < 7u; ++c) for (d = 0u; d < 7u; ++d)
                for (x = 0u; x < 7u; ++x) for (y = 0u; y < 7u; ++y) {
                    int16_t exact = oracle(small[a], small[b], small[c], small[d], f[x], f[y]);
                    int16_t top = interp1d(small[a], small[b], f[x]);
                    int16_t bottom = interp1d(small[c], small[d], f[x]);
                    int16_t sequential = interp1d(top, bottom, f[y]);
                    int32_t error = (int32_t)sequential - exact;
                    if (error < 0) error = -error;
                    assert(error <= 1);
                    if (error != 0) ++double_round_differences;
                }
        assert(double_round_differences != 0u);
    }
    {
        int16_t out = 123;
        assert(pc_bilinear_interp_q(0, 100, 200, 300, 32768u, 32768u, &out) && out == 150);
        assert(pc_bilinear_interp_q(0, 1, 0, 1, 32768u, 0u, &out) && out == 0);
        out = 123;
        assert(!pc_bilinear_interp_q(0, 1, 2, 3, 65537u, 0u, &out) && out == 123);
        assert(!pc_bilinear_interp_q(0, 1, 2, 3, 0u, 65537u, &out) && out == 123);
        assert(!pc_bilinear_interp_q(0, 1, 2, 3, 0u, 0u, NULL));
    }
    for (int16_t grid_x = 0; grid_x <= 100; ++grid_x) for (int16_t grid_y = 0; grid_y <= 100; ++grid_y) {
        int16_t out;
        uint32_t fx = (uint32_t)grid_x * 65536u / 100u;
        uint32_t fy = (uint32_t)grid_y * 65536u / 100u;
        assert(pc_bilinear_interp_q(0, 100, 200, 300, fx, fy, &out));
        assert(out == oracle(0, 100, 200, 300, fx, fy));
    }
    printf("bilinear tests passed: exhaustive+seeded=%lu, sequential double-round differences=%lu\n",
           (unsigned long)tested, (unsigned long)double_round_differences);
    return 0;
}
