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

    SegmentDetector::SegmentDetector(float sampleRate, size_t maxBufferSize, const IFactory& factory)
    : sampleRate_(sampleRate)
    , minLength_(maxBufferSize / 2)
    , maxLength_(maxBufferSize)
    , tempBuffer_(factory.createBuffer(static_cast<size_t>(maxBufferSize)))
    , polarity_(factory.createPolarity())
    {
        polarity_->addListener(this);
    }

    SegmentDetector::~SegmentDetector()
    {
        polarity_->removeListener(this);
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
        auto* ptr = buffer.getReadPtr();
        for(auto i = 0; i < buffer.size(); ++i)
        {
            const auto value = *ptr++;
            const auto bufSize = tempBuffer_->size();

            if(minLength_ <= bufSize && bufSize < maxLength_)
            {
                polarity_->set(value, true);
            }
            else if(maxLength_ <= bufSize)
            {
                tempBuffer_->clear();
            }
            tempBuffer_->push(value);
        }
    }

    void SegmentDetector::onPolarityChanged()
    {
        for(auto* listener: listeners_)
            listener->onSegmentDetected(*tempBuffer_);

        tempBuffer_->clear();
    }
}
