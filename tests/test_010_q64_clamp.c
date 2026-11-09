#include <stdint.h>
#include <limits.h>
#include "pc_q64_clamp.h"
#define CHECK(x) do { if (!(x)) return __LINE__; } while (0)
int main(void){int64_t out=99;
 CHECK(pc_q64_clamp(INT64_MIN,INT64_MIN,INT64_MAX,&out)&&out==INT64_MIN);
 CHECK(pc_q64_clamp(INT64_MAX,INT64_MIN,INT64_MAX,&out)&&out==INT64_MAX);
 CHECK(pc_q64_clamp(5,5,9,&out)&&out==5);
 CHECK(pc_q64_clamp(9,5,9,&out)&&out==9);
 CHECK(pc_q64_clamp(4,5,9,&out)&&out==5);
 CHECK(pc_q64_clamp(10,5,9,&out)&&out==9);
 out=123; CHECK(!pc_q64_clamp(1,2,1,&out)&&out==123);
 CHECK(!pc_q64_clamp(1,0,1,0));
 out=77; CHECK(!pc_q64_clamp(1,2,1,0)&&out==77);
 out=3; CHECK(pc_q64_clamp(8,0,10,&out)&&out==8);
 out=8; CHECK(pc_q64_clamp(out,0,10,&out)&&out==8);
 return 0;}
