#include "RandomRange.h"
#include <cstdlib>

namespace rp::curtis
{
    RandomRangeFloat::RandomRangeFloat(float min, float max)
    : min_(min)
    , max_(max)
    , difference_(max_ - min_)
    {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    void RandomRangeFloat::setMin(float value)
    {
        if(value > max_)
            value = min_;
        min_ = value;
        difference_ = max_ - min_;
    }

    void RandomRangeFloat::setMax(float value)
    {
        if(value < min_)
            value = max_;
        max_ = value;
        difference_ = max_ - min_;
    }

    float RandomRangeFloat::getValue() const
    {
        return min_ + difference_ * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    RandomRangeSizeT::RandomRangeSizeT(size_t min, size_t max)
    : min_(min)
    , max_(max)
    , difference_(max_ - min_)
    {}

    void RandomRangeSizeT::setMin(size_t value)
    {
        if(value > max_)
            value = max_;
        min_ = value;
        difference_ = max_ - min_;
    }

    void RandomRangeSizeT::setMax(size_t value)
    {
        if(value < min_)
            value = min_;
        max_ = value;
        difference_ = max_ - min_;
    }

    size_t RandomRangeSizeT::getValue() const
    {
        if(difference_ == 0)
            return min_;
        return min_ + static_cast<size_t>(rand()) % difference_;
    }
}
