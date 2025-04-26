#pragma once
#include <JuceHeader.h>



class LabeledTextBox : public juce::Component
{
public:
    LabeledTextBox(const juce::String& labelText = "Label");

    void resized() override;
    void setText(const juce::String& newText);
    void paint(juce::Graphics& g) override;

    juce::String getText() const;

private:
    juce::Label label;
    juce::TextEditor textEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabeledTextBox)
};

