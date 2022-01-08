#include "SegmentDetector.h"

namespace rp::curtis
{
    namespace
    {
        size_t msToSamples(float ms, float sampleRate)
        {
            return static_cast<size_t>(ms / 1000.f * sampleRate);
        }
    }

    SegmentDetector::SegmentDetector(float sampleRate, const IFactory& factory)
    : sampleRate_(sampleRate)
    , tempBuffer_(factory.createBuffer(static_cast<size_t>(sampleRate * 0.1))) // max 100 msec
    {
    }

    void SegmentDetector::setSegmentMinLength(float ms)
    {
        minLength_ = msToSamples(ms, sampleRate_);
    }

    void SegmentDetector::setSegmentMaxLength(float ms)
    {
        maxLength_ = msToSamples(ms, sampleRate_);
    }

    void SegmentDetector::addListener(ISegmentDetector::Listener* listener)
    {
        listeners_.insert(listener);
    }

    void SegmentDetector::removeListener(ISegmentDetector::Listener* listener)
    {
        listeners_.erase(listener);
    }

    void SegmentDetector::process(IBuffer& buffer)
    {
        if(tempBuffer_->size() + buffer.size() < minLength_)
        {
            tempBuffer_->append(buffer);
            const auto lastValue = tempBuffer_->getLast();

        }
        else
        {
            auto* ptr =  buffer.get();
            for(auto i = 0; i < buffer.size(); ++i)
            {
                const auto value = *ptr++;
                if(tempBuffer_->size() + i >= maxLength_)
                    clear();

                tempBuffer_->push(value);
            }
        }

    }

    void SegmentDetector::clear()
    {
        tempBuffer_->clean();
    }

}
