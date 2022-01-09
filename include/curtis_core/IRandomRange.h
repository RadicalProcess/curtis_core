#pragma once

#include <memory>

namespace rp::curtis
{
    template<typename T>
    class IRandomRange
    {
    public:
        virtual ~IRandomRange() = default;

        virtual void setMin(T value) = 0;
        virtual void setMax(T value) = 0;
        virtual T getValue() const = 0;
    };

    using RandomRangeFloatPtr = std::unique_ptr<IRandomRange<float>>;
    using RandomRangeSizeTPtr = std::unique_ptr<IRandomRange<size_t>>;

}
