#pragma once

#include <set>

#include "ISegmentDetector.h"
#include "Factory.h"

namespace rp::curtis
{
    class SegmentDetector : public ISegmentDetector
    {
    public:
        SegmentDetector(float sampleRate, const IFactory& factory = Factory());

        ~SegmentDetector() override = default;

        void setSegmentMinLength(float ms) override;

        void setSegmentMaxLength(float ms) override;

        void addListener(Listener* listener) override;

        void removeListener(Listener* listener) override;

        void process(IBuffer& buffer) override;


    private:
        void clear();



        const float sampleRate_;
        BufferPtr tempBuffer_;
        size_t minLength_ ;
        size_t maxLength_;

        std::set<Listener*> listeners_;


    };
}
