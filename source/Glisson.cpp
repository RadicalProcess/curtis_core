#include "Glisson.h"

namespace rp::curtis
{
    Glisson::Glisson(const IFactory& factory)
    : startRandomRange_(factory.createRandomRangeFloat(1.0f, 1.0f))
    , endRandomRange_(factory.createRandomRangeFloat(1.0f, 1.0f))
    , startSpeed_(1.0f)
    , endSpeed_(1.0f)
    , glisson_(true)
    {
    }

    void Glisson::update()
    {
        startSpeed_ = startRandomRange_->getValue();
        endSpeed_ = endRandomRange_->getValue();
    }

    float Glisson::getSpeedAt(float phase)
    {
        return glisson_ ? (endSpeed_ - startSpeed_) * phase + startSpeed_ : startSpeed_;
    }

    void Glisson::setGlissonEnabled(bool enabled)
    {
        glisson_ = enabled;
    }

    IRandomRange<float>& Glisson::getStartRandomRange()
    {
        return *startRandomRange_;
    }

    IRandomRange<float>& Glisson::getEndRandomRange()
    {
        return *endRandomRange_;
    }
}
