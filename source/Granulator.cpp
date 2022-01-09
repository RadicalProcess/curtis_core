#include <IFactory.h>
#include "Granulator.h"

namespace rp::curtis
{
    Granulator::Granulator(const ISegmentBank& segmentBank, const IFactory& factory)
    : segmentBank_(segmentBank)
    , playBuffer_(factory.createBuffer())
    , playIndex_(0)
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
        if(playBuffer_->size() == 0)
        {
            auto* cache = segmentBank_.getCache(0);
            if (cache == nullptr)
            {
                buffer.clear();
                return;
            }
            playBuffer_->copyFrom(*cache);
        }
        auto* destPtr = buffer.getWritePtr();
        auto destSizeRequirement = buffer.size();

        auto* srcPtr = playBuffer_->getReadPtr();
        while(destSizeRequirement--)
        {
            *destPtr++ = *srcPtr++;
            playIndex_++;
            if(playIndex_ == playBuffer_->size())
            {
                // in case source play buffer is exhausted
                playIndex_ = 0;
                playBuffer_->copyFrom(*segmentBank_.getCache(0)); // get new one
                srcPtr = playBuffer_->getReadPtr();
            }
        }
    }
}
