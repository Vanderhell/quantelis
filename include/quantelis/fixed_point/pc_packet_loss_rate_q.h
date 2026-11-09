#ifndef PC_PC_PACKET_LOSS_RATE_Q_H
#define PC_PC_PACKET_LOSS_RATE_Q_H
#include <stdbool.h>
#include <stdint.h>
/* Compute round-nearest-even((lost_packets * 2^fractional_bits) / sent_packets).
 * Requires sent_packets > 0, lost_packets <= sent_packets, fractional_bits <= 31,
 * and non-null rate_q. Failure leaves *rate_q unchanged. */
bool pc_packet_loss_rate_q(uint32_t lost_packets, uint32_t sent_packets,
                           unsigned fractional_bits, uint32_t *rate_q);
#endif
