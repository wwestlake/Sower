#pragma once
#include <JuceHeader.h>

class LabeledSlider : public juce::Component
{
public:
    LabeledSlider(const juce::String& labelText = "Label");

    void resized() override;
    void paint(juce::Graphics& g) override;

    void setValue(double newValue, juce::NotificationType notification = juce::dontSendNotification);
    double getValue() const;

    void setRange(double min, double max, double interval = 0.01);
    void setText(const juce::String& newText); // Optional relabel

    juce::Slider& getSlider(); // Optional access to configure externally
    void setSliderStyle(juce::Slider::SliderStyle style);

private:
    juce::Label label;
    juce::Slider slider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabeledSlider)
};
