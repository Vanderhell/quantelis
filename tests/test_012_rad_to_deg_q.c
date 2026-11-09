#include <limits.h>
#include "pc_rad_to_deg_q.h"
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
int main(void)
{
    int32_t out = 19;
    CHECK(pc_rad_to_deg_q(0, &out) && out == 0);
    CHECK(pc_rad_to_deg_q(102944, &out) && out == 5898257);
    CHECK(pc_rad_to_deg_q(-102944, &out) && out == -5898257);
    CHECK(pc_rad_to_deg_q(205887, &out));
    CHECK(pc_rad_to_deg_q(-205887, &out));
    out = 19;
    CHECK(!pc_rad_to_deg_q(INT32_MAX, &out) && out == 19);
    CHECK(!pc_rad_to_deg_q(INT32_MIN, &out) && out == 19);
    CHECK(!pc_rad_to_deg_q(37500000, &out) && out == 19);
    CHECK(!pc_rad_to_deg_q(1, 0));
    return 0;
}
