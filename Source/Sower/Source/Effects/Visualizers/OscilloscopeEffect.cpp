#include "OscilloscopeEffect.h"

void OscilloscopeEffect::setVisualizerCallback(std::function<void(std::shared_ptr<VisualizerDataBase>)> callback)
{
    visualizerCallback = std::move(callback);
}

void OscilloscopeEffect::processFrame(const float* input, size_t numSamples)
{
    if (visualizerCallback)
    {
        std::shared_ptr<VisualizerDataBase> data = std::make_shared<OscilloscopeData>( input, numSamples );
        visualizerCallback(data);
    }
}
