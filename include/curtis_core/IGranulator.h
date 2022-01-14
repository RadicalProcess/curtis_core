#pragma once

#include <memory>

#include "IStereoProcessor.h"

namespace rp::curtis
{
    class IGranulatorParameter
    {
    public:
        virtual ~IGranulatorParameter() = default;
        virtual  void setDensity(int percentage) = 0;

        virtual void setRepeatMin(size_t count) = 0;
        virtual void setRepeatMax(size_t count) = 0;
        virtual void setRandomRange(size_t range) = 0;

        virtual void setGlissonEnabled(bool enabled) = 0;

        virtual void setStartMinSpeed(float speed) = 0;
        virtual void setStartMaxSpeed(float speed) = 0;
        virtual void setEndMinSpeed(float speed) = 0;
        virtual void setEndMaxSpeed(float speed) = 0;
    };

    class IGranulator : public IGranulatorParameter
                      , public IStereoProcessor
    {
    public:
        virtual ~IGranulator() = default;
    };

    using GranulatorPtr = std::unique_ptr<IGranulator>;
}
