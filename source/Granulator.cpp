#include <IFactory.h>
#include "Granulator.h"

namespace rp::curtis
{
    Granulator::Granulator(const ISegmentBank& segmentBank, const IFactory& factory)
    : segmentBank_(segmentBank)
    , playBuffer_(factory.createBuffer())
    , requestNextBuffer_(true)
    , repeatRange_(factory.createRandomRangeSizeT(1, 1))
    , randomRange_(1)
    , glissonEnabled_(true)
    , startSpeedRange_(factory.createRandomRangeFloat(1.0f, 1.0f))
    , endSpeedRange_(factory.createRandomRangeFloat(1.0f, 1.0f))
    {
    }

    void Granulator::setRepeatMin(size_t count)
    {
        repeatRange_->setMin(count);
    }

    void Granulator::setRepeatMax(size_t count)
    {
        repeatRange_->setMax(count);
    }

    void Granulator::setRandomRange(size_t range)
    {
        randomRange_ = range;
    }

    void Granulator::setGlissonEnabled(bool enabled)
    {
        glissonEnabled_ = enabled;
    }

    void Granulator::setStartMinSpeed(float speed)
    {
        startSpeedRange_->setMin(speed);
    }

    void Granulator::setStartMaxSpeed(float speed)
    {
        startSpeedRange_->setMax(speed);
    }

    void Granulator::setEndMinSpeed(float speed)
    {
        endSpeedRange_->setMin(speed);
    }

    void Granulator::setEndMaxSpeed(float speed)
    {
        endSpeedRange_->setMax(speed);
    }

    void Granulator::process(IBuffer& buffer)
    {
        if(requestNextBuffer_)
        {
            auto* cache = segmentBank_.getCache(0);
            if (cache == nullptr)
            {
                buffer.clear();
                return;
            }
        }



    }
}
