#include <assert.h>
#undef assert
#define assert(condition) do { if (!(condition)) return __LINE__; } while (0)
#include <stdint.h>
#include <limits.h>
#include "pc_deg_to_rad_q.h"
int main(void) {
    int32_t out = 17;
    assert(pc_deg_to_rad_q(0, &out) && out == 0);
    assert(pc_deg_to_rad_q(90 * 65536, &out) && out == 102944);
    assert(pc_deg_to_rad_q(-90 * 65536, &out) && out == -102944);
    assert(pc_deg_to_rad_q(180 * 65536, &out) && out == 205887);
    assert(pc_deg_to_rad_q(INT32_MIN, &out));
    assert(pc_deg_to_rad_q(INT32_MAX, &out));
    out = 123;
    assert(!pc_deg_to_rad_q(1, 0) && out == 123);
    return 0;
}
