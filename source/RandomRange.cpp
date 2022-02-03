#include "RandomRange.h"
#include <cstdlib>
#include <cmath>

namespace rp::curtis
{
    RandomRange::RandomRange(float a, float b)
    : a_(a)
    , b_(b)
    {
    }

    void RandomRange::setA(float value)
    {
        a_ = value;
    }

    void RandomRange::setB(float value)
    {
        b_ = value;
    }

    float RandomRange::getValue() const
    {
        const auto difference =  std::fabs(b_ - a_);
        return (a_ <= b_ ? a_ : b_) + difference * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
}
