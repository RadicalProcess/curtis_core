#pragma once

#include <cstdlib>

#include "IBuffer.h"

namespace rp::curtis
{
    class Buffer : public IBuffer
    {
    public:
        Buffer();

        Buffer(size_t capacity);

        Buffer(float* buffer, size_t size);

        ~Buffer();

        void copyFrom(const IBuffer& buffer) override;

        size_t size() const override;

        bool owned() const override;

        void clear() override;

        void append(const IBuffer& buffer) override;

        void push(float value) override;

        const float* getReadPtr() const override;

        float* getWritePtr() override;

        float getLast() const override;

    private:
        float* data_;
        size_t size_;
        const size_t capacity_;
        const bool owned_;
    };
}
