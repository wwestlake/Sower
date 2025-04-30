#pragma once

#include "VisualizerDataBase.h"
#include "../EffectBase.h"
#include "../EffectDataBase.h""
#include <memory>

struct OscilloscopeData : public VisualizerDataBase
{
    const float* buffer = nullptr;
    size_t numSamples = 0;

    OscilloscopeData(const float* b, size_t n)
        : buffer(b), numSamples(n)
    {
    }
};

class OscilloscopeEffect : public EffectBase
{
    const EffectMetadata OscilloscopeMetadata = {
        "Oscilloscope",
        "Displays a real-time waveform of the signal at this point in the chain.",
        "Visualization",
        "icon_scope" // Use whatever icon name or ID your UI system expects
    };

public:
    OscilloscopeEffect() = default;
    ~OscilloscopeEffect() override = default;

    virtual void setVisualizerCallback(std::function<void(std::shared_ptr<VisualizerDataBase>)> callback) override;
    void processFrame(const float* input, size_t numSamples);

    virtual void prepare(double sampleRate, int samplesPerBlock) override {};
    virtual void reset() override {};
    //virtual const char* getName() override { return "Osciliscope"; };
    //virtual const EffectMetadata& getMetadata() override { return OscilloscopeMetadata; };


private:
    std::function<void(std::shared_ptr<VisualizerDataBase>)> visualizerCallback;
};
