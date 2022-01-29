#pragma once
#include <cstdlib>

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
    {
    public:
        Curtis(float sampleRate, size_t blockSize, const IFactory& factory = Factory());

        ~Curtis() override= default;

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

    private:
        InputMixPtr inputMix_;
        SegmentBankPtr segmentBank_;
        SegmentDetectorPtr segmentDetector_;
        GranulatorPtr granulator_;
        std::vector<BufferPtr> dryBuffers_;

        float dry_ {0.0f};
        float wet_ {1.0f};
    };
}
