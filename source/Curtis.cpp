#include "Curtis.h"

namespace rp::curtis
{
    Curtis::Curtis(float sampleRate, const IFactory& factory)
    : segmentBank_(factory.createSegmentBank(32))
    , segmentDetector_(factory.createSegmentDetector(sampleRate))
    , granulator_(factory.createGranulator())
    {
    }

    void Curtis::setSegmentMinLength(float ms)
    {

    }

    void Curtis::setSegmentMaxLength(float ms)
    {

    }

    void Curtis::setRepeatMin(size_t count)
    {

    }

    void Curtis::setRepeatMax(size_t count)
    {

    }

    void Curtis::setRandomRange(size_t range)
    {

    }

    void Curtis::setGlissonEnabled(bool enabled)
    {

    }

    void Curtis::setStartMinSpeed(float speed)
    {

    }

    void Curtis::setStartMaxSpeed(float speed)
    {

    }

    void Curtis::setEndMinSpeed(float speed)
    {

    }

    void Curtis::setEndMaxSpeed(float speed)
    {

    }

    void Curtis::process(Buffer& buffer)
    {

    }
}
