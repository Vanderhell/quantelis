#ifndef PC_VOLTAGE_DIVIDER_Q_H
#define PC_VOLTAGE_DIVIDER_Q_H
#include <stdbool.h>
#include <stdint.h>
bool pc_voltage_divider_q(uint32_t input_q16, uint32_t resistance_top,
                          uint32_t resistance_bottom, uint32_t *output_q16);
#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_voltage_divider_q
#define pc_voltage_divider_q pc_voltage_divider_q
#endif
#ifndef pc_voltage_divider_q
#define pc_voltage_divider_q pc_voltage_divider_q
#endif
#ifndef PC_VOLTAGE_DIVIDER_Q_H
#define PC_VOLTAGE_DIVIDER_Q_H PC_VOLTAGE_DIVIDER_Q_H
#endif

