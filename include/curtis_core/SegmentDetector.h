#pragma once

#include <set>

#include "IPolarity.h"
#include "ISegmentDetector.h"
#include "Factory.h"

namespace rp::curtis
{
    class SegmentDetector : public ISegmentDetector
                          , public IPolarity::Listener
    {
    public:
        SegmentDetector(float sampleRate, size_t maxBufferSize, const IFactory& factory = Factory());

        ~SegmentDetector() override;

        void setSegmentMinLength(float ms) override;

        void setSegmentMaxLength(float ms) override;

        void addListener(ISegmentDetector::Listener* listener) override;

        void removeListener(ISegmentDetector::Listener* listener) override;

        void process(IBuffer& buffer) override;

    private:
        void onPolarityChanged() override;

        const float sampleRate_;
        BufferPtr tempBuffer_;
        size_t minLength_ ;
        size_t maxLength_;
        PolarityPtr polarity_;

        std::set<ISegmentDetector::Listener*> listeners_;


    };
}
