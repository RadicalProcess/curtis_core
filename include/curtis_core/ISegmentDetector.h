#pragma once

#include <memory>
#include <vector>

namespace rp::curtis
{
    class ISegmentDetectorParameter
    {
    public:
        virtual ~ISegmentDetectorParameter() = default;

        virtual void setSegmentMinLength(float ms) = 0;

        virtual void setSegmentMaxLength(float ms) = 0;
    };

    class ISegmentDetector : public ISegmentDetectorParameter
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = 0;

            virtual void onSegmentDetected(const std::vector<float>& segment) = 0;
        };

    public:
        virtual ~ISegmentDetector() = default;


        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;


    };

    using SegmentDetectorPtr = std::unique_ptr<ISegmentDetector>;
}
