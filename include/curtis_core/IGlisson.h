#pragma once

#include <memory>
#include "IRandomRange.h"

namespace rp::curtis
{
    class IGlisson
    {
    public:
        virtual ~IGlisson() = default;

        virtual void update() = 0;

        virtual float getSpeedAt(float phase) = 0;

        virtual void setGlissonEnabled(bool enabled) = 0;

        virtual IRandomRange<float>& getStartRandomRange() = 0;

        virtual IRandomRange<float>& getEndRandomRange() = 0;
    };

    using GlissonPtr = std::unique_ptr<IGlisson>;
}
