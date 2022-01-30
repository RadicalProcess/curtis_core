#pragma once

namespace rp::curtis
{
    struct VisualizationDataSet
    {
        VisualizationDataSet(float pitch, float pan, float sampleL, float sampleR, bool segment)
        : pitch(pitch), pan(pan), sampleL(sampleL), sampleR(sampleR), segment(segment){}

        float pitch;
        float pan;
        float sampleL;
        float sampleR;
        bool segment;
    };
}
