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

    SegmentDetector::SegmentDetector(float sampleRate)
    : sampleRate_(sampleRate)
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
}
