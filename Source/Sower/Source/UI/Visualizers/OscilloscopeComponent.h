#pragma once

#include <JuceHeader.h>
#include "Plot2DComponent.h"
#include "../LabeledSlider.h"

class OscilloscopeComponent : public juce::Component
{
public:
    OscilloscopeComponent();
    ~OscilloscopeComponent() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Plot2DComponent plot;

    LabeledSlider timeScaleSlider{ "Time Scale" };
    LabeledSlider verticalScaleSlider{ "Vertical Scale" };
    LabeledSlider triggerThresholdSlider{ "Trigger Level" };
    LabeledSlider brightnessSlider{ "Brightness" }; // New brightness control

    juce::TextButton triggerEdgeButton{ "Toggle Edge" };
    juce::TextButton pauseButton{ "Pause" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilloscopeComponent)
};
