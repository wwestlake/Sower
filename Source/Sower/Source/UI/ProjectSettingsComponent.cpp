#include "ProjectSettingsComponent.h"
#include "ThemeManager.h"

//==============================================================================
ProjectSettingsComponent::ProjectSettingsComponent()
{
    addAndMakeVisible(projectRootLabel);
    addAndMakeVisible(projectRootPath);
    addAndMakeVisible(browseProjectRootButton);
    browseProjectRootButton.onClick = [this]() { openProjectRootChooser(); };

    addAndMakeVisible(modulePathsLabel);
    addAndMakeVisible(addModuleFolderButton);
    addAndMakeVisible(moduleListViewport);
    moduleListViewport.setViewedComponent(&moduleListContainer, false);
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

    themeSelector.addItem("Light", 1);
    themeSelector.addItem("Dark", 2);
    themeSelector.setSelectedId(2);

    themeSelector.onChange = [this]()
        {
            if (themeSelector.getSelectedId() == 1)
                ThemeManager().applyTheme(ThemeManager::Light);
            else
                ThemeManager().applyTheme(ThemeManager::Dark);
        };
}

//==============================================================================
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
    moduleListViewport.setBounds(area.removeFromTop(150));

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

//==============================================================================
void ProjectSettingsComponent::openProjectRootChooser()
{
    folderChooser = std::make_unique<juce::FileChooser>(
        "Choose a project root folder...", juce::File(), juce::String());

    folderChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
        [this](const juce::FileChooser& fc)
        {
            auto f = fc.getResult();
            if (f.isDirectory())
                projectRootPath.setText(f.getFullPathName(), juce::dontSendNotification);
        });
}

void ProjectSettingsComponent::openModuleFolderChooser()
{
    folderChooser = std::make_unique<juce::FileChooser>(
        "Add module folder...", juce::File(), juce::String());

    folderChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
        [this](const juce::FileChooser& fc)
        {
            auto f = fc.getResult();
            if (f.isDirectory())
            {
                moduleListContainer.addFolder(f);
                moduleListViewport.repaint();
            }
        });
}

//==============================================================================
juce::var ProjectSettingsComponent::getJson() const
{
    juce::DynamicObject::Ptr obj = new juce::DynamicObject();
    obj->setProperty("projectRoot", projectRootPath.getText());

    juce::Array<juce::File> folders = moduleListContainer.getAllFolders();
    juce::Array<juce::var> folderPaths;
    for (const auto& f : folders)
        folderPaths.add(f.getFullPathName());

    obj->setProperty("modulePaths", folderPaths);
    obj->setProperty("outputFormat", formatBox.getText());
    obj->setProperty("sampleRate", sampleRateBox.getText());
    obj->setProperty("bitDepth", bitDepthBox.getText());
    obj->setProperty("channels", channelBox.getText());

    return obj.get();
}

void ProjectSettingsComponent::setFromJson(const juce::var& json)
{
    if (auto* obj = json.getDynamicObject())
    {
        projectRootPath.setText(obj->getProperty("projectRoot").toString());

        if (auto* arr = obj->getProperty("modulePaths").getArray())
        {
            moduleListContainer.clearAll();
            for (const auto& v : *arr)
                moduleListContainer.addFolder(juce::File(v.toString()));
        }

        formatBox.setText(obj->getProperty("outputFormat").toString());
        sampleRateBox.setText(obj->getProperty("sampleRate").toString());
        bitDepthBox.setText(obj->getProperty("bitDepth").toString());
        channelBox.setText(obj->getProperty("channels").toString());
    }
}

//==============================================================================
// ModuleListContainer Methods
void ProjectSettingsComponent::ModuleListContainer::addFolder(const juce::File& folder)
{
    auto* item = new ModuleItem(folder, [this](ModuleItem* toRemove)
        {
            juce::MessageManager::callAsync([this, toRemove]()
                {
                    items.removeObject(toRemove, true);
                    resized();
                    setSize(getParentWidth(), items.size() * 35);
                    if (auto* parent = getParentComponent())
                        parent->resized();
                });
        });

    items.add(item);
    addAndMakeVisible(item);
    resized();
    setSize(getParentWidth(), items.size() * 35);
    if (auto* parent = getParentComponent())
        parent->resized();
}

void ProjectSettingsComponent::ModuleListContainer::clearAll()
{
    items.clear(true);
    resized();
}

void ProjectSettingsComponent::ModuleListContainer::resized()
{
    int y = 0;
    for (auto* item : items)
    {
        item->setBounds(0, y, getWidth(), 30);
        y += 35;
    }
    setSize(getParentWidth(), y);
}

void ProjectSettingsComponent::ModuleListContainer::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
}

juce::Array<juce::File> ProjectSettingsComponent::ModuleListContainer::getAllFolders() const
{
    juce::Array<juce::File> out;
    for (auto* i : items)
        out.add(i->folder);
    return out;
}

//==============================================================================
// ModuleItem Methods
ProjectSettingsComponent::ModuleListContainer::ModuleItem::ModuleItem(
    const juce::File& f, std::function<void(ModuleItem*)> onDelete)
    : folder(f), onDeleteCallback(std::move(onDelete))
{
    pathLabel.setText(folder.getFullPathName(), juce::dontSendNotification);
    addAndMakeVisible(pathLabel);

    removeButton.onClick = [safeThis = juce::Component::SafePointer<ModuleItem>(this)]()
        {
            if (safeThis)
            {
                juce::MessageManager::callAsync([safeThis]()
                    {
                        if (safeThis && safeThis->onDeleteCallback)
                            safeThis->onDeleteCallback(safeThis.getComponent());
                    });
            }
        };

    addAndMakeVisible(removeButton);
}

void ProjectSettingsComponent::ModuleListContainer::ModuleItem::resized()
{
    auto area = getLocalBounds().reduced(4);
    removeButton.setBounds(area.removeFromRight(80));
    pathLabel.setBounds(area);
}

void ProjectSettingsComponent::ModuleListContainer::ModuleItem::paint(juce::Graphics& g)
{
    g.drawRect(getLocalBounds());
}
