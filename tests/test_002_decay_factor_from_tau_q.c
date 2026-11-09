#include "pc_decay_factor_from_tau_q.h"
#include <assert.h>
#include <stdint.h>

int main(void)
{
    static const uint32_t tau[] = {1u, 2u, 3u, 4u, 8u, 131071u, 131072u};
    static const uint32_t expected[] = {24109u, 39750u, 46959u, 51039u,
                                        57835u, 65535u, 65536u};
    uint32_t output = UINT32_C(0xA5A5A5A5);
    unsigned i;
    for (i = 0u; i < sizeof(tau) / sizeof(tau[0]); ++i) {
        assert(pc_decay_factor_from_tau_q(tau[i], &output));
        assert(output == expected[i]);
    }
    assert(!pc_decay_factor_from_tau_q(0u, &output));
    assert(output == 65536u);
    assert(!pc_decay_factor_from_tau_q(1u, NULL));
    return 0;
}
