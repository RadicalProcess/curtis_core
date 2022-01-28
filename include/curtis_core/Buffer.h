#pragma once

#include <cstdlib>

#include "IBuffer.h"

namespace rp::curtis
{
    class Buffer : public IBuffer
    {
    public:
        Buffer(size_t capacity, bool fill = false);

        Buffer(float* buffer, size_t size);

        ~Buffer() override;

        void copyFrom(const IBuffer& buffer) override;

        size_t size() const override;

        bool owned() const override;

        void clear() override;

        void push(float value) override;

        const float* getReadPtr() const override;

        float* getWritePtr() override;

        float getLast() const override;

        bool full() const override;

        void applyGain(float gain) override;

    private:
        float* data_;
        size_t size_;
        const size_t capacity_;
        const bool owned_;
    };
}
