#include <assert.h>
#undef assert
#define assert(condition) do { if (!(condition)) return __LINE__; } while (0)
#include <stdint.h>
#include "pc_voltage_divider_q.h"
int main(void){uint32_t q=77;
 assert(pc_voltage_divider_q(65536,1000,1000,&q)&&q==32768);
 assert(pc_voltage_divider_q(UINT32_MAX,0,UINT32_MAX,&q)&&q==UINT32_MAX);
 assert(pc_voltage_divider_q(UINT32_MAX,UINT32_MAX,0,&q)&&q==0);
 assert(pc_voltage_divider_q(0,0,1,&q)&&q==0);
 q=77;assert(!pc_voltage_divider_q(UINT32_MAX,0,0,&q)&&q==77);
 assert(!pc_voltage_divider_q(1,1,1,0));return 0;}
