#pragma once

#include <JuceHeader.h>
#include "UI/WorkbenchTabsComponent.h"
#include "UI/StatusBarComponent.h"
#include "UI/ThemeManager.h"

class MainComponent : public juce::Component,
    public juce::MenuBarModel
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // MenuBarModel overrides
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int menuIndex, const juce::String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

private:
    juce::MenuBarComponent menuBar{ this };
    WorkbenchTabsComponent workbenchTabs;
    StatusBarComponent statusBar;
    //ThemeManager themeManager; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
