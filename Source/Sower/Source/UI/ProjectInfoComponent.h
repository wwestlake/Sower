#pragma once
#include <JuceHeader.h>
#include "LabeledTextBox.h"
#include "AudioFileManagerComponent.h"

class ProjectInfoComponent : public juce::Component
{
public:
    ProjectInfoComponent();

    void resized() override;
    void paint(juce::Graphics& g) override;
    juce::var getJson() const;
    void setFromJson(const juce::var& json);

private:
    LabeledTextBox projectNameField{ "Project Name" };
    LabeledTextBox authorField{ "Author" };
    LabeledTextBox copyrightField{ "Copyright" };
    LabeledTextBox descriptionField{ "Description" };

    AudioFileManagerComponent fileSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectInfoComponent)
};
