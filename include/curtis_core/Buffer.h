#pragma once

#include <cstdlib>

namespace rp::curtis
{
    class Buffer
    {
    public:
        Buffer(float* buffer, size_t size);

    private:
        float* const buffer_;
        const size_t size_;
    };
}
