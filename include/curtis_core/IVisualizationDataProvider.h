#pragma once

#include <vector>
#include "VisualizationDataSet.h"

namespace rp::curtis
{
    class IVisualizationDataProvider
    {
    public:
        virtual ~IVisualizationDataProvider() = default;

        virtual const std::vector<VisualizationDataSet>& getVisualizationDataSets() = 0;
    };
}

