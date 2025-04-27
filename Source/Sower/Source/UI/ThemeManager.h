// ThemeManager.h
#pragma once

#include <JuceHeader.h>

struct Theme
{
    juce::String name;
    std::unique_ptr<juce::LookAndFeel_V4> lookAndFeel;
};

class ThemeManager
{
public:
    static void initializeThemes();
    static void setActiveTheme(const juce::String& name);
    static void setActiveTheme(int index);
    static Theme& getActiveTheme();  // <-- fixed to return by reference
    static juce::StringArray getAvailableThemeNames();
    static void shutdownThemes();

private:
    static std::vector<Theme> themes;
    static Theme* currentTheme;
};
