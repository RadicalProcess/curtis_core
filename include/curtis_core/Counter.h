#pragma once

#include "ICounter.h"

#include "Factory.h"
#include "IRandomRange.h"

namespace rp::curtis
{
    class Counter : public ICounter
    {
    public:
        Counter(const IFactory& factory = Factory());

        ~Counter() override = default;

        void setMaxCount(size_t count) override;

        bool count() override;

    private:
        size_t maxCount_;
        size_t remaining_;
    };
}
