#ifndef PC_BILINEAR_INTERP_Q_H
#define PC_BILINEAR_INTERP_Q_H

#include <stdbool.h>
#include <stdint.h>

/* Single-round bilinear interpolation of signed-Q15 corners. fx/fy are
 * unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even. */
bool pc_bilinear_interp_q(int16_t v00_q15, int16_t v10_q15,
                          int16_t v01_q15, int16_t v11_q15,
                          uint32_t fx_q0_16, uint32_t fy_q0_16,
                          int16_t *value_q15);

#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_bilinear_interp_q
#define pc_bilinear_interp_q pc_bilinear_interp_q
#endif
#ifndef pc_bilinear_interp_q
#define pc_bilinear_interp_q pc_bilinear_interp_q
#endif
#ifndef PC_BILINEAR_INTERP_Q_H
#define PC_BILINEAR_INTERP_Q_H PC_BILINEAR_INTERP_Q_H
#endif

