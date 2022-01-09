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
            auto* cache = segmentBank_.getCache(0);
            if (cache == nullptr)
            {
                buffer.clear();
                return;
            }
            playBuffer_->copyFrom(*cache);
            updateSpeed();
        }
        auto* destPtr = buffer.getWritePtr();
        auto destSizeRequirement = buffer.size();

        auto* sourceSamplePtr = playBuffer_->getReadPtr();;
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
                updateSpeed();
                playIndex_ = 0;
                if(repeatCount_ > 0)
                {
                    repeatCount_--;
                }
                else
                {
                    repeatCount_ = repeatRange_->getValue();
                    auto fromLatest = randomRange_ == 0 ? 0 : rand() % randomRange_;
                    playBuffer_->copyFrom(*segmentBank_.getCache(fromLatest)); // get new one
                    sourceSamplePtr = playBuffer_->getReadPtr();
                }
            }
        }
    }
}
