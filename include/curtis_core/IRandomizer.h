#pragma once

#include <memory>

namespace rp::curtis
{
    class IRandomizer
    {
    public:
        virtual ~IRandomizer() = default;

        virtual void setRange(size_t range) = 0;

        virtual size_t getValue() const = 0;
    };

    using RandomizerPtr = std::unique_ptr<IRandomizer>;
}
