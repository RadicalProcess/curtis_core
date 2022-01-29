#pragma once

#include <memory>

namespace rp::curtis
{
    class IRandomRange
    {
    public:
        virtual ~IRandomRange() = default;

        virtual void setA(float value) = 0;

        virtual void setB(float value) = 0;

        virtual float getValue() const = 0;
    };

    using RandomRangePtr = std::unique_ptr<IRandomRange>;
}
