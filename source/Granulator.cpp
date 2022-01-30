#include "Granulator.h"

#include <cmath>

#include "IFactory.h"
#include "VisualizationDataSet.h"

namespace rp::curtis
{
    namespace
    {
        size_t wrap(int index, size_t size)
        {
            return index >= 0 ?
                static_cast<size_t>(index) :
                static_cast<size_t>(index + static_cast<int>(size));
        }
    }

    Granulator::Granulator(const ISegmentBank& segmentBank, size_t maxBufferSize, const IFactory& factory)
    : segmentBank_(segmentBank)
    , readBuffer_(factory.createReadBuffer(maxBufferSize))
    , counter_(factory.createCounter())
    , randomizer_(factory.createRandomizer())
    , glisson_(factory.createGlisson())
    , density_(factory.createDensity())
    , panner_(factory.createPanner())
    , latestIndex_(0)
    {
    }

    void Granulator::setDensity(int percentage)
    {
        density_->set(percentage);
    }

    void Granulator::setRandomRange(size_t range)
    {
        randomizer_->setRange(range);
    }

    ICounter& Granulator::getCounter()
    {
        return *counter_;
    }

    IGlisson& Granulator::getGlisson()
    {
        return *glisson_;
    }

    IPanner& Granulator::getPanner()
    {
        return *panner_;
    }

    void Granulator::process(IBuffer& leftBuffer, IBuffer& rightBuffer)
    {
        auto visualizationDataSet = VisualizationDataSet();
        auto* leftPtr = leftBuffer.getWritePtr();
        auto* rightPtr = rightBuffer.getWritePtr();
        auto sampleCount = leftBuffer.size();
        while(sampleCount--)
        {
            const auto sample = density_->get() ? readBuffer_->getSample() : 0.0f;
            const auto phase = readBuffer_->getPhase();
            const auto [leftGain, rightGain, position] = panner_->getGainAt(phase);
            const auto speed = glisson_->getSpeedAt(phase);
            const auto leftSample = sample * leftGain;
            const auto rightSample = sample * rightGain;
            *leftPtr++ = leftSample;
            *rightPtr++ = rightSample;

            visualizationDataSet.pitch = speed;
            visualizationDataSet.pan = position;
            visualizationDataSet.sampleL = leftSample;
            visualizationDataSet.sampleR = rightSample;

            if(readBuffer_->advancePlayHead(speed))
            {
                if(counter_->count())
                {
                    latestIndex_ = segmentBank_.getLatestCacheIndex();
                }
                density_->roll();
                glisson_->update();
                auto target = static_cast<int>(latestIndex_) - static_cast<int>(randomizer_->getValue());
                readBuffer_->updateBuffer(segmentBank_.getCache(wrap(target, segmentBank_.size())));
            }
        }
    }
}
