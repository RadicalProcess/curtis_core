#pragma once

#include "IReadBuffer.h"
#include "IBuffer.h"
#include "Factory.h"

namespace rp::curtis
{
    class ReadBuffer : public IReadBuffer
    {
    public:
        ReadBuffer(size_t maxBufferSize, const IFactory& factory = Factory());

        ~ReadBuffer() override = default;

        void updateBuffer(const IBuffer& buffer) override;

        bool advancePlayHead(float advancement) override;

        float getSample() const override;

        float getPhase() const override;

    private:
        BufferPtr playBuffer_;

        float playHead_;
    };
}
