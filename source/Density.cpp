#include "Density.h"

namespace rp::curtis
{
    Density::Density()
    : percentage_(100)
    , state_(true)
    {}

    void Density::set(int percentage)
    {
        percentage_ = percentage;
    }

    void Density::roll()
    {
        state_ = rand() % 100 < percentage_;
    }

    bool Density::get() const
    {
        return state_;
    }
}
