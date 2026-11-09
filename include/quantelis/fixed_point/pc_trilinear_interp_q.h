#ifndef PC_TRILINEAR_INTERP_Q_H
#define PC_TRILINEAR_INTERP_Q_H

#include <stdbool.h>
#include <stdint.h>

/* Single-round trilinear interpolation of signed-Q15 corners. fx/fy/fz are
 * unsigned Q0.16 in [0,65536]; output rounds nearest, ties-to-even. */
bool pc_trilinear_interp_q(
    int16_t v000_q15, int16_t v100_q15, int16_t v010_q15, int16_t v110_q15,
    int16_t v001_q15, int16_t v101_q15, int16_t v011_q15, int16_t v111_q15,
    uint32_t fx_q0_16, uint32_t fy_q0_16, uint32_t fz_q0_16,
    int16_t *value_q15);

#endif

/* Canonical facade; the legacy implementation and contract are preserved. */
#ifndef pc_trilinear_interp_q
#define pc_trilinear_interp_q pc_trilinear_interp_q
#endif
#ifndef pc_trilinear_interp_q
#define pc_trilinear_interp_q pc_trilinear_interp_q
#endif
#ifndef PC_TRILINEAR_INTERP_Q_H
#define PC_TRILINEAR_INTERP_Q_H PC_TRILINEAR_INTERP_Q_H
#endif

