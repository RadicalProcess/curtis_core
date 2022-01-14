#pragma once

#include <memory>
#include "IStereoProcessor.h"

namespace rp::curtis
{
    class IInputMixParameter
    {
    public:
        virtual ~IInputMixParameter() = default;

        virtual void setMix(float mix) = 0;
    };

    class IInputMix : public IInputMixParameter,
                      public IStereoProcessor
    {
    public:
        virtual ~IInputMix() = default;
    };

    using InputMixPtr = std::unique_ptr<IInputMix>;
}
