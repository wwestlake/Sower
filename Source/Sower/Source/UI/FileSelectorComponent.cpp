#include "FileSelectorComponent.h"

FileSelectorComponent::FileSelectorComponent(const juce::String& labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(label);

    filePathDisplay.setReadOnly(true);
    addAndMakeVisible(filePathDisplay);

    browseButton.addListener(this);
    addAndMakeVisible(browseButton);
}
void FileSelectorComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void FileSelectorComponent::resized()
{
    auto area = getLocalBounds().reduced(5);
    auto labelArea = area.removeFromTop(20);
    label.setBounds(labelArea);

    area.removeFromTop(5); // spacing

    auto browseWidth = 80;
    filePathDisplay.setBounds(area.removeFromLeft(area.getWidth() - browseWidth - 5));
    browseButton.setBounds(area);
}

void FileSelectorComponent::buttonClicked(juce::Button* b)
{
    if (b == &browseButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>("Select a file...", juce::File(), "*");

        DBG("Chooser launched");

        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto chosen = fc.getResult();
                if (chosen.existsAsFile())
                {
                    selectedFile = chosen;
                    filePathDisplay.setText(selectedFile.getFullPathName(), juce::dontSendNotification);
                }

                // Clean up the fileChooser after use
                fileChooser.reset();
            });
    }
}

juce::File FileSelectorComponent::getSelectedFile() const
{
    return selectedFile;
}
