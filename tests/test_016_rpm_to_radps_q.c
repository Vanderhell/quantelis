#include <limits.h>
#include "pc_rpm_to_radps_q.h"
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
int main(void){int32_t out=9;CHECK(pc_rpm_to_radps_q(0,&out)&&out==0);CHECK(pc_rpm_to_radps_q(60*65536,&out)&&out==411775);CHECK(pc_rpm_to_radps_q(-60*65536,&out)&&out==-411775);CHECK(pc_rpm_to_radps_q(INT32_MIN,&out));CHECK(pc_rpm_to_radps_q(INT32_MAX,&out));out=19;CHECK(!pc_rpm_to_radps_q(1,0)&&out==19);int32_t prev=INT32_MIN;for(int32_t v=-32768;v<=32767;++v){CHECK(pc_rpm_to_radps_q(v,&out));CHECK(out>=prev);prev=out;}return 0;}
