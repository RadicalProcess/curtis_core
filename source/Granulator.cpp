#include <IFactory.h>
#include "Granulator.h"

namespace rp::curtis
{
    Granulator::Granulator(const ISegmentBank& segmentBank, const IFactory& factory)
    : segmentBank_(segmentBank)
    , playBuffer_(factory.createBuffer())
    , requestNextBuffer_(true)
    , repeatMix_(1)
    , repeatMax_(1)
    , randomRange_(1)
    , glissonEnabled_(true)
    , startMinSpeed_(1.0f)
    , startMaxSpeed_(1.0f)
    , endMinSpeed_(1.0f)
    , endMaxSpeed_(1.0f)
    {
    }

    void Granulator::setRepeatMin(size_t count)
    {
        repeatMix_ = count;
    }

    void Granulator::setRepeatMax(size_t count)
    {
        repeatMax_ = count;
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
        startMinSpeed_ = speed;
    }

    void Granulator::setStartMaxSpeed(float speed)
    {
        startMaxSpeed_ = speed;
    }

    void Granulator::setEndMinSpeed(float speed)
    {
        endMinSpeed_ = speed;
    }

    void Granulator::setEndMaxSpeed(float speed)
    {
        endMaxSpeed_ = speed;
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
