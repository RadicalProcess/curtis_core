#include "Panner.h"
#include <cmath>

namespace rp::curtis
{
    float rangedRandom(float a, float b)
    {
        const auto distance = std::fabs(b-a);
        return std::fmin(a, b) + rand() / static_cast<float>(RAND_MAX) * distance;
    }

    Panner::Panner()
    : startA_(0.0f)
    , startB_(0.0f)
    , endA_(0.0f)
    , endB_(0.0f)
    , start_(0.0f)
    , end_(0.0f)
    {}

    void Panner::setStartA(float position)
    {
        startA_ = position;
    }

    void Panner::setStartB(float position)
    {
        startB_ = position;
    }

    void Panner::setEndA(float position)
    {
        endA_ = position;
    }

    void Panner::setEndB(float position)
    {
        endB_ = position;
    }

    void Panner::update()
    {
        start_ = rangedRandom(startA_, startB_);
        end_ = rangedRandom(endA_, endB_);
    }

    std::tuple<float, float, float> Panner::getGainAt(float phase) const
    {
        auto position = start_ + (end_ - start_) * phase;
        const auto normalized = (position + 1.0f)  / 2.0f;
        return { std::cosf(normalized * static_cast<float>(M_PI_2)),
                 std::cosf((1.0f-normalized) * static_cast<float>(M_PI_2)),
                 position };
    }
}
