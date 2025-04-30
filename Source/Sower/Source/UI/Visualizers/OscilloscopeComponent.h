#pragma once

#include <JuceHeader.h>
#include "../ThemeColorId.h"
#include "../LabeledSlider.h" // Include your new slider

class OscilloscopeComponent : public juce::Component,
    private juce::Timer
{
public:
    OscilloscopeComponent();
    ~OscilloscopeComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void pushNewBuffer(const float* data, size_t numSamples, int channelId);

private:
    void timerCallback() override;

    // === UI Controls ===
    LabeledSlider timeScaleSlider{ "Time Scale" };
    LabeledSlider verticalScaleSlider{ "Vertical Scale" };
    LabeledSlider triggerThresholdSlider{ "Trigger" };

    juce::ToggleButton triggerEdgeButton;
    juce::ToggleButton pauseButton;

    juce::GroupComponent controlGroup{ "controls", "Scope Controls" };

    std::vector<float> waveformBuffer;
    std::mutex bufferMutex;
    bool isPaused = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilloscopeComponent)
};
