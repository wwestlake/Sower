#include "OscilloscopeComponent.h"

OscilloscopeComponent::OscilloscopeComponent()
{
    // === Plot visuals ===
    addAndMakeVisible(plot);
    plot.setShowGrid(true);
    plot.setGridLineColor(juce::Colours::cyan);
    plot.setAxisLineColor(juce::Colours::blue);
    plot.setTickMarkColor(juce::Colours::yellow);
    plot.setMarkerColor(juce::Colours::yellow);
    plot.setAxisAlpha(1.0f);

    // Force initial axis ranges (ensures axis lines/ticks render correctly)
    plot.setXRange(-1.0f, 1.0f);      // Time scale default range
    plot.setYRange(-1.0f, 1.0f);     // Vertical scale default range
    plot.setHorizontalMarker(0, 0.0f, "Trigger"); // Show trigger marker at 0.0

    // === Time Scale Slider ===
    addAndMakeVisible(timeScaleSlider);
    timeScaleSlider.setRange(0.01, 1.0, 0.01);
    timeScaleSlider.setValue(1.0);
    timeScaleSlider.getSlider().onValueChange = [this]()
        {

        };

    // === Vertical Scale Slider ===
    addAndMakeVisible(verticalScaleSlider);
    verticalScaleSlider.setRange(0.01, 1.0, 0.01);
    verticalScaleSlider.setValue(1.0);
    verticalScaleSlider.getSlider().onValueChange = [this]()
        {
        };

    // === Trigger Threshold Slider ===
    addAndMakeVisible(triggerThresholdSlider);
    triggerThresholdSlider.setRange(-1.0, 1.0, 0.01);
    triggerThresholdSlider.setValue(0.0);
    triggerThresholdSlider.getSlider().onValueChange = [this]()
        {
            plot.setHorizontalMarker(0, triggerThresholdSlider.getValue(), "Trigger");
        };

    // === Brightness Slider ===
    addAndMakeVisible(brightnessSlider);
    brightnessSlider.setRange(0.1, 1.0, 0.01);
    brightnessSlider.setValue(1.0);
    brightnessSlider.getSlider().onValueChange = [this]()
        {
            plot.setAxisAlpha(brightnessSlider.getValue());
            plot.repaint();
        };

    // === Buttons ===
    addAndMakeVisible(triggerEdgeButton);
    addAndMakeVisible(pauseButton);
}

void OscilloscopeComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscilloscopeComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto topRow = area.removeFromTop(100);

    auto quarterWidth = topRow.getWidth() / 4;

    auto timeCol = topRow.removeFromLeft(quarterWidth).reduced(4);
    timeScaleSlider.setBounds(timeCol);

    auto vertCol = topRow.removeFromLeft(quarterWidth).reduced(4);
    verticalScaleSlider.setBounds(vertCol);

    auto trigCol = topRow.removeFromLeft(quarterWidth).reduced(4);
    triggerThresholdSlider.setBounds(trigCol);

    auto brightCol = topRow.removeFromLeft(quarterWidth).reduced(4);
    brightnessSlider.setBounds(brightCol);

    auto buttonRow = area.removeFromTop(30);
    triggerEdgeButton.setBounds(buttonRow.removeFromLeft(120).reduced(4));
    pauseButton.setBounds(buttonRow.removeFromLeft(120).reduced(4));

    plot.setBounds(area);
}
