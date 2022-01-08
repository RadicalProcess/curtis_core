#pragma once

#include <memory>
#include <vector>

namespace rp::curtis
{
    class ISegmentDetector
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = 0;

            virtual onSegmentDetected(const std::vector<float>& segment);
        }
    public:
        virtual ~ISegmentDetector() = 0;

    };
}
