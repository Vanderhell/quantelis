#include "pc_packet_loss_rate_q.h"
#include "pc_q_div_round_even.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* Independent shift/divide reference; does not multiply lost by 2^fractional_bits. */
static uint32_t reference(uint32_t lost, uint32_t sent, unsigned bits)
{
    uint64_t remainder = lost;
    uint64_t quotient = 0u;
    unsigned i;
    if (lost == sent) return UINT32_C(1) << bits;
    for (i = 0u; i < bits; ++i) {
        remainder *= 2u;
        quotient *= 2u;
        if (remainder >= sent) {
            remainder -= sent;
            ++quotient;
        }
    }
    if (remainder > (uint64_t)sent - remainder ||
        (remainder == (uint64_t)sent - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    return (uint32_t)quotient;
}

static int check(uint32_t lost, uint32_t sent, unsigned bits)
{
    uint32_t actual = 0u;
    uint32_t expected = reference(lost, sent, bits);
    if (!pc_packet_loss_rate_q(lost, sent, bits, &actual) || actual != expected) {
        (void)fprintf(stderr, "lost=%u sent=%u bits=%u expected=%u actual=%u\n",
                      (unsigned)lost, (unsigned)sent, bits,
                      (unsigned)expected, (unsigned)actual);
        return 1;
    }
    return 0;
}

static int check_generic_overlap(uint32_t lost, uint32_t sent, unsigned bits)
{
    uint32_t actual = 0u;
    int32_t generic = -1;
    if (!pc_packet_loss_rate_q(lost, sent, bits, &actual) ||
        !pc_q_div_round_even((int32_t)lost, (int32_t)sent, bits, &generic) ||
        actual != (uint32_t)generic) return 1;
    return 0;
}

int main(void)
{
    uint32_t sent, lost, seed = UINT32_C(0x3242);
    unsigned bits, i;
    for (sent = 1u; sent <= 255u; ++sent) {
        for (lost = 0u; lost <= sent; ++lost) {
            for (bits = 0u; bits <= 31u; ++bits) {
                if (check(lost, sent, bits)) return 1;
                if (bits <= 30u && check_generic_overlap(lost, sent, bits)) return 1;
            }
        }
    }
    for (i = 0u; i < 100000u; ++i) {
        uint32_t candidate_sent, candidate_lost;
        unsigned candidate_bits;
        seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
        candidate_sent = seed == 0u ? UINT32_MAX : seed;
        seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
        candidate_lost = seed % (candidate_sent + (candidate_sent != UINT32_MAX));
        if (candidate_lost > candidate_sent) candidate_lost = candidate_sent;
        candidate_bits = (seed >> 24) & 31u;
        if (check(candidate_lost, candidate_sent, candidate_bits)) return 1;
    }
    if (check(UINT32_MAX, UINT32_MAX, 31u) || check(UINT32_MAX - 1u, UINT32_MAX, 31u) ||
        check(0u, 1u, 31u)) return 1;
    {
        uint32_t unchanged = 77u;
        if (pc_packet_loss_rate_q(0u, 0u, 16u, &unchanged) || unchanged != 77u) return 1;
        if (pc_packet_loss_rate_q(2u, 1u, 16u, &unchanged) || unchanged != 77u) return 1;
        if (pc_packet_loss_rate_q(0u, 1u, 32u, &unchanged) || unchanged != 77u) return 1;
        if (pc_packet_loss_rate_q(0u, 1u, 16u, NULL)) return 1;
    }
    return 0;
}
