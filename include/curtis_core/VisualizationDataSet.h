#pragma once

namespace rp::curtis
{
    struct VisualizationDataSet
    {
        void scale(float ratio)
        {
            pitch *= ratio;
            pan *= ratio;
            sampleL *= ratio;
            sampleR *= ratio;
        }

        float pitch;
        float pan;
        float sampleL;
        float sampleR;
        bool segment;
    };
}
