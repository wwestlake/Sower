#include "WorkbenchTabsComponent.h"

WorkbenchTabsComponent::WorkbenchTabsComponent()
{
    // Add tabs and corresponding components
    tabHolder.addTab("Project Info", juce::Colours::lightgrey, &projectInfo, false);
    tabHolder.addTab("Project Settings", juce::Colours::lightgrey, &projectSettings, false);

    addAndMakeVisible(tabHolder);
}
void WorkbenchTabsComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}

void WorkbenchTabsComponent::resized()
{
    tabHolder.setBounds(getLocalBounds());
}
