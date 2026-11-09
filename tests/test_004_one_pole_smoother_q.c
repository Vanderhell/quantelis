#include "pc_one_pole_smoother_q.h"
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#define CHECK(c) do { if (!(c)) return __LINE__; } while (0)
static uint32_t next(uint32_t *s){*s=*s*1664525u+1013904223u;return *s;}
int main(void){int32_t s=3;CHECK(pc_one_pole_smoother_q(10,0,&s)&&s==3);CHECK(pc_one_pole_smoother_q(10,65536,&s)&&s==10);s=0;CHECK(pc_one_pole_smoother_q(10,32768,&s)&&s==5);CHECK(pc_one_pole_smoother_q(10,32768,&s)&&s==7);s=0;CHECK(pc_one_pole_smoother_q(1,1,&s)&&s==0);s=INT32_MIN;CHECK(pc_one_pole_smoother_q(INT32_MAX,65536,&s)&&s==INT32_MAX);s=INT32_MAX;CHECK(pc_one_pole_smoother_q(INT32_MIN,65536,&s)&&s==INT32_MIN);s=7;CHECK(!pc_one_pole_smoother_q(9,65537,&s)&&s==7);CHECK(!pc_one_pole_smoother_q(9,1,NULL));{uint32_t seed=408u;for(uint32_t i=0;i<1000000u;++i){int32_t x=(int32_t)next(&seed);uint32_t a=next(&seed)%65537u;int64_t p=((int64_t)x-s)*a;uint64_t m=p<0?(uint64_t)(-p):(uint64_t)p,q=m/65536u,r=m%65536u;if(r>32768u||(r==32768u&&(q&1u)))++q;int32_t expected=(int32_t)((int64_t)s+(p<0?-(int64_t)q:(int64_t)q));CHECK(pc_one_pole_smoother_q(x,a,&s)&&s==expected);}}{int32_t x=INT32_MIN;for(uint32_t i=0;i<100000u;++i)CHECK(pc_one_pole_smoother_q(INT32_MAX,32768u,&x));CHECK(x>INT32_MIN&&x<INT32_MAX);}return 0;}
