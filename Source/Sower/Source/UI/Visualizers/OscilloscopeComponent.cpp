#include "OscilloscopeComponent.h"

OscilloscopeComponent::OscilloscopeComponent()
{
    // Add LabeledSliders
    addAndMakeVisible(timeScaleSlider);
    timeScaleSlider.setRange(1.0, 100.0, 1.0);
    timeScaleSlider.setValue(20.0);
    //timeScaleSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);

    addAndMakeVisible(verticalScaleSlider);
    verticalScaleSlider.setRange(0.1, 5.0, 0.1);
    verticalScaleSlider.setValue(1.0);
    //verticalScaleSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(triggerThresholdSlider);
    triggerThresholdSlider.setRange(-1.0, 1.0, 0.01);
    triggerThresholdSlider.setValue(0.0);
    //triggerThresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);

    // Add buttons
    triggerEdgeButton.setButtonText("Rising Edge");
    triggerEdgeButton.setToggleState(true, juce::dontSendNotification);

    pauseButton.setButtonText("Pause");
    pauseButton.setToggleState(false, juce::dontSendNotification);

    addAndMakeVisible(triggerEdgeButton);
    addAndMakeVisible(pauseButton);

    addAndMakeVisible(controlGroup);

    startTimerHz(30); // Refresh ~30 FPS
}

OscilloscopeComponent::~OscilloscopeComponent() {}

void OscilloscopeComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto topRow = area.removeFromTop(100);

    auto thirdWidth = topRow.getWidth() / 3;

    // Time Scale
    auto timeCol = topRow.removeFromLeft(thirdWidth).reduced(4);
    timeScaleSlider.setBounds(timeCol);

    // Vertical Scale
    auto vertCol = topRow.removeFromLeft(thirdWidth).reduced(4);
    verticalScaleSlider.setBounds(vertCol);

    // Trigger
    auto trigCol = topRow.removeFromLeft(thirdWidth).reduced(4);
    triggerThresholdSlider.setBounds(trigCol);

    // Buttons below
    auto buttonRow = area.removeFromTop(30);
    triggerEdgeButton.setBounds(buttonRow.removeFromLeft(120).reduced(4));
    pauseButton.setBounds(buttonRow.removeFromLeft(120).reduced(4));
}

void OscilloscopeComponent::paint(juce::Graphics& g)
{
    auto bg = findColour(toColourId(ThemeColorId::OscilloscopeGrid));
    g.fillAll(bg);

    g.setColour(findColour(toColourId(ThemeColorId::OscilloscopeWaveformInactive)));
    g.drawText("Oscilloscope Display Area (Coming Soon)", getLocalBounds(), juce::Justification::centred);
}

void OscilloscopeComponent::pushNewBuffer(const float* data, size_t numSamples, int channelId)
{
    if (pauseButton.getToggleState())
        return;

    std::scoped_lock lock(bufferMutex);
    waveformBuffer.assign(data, data + numSamples);
}

void OscilloscopeComponent::timerCallback()
{
    repaint();
}
