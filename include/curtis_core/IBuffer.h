#pragma once

#include <memory>

namespace rp::curtis
{
    class IBuffer
    {
    public:
        virtual ~IBuffer() = default;

        virtual void copyFrom(const IBuffer& buffer) = 0;

        virtual size_t size() const = 0;

        virtual const float* get() const = 0;

        virtual bool owned() const = 0;

        virtual void clear() = 0;

        virtual void append(const IBuffer& buffer) = 0;

        virtual void push(float value) = 0;

        virtual float getLast() const = 0;
    };

    using BufferPtr = std::unique_ptr<IBuffer>;
}
