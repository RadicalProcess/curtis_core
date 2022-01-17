#pragma once

#include <memory>
#include "IBuffer.h"
#include "IStereoProcessor.h"

namespace rp::curtis
{
    class IPannerParameter
    {
    public:
        virtual ~IPannerParameter() = default;

        virtual void setStartLeft(float position) = 0;

        virtual void setStartRight(float position) = 0;

        virtual void setEndLeft(float position) = 0;

        virtual void setEndRight(float position) = 0;
    };


    class IPanner : public IPannerParameter
    {
    public:
        ~IPanner() override= default;

        virtual void update() = 0;

        virtual std::pair<float, float> getGainAt(float phase) const = 0;
    };

    using PannerPtr = std::unique_ptr<IPanner>;
}

