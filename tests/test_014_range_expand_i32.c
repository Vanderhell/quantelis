#include "pc_range_expand_i32.h"
#include <limits.h>
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
int main(void)
{
    int32_t lo = 0, hi = 0;
    CHECK(pc_range_expand_i32(2, 8, 3, &lo, &hi) && lo == -1 && hi == 11);
    lo = 99; hi = 77;
    CHECK(pc_range_expand_i32(2, 8, 0, &lo, &hi) && lo == 2 && hi == 8);
    lo = 99; hi = 77;
    CHECK(!pc_range_expand_i32(INT32_MIN, 0, 1, &lo, &hi) && lo == 99 && hi == 77);
    CHECK(!pc_range_expand_i32(0, INT32_MAX, 1, &lo, &hi) && lo == 99 && hi == 77);
    CHECK(!pc_range_expand_i32(8, 2, 1, &lo, &hi));
    CHECK(!pc_range_expand_i32(1, 2, 0, &lo, &lo));
    return 0;
}
