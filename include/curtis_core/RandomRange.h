#pragma once

#include "IRandomRange.h"

namespace rp::curtis
{
    class RandomRangeFloat : public IRandomRange<float>
    {
    public:
        RandomRangeFloat(float min, float max);

        ~RandomRangeFloat() override = default;

        void setMin(float value) override;

        void setMax(float value) override;

        float getValue() const override;

    protected:
        float min_;
        float max_;
        float difference_;
    };

    class RandomRangeSizeT : public IRandomRange<size_t>
    {
    public:
        RandomRangeSizeT(size_t min, size_t max);

        ~RandomRangeSizeT() override = default;

        void setMin(size_t value) override;

        void setMax(size_t value) override;

        size_t getValue() const override;

    protected:
        size_t min_;
        size_t max_;
        size_t difference_;
    };
}
