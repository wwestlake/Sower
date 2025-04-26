#include "LabeledTextBox.h"

LabeledTextBox::LabeledTextBox(const juce::String& labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(label);

    textEditor.setMultiLine(false);
    textEditor.setText("");
    addAndMakeVisible(textEditor);
}
void LabeledTextBox::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}
void LabeledTextBox::resized()
{
    auto area = getLocalBounds().reduced(4);
    label.setBounds(area.removeFromTop(20));
    textEditor.setBounds(area.removeFromTop(24));
}

void LabeledTextBox::setText(const juce::String& newText)
{
    textEditor.setText(newText, juce::dontSendNotification);
}

juce::String LabeledTextBox::getText() const
{
    return textEditor.getText();
}
