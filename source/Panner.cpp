#include "Panner.h"
#include <cmath>

namespace rp::curtis
{
    float rangedRandom(float min, float max)
    {
        return min + (rand() / ( static_cast<float>(RAND_MAX) / (max-min))) ;
    }

    Panner::Panner()
    : startLeft_(0.0f)
    , startRight_(0.0f)
    , endLeft_(0.0f)
    , endRight_(0.0f)
    , start_(0.0f)
    , end_(0.0f)
    {}

    void Panner::setStartA(float position)
    {
        startLeft_ = position;
    }

    void Panner::setStartB(float position)
    {
        startRight_ = position;
    }

    void Panner::setEndA(float position)
    {
        endLeft_ = position;
    }

    void Panner::setEndB(float position)
    {
        endRight_ = position;
    }

    void Panner::update()
    {
        start_ = rangedRandom(startLeft_, startRight_);
        end_ = rangedRandom(endLeft_, endRight_);
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
