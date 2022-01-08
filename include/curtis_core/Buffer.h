#pragma once

#include <cstdlib>

#include "IBuffer.h"

namespace rp::curtis
{
    class Buffer : public IBuffer
    {
    public:
        Buffer(size_t capacity);

        Buffer(float* buffer, size_t size);

        ~Buffer();

        size_t size() const override;

        bool owned() const override;

        void clean() override;

        void append(const IBuffer& buffer) override;

        const float* get() const override;

    private:
        float* buffer_;
        size_t size_;
        const size_t capacity_;
        const bool owned_;
    };
}
