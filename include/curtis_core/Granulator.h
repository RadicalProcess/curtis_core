#pragma once

#include <set>
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
        Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, size_t visualizationCacheSize, const IFactory& factory = Factory());

        ~Granulator() override = default;

        void setDensity(int percentage) override;

        void setRandomRange(size_t range) override;

        ICounter& getCounter() override;

        IGlisson& getGlisson() override;

        IPanner& getPanner() override;

        void process(IBuffer& left, IBuffer& right) override;

        void addListener(Listener* listener) override;

        void removeListener(Listener* listener) override;

    private:
        const ISegmentBank& segmentBank_;
        ReadBufferPtr readBuffer_;
        CounterPtr counter_;
        RandomizerPtr randomizer_;
        GlissonPtr glisson_;
        DensityPtr density_;
        PannerPtr panner_;
        size_t latestIndex_;
        const size_t visualizationCacheSize_;
        std::vector<VisualizationDataSet> visualizationCache_;
        std::set<Listener*> listeners_;
    };
}
