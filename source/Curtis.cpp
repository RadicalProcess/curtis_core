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

    Curtis::Curtis(float sampleRate, size_t blockSize, const IFactory& factory)
    : inputMix_(factory.createInputMix())
    , segmentBank_(factory.createSegmentBank(32, calcMaxBufferSize(sampleRate)))
    , segmentDetector_(factory.createSegmentDetector(sampleRate, calcMaxBufferSize(sampleRate)))
    , granulator_(factory.createGranulator(*segmentBank_, calcMaxBufferSize(sampleRate), 512))
    {
        segmentDetector_->addListener(dynamic_cast<ISegmentDetector::Listener*>(segmentBank_.get()));
        for(auto i = 0; i < 2; ++i)
            dryBuffers_.emplace_back(std::make_unique<Buffer>(blockSize, true));
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

    void Curtis::setRepeat(size_t maxCount)
    {
        granulator_->getCounter().setMaxCount(maxCount);
    }

    void Curtis::setRandomRange(size_t range)
    {
        granulator_->setRandomRange(range);
    }

    void Curtis::setGlissonEnabled(bool enabled)
    {
        granulator_->getGlisson().setGlissonEnabled(enabled);
    }

    void Curtis::setStartSpeedA(float speed)
    {
        granulator_->getGlisson().getStartRandomRange().setA(speed);
    }

    void Curtis::setStartSpeedB(float speed)
    {
        granulator_->getGlisson().getStartRandomRange().setB(speed);
    }

    void Curtis::setEndSpeedA(float speed)
    {
        granulator_->getGlisson().getEndRandomRange().setA(speed);
    }

    void Curtis::setEndSpeedB(float speed)
    {
        granulator_->getGlisson().getEndRandomRange().setB(speed);
    }

    void Curtis::setStartPositionA(float position)
    {
        granulator_->getPanner().setStartA(position);
    }

    void Curtis::setStartPositionB(float position)
    {
        granulator_->getPanner().setStartB(position);
    }

    void Curtis::setEndPositionA(float position)
    {
        granulator_->getPanner().setEndA(position);
    }

    void Curtis::setEndPositionB(float position)
    {
        granulator_->getPanner().setEndB(position);
    }

    void Curtis::setDry(float dry)
    {
        dry_ = dry;
    }

    void Curtis::setWet(float wet)
    {
        wet_ = wet;
    }

    void Curtis::process(IBuffer& left, IBuffer& right)
    {
        dryBuffers_[0]->copyFrom(left);
        dryBuffers_[1]->copyFrom(right);

        inputMix_->process(left, right);
        segmentDetector_->process(left);
        granulator_->process(left, right);

        dryBuffers_[0]->applyGain(dry_);
        dryBuffers_[1]->applyGain(dry_);
        left.applyGain(wet_);
        right.applyGain(wet_);

        left.addFrom(*dryBuffers_[0]);
        right.addFrom(*dryBuffers_[1]);
    }
}
