// ThemeManager.cpp
#include "ThemeManager.h"

std::vector<Theme> ThemeManager::themes;
Theme* ThemeManager::currentTheme = nullptr;

void ThemeManager::initializeThemes()
{
    themes.clear();

    // Insert Dark Theme first
    auto darkTheme = std::make_unique<juce::LookAndFeel_V4>();
    darkTheme->setColour(juce::TabbedComponent::backgroundColourId, juce::Colours::darkgrey);
    darkTheme->setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::black);
    themes.push_back({ "Dark", std::move(darkTheme) });

    // Insert Light Theme second
    auto lightTheme = std::make_unique<juce::LookAndFeel_V4>();
    lightTheme->setColour(juce::TabbedComponent::backgroundColourId, juce::Colours::lightgrey);
    lightTheme->setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::white);
    themes.push_back({ "Light", std::move(lightTheme) });

    // Set default theme to index 0
    setActiveTheme(0);
}

void ThemeManager::setActiveTheme(const juce::String& name)
{
    for (auto& theme : themes)
    {
        if (theme.name == name)
        {
            currentTheme = &theme;
            juce::Desktop::getInstance().setDefaultLookAndFeel(currentTheme->lookAndFeel.get());
            return;
        }
    }
}

void ThemeManager::setActiveTheme(int index)
{
    if (index >= 0 && index < static_cast<int>(themes.size()))
    {
        currentTheme = &themes[index];
        juce::Desktop::getInstance().setDefaultLookAndFeel(currentTheme->lookAndFeel.get());
    }
}

Theme& ThemeManager::getActiveTheme()
{
    if (currentTheme != nullptr)
        return *currentTheme;

    jassertfalse; // Should never happen if properly initialized
    static Theme dummyFallbackTheme{ "Fallback", std::make_unique<juce::LookAndFeel_V4>() };
    return dummyFallbackTheme;
}

juce::StringArray ThemeManager::getAvailableThemeNames()
{
    juce::StringArray names;
    for (auto& theme : themes)
        names.add(theme.name);
    return names;
}

void ThemeManager::shutdownThemes()
{
    themes.clear();
    currentTheme = nullptr;
}
