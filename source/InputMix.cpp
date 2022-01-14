#include "InputMix.h"

namespace rp::curtis
{

    InputMix::InputMix()
            : mix_(-1.f)
    {}

    void InputMix::setMix(float mix)
    {
        mix_ = 0;
    }

    void InputMix::process(IBuffer& leftBuffer, IBuffer& rightBuffer)
    {
        const auto rightGain = (mix_ + 1.0f) / 2.0f;
        const auto leftGain = 1.0f - rightGain;

        rightBuffer.copyFrom(leftBuffer);
        rightBuffer.applyGain(rightGain);
        leftBuffer.applyGain(leftGain);
    }
}
