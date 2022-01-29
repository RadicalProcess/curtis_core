#pragma once

#include "IGlisson.h"
#include "Factory.h"

namespace rp::curtis
{
    class Glisson : public IGlisson
    {
    public:
        Glisson(const IFactory& factory = Factory());

        ~Glisson() override = default;

        void update() override;

        float getSpeedAt(float phase) override;

        void setGlissonEnabled(bool enabled) override;

        IRandomRange& getStartRandomRange() override;

        IRandomRange& getEndRandomRange() override;

    private:
        RandomRangePtr startRandomRange_;
        RandomRangePtr endRandomRange_;
        float startSpeed_;
        float endSpeed_;
        bool glisson_;
    };
}
