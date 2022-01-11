#include "ReadBuffer.h"

#include <cmath>
#include <algorithm>

namespace rp::curtis
{
    ReadBuffer::ReadBuffer(size_t maxBufferSize, const IFactory& factory)
    : playBuffer_(factory.createBuffer(maxBufferSize, false))
    {
    }

    void ReadBuffer::updateBuffer(const IBuffer& buffer)
    {
        playBuffer_->copyFrom(buffer);
    }

    bool ReadBuffer::advancePlayHead(float advancement)
    {
        playHead_ += advancement;
        if(static_cast<size_t>(playHead_) >= playBuffer_->size())
        {
            playHead_ = 0.0f;
            return true;
        }
        return false;
    }

    float ReadBuffer::getSample() const
    {
        const auto index = static_cast<size_t>(playHead_);
        const auto decimal = playHead_ - std::floorf(playHead_);

        const auto nextSample = std::min(index + 1, playBuffer_->size()-1);
        const auto* sourceSamplePtr = playBuffer_->getReadPtr();

        const auto left = sourceSamplePtr[index];
        const auto right = sourceSamplePtr[nextSample];

        return (right-left) * decimal + left;
    }

    float ReadBuffer::getPhase() const
    {
        return playHead_ / static_cast<float>(playBuffer_->size());
    }
}
