#include "Curtis.h"

namespace rp::curtis
{
    Curtis::Curtis(float sampleRate, const IFactory& factory)
    : segmentBank_(factory.createSegmentBank(32))
    , segmentDetector_(factory.createSegmentDetector(sampleRate))
    , granulator_(factory.createGranulator(*segmentBank_))
    {
        segmentDetector_->addListener(dynamic_cast<ISegmentDetector::Listener*>(segmentBank_.get()));
    }

    void Curtis::setSegmentMinLength(float ms)
    {
        segmentDetector_->setSegmentMinLength(ms);
    }

    void Curtis::setSegmentMaxLength(float ms)
    {
        segmentDetector_->setSegmentMaxLength(ms);
    }

    void Curtis::setRepeatMin(size_t count)
    {
        granulator_->setRepeatMin(count);
    }

    void Curtis::setRepeatMax(size_t count)
    {
        granulator_->setRepeatMax(count);
    }

    void Curtis::setRandomRange(size_t range)
    {
        granulator_->setRandomRange(range);
    }

    void Curtis::setGlissonEnabled(bool enabled)
    {
        granulator_->setGlissonEnabled(enabled);
    }

    void Curtis::setStartMinSpeed(float speed)
    {
        granulator_->setStartMinSpeed(speed);
    }

    void Curtis::setStartMaxSpeed(float speed)
    {
        granulator_->setStartMaxSpeed(speed);
    }

    void Curtis::setEndMinSpeed(float speed)
    {
        granulator_->setEndMinSpeed(speed);
    }

    void Curtis::setEndMaxSpeed(float speed)
    {
        granulator_->setEndMaxSpeed(speed);
    }

    void Curtis::process(IBuffer& buffer)
    {
        segmentDetector_->process(buffer);
        granulator_->process(buffer);
    }
}
