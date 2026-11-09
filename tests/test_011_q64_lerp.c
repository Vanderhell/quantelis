#include <stdint.h>
#include <limits.h>
#include "pc_q64_lerp.h"
#define CHECK(x) do { if (!(x)) return __LINE__; } while (0)
int main(void){int64_t out=123;
 CHECK(pc_q64_lerp(1,2,1,2,&out)&&out==2);
 CHECK(pc_q64_lerp(0,1,1,2,&out)&&out==0);
 CHECK(pc_q64_lerp(-2,-1,1,2,&out)&&out==-2);
 CHECK(pc_q64_lerp(-1,0,1,2,&out)&&out==0);
 CHECK(pc_q64_lerp(INT64_MIN,INT64_MAX,1,2,&out)&&out==0);
 CHECK(pc_q64_lerp(INT64_MAX,INT64_MIN,1,2,&out)&&out==0);
 CHECK(pc_q64_lerp(INT64_MIN,INT64_MAX,0,UINT64_MAX,&out)&&out==INT64_MIN);
 CHECK(pc_q64_lerp(INT64_MIN,INT64_MAX,UINT64_MAX,UINT64_MAX,&out)&&out==INT64_MAX);
 CHECK(pc_q64_lerp(INT64_MIN,INT64_MAX,1,UINT64_MAX,&out)&&out==INT64_MIN+1);
 out=77; CHECK(!pc_q64_lerp(1,2,1,0,&out)&&out==77);
 CHECK(!pc_q64_lerp(1,2,2,1,&out)&&out==77);
 CHECK(!pc_q64_lerp(1,2,0,1,0));
 return 0;}
