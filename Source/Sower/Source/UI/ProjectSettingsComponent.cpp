// ProjectSettingsComponent.cpp
#include "ProjectSettingsComponent.h"
#include "ThemeManager.h"

ProjectSettingsComponent::ProjectSettingsComponent()
{
    addAndMakeVisible(projectRootLabel);
    addAndMakeVisible(projectRootPath);
    addAndMakeVisible(browseProjectRootButton);
    browseProjectRootButton.onClick = [this]() { openProjectRootChooser(); };

    addAndMakeVisible(modulePathsLabel);
    addAndMakeVisible(addModuleFolderButton);
    addAndMakeVisible(moduleListBox);
    moduleListBox.setModel(this);

    addModuleFolderButton.onClick = [this]() { openModuleFolderChooser(); };

    addAndMakeVisible(outputLabel);
    addAndMakeVisible(formatBox);
    addAndMakeVisible(sampleRateBox);
    addAndMakeVisible(bitDepthBox);
    addAndMakeVisible(channelBox);

    formatBox.addItemList({ "WAV", "AIFF", "FLAC", "MP3" }, 1);
    sampleRateBox.addItemList({ "44100", "48000", "96000" }, 1);
    bitDepthBox.addItemList({ "16-bit", "24-bit", "32-bit" }, 1);
    channelBox.addItemList({ "Mono", "Stereo" }, 1);

    formatBox.setSelectedId(1);
    sampleRateBox.setSelectedId(1);
    bitDepthBox.setSelectedId(2);
    channelBox.setSelectedId(2);

    addAndMakeVisible(themeLabel);
    addAndMakeVisible(themeSelector);
    populateThemesDropdown();

    themeSelector.onChange = [this]()
        {
            auto selectedName = themeSelector.getText();
            ThemeManager::setActiveTheme(selectedName);
        };
}

ProjectSettingsComponent::~ProjectSettingsComponent() = default;

void ProjectSettingsComponent::populateThemesDropdown()
{
    auto names = ThemeManager::getAvailableThemeNames();
    themeSelector.clear();

    int id = 1;
    for (const auto& name : names)
        themeSelector.addItem(name, id++);

    if (themeSelector.getSelectedId() == 0)
    {
        auto defaultTheme = ThemeManager::getActiveTheme().name;
        themeSelector.setText(defaultTheme, juce::dontSendNotification);
    }
}

void ProjectSettingsComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    int rowHeight = 28;

    projectRootLabel.setBounds(area.removeFromTop(rowHeight));
    projectRootPath.setBounds(10, area.getY(), getWidth() - 120, rowHeight);
    browseProjectRootButton.setBounds(getWidth() - 100, area.getY(), 90, rowHeight);
    area.removeFromTop(rowHeight + 10);

    modulePathsLabel.setBounds(area.removeFromTop(rowHeight));
    addModuleFolderButton.setBounds(area.removeFromTop(rowHeight));
    moduleListBox.setBounds(area.removeFromTop(150));

    area.removeFromTop(10);
    outputLabel.setBounds(area.removeFromTop(rowHeight));

    formatBox.setBounds(10, area.getY(), 120, rowHeight);
    sampleRateBox.setBounds(140, area.getY(), 100, rowHeight);
    bitDepthBox.setBounds(250, area.getY(), 100, rowHeight);
    channelBox.setBounds(360, area.getY(), 100, rowHeight);

    themeLabel.setBounds(10, getHeight() - 60, 100, 24);
    themeSelector.setBounds(120, getHeight() - 60, 150, 24);
}

void ProjectSettingsComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void ProjectSettingsComponent::openProjectRootChooser()
{
    folderChooser = std::make_unique<juce::FileChooser>("Select Project Root Folder", juce::File(), "*", true);
    auto chooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories;

    folderChooser->launchAsync(chooserFlags, [this](const juce::FileChooser& chooser)
        {
            auto result = chooser.getResult();
            if (result.exists())
            {
                projectRootPath.setText(result.getFullPathName());
            }
        });
}

void ProjectSettingsComponent::openModuleFolderChooser()
{
    folderChooser = std::make_unique<juce::FileChooser>("Add Module Folder", juce::File(), "*", true);
    auto chooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories;

    folderChooser->launchAsync(chooserFlags, [this](const juce::FileChooser& chooser)
        {
            auto result = chooser.getResult();
            if (result.exists())
            {
                moduleFolders.add(result);
                moduleListBox.updateContent();
                moduleListBox.repaint();
            }
        });
}

// ==========================
// ListBoxModel Implementation
// ==========================
int ProjectSettingsComponent::getNumRows()
{
    return moduleFolders.size();
}

void ProjectSettingsComponent::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    auto bgColor = findColour(juce::ListBox::backgroundColourId);
    auto textColor = findColour(juce::ListBox::textColourId);

    if (rowIsSelected)
        g.fillAll(bgColor.brighter(0.2f));
    else
        g.fillAll(bgColor);

    if (rowNumber >= 0 && rowNumber < moduleFolders.size())
    {
        g.setColour(textColor);
        g.drawText(moduleFolders[rowNumber].getFullPathName(),
            4, 0, width - 8, height, juce::Justification::centredLeft);
    }
}

void ProjectSettingsComponent::listBoxItemClicked(int row, const juce::MouseEvent& e)
{
    if (e.mods.isRightButtonDown())
    {
        if (row >= 0 && row < moduleFolders.size())
        {
            moduleFolders.remove(row);
            moduleListBox.updateContent();
            moduleListBox.repaint();
        }
    }
}
