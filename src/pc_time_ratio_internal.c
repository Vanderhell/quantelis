#include "pc_time_ratio_internal.h"

static bool mul_div_fallback(uint64_t a, uint64_t b, uint64_t d,
                            uint64_t *quotient, uint64_t *remainder)
{
    const uint64_t whole = a / d;
    const uint64_t rem_a = a % d;
    uint64_t base;
    uint64_t part_q = 0;
    uint64_t rem = 0;
    unsigned bit = 64u;

    if (whole != 0u && b > UINT64_MAX / whole) return false;
    base = whole * b;
    while (bit != 0u) {
        uint64_t carry;
        --bit;
        carry = rem >= d - rem ? UINT64_C(1) : UINT64_C(0);
        rem = carry != 0u ? rem - (d - rem) : rem + rem;
        if (part_q > (UINT64_MAX - carry) / UINT64_C(2)) return false;
        part_q = part_q * UINT64_C(2) + carry;
        if (((b >> bit) & UINT64_C(1)) != 0u) {
            carry = rem >= d - rem_a ? UINT64_C(1) : UINT64_C(0);
            rem = carry != 0u ? rem - (d - rem_a) : rem + rem_a;
            if (part_q > UINT64_MAX - carry) return false;
            part_q += carry;
        }
    }
    if (part_q > UINT64_MAX - base) return false;
    *quotient = base + part_q;
    *remainder = rem;
    return true;
}

bool pc_time_ratio_mul_divmod_u64(uint64_t value, uint64_t numerator,
                                  uint64_t denominator, uint64_t *quotient,
                                  uint64_t *remainder)
{
    uint64_t q;
    uint64_t r;
    if (quotient == 0 || remainder == 0 || denominator == 0u) return false;
    if (numerator == 0u || value <= UINT64_MAX / numerator) {
        const uint64_t product = value * numerator;
        q = product / denominator;
        r = product % denominator;
    } else if (!mul_div_fallback(value, numerator, denominator, &q, &r)) {
        return false;
    }
    *quotient = q;
    *remainder = r;
    return true;
}
