#pragma once

#include "VisualizationDataSet.h"

namespace rp::curtis
{
    class IVisualizationDataCache
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onVisualizationDataCacheFilled(const std::vector<VisualizationDataSet> cache) = 0;
        };

    public:
        virtual ~IVisualizationDataCache() = default;

        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;
    };
}

