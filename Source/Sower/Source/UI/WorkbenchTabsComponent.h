#pragma once
#include <JuceHeader.h>
#include "ProjectInfoComponent.h"
#include "ProjectSettingsComponent.h"
#include "../Tests/TestHarness.h"
#include "Visualizers/OscilloscopeComponent.h"

class WorkbenchTabsComponent : public juce::Component
{
public:
    WorkbenchTabsComponent();
    ~WorkbenchTabsComponent() override = default;

    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    juce::TabbedComponent tabHolder{ juce::TabbedButtonBar::TabsAtTop };

    // Subcomponents to display in tabs
    ProjectInfoComponent projectInfo;
    ProjectSettingsComponent projectSettings;
    TestHarness testHarness;
    OscilloscopeComponent scope;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WorkbenchTabsComponent)
};
