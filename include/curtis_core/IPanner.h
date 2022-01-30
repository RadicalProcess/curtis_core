#pragma once

#include <memory>
#include <tuple>
#include "IBuffer.h"
#include "IStereoProcessor.h"

namespace rp::curtis
{
    class IPanner
    {
    public:
        virtual ~IPanner() = default;

        virtual void update() = 0;

        virtual void setStartA(float position) = 0;

        virtual void setStartB(float position) = 0;

        virtual void setEndA(float position) = 0;

        virtual void setEndB(float position) = 0;

        virtual std::tuple<float, float, float> getGainAt(float phase) const = 0;
    };

    using PannerPtr = std::unique_ptr<IPanner>;
}

