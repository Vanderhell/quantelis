#include "pc_trilinear_interp_q.h"
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#if LDBL_MANT_DIG < 64
#error "The independent long-double oracle requires at least 64 significand bits."
#endif

static uint32_t rng = 0x865C1A4u;
static uint32_t next_u32(void)
{
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng;
}
static int16_t from_bits(uint16_t bits)
{
    return bits <= (uint16_t)INT16_MAX ? (int16_t)bits
                                       : (int16_t)((int32_t)bits - 65536);
}
static int16_t oracle(const int16_t v[8], uint32_t fx, uint32_t fy, uint32_t fz)
{
    const uint64_t s = 65536u;
    uint64_t w[8];
    uint64_t x0 = s - fx, y0 = s - fy, z0 = s - fz;
    int64_t weighted;
    long double exact, frac;
    int64_t q;
    w[0] = x0 * y0 * z0; w[1] = (uint64_t)fx * y0 * z0;
    w[2] = x0 * (uint64_t)fy * z0; w[3] = (uint64_t)fx * fy * z0;
    w[4] = x0 * y0 * (uint64_t)fz; w[5] = (uint64_t)fx * y0 * fz;
    w[6] = x0 * (uint64_t)fy * fz; w[7] = (uint64_t)fx * fy * fz;
    weighted = 0;
    for (size_t i = 0u; i < 8u; ++i) weighted += (int64_t)v[i] * (int64_t)w[i];
    exact = (long double)weighted / 281474976710656.0L;
    q = (int64_t)exact;
    frac = exact - (long double)q;
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
static int16_t sequential(const int16_t v[8], uint32_t fx, uint32_t fy, uint32_t fz)
{
    int16_t a = interp1d(v[0], v[1], fx), b = interp1d(v[2], v[3], fx);
    int16_t c = interp1d(v[4], v[5], fx), d = interp1d(v[6], v[7], fx);
    return interp1d(interp1d(a, b, fy), interp1d(c, d, fy), fz);
}

int main(void)
{
    static const int16_t values[] = {INT16_MIN, -1, 0, 1, INT16_MAX};
    static const uint32_t fractions[] = {0u, 32768u, 65536u};
    int16_t v[8], got;
    uint32_t tested = 0u;
    uint32_t staged_differences = 0u, max_staged_difference = 0u;
    for (uint32_t code = 0u; code < 390625u; ++code) {
        uint32_t x = code;
        for (size_t i = 0u; i < 8u; ++i) { v[i] = values[x % 5u]; x /= 5u; }
        for (size_t fx = 0u; fx < 3u; ++fx) for (size_t fy = 0u; fy < 3u; ++fy)
            for (size_t fz = 0u; fz < 3u; ++fz) {
                int16_t minv = v[0], maxv = v[0];
                assert(pc_trilinear_interp_q(v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],
                    fractions[fx], fractions[fy], fractions[fz], &got));
                for (size_t i = 1u; i < 8u; ++i) { if (v[i] < minv) minv = v[i]; if (v[i] > maxv) maxv = v[i]; }
                assert(got == oracle(v, fractions[fx], fractions[fy], fractions[fz]));
                assert(got >= minv && got <= maxv);
                {
                    int32_t difference = (int32_t)got - sequential(v, fractions[fx], fractions[fy], fractions[fz]);
                    if (difference < 0) difference = -difference;
                    if (difference != 0) ++staged_differences;
                    if ((uint32_t)difference > max_staged_difference)
                        max_staged_difference = (uint32_t)difference;
                }
                ++tested;
            }
    }
    for (uint32_t i = 0u; i < 100000u; ++i) {
        uint32_t fx = next_u32() % 65537u, fy = next_u32() % 65537u, fz = next_u32() % 65537u;
        int16_t minv, maxv;
        for (size_t j = 0u; j < 8u; ++j) v[j] = from_bits((uint16_t)next_u32());
        minv = maxv = v[0];
        for (size_t j = 1u; j < 8u; ++j) { if (v[j] < minv) minv = v[j]; if (v[j] > maxv) maxv = v[j]; }
        assert(pc_trilinear_interp_q(v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],fx,fy,fz,&got));
        assert(got == oracle(v, fx, fy, fz));
        assert(got >= minv && got <= maxv);
        ++tested;
    }
    {
        int16_t constant[8] = {INT16_MIN,INT16_MIN,INT16_MIN,INT16_MIN,
                               INT16_MIN,INT16_MIN,INT16_MIN,INT16_MIN};
        assert(pc_trilinear_interp_q(constant[0],constant[1],constant[2],constant[3],
            constant[4],constant[5],constant[6],constant[7],32768u,32768u,32768u,&got));
        assert(got == INT16_MIN);
        assert(pc_trilinear_interp_q(0,1,2,3,4,5,6,7,65536u,0u,65536u,&got) && got == 5);
        got = 123;
        assert(!pc_trilinear_interp_q(0,1,2,3,4,5,6,7,65537u,0u,0u,&got) && got == 123);
        assert(!pc_trilinear_interp_q(0,1,2,3,4,5,6,7,0u,65537u,0u,&got) && got == 123);
        assert(!pc_trilinear_interp_q(0,1,2,3,4,5,6,7,0u,0u,65537u,&got) && got == 123);
        assert(!pc_trilinear_interp_q(0,1,2,3,4,5,6,7,0u,0u,0u,NULL));
    }
    printf("trilinear tests passed: exhaustive+seeded=%lu, staged differences=%lu max=%lu\n",
           (unsigned long)tested, (unsigned long)staged_differences,
           (unsigned long)max_staged_difference);
    return 0;
}
