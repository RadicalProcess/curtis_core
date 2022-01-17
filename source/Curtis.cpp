#include "Curtis.h"

namespace rp::curtis
{
    namespace
    {
        size_t calcMaxBufferSize(float sampleRate)
        {
            return static_cast<size_t>(sampleRate);// 1000ms
        }
    }

    Curtis::Curtis(float sampleRate, const IFactory& factory)
    : inputMix_(factory.createInputMix())
    , segmentBank_(factory.createSegmentBank(32, calcMaxBufferSize(sampleRate)))
    , segmentDetector_(factory.createSegmentDetector(sampleRate, calcMaxBufferSize(sampleRate)))
    , granulator_(factory.createGranulator(*segmentBank_, calcMaxBufferSize(sampleRate)))
    {
        segmentDetector_->addListener(dynamic_cast<ISegmentDetector::Listener*>(segmentBank_.get()));
    }

    void Curtis::setMix(float mix)
    {
        inputMix_->setMix(mix);
    }

    void Curtis::setSegmentMinLength(float ms)
    {
        segmentDetector_->setSegmentMinLength(ms);
    }

    void Curtis::setDensity(int percentage)
    {
        granulator_->setDensity(percentage);
    }

    void Curtis::setRepeatMin(size_t count)
    {
        granulator_->getCounter().getRandomRange().setMin(count);
    }

    void Curtis::setRepeatMax(size_t count)
    {
        granulator_->getCounter().getRandomRange().setMax(count);
    }

    void Curtis::setRandomRange(size_t range)
    {
        granulator_->setRandomRange(range);
    }

    void Curtis::setGlissonEnabled(bool enabled)
    {
        granulator_->getGlisson().setGlissonEnabled(enabled);
    }

    void Curtis::setStartMinSpeed(float speed)
    {
        granulator_->getGlisson().getStartRandomRange().setMin(speed);
    }

    void Curtis::setStartMaxSpeed(float speed)
    {
        granulator_->getGlisson().getStartRandomRange().setMax(speed);
    }

    void Curtis::setEndMinSpeed(float speed)
    {
        granulator_->getGlisson().getEndRandomRange().setMin(speed);
    }

    void Curtis::setEndMaxSpeed(float speed)
    {
        granulator_->getGlisson().getEndRandomRange().setMax(speed);
    }

    void Curtis::setStartLeft(float position)
    {
        granulator_->getPanner().setStartLeft(position);
    }

    void Curtis::setStartRight(float position)
    {
        granulator_->getPanner().setStartRight(position);
    }

    void Curtis::setEndLeft(float position)
    {
        granulator_->getPanner().setEndLeft(position);
    }

    void Curtis::setEndRight(float position)
    {
        granulator_->getPanner().setEndRight(position);
    }

    void Curtis::process(IBuffer& left, IBuffer& right)
    {
        inputMix_->process(left, right);
        segmentDetector_->process(left);
        granulator_->process(left, right);
    }
}
