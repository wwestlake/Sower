#pragma once

#include <JuceHeader.h>

class ProjectSettingsComponent : public juce::Component
{
public:
    ProjectSettingsComponent();

    void resized() override;
    void paint(juce::Graphics& g) override;

    juce::var getJson() const;
    void setFromJson(const juce::var& json);

private:
    // === Project Root Folder ===
    juce::Label projectRootLabel{ "Project Root", "Project Root Folder:" };
    juce::TextEditor projectRootPath;
    juce::TextButton browseProjectRootButton{ "Browse..." };
    std::unique_ptr<juce::FileChooser> folderChooser;

    // === Module Folder List ===
    juce::Label modulePathsLabel{ "Module Paths", "Module Folders:" };
    juce::TextButton addModuleFolderButton{ "+ Add Folder" };
    juce::Viewport moduleListViewport;

    class ModuleListContainer : public juce::Component
    {
    public:
        void addFolder(const juce::File& folder);
        void clearAll();
        void resized() override;
        void paint(juce::Graphics& g) override;
        juce::Array<juce::File> getAllFolders() const;

        class ModuleItem : public juce::Component
        {
        public:
            juce::File folder;

            ModuleItem(const juce::File& f, std::function<void(ModuleItem*)> onDelete);
            void resized() override;
            void paint(juce::Graphics& g) override;

        private:
            juce::Label pathLabel;
            juce::TextButton removeButton{ "Remove" };
            std::function<void(ModuleItem*)> onDeleteCallback;
        };

    private:
        juce::OwnedArray<ModuleItem> items;
    };

    ModuleListContainer moduleListContainer;

    // === Audio Output Settings ===
    juce::Label outputLabel{ "Output Settings", "Audio Output Settings:" };
    juce::ComboBox formatBox;
    juce::ComboBox sampleRateBox;
    juce::ComboBox bitDepthBox;
    juce::ComboBox channelBox;

    // === Theme ===
    juce::Label themeLabel{ "Theme", "Theme:" };
    juce::ComboBox themeSelector;

    void openProjectRootChooser();
    void openModuleFolderChooser();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectSettingsComponent)
};
