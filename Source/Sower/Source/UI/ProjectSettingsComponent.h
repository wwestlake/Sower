// ProjectSettingsComponent.h
#pragma once

#include <JuceHeader.h>

class ProjectSettingsComponent : public juce::Component,
    private juce::ListBoxModel
{
public:
    ProjectSettingsComponent();
    ~ProjectSettingsComponent() override;

    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    juce::Label projectRootLabel{ "Project Root", "Project Root Folder:" };
    juce::TextEditor projectRootPath;
    juce::TextButton browseProjectRootButton{ "Browse..." };
    std::unique_ptr<juce::FileChooser> folderChooser;

    juce::Label modulePathsLabel{ "Module Paths", "Module Folders:" };
    juce::TextButton addModuleFolderButton{ "+ Add Folder" };
    juce::ListBox moduleListBox;
    juce::Array<juce::File> moduleFolders;

    juce::Label outputLabel{ "Output Settings", "Audio Output Settings:" };
    juce::ComboBox formatBox;
    juce::ComboBox sampleRateBox;
    juce::ComboBox bitDepthBox;
    juce::ComboBox channelBox;

    juce::Label themeLabel{ "Theme", "Theme:" };
    juce::ComboBox themeSelector;

    void openProjectRootChooser();
    void openModuleFolderChooser();
    void populateThemesDropdown();

    // ListBoxModel overrides
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent&) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectSettingsComponent)
};
