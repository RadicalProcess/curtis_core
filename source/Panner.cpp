#include "Panner.h"
#include <cmath>

namespace rp::curtis
{
    Panner::Panner()
    : position_(0.0f)
    {}

    void Panner::set(float position)
    {
        position_ = position;
    }

    void Panner::process(IBuffer& inputLeft, IBuffer& right)
    {
        const auto normalized = (position_ + 1.0f)  / 2.0f;
        const auto leftGain = std::cosf(normalized * static_cast<float>(M_PI_2));
        const auto rightGain =  std::cosf((1.0f-normalized) * static_cast<float>(M_PI_2));
        right.copyFrom(inputLeft);
        inputLeft.applyGain(leftGain);
        right.applyGain(rightGain);
    }
}
