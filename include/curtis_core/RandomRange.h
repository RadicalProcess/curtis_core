#pragma once

#include "IRandomRange.h"

namespace rp::curtis
{
    class RandomRange : public IRandomRange
    {
    public:
        RandomRange(float a, float b);

        ~RandomRange() override = default;

        void setA(float value) override;

        void setB(float value) override;

        float getValue() const override;

    protected:
        float a_;
        float b_;
    };
}
