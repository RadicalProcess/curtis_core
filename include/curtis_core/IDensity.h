#pragma once

#include <memory>

namespace rp::curtis
{
    class IDensity
    {
    public:
        virtual ~IDensity() = default;

        virtual void set(int percentage) = 0;

        virtual void roll() = 0;

        virtual bool get() const = 0;
    };

    using DensityPtr = std::unique_ptr<IDensity>;
}
