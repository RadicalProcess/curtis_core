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
    , polarity_(factory.createPolarity())
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
            polarity_->set(tempBuffer_->getLast(), false);
        }
        else
        {
            auto* ptr = buffer.get();
            for(auto i = 0; i < buffer.size(); ++i)
            {
                const auto value = *ptr++;
                polarity_->set(value, true);

                if(tempBuffer_->size() >= maxLength_)
                    tempBuffer_->clean();

                tempBuffer_->push(value);
            }
        }
    }

    void SegmentDetector::onPolarityChanged()
    {
        for(auto* listener: listeners_)
            listener->onSegmentDetected(*tempBuffer_);

        tempBuffer_->clean();
    }
}
