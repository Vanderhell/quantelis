#include "pc_roll_pitch_from_accel_q.h"
#include <stddef.h>
#include <stdint.h>
#define ONE INT32_C(1073741824)
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
int main(void)
{
    int32_t v[3] = { 0, 0, ONE }, r = 71, p = 72;
    uint32_t seed = 1385u;
    CHECK(!pc_roll_pitch_from_accel_q(NULL, &r, &p));
    CHECK(!pc_roll_pitch_from_accel_q(v, NULL, &p));
    CHECK(!pc_roll_pitch_from_accel_q(v, &r, NULL));
    CHECK(pc_roll_pitch_from_accel_q(v, &r, &p) && r == 0 && p == 0);
    v[1] = ONE; v[2] = 0;
    CHECK(pc_roll_pitch_from_accel_q(v, &r, &p) &&
          r >= INT32_C(1073741820) && r <= INT32_C(1073741828) && p == 0);
    v[1] = 0; v[2] = -ONE;
    CHECK(pc_roll_pitch_from_accel_q(v, &r, &p) && r == INT32_MIN && p == 0);
    v[0] = ONE; v[2] = 0;
    CHECK(pc_roll_pitch_from_accel_q(v, &r, &p) && r == 0 && p == -INT32_C(1073741824));
    v[0] = -ONE;
    CHECK(pc_roll_pitch_from_accel_q(v, &r, &p) && r == 0 && p == INT32_C(1073741824));
    v[0] = v[1] = v[2] = 0; r = 71; p = 72;
    CHECK(!pc_roll_pitch_from_accel_q(v, &r, &p) && r == 71 && p == 72);
    v[0] = ONE + 1;
    CHECK(!pc_roll_pitch_from_accel_q(v, &r, &p) && r == 71 && p == 72);
    for (unsigned i = 0; i < 10000; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
            v[j] = (int32_t)((int64_t)(seed % UINT32_C(2147483649)) - ONE);
        }
        if (!(v[0] | v[1] | v[2])) v[2] = 1;
        CHECK(pc_roll_pitch_from_accel_q(v, &r, &p));
        CHECK(p >= -INT32_C(1073741824) && p <= INT32_C(1073741824));
        CHECK(r >= INT32_MIN && r <= INT32_MAX);
    }
    return 0;
}
