#pragma once

#include "VisualizationData.h"

namespace rp::curtis
{
    class IVisualizationDataProvider
    {
    public:
        virtual ~IVisualizationDataProvider() = default;

        virtual const VisualizationData& getVisualizationData() = 0;
    };
}

