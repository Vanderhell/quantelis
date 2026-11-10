#include "pc_strain_ratio_q.h"
#include <stdint.h>
int main(void){int32_t out=77;if(!pc_strain_ratio_q(120,120,131072,&out)||out!=500)return 1;if(!pc_strain_ratio_q(1,2000,65536,&out)||out!=0)return 2;if(!pc_strain_ratio_q(3,2000,65536,&out)||out!=2)return 3;if(!pc_strain_ratio_q(-3,2000,65536,&out)||out!=-2)return 4;out=77;if(pc_strain_ratio_q(1,0,1,&out)||out!=77)return 5;return 0;}
