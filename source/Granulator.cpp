#include "Granulator.h"

#include <cmath>

#include "IFactory.h"

namespace rp::curtis
{
    namespace
    {
        size_t wrap(int index, size_t size)
        {
            return index >= 0 ?
                static_cast<size_t>(index) :
                static_cast<size_t>(index + static_cast<int>(size));
        }
    }

    Granulator::Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, const IFactory& factory)
    : segmentBank_(segmentBank)
    , readBuffer_(factory.createReadBuffer(maxBufferSize))
    , counter_(factory.createCounter())
    , randomizer_(factory.createRandomizer())
    , glisson_(factory.createGlisson())
    , density_(factory.createDensity())
    , panner_(factory.createPanner())
    , latestIndex_(0)
    {
    }

    void Granulator::setDensity(int percentage)
    {
        density_->set(percentage);
    }

    void Granulator::setRepeatMin(size_t count)
    {
        counter_->getRandomRange().setMin(count);
    }

    void Granulator::setRepeatMax(size_t count)
    {
        counter_->getRandomRange().setMax(count);
    }

    void Granulator::setRandomRange(size_t range)
    {
        randomizer_->setRange(range);
    }

    void Granulator::setGlissonEnabled(bool enabled)
    {
        glisson_->setGlissonEnabled(enabled);
    }

    void Granulator::setStartMinSpeed(float speed)
    {
        glisson_->getStartRandomRange().setMin(speed);
    }

    void Granulator::setStartMaxSpeed(float speed)
    {
        glisson_->getStartRandomRange().setMax(speed);
    }

    void Granulator::setEndMinSpeed(float speed)
    {
        glisson_->getEndRandomRange().setMin(speed);
    }

    void Granulator::setEndMaxSpeed(float speed)
    {
        glisson_->getEndRandomRange().setMax(speed);
    }

    void Granulator::process(IBuffer& leftBuffer, IBuffer& rightBuffer)
    {
        auto* destPtr = leftBuffer.getWritePtr();
        auto sampleCount = leftBuffer.size();
        while(sampleCount--)
        {
            *destPtr++ = density_->get() ? readBuffer_->getSample() : 0.0f;
            const auto phase = readBuffer_->getPhase();
            const auto speed = glisson_->getSpeedAt(phase);
            if( readBuffer_->advancePlayHead(speed))
            {

                if(counter_->count())
                {
                    latestIndex_ = segmentBank_.getLatestCacheIndex();
                }
                density_->roll();
                glisson_->update();
                auto target = static_cast<int>(latestIndex_) - static_cast<int>(randomizer_->getValue());
                readBuffer_->updateBuffer(segmentBank_.getCache(wrap(target, segmentBank_.size())));
            }
        }
    }

    IPannerParameter& Granulator::getPanner()
    {
        return *panner_;
    }
}
