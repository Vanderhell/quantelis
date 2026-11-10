#include "pc_table_inverse_index_q.h"
#include <assert.h>
#undef assert
#define assert(condition) do { if (!(condition)) return __LINE__; } while (0)
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static uint32_t rng = 0x858C1A4u;
static uint32_t next_u32(void)
{
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng;
}
static int32_t from_bits(uint32_t bits)
{
    return bits <= (uint32_t)INT32_MAX ? (int32_t)bits
                                      : (int32_t)((int64_t)bits - 4294967296LL);
}
static int compare_i32(const void *left, const void *right)
{
    int32_t a = *(const int32_t *)left, b = *(const int32_t *)right;
    return (a > b) - (a < b);
}
static int64_t round_ratio_even(uint64_t numerator, uint32_t denominator)
{
    uint64_t q = numerator / denominator, r = numerator % denominator;
    if (r > denominator - r ||
        (r == denominator - r && (q & 1u) != 0u)) ++q;
    return (int64_t)q;
}
static bool oracle(const int32_t *a, size_t n, int32_t sample, int32_t *out)
{
    size_t i;
    if (n < 2u || n > 32768u) return false;
    for (i = 1u; i < n; ++i) if (a[i - 1u] >= a[i]) return false;
    if (sample <= a[0]) { *out = 0; return true; }
    if (sample >= a[n - 1u]) { *out = (int32_t)((uint32_t)(n - 1u) << 16); return true; }
    for (i = 1u; i < n; ++i) {
        if (sample == a[i]) { *out = (int32_t)((uint32_t)i << 16); return true; }
        if (sample < a[i]) {
            uint64_t offset = (uint64_t)((int64_t)sample - a[i - 1u]);
            uint32_t gap = (uint32_t)((int64_t)a[i] - a[i - 1u]);
            uint32_t fraction = (uint32_t)round_ratio_even(offset * 65536u, gap);
            *out = (int32_t)(((uint32_t)(i - 1u) << 16) + fraction);
            return true;
        }
    }
    return false;
}

int main(void)
{
    int32_t values[16], got, expected;
    static int32_t maximum_count_table[32768];
    uint32_t tested = 0u;
    size_t n, i;
    for (n = 2u; n <= 7u; ++n) {
        uint32_t cases = 1u;
        uint32_t code;
        for (i = 0u; i < n; ++i) cases *= 7u;
        for (code = 0u; code < cases; ++code) {
            uint32_t x = code;
            bool strict = true;
            for (i = 0u; i < n; ++i) { values[i] = (int32_t)(x % 7u) - 3; x /= 7u; }
            for (i = 1u; i < n; ++i) if (values[i - 1u] >= values[i]) strict = false;
            if (!strict) continue;
            for (int32_t sample = -5; sample <= 5; ++sample) {
                assert(oracle(values, n, sample, &expected));
                assert(pc_table_inverse_index_q(values, n, sample, &got) && got == expected);
                ++tested;
            }
        }
    }
    for (i = 0u; i < 50000u; ++i) {
        size_t j, len = 2u + next_u32() % 15u;
        int32_t sample = from_bits(next_u32());
        for (j = 0u; j < len; ++j) values[j] = from_bits(next_u32());
        qsort(values, len, sizeof(values[0]), compare_i32);
        {
            size_t write = 1u;
            for (j = 1u; j < len; ++j)
                if (values[j] != values[write - 1u]) values[write++] = values[j];
            len = write;
        }
        if (len < 2u) { values[0] = INT32_MIN; values[1] = INT32_MAX; len = 2u; }
        assert(oracle(values, len, sample, &expected));
        assert(pc_table_inverse_index_q(values, len, sample, &got) && got == expected);
        ++tested;
    }
    {
        static const int32_t ties[] = {0, 131072};
        static const int32_t full[] = {INT32_MIN, INT32_MAX};
        static const int32_t knots[] = {INT32_MIN, -100, 0, 100, INT32_MAX};
        assert(pc_table_inverse_index_q(ties, 2u, 1, &got) && got == 0);
        assert(pc_table_inverse_index_q(ties, 2u, 3, &got) && got == 2);
        assert(pc_table_inverse_index_q(ties, 2u, 5, &got) && got == 2);
        assert(pc_table_inverse_index_q(full, 2u, 0, &got) && got == 32768);
        assert(pc_table_inverse_index_q(knots, 5u, 0, &got) && got == 2 * 65536);
        assert(pc_table_inverse_index_q(knots, 5u, INT32_MIN, &got) && got == 0);
        assert(pc_table_inverse_index_q(knots, 5u, INT32_MAX, &got) && got == 4 * 65536);
    }
    for (size_t j = 0u; j < 32768u; ++j) maximum_count_table[j] = (int32_t)j - 16384;
    assert(pc_table_inverse_index_q(maximum_count_table, 32768u, 0, &got));
    assert(got == 16384 * 65536);
    assert(pc_table_inverse_index_q(maximum_count_table, 32768u, INT32_MAX, &got));
    assert(got == 32767 * 65536);
    got = 123;
    assert(!pc_table_inverse_index_q(NULL, 2u, 0, &got) && got == 123);
    assert(!pc_table_inverse_index_q(values, 1u, 0, &got) && got == 123);
    assert(!pc_table_inverse_index_q(values, 32769u, 0, &got) && got == 123);
    assert(!pc_table_inverse_index_q(values, 2u, 0, NULL));
    printf("inverse index tests passed: differential=%lu seeded=50000\n", (unsigned long)tested);
    return 0;
}
