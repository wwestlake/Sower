#include <JuceHeader.h>
#include "OscilloscopeEffect.h"
#include "OscilloscopeData.h"

void OscilloscopeEffect::setVisualizerCallback(std::function<void(std::shared_ptr<VisualizerDataBase>)> callback)
{
    visualizerCallback = std::move(callback);
}

void OscilloscopeEffect::processFrame(const float* input, size_t numSamples)
{
    if (visualizerCallback)
    {
        double timeNow = juce::Time::getMillisecondCounterHiRes() / 1000.0;

        std::shared_ptr<VisualizerDataBase> data = std::make_shared<OscilloscopeData>(
            input, numSamples, timeNow,this->sampleRate
        );

        visualizerCallback(data);
    }
}
