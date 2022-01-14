#pragma once

#include <memory>
#include "IBuffer.h"

namespace rp::curtis
{
    class IPanner
    {
    public:
        virtual ~IPanner() = default;

        virtual void set(float position) = 0;

        virtual void process(IBuffer& inletLeft, IBuffer& right) = 0;
    };

    using PannerPtr = std::unique_ptr<IPanner>;
}
