#pragma once

#include <memory>

#include "ISegmentBank.h"
#include "ISegmentDetector.h"
#include "IGranulator.h"

namespace rp::curtis
{
    class IFactory
    {
    public:
        virtual ~IFactory() = default;

        virtual SegmentBankPtr createSegmentBank(size_t numCaches) = 0;

        virtual SegmentDetectorPtr createSegmentDetector(float sampleRate) = 0;

        virtual GranulatorPtr createGranulator() = 0;
    };

    using FactoryPtr = std::unique_ptr<IFactory>;
}
