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
        Curtis(float sampleRate, const IFactory& factory = Factory());

        ~Curtis() override= default;

        void setMix(float mix);
        void setSegmentMinLength(float ms);

        void setDensity(int percentage);

        void setRepeatMin(size_t count);
        void setRepeatMax(size_t count);
        void setRandomRange(size_t range);

        void setGlissonEnabled(bool enabled);
        void setStartMinSpeed(float speed);
        void setStartMaxSpeed(float speed);
        void setEndMinSpeed(float speed);
        void setEndMaxSpeed(float speed);

        void setStartLeft(float position);
        void setStartRight(float position);
        void setEndLeft(float position);
        void setEndRight(float position);

        void process(IBuffer& left, IBuffer& right) override;

    private:
        InputMixPtr inputMix_;
        SegmentBankPtr segmentBank_;
        SegmentDetectorPtr segmentDetector_;
        GranulatorPtr granulator_;

    };
}
