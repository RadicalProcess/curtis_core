#include "Randomizer.h"

#include <cmath>

namespace rp::curtis
{
    Randomizer::Randomizer()
    : range_(0)
    {
    }

    void Randomizer::setRange(size_t range)
    {
        range_ = range;
    }

    size_t Randomizer::getValue() const
    {
        return range_ == 0 ? 0 : rand() % static_cast<int>(range_);
    }
}
