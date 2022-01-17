#pragma once

#include <memory>
#include "IStereoProcessor.h"

namespace rp::curtis
{
    class IInputMix : public IStereoProcessor
    {
    public:
        virtual void setMix(float mix) = 0;

        virtual ~IInputMix() = default;
    };

    using InputMixPtr = std::unique_ptr<IInputMix>;
}
