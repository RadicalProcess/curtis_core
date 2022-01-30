#pragma once

#include <vector>
#include <stdexcept>

#include "Buffer.h"

namespace rp::curtis
{
    struct VisualizationData
    {
        inline
        explicit VisualizationData(size_t size)
        : pitch(size, true)
        , pan(size, true)
        , segment(size, true)
        , waveLeft(size, true)
        , waveRight(size, true)
        {
        }

        inline
        size_t size() const
        {
            return pitch.size();
        }

        inline
        VisualizationData& operator=(const VisualizationData& visualizationData)
        {
            if(size() != visualizationData.size())
                throw std::out_of_range("trying to copy visualization data with different sizes");

            pitch.copyFrom(visualizationData.pitch);
            pan.copyFrom(visualizationData.pan);
            segment.copyFrom(visualizationData.segment);
            waveLeft.copyFrom(visualizationData.waveLeft);
            waveRight.copyFrom(visualizationData.waveRight);

            return *this;
        }

        Buffer pitch;
        Buffer pan;
        Buffer segment;
        Buffer waveLeft;
        Buffer waveRight;
    };
}
