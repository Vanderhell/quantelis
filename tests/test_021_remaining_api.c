#include "pc_bearing2_q.h"
#include "pc_constant_velocity_predict_q.h"
#include "pc_decay_factor_from_halflife_q.h"
#include "pc_direction_quantize8_q.h"
#include "pc_direction_quantize16_q.h"
#include "pc_q_hypot2.h"
#include "pc_q_hypot3.h"
#include "pc_time_to_target_q.h"
#include "pc_ratio_round_even_u32.h"
#include "pc_time_ratio_internal.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define CHECK(x) do { if (!(x)) return __LINE__; } while (0)

static uint32_t rng = UINT32_C(0x7A61D39B);
static int32_t signed_from_bits(uint32_t bits)
{
    return bits <= (uint32_t)INT32_MAX ? (int32_t)bits : (int32_t)((int64_t)bits - INT64_C(4294967296));
}

static uint32_t next_u32(void)
{
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}

static uint32_t reference_turns(double radians)
{
    double turns = radians / (2.0 * 3.14159265358979323846);
    if (turns < 0.0) turns += 1.0;
    return (uint32_t)(uint64_t)floor(turns * 4294967296.0 + 0.5);
}

static uint32_t phase_error(uint32_t got, uint32_t ref)
{
    uint32_t err = got > ref ? got - ref : ref - got;
    return err > UINT32_MAX / 2u ? UINT32_MAX - err + 1u : err;
}

static uint32_t round_even_u32_reference(uint32_t n, uint32_t d)
{
    uint32_t q = n / d, r = n % d;
    if ((uint64_t)r * 2u > d || ((uint64_t)r * 2u == d && (q & 1u))) ++q;
    return q;
}

