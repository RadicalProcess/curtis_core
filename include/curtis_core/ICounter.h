#pragma once

#include <memory>
#include <functional>

#include "IRandomRange.h"

namespace rp::curtis
{
    class ICounter
    {
    public:
        virtual ~ICounter() = default;

        virtual IRandomRange<size_t>& getRandomRange() = 0;

        virtual void count(const std::function<void()>& onCountEnded) = 0;
    };

    using CounterPtr = std::unique_ptr<ICounter>;
}
