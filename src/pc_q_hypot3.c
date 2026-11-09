#include "pc_q_hypot3.h"
#include <stddef.h>

bool rm_q_hypot3(int32_t x,int32_t y,int32_t z,int32_t*out){uint64_t ax=x<0?(uint64_t)(-(int64_t)x):(uint64_t)x;uint64_t ay=y<0?(uint64_t)(-(int64_t)y):(uint64_t)y;uint64_t az=z<0?(uint64_t)(-(int64_t)z):(uint64_t)z;uint64_t target=ax*ax+ay*ay+az*az,lo=0,hi=UINT64_C(4294967296),q,delta;if(!out)return false;while(lo+1<hi){uint64_t m=lo+(hi-lo)/2;if(m*m<=target)lo=m;else hi=m;}q=lo;delta=target-q*q;if(4*delta>4*q+1||(4*delta==4*q+1&&(q&1u)))++q;if(q>INT32_MAX)return false;*out=(int32_t)q;return true;}
