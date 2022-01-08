#pragma once

#include <memory>

namespace rp::curtis
{
    class IGranulator
    {
    public:
        virtual ~IGranulator() = default;

        virtual void setRepeatMin(size_t count) = 0;
        virtual void setRepeatMax(size_t count) = 0;
        virtual void setRandomRange(size_t range) = 0;

        virtual void setGlissonEnabled(bool enabled) = 0;

        virtual void setStartMinSpeed(float speed) = 0;
        virtual void setStartMaxSpeed(float speed) = 0;
        virtual void setEndMinSpeed(float speed) = 0;
        virtual void setEndMaxSpeed(float speed) = 0;
    };

    using GranulatorPtr = std::unique_ptr<IGranulator>;
}
