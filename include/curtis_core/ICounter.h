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

        virtual void setMaxCount(size_t count) = 0;

        virtual bool count() = 0;
    };

    using CounterPtr = std::unique_ptr<ICounter>;
}
