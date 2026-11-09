#include "pc_packet_loss_rate_q.h"
#include <stddef.h>

bool pc_packet_loss_rate_q(uint32_t lost_packets, uint32_t sent_packets,
                           unsigned fractional_bits, uint32_t *rate_q)
{
    uint64_t scaled, quotient, remainder;
    if (rate_q == NULL || sent_packets == 0u || lost_packets > sent_packets ||
        fractional_bits > 31u) return false;
    scaled = (uint64_t)lost_packets << fractional_bits;
    quotient = scaled / sent_packets;
    remainder = scaled % sent_packets;
    if (remainder > (uint64_t)sent_packets - remainder ||
        (remainder == (uint64_t)sent_packets - remainder && (quotient & 1u) != 0u)) {
        ++quotient;
    }
    *rate_q = (uint32_t)quotient;
    return true;
}
