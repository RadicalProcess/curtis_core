#pragma once

#include <cstddef>
#include "IGranulator.h"
#include "IProcessor.h"
#include "ISegmentBank.h"

namespace rp::curtis
{
    class Granulator : public IGranulator
                     , public IProcessor
    {
    public:
        Granulator(const ISegmentBank& segmentBank);

        ~Granulator() override = default;

        void setRepeatMin(size_t count) override;

        void setRepeatMax(size_t count) override;

        void setRandomRange(size_t range) override;

        void setGlissonEnabled(bool enabled) override;

        void setStartMinSpeed(float speed) override;

        void setStartMaxSpeed(float speed) override;

        void setEndMinSpeed(float speed) override;

        void setEndMaxSpeed(float speed) override;

        void process(IBuffer& buffer) override;

    private:
        const ISegmentBank& segmentBank_;

        size_t repeatMix_;
        size_t repeatMax_;
        size_t randomRange_;

        bool glissonEnabled_;
        float startMinSpeed_;
        float startMaxSpeed_;
        float endMinSpeed_;
        float endMaxSpeed_;
    };
}
