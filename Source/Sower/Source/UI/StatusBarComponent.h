#pragma once
#include <JuceHeader.h>

class StatusBarComponent : public juce::Component
{
public:
    StatusBarComponent();

    void resized() override;
    void setStatusText(const juce::String& text);
    void paint(juce::Graphics&) override;

private:
    juce::TextButton playButton{ "▶" };
    juce::TextButton stopButton{ "⏹" };
    juce::TextButton repeatButton{ "🔁" };

    juce::Label statusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StatusBarComponent)
};
