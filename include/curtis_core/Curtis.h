#pragma once
#include <cstdlib>

#include "Buffer.h"
#include "ISegmentBank.h"
#include "ISegmentDetector.h"
#include "IProcessor.h"
#include "IGranulator.h"
#include "Factory.h"

namespace rp::curtis
{
    class Curtis : public ISegmentDetectorParameter,
                   public IGranulator,
                   public IProcessor

    {
    public:
        Curtis(float sampleRate, const IFactory& factory = Factory());

        void setSegmentMinLength(float ms) override;
        void setSegmentMaxLength(float ms) override;

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
        SegmentBankPtr segmentBank_;
        SegmentDetectorPtr segmentDetector_;
        GranulatorPtr granulator_;

    };
}
