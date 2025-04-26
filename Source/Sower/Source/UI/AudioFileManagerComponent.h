#pragma once

#include <JuceHeader.h>

class AudioFileManagerComponent : public juce::Component
{
public:
    AudioFileManagerComponent();
    ~AudioFileManagerComponent() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void openFileChooser();
    void updateFileList(const juce::Array<juce::File>& newFiles);

    // Subcomponent that holds and lays out file items
    class FileListContainer : public juce::Component
    {
    public:
        void addFileItem(const juce::File& file);
        void clearItems();
        void resized() override;

    private:
        class FileItemComponent : public juce::Component
        {
        public:
            FileItemComponent(const juce::File& file);
            void paint(juce::Graphics&) override;
            void resized() override;

        private:
            juce::File file;
            juce::Label pathLabel, detailsLabel;
        };

        juce::OwnedArray<FileItemComponent> items;
    };

    juce::TextButton addFilesButton{ "+ Add File(s)..." };
    juce::Viewport fileListViewport;
    FileListContainer fileListContainer;

    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioFileManagerComponent)
};
