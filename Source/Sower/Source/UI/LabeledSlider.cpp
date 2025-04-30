#include "LabeledSlider.h"

LabeledSlider::LabeledSlider(const juce::String& labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    addAndMakeVisible(slider);
}

void LabeledSlider::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void LabeledSlider::resized()
{
    auto area = getLocalBounds().reduced(4);
    label.setBounds(area.removeFromTop(20));
    slider.setBounds(area.removeFromTop(24));
}

void LabeledSlider::setSliderStyle(juce::Slider::SliderStyle style)
{
    slider.setSliderStyle(style);
}

void LabeledSlider::setValue(double newValue, juce::NotificationType notification)
{
    slider.setValue(newValue, notification);
}

double LabeledSlider::getValue() const
{
    return slider.getValue();
}

void LabeledSlider::setRange(double min, double max, double interval)
{
    slider.setRange(min, max, interval);
}

void LabeledSlider::setText(const juce::String& newText)
{
    label.setText(newText, juce::dontSendNotification);
}

juce::Slider& LabeledSlider::getSlider()
{
    return slider;
}
