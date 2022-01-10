#include "Granulator.h"

#include <cmath>

#include "IFactory.h"

namespace rp::curtis
{
    Granulator::Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, const IFactory& factory)
    : segmentBank_(segmentBank)
    , playBuffer_(factory.createBuffer(maxBufferSize))
    , playIndex_(0)
    , counter_(factory.createCounter())
    , randomizer_(factory.createRandomizer())
    , glisson_(factory.createGlisson())
    {
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

    void Granulator::process(IBuffer& buffer)
    {
        if(playBuffer_->size() == 0)
        {
            auto latestCacheIndex = segmentBank_.getLatestCacheIndex();
            if (latestCacheIndex == std::nullopt)
            {
                buffer.clear();
                return;
            }
            playBuffer_->copyFrom(segmentBank_.getCache(latestCacheIndex.value()));
            glisson_->update();
        }
        auto* destPtr = buffer.getWritePtr();
        auto destSizeRequirement = buffer.size();

        auto* sourceSamplePtr = playBuffer_->getReadPtr();

        auto updatePlayBuffer = [&](){
            auto target = static_cast<int>(latestIndex_) - randomizer_->getValue();
            if(target < 0)
                target += static_cast<int>(segmentBank_.size());
            playBuffer_->copyFrom(segmentBank_.getCache(static_cast<size_t>(target)));
            sourceSamplePtr = playBuffer_->getReadPtr();
        };

        while(destSizeRequirement--)
        {
            const auto decimal = playIndex_ - std::floorf(playIndex_);
            const auto nextSample = std::min(static_cast<size_t>(playIndex_) + 1, playBuffer_->size()-1);
            const auto left = sourceSamplePtr[static_cast<size_t>(playIndex_)];
            const auto right = sourceSamplePtr[nextSample];
            const auto interpolated = (right-left) * decimal + left;

            *destPtr++ = interpolated;
            playIndex_ += glisson_->getSpeedAt(playIndex_ / static_cast<float>(playBuffer_->size()));

            if(static_cast<size_t>(playIndex_) >= playBuffer_->size())
            {
                playIndex_ = 0;
                counter_->count([this](){
                    latestIndex_ = segmentBank_.getLatestCacheIndex().value();
                });
                glisson_->update();
                updatePlayBuffer();
            }
        }
    }
}
