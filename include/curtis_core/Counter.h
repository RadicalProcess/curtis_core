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

        IRandomRange<size_t>& getRandomRange() override;

        void count(const std::function<void()>& onCountEnded) override;

    private:
        RandomRangeSizeTPtr repeatRandomRange_;
        size_t remaining_;
    };
}
