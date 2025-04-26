#pragma once

#include <JuceHeader.h>

class ThemeManager
{
public:
    enum Theme
    {
        Light,
        Dark
    };

    ThemeManager();

    void applyTheme(Theme theme);
    Theme getCurrentTheme() const;

private:
    Theme currentTheme = Dark;

    juce::LookAndFeel_V4 lightThemeLAF;
    juce::LookAndFeel_V4 darkThemeLAF;
};
