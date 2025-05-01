#include "WorkbenchTabsComponent.h"
#include "ThemeManager.h"
#include "../Effects/Visualizers/OscilloscopeEffect.h"

WorkbenchTabsComponent::WorkbenchTabsComponent()
{
    auto tabBackground = juce::LookAndFeel::getDefaultLookAndFeel()
        .findColour(juce::TabbedComponent::backgroundColourId);

    tabHolder.addTab("Project Info", tabBackground, &projectInfo, false);
    tabHolder.addTab("Project Settings", tabBackground, &projectSettings, false);
    tabHolder.addTab("Test", tabBackground, &testHarness, false);
    tabHolder.addTab("O-Scope", tabBackground, &scope, false);
    testHarness.attachDataSource([this](std::shared_ptr<VisualizerDataBase> data) {
        if (auto oscData = std::dynamic_pointer_cast<OscilloscopeData>(data))
        {
            scope.pushData(*oscData); // or setData(), whatever you have
        }
        });

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
