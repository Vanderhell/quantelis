#ifndef PC_STRAIN_RATIO_Q_H
#define PC_STRAIN_RATIO_Q_H
#include <stdbool.h>
#include <stdint.h>

/* Convert a signed resistance change to strain using GF = (deltaR/R)/strain.
 * Inputs: delta resistance in milliohms, nominal resistance in ohms,
 * gauge factor UQ16.16. Output is signed microstrain, nearest-even. */
bool pc_strain_ratio_q(int32_t delta_resistance_milliohm,
                       uint16_t nominal_resistance_ohm,
                       uint32_t gauge_factor_q16_16,
                       int32_t *strain_microstrain);
#endif
