#pragma once

#include <memory>
#include "IBuffer.h"

namespace rp::curtis
{
    class IReadBuffer
    {
    public:
        virtual ~IReadBuffer() = default;

        virtual void updateBuffer(const IBuffer& buffer) = 0;

        virtual bool advancePlayHead(float advancement) = 0;

        virtual float getSample() const = 0;

        virtual float getPhase() const = 0;
    };

    using ReadBufferPtr = std::unique_ptr<IReadBuffer>;
}
