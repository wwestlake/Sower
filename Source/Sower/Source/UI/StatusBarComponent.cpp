#include "StatusBarComponent.h"

StatusBarComponent::StatusBarComponent()
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(repeatButton);

    statusLabel.setText("Ready", juce::dontSendNotification);
    statusLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(statusLabel);
}

void StatusBarComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void StatusBarComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto buttonArea = area.removeFromLeft(100);

    playButton.setBounds(buttonArea.removeFromLeft(30));
    stopButton.setBounds(buttonArea.removeFromLeft(30));
    repeatButton.setBounds(buttonArea.removeFromLeft(30));

    statusLabel.setBounds(area);
}

void StatusBarComponent::setStatusText(const juce::String& text)
{
    statusLabel.setText(text, juce::dontSendNotification);
}