int main(void)
{
    static const int32_t edge[] = {INT32_MIN, INT32_MIN + 1, -1, 0, 1, INT32_MAX - 1, INT32_MAX};
    uint32_t i;
    int32_t out32;
    uint32_t outu;
    uint8_t out8;
    uint32_t max_bearing_error = 0u;

    outu = 123u; CHECK(!pc_decay_factor_from_halflife_q(0u, &outu) && outu == 123u);
    CHECK(!pc_decay_factor_from_halflife_q(1u, NULL));
    for (i = 1u; i < 100000u; ++i) {
        double exact = exp(-0.69314718055994530942 / (double)i) * 65536.0;
        uint32_t expected = (uint32_t)floor(exact + 0.5);
        CHECK(pc_decay_factor_from_halflife_q(i, &outu));
        CHECK(outu == expected);
    }
    CHECK(pc_decay_factor_from_halflife_q(UINT32_MAX, &outu) && outu == 65536u);

    out8 = 99u; CHECK(!pc_direction_quantize8_q(0u, NULL) && out8 == 99u);
    CHECK(!pc_direction_quantize16_q(0u, NULL));
    for (i = 0u; i < 100000u; ++i) {
        uint32_t phase = next_u32();
        uint8_t e8 = (uint8_t)((((uint64_t)phase + UINT64_C(0x10000000)) >> 29) & 7u);
        uint8_t e16 = (uint8_t)((((uint64_t)phase + UINT64_C(0x08000000)) >> 28) & 15u);
        CHECK(pc_direction_quantize8_q(phase, &out8) && out8 == e8);
        CHECK(pc_direction_quantize16_q(phase, &out8) && out8 == e16);
    }

    out32 = 77; CHECK(!pc_q_hypot2(0, 0, NULL));
    CHECK(!pc_q_hypot3(0, 0, 0, NULL));
    for (i = 0u; i < 100000u; ++i) {
        int32_t x = signed_from_bits(next_u32()), y = signed_from_bits(next_u32()), z = signed_from_bits(next_u32());
        double e2 = floor(sqrt((double)x*x + (double)y*y) + 0.5);
        double e3 = floor(sqrt((double)x*x + (double)y*y + (double)z*z) + 0.5);
        if (e2 <= INT32_MAX) CHECK(pc_q_hypot2(x, y, &out32) && out32 == (int32_t)e2);
        else { out32=77; CHECK(!pc_q_hypot2(x, y, &out32) && out32 == 77); }
        if (e3 <= INT32_MAX) CHECK(pc_q_hypot3(x, y, z, &out32) && out32 == (int32_t)e3);
        else { out32=77; CHECK(!pc_q_hypot3(x, y, z, &out32) && out32 == 77); }
    }
    for (i = 0u; i < sizeof(edge)/sizeof(edge[0]); ++i) {
        unsigned j;
        for (j = 0u; j < sizeof(edge)/sizeof(edge[0]); ++j) {
            int64_t dx = (int64_t)edge[j] - edge[i];
            int64_t dy = (int64_t)edge[(i+j)%7u] - edge[i];
            uint32_t got;
            CHECK(pc_bearing2_q(edge[i], edge[i], edge[j], edge[(i+j)%7u], &got));
            if (dx == 0 && dy == 0) CHECK(got == 0u);
            else {
                uint32_t ref = reference_turns(atan2((double)dy, (double)dx));
                uint32_t err = phase_error(got, ref);
                if (err > max_bearing_error) max_bearing_error = err;
                CHECK(err <= 32u);
            }
        }
    }
    for (i = 0u; i < 100000u; ++i) {
        int32_t ox=signed_from_bits(next_u32()), oy=signed_from_bits(next_u32());
        int32_t tx=signed_from_bits(next_u32()), ty=signed_from_bits(next_u32());
        int64_t dx=(int64_t)tx-ox, dy=(int64_t)ty-oy;
        uint32_t got, ref;
        CHECK(pc_bearing2_q(ox, oy, tx, ty, &got));
        if (dx == 0 && dy == 0) CHECK(got == 0u);
        else { uint32_t err; ref=reference_turns(atan2((double)dy,(double)dx)); err=phase_error(got,ref); if(err>max_bearing_error)max_bearing_error=err; CHECK(err<=32u); }
    }

    {
        static const int32_t cx[4] = {1, 0, -1, 0};
        static const int32_t cy[4] = {0, 1, 0, -1};
        static const uint32_t cp[4] = {0u, UINT32_C(0x40000000), UINT32_C(0x80000000), UINT32_C(0xC0000000)};
        unsigned k;
        for (k=0u;k<4u;++k) { uint32_t got; CHECK(pc_bearing2_q(0,0,cx[k],cy[k],&got)); CHECK(phase_error(got,cp[k])<=32u); }
    }
    out32=123; CHECK(!pc_constant_velocity_predict_q(INT32_MAX, 1, UINT32_MAX, &out32) && out32==123);
    CHECK(!pc_constant_velocity_predict_q(0, 1, 1, NULL));
    for (i=0u; i<100000u; ++i) {
        int32_t p=signed_from_bits(next_u32()), v=signed_from_bits(next_u32()); uint32_t dt=next_u32();
        long double exact=(long double)p+(long double)v*(long double)dt/1000000.0L;
        long double rounded=roundl(exact);
        bool ok=rounded>=INT32_MIN && rounded<=INT32_MAX;
        out32=123;
        CHECK(pc_constant_velocity_predict_q(p,v,dt,&out32)==ok);
        if(ok) CHECK(out32==(int32_t)rounded); else CHECK(out32==123);
    }
    CHECK(pc_time_to_target_q(INT32_MIN, INT32_MAX, INT32_MAX, &((uint64_t){0})));
    {
        uint64_t t=999u;
        CHECK(!pc_time_to_target_q(INT32_MIN, INT32_MAX, 0, &t) && t==999u);
        CHECK(!pc_time_to_target_q(INT32_MIN, INT32_MAX, -1, &t) && t==999u);
        CHECK(pc_time_to_target_q(1,1,0,&t) && t==0u);
        for(i=0u;i<100000u;++i){
            int32_t p=signed_from_bits(next_u32()), target=signed_from_bits(next_u32()), v=signed_from_bits(next_u32());
            int64_t diff=(int64_t)target-p; bool valid=diff==0 || (v!=0 && ((diff<0)==(v<0)));
            CHECK(pc_time_to_target_q(p,target,v,&t)==valid);
            if(valid){uint64_t d=(uint64_t)(diff<0?-diff:diff), s=(uint64_t)(v<0?-(int64_t)v:v); uint64_t expected=diff==0?0u:(d*UINT64_C(1000000)+s-1u)/s; CHECK(t==expected);}
        }
    }
    outu=321u; CHECK(!pc_ratio_round_even_u32(1u,0u,&outu) && outu==321u);
    CHECK(!pc_ratio_round_even_u32(1u,1u,NULL));
    for(i=0u;i<100000u;++i){uint32_t n=next_u32(),d=next_u32(); if(d==0u)d=1u; CHECK(pc_ratio_round_even_u32(n,d,&outu)); CHECK(outu==round_even_u32_reference(n,d));}
    {
        uint64_t q=9u,r=8u;
        CHECK(!pc_time_ratio_mul_divmod_u64(1u,1u,0u,&q,&r) && q==9u && r==8u);
        CHECK(!pc_time_ratio_mul_divmod_u64(1u,1u,1u,NULL,&r) && r==8u);
        CHECK(!pc_time_ratio_mul_divmod_u64(1u,1u,1u,&q,NULL) && q==9u);
        for(i=0u;i<100000u;++i) {
            uint64_t a=((uint64_t)next_u32()<<32)|next_u32();
            uint64_t b=((uint64_t)next_u32()<<32)|next_u32();
            uint64_t d=((uint64_t)next_u32()<<32)|next_u32();
            bool expected_ok;
            if(d==0u)d=1u;
#if defined(__SIZEOF_INT128__)
            {
                __uint128_t product=(__uint128_t)a*(__uint128_t)b;
                __uint128_t expected_q=product/d;
                expected_ok=expected_q<=UINT64_MAX;
                q=9u;r=8u;
                CHECK(pc_time_ratio_mul_divmod_u64(a,b,d,&q,&r)==expected_ok);
                if(expected_ok) CHECK(q==(uint64_t)expected_q && r==(uint64_t)(product%d));
                else CHECK(q==9u && r==8u);
            }
#else
            a=next_u32(); b=next_u32(); d=(uint32_t)next_u32()+1u;
            {
                uint64_t product=a*b;
                expected_ok=true;
                CHECK(pc_time_ratio_mul_divmod_u64(a,b,d,&q,&r));
                CHECK(q==product/d && r==product%d);
            }
#endif
        }
    }
    printf("remaining API differential tests passed; bearing max error=%lu phase codes (1/2^32 turn)\n", (unsigned long)max_bearing_error);
    return 0;
}
