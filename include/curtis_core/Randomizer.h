#pragma once

#include "IRandomizer.h"

namespace rp::curtis
{
    class Randomizer : public IRandomizer
    {
    public:
        Randomizer();

        void setRange(size_t range) override;

        size_t getValue() const override;
    private:
        size_t range_;
    };
}
