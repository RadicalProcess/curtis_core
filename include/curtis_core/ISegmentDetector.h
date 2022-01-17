#pragma once

#include <memory>
#include <vector>

#include "IProcessor.h"

namespace rp::curtis
{
    class ISegmentDetector : public IProcessor
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onSegmentDetected(const IBuffer& buffer) = 0;
        };

    public:
        virtual ~ISegmentDetector() = default;

        virtual void setSegmentMinLength(float ms) = 0;

        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;
    };

    using SegmentDetectorPtr = std::unique_ptr<ISegmentDetector>;
}
