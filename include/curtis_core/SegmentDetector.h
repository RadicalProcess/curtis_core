#pragma once

#include <set>

#include "ISegmentDetector.h"

namespace rp::curtis
{
    class SegmentDetector : public ISegmentDetector
    {
    public:
        SegmentDetector(float sampleRate);

        ~SegmentDetector() override = default;

        void setSegmentMinLength(float ms) override;

        void setSegmentMaxLength(float ms) override;

        void addListener(Listener* listener) override;

        void removeListener(Listener* listener) override;

    private:
        const float sampleRate_;
        size_t minLength_;
        size_t maxLength_;

        std::set<Listener*> listeners_;
    };
}
