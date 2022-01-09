#include "Granulator.h"

#include <cmath>

#include "IFactory.h"

namespace rp::curtis
{
    Granulator::Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, const IFactory& factory)
    : segmentBank_(segmentBank)
    , playBuffer_(factory.createBuffer(maxBufferSize))
    , playIndex_(0)
    , repeatRange_(factory.createRandomRangeSizeT(0, 0))
    , randomRange_(0)
    , glissonEnabled_(true)
    , startSpeedRange_(factory.createRandomRangeFloat(1.0f, 1.0f))
    , endSpeedRange_(factory.createRandomRangeFloat(1.0f, 1.0f))
    , repeatCount_(0)
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

    void Granulator::updateSpeed()
    {
        startSpeed_ = startSpeedRange_->getValue();
        endSpeed_ = endSpeedRange_->getValue();
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
            updateSpeed();
        }
        auto* destPtr = buffer.getWritePtr();
        auto destSizeRequirement = buffer.size();

        auto* sourceSamplePtr = playBuffer_->getReadPtr();

        auto updatePlayBuffer = [&](){
            const auto gapFromLatest = randomRange_ == 0 ? 0 : rand() % static_cast<int>(randomRange_);
            auto target = static_cast<int>(latestIndex_) - gapFromLatest;
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
            const float positionInBuffer = playIndex_ / static_cast<float>(playBuffer_->size());
            const float speedAtThePosition = ( endSpeed_ - startSpeed_ ) * positionInBuffer + startSpeed_;
            playIndex_ += speedAtThePosition;

            if(static_cast<size_t>(playIndex_) >= playBuffer_->size())
            {
                playIndex_ = 0;
                if(repeatCount_ > 0)
                {
                    repeatCount_--;
                }
                else
                {
                    repeatCount_ = repeatRange_->getValue();
                    latestIndex_ = segmentBank_.getLatestCacheIndex().value();
                }
                updateSpeed();
                updatePlayBuffer();
            }
        }
    }
}
