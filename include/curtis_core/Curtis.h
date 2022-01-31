#pragma once
#include <cstdlib>
#include <set>

#include "Buffer.h"
#include "ISegmentBank.h"
#include "ISegmentDetector.h"
#include "IStereoProcessor.h"
#include "IGranulator.h"
#include "IInputMix.h"
#include "Factory.h"

namespace rp::curtis
{
    class Curtis : public IStereoProcessor
                 , public IVisualizationDataCache::Listener
                 , public IVisualizationDataCache
    {
    public:
        Curtis(float sampleRate, size_t blockSize, size_t visualizationCacheSize, const IFactory& factory = Factory());

        ~Curtis() override;

        void setMix(float mix);
        void setSegmentMinLength(float ms);

        void setDensity(int percentage);

        void setRepeat(size_t count);
        void setRandomRange(size_t range);

        void setGlissonEnabled(bool enabled);
        void setStartSpeedA(float speed);
        void setStartSpeedB(float speed);
        void setEndSpeedA(float speed);
        void setEndSpeedB(float speed);

        void setStartPositionA(float position);
        void setStartPositionB(float position);
        void setEndPositionA(float position);
        void setEndPositionB(float position);

        void setDry(float dry);
        void setWet(float wet);

        void process(IBuffer& left, IBuffer& right) override;

        void addListener(Listener* listener) override;

        void removeListener(Listener* listener) override;

    private:
        void onVisualizationDataCacheFilled(const std::vector<VisualizationDataSet>& cache) override;

        InputMixPtr inputMix_;
        SegmentBankPtr segmentBank_;
        SegmentDetectorPtr segmentDetector_;
        GranulatorPtr granulator_;
        std::vector<BufferPtr> dryBuffers_;
        std::set<Listener*> listeners_;

        float dry_ {0.0f};
        float wet_ {1.0f};

    };
}
