#pragma once

#include "Buffer.h"

namespace rp::curtis
{
    class IStereoProcessor
    {
    public:
        virtual ~IStereoProcessor() = default;

        virtual void process(IBuffer& leftBuffer, IBuffer& rightBuffer) = 0;
    };

    using StereoProcessorPtr = std::unique_ptr<IStereoProcessor>;
}
