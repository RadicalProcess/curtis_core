#pragma once

#include "IInputMix.h"

namespace rp::curtis
{
    class InputMix : public IInputMix
    {
    public:
        InputMix();

        ~InputMix() override = default;

        void setMix(float mix) override;

        void process(IBuffer& leftBuffer, IBuffer& rightBuffer) override;

    private:
        float mix_;
    };
}
