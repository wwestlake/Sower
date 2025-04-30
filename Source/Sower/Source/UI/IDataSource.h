#pragma once

#include <functional>
#include "../Effects/Visualizers/VisualizerDataBase.h"

class IDataSource
{
public:
    virtual ~IDataSource() = default;

    // Allow a UI visualizer to register a callback for visual data updates
    virtual void attachDataSource(std::function<void(std::shared_ptr<VisualizerDataBase>)> callback) = 0;
};
