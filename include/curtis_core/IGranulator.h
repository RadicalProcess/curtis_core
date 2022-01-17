#pragma once

#include <memory>

#include "IStereoProcessor.h"
#include "IPanner.h"
#include "IGlisson.h"
#include "ICounter.h"

namespace rp::curtis
{
    class IGranulator : public IStereoProcessor
    {
    public:
        virtual ~IGranulator() = default;

        virtual  void setDensity(int percentage) = 0;

        virtual void setRandomRange(size_t range) = 0;

        virtual ICounter& getCounter() = 0;
        virtual IGlisson& getGlisson() = 0;
        virtual IPanner& getPanner() = 0;
    };

    using GranulatorPtr = std::unique_ptr<IGranulator>;
}
