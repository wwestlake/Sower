#include "AudioFileManagerComponent.h"

//==============================================================================
// AudioFileManagerComponent

AudioFileManagerComponent::AudioFileManagerComponent()
{
    addAndMakeVisible(addFilesButton);
    addFilesButton.onClick = [this]() { openFileChooser(); };

    fileListViewport.setViewedComponent(&fileListContainer, false);
    addAndMakeVisible(fileListViewport);
}

void AudioFileManagerComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioFileManagerComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    addFilesButton.setBounds(area.removeFromTop(30));
    area.removeFromTop(10);
    fileListViewport.setBounds(area);
}

void AudioFileManagerComponent::openFileChooser()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select audio files...", juce::File(), "*.wav;*.aiff;*.mp3");

    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles
        | juce::FileBrowserComponent::canSelectMultipleItems,
        [this](const juce::FileChooser& fc)
        {
            DBG("Callback fired");
            auto files = fc.getResults();
            DBG("Files selected: " + juce::String(files.size()));
            updateFileList(files);
            fileChooser.reset();
        });
}

void AudioFileManagerComponent::updateFileList(const juce::Array<juce::File>& newFiles)
{
    DBG("updateFileList called with " + juce::String(newFiles.size()) + " files");

    fileListContainer.clearItems();

    for (const auto& file : newFiles)
    {
        DBG("Adding file: " + file.getFileName());
        fileListContainer.addFileItem(file);
    }

    int itemHeight = 70;
    fileListContainer.setSize(fileListViewport.getWidth(), newFiles.size() * itemHeight);
    fileListContainer.resized();
}

//==============================================================================
// FileListContainer

void AudioFileManagerComponent::FileListContainer::addFileItem(const juce::File& file)
{
    auto* item = new FileItemComponent(file);
    items.add(item);
    addAndMakeVisible(item);
}

void AudioFileManagerComponent::FileListContainer::clearItems()
{
    for (auto* item : items)
        removeChildComponent(item);

    items.clear(true);
}

void AudioFileManagerComponent::FileListContainer::resized()
{
    int y = 0;
    for (auto* item : items)
    {
        item->setBounds(5, y, getWidth() - 10, 60);
        y += 70;
    }

    setSize(getWidth(), std::max(y, getHeight()));
}

//==============================================================================
// FileItemComponent

AudioFileManagerComponent::FileListContainer::FileItemComponent::FileItemComponent(const juce::File& f)
    : file(f)
{
    auto font = juce::Font(14.0f);

    pathLabel.setText(file.getFullPathName(), juce::dontSendNotification);
    pathLabel.setFont(font);
    addAndMakeVisible(pathLabel);

    juce::String detailText = file.getFileName()
        + " | " + juce::File::descriptionOfSizeInBytes(file.getSize())
        + " | " + file.getLastModificationTime().toString(true, true);

    detailsLabel.setText(detailText, juce::dontSendNotification);
    detailsLabel.setFont(font.withHeight(12.0f));
    addAndMakeVisible(detailsLabel);
}

void AudioFileManagerComponent::FileListContainer::FileItemComponent::paint(juce::Graphics& g)
{
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1), 6.0f, 1.0f);
}

void AudioFileManagerComponent::FileListContainer::FileItemComponent::resized()
{
    auto area = getLocalBounds().reduced(5);
    pathLabel.setBounds(area.removeFromTop(20));
    detailsLabel.setBounds(area.removeFromTop(20));
}
