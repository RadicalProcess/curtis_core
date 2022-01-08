#pragma once

#include <cstddef>
#include "IGranulator.h"

namespace rp::curtis
{
    class Granulator : public IGranulator
    {
    public:
        Granulator();

        ~Granulator() override = default;

        void setRepeatMin(size_t count) override;

        void setRepeatMax(size_t count) override;

        void setRandomRange(size_t range) override;

        void setGlissonEnabled(bool enabled) override;

        void setStartMinSpeed(float speed) override;

        void setStartMaxSpeed(float speed) override;

        void setEndMinSpeed(float speed) override;

        void setEndMaxSpeed(float speed) override;

    };
}
