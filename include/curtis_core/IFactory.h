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

        virtual SegmentBankPtr createSegmentBank(size_t numCaches) const = 0;

        virtual SegmentDetectorPtr createSegmentDetector(float sampleRate) const = 0;

        virtual GranulatorPtr createGranulator() const = 0;

        virtual BufferPtr createBuffer(size_t capacity) const = 0;

        virtual BufferPtr createBuffer(float* buffer, size_t size) const = 0;
    };

    using FactoryPtr = std::unique_ptr<IFactory>;
}
