#include <limits.h>
#include "pc_radps_to_rpm_q.h"
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
int main(void){int32_t out=9;CHECK(pc_radps_to_rpm_q(0,&out)&&out==0);CHECK(pc_radps_to_rpm_q(411775,&out));CHECK(pc_radps_to_rpm_q(-411775,&out));out=19;CHECK(!pc_radps_to_rpm_q(INT32_MAX,&out)&&out==19);CHECK(!pc_radps_to_rpm_q(INT32_MIN,&out)&&out==19);CHECK(!pc_radps_to_rpm_q(1,0));return 0;}
