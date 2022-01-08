#pragma once

#include "Buffer.h"

namespace rp::curtis
{
    class IProcessor
    {
    public:
        virtual ~IProcessor() = default;

        virtual void process(Buffer& buffer) = 0;
    };

    using ProcessorPtr = std::unique_ptr<IProcessor>;
}
