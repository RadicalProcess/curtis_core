#pragma once

#include <cstddef>

#include "IGranulator.h"
#include "IProcessor.h"
#include "ISegmentBank.h"
#include "IRandomRange.h"
#include "IRandomizer.h"
#include "ICounter.h"
#include "IPanner.h"

#include "Factory.h"


namespace rp::curtis
{
    class Granulator : public IGranulator
    {
    public:
        Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, const IFactory& factory = Factory());

        ~Granulator() override = default;

        void setDensity(int percentage) override;

        void setRandomRange(size_t range) override;

        ICounter& getCounter() override;

        IGlisson& getGlisson() override;

        IPanner& getPanner() override;

        void process(IBuffer& left, IBuffer& right) override;

    private:
        const ISegmentBank& segmentBank_;
        ReadBufferPtr readBuffer_;
        CounterPtr counter_;
        RandomizerPtr randomizer_;
        GlissonPtr glisson_;
        DensityPtr density_;
        PannerPtr panner_;
        size_t latestIndex_;
    };
}
