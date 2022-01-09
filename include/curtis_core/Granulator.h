#pragma once

#include <cstddef>

#include "IGranulator.h"
#include "IProcessor.h"
#include "ISegmentBank.h"
#include "IRandomRange.h"
#include "Factory.h"

namespace rp::curtis
{
    class Granulator : public IGranulator
    {
    public:
        Granulator(const ISegmentBank& segmentBank, const IFactory& factory = Factory());

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
        BufferPtr playBuffer_;
        size_t playIndex_;

        RandomRangeSizeTPtr repeatRange_;
        size_t randomRange_;

        bool glissonEnabled_;
        RandomRangeFloatPtr startSpeedRange_;
        RandomRangeFloatPtr endSpeedRange_;
    };
}
