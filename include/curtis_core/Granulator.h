#pragma once

#include <cstddef>

#include "IGranulator.h"
#include "IProcessor.h"
#include "ISegmentBank.h"
#include "IRandomRange.h"
#include "IRandomizer.h"
#include "ICounter.h"
#include "Factory.h"

namespace rp::curtis
{
    class Granulator : public IGranulator
    {
    public:
        Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, const IFactory& factory = Factory());

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

        void updateSpeed();

        const ISegmentBank& segmentBank_;
        BufferPtr playBuffer_;
        float playIndex_;
        CounterPtr counter_;

        RandomizerPtr randomizer_;
        GlissonPtr glisson_;
        size_t latestIndex_;
    };
}
