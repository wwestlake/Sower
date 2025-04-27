#include "MainComponent.h"
#include "UI/ThemeManager.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(menuBar);
    addAndMakeVisible(workbenchTabs);
    addAndMakeVisible(statusBar);

    setSize(800, 600);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}


void MainComponent::resized()
{
    auto area = getLocalBounds();

    menuBar.setBounds(area.removeFromTop(24));
    statusBar.setBounds(area.removeFromBottom(40));
    workbenchTabs.setBounds(area);
}

//==============================================================================
juce::StringArray MainComponent::getMenuBarNames()
{
    return { "File", "Edit", "Help" };
}

juce::PopupMenu MainComponent::getMenuForIndex(int menuIndex, const juce::String& menuName)
{
    juce::PopupMenu menu;

    if (menuName == "File")
    {
        menu.addItem(1, "New Project");
        menu.addItem(2, "Open...");
        menu.addItem(3, "Save");
        menu.addSeparator();
        menu.addItem(4, "Exit");
    }
    else if (menuName == "Edit")
    {
        menu.addItem(10, "Undo");
        menu.addItem(11, "Redo");
        menu.addSeparator();
        menu.addItem(12, "Cut");
        menu.addItem(13, "Copy");
        menu.addItem(14, "Paste");
    }
    else if (menuName == "Help")
    {
        menu.addItem(20, "About");
    }

    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/)
{
    switch (menuItemID)
    {
    case 1: statusBar.setStatusText("New Project"); break;
    case 2: statusBar.setStatusText("Open..."); break;
    case 3: statusBar.setStatusText("Save"); break;
    case 4: juce::JUCEApplication::getInstance()->systemRequestedQuit(); break;
    case 20: juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "About", "DSP Workbench\nBuilt with JUCE."); break;
    default: break;
    }
}
