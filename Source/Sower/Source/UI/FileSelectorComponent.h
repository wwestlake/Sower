#pragma once
#include <JuceHeader.h>

class FileSelectorComponent : public juce::Component,
    private juce::Button::Listener
{
public:
    FileSelectorComponent(const juce::String& labelText = "Select File:");
    ~FileSelectorComponent() override = default;

    void resized() override;
    void paint(juce::Graphics& g) override;

    juce::File getSelectedFile() const;

private:
    void buttonClicked(juce::Button* button) override;

    juce::Label label;
    juce::TextEditor filePathDisplay;
    juce::TextButton browseButton{ "Browse..." };

    juce::File selectedFile;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileSelectorComponent)
};
