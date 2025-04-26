#include "ThemeManager.h"

ThemeManager::ThemeManager()
{
    lightThemeLAF.setColourScheme(juce::LookAndFeel_V4::getLightColourScheme());
    darkThemeLAF.setColourScheme(juce::LookAndFeel_V4::getDarkColourScheme());

    applyTheme(Dark); // Default to dark theme
}

void ThemeManager::applyTheme(Theme theme)
{
    currentTheme = theme;

    auto* laf = (theme == Light) ? &lightThemeLAF : &darkThemeLAF;
    juce::LookAndFeel::setDefaultLookAndFeel(laf);

    // Core component backgrounds
    laf->setColour(juce::ResizableWindow::backgroundColourId, juce::Colour::fromRGB(28, 30, 34)); // near black

    // Text Editors
    laf->setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromRGB(40, 42, 48));
    laf->setColour(juce::TextEditor::textColourId, juce::Colours::white);
    laf->setColour(juce::TextEditor::outlineColourId, juce::Colours::darkgrey);
    laf->setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::lightslategrey);

    // ComboBoxes
    laf->setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(40, 42, 48));
    laf->setColour(juce::ComboBox::textColourId, juce::Colours::white);
    laf->setColour(juce::ComboBox::outlineColourId, juce::Colours::grey);
    laf->setColour(juce::ComboBox::arrowColourId, juce::Colours::white);

    // Buttons
    laf->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(40, 42, 48));
    laf->setColour(juce::TextButton::buttonOnColourId, juce::Colour::fromRGB(60, 62, 68));
    laf->setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    laf->setColour(juce::TextButton::textColourOnId, juce::Colours::white);

    // Scrollbars
    laf->setColour(juce::ScrollBar::thumbColourId, juce::Colours::grey);
    laf->setColour(juce::ScrollBar::trackColourId, juce::Colour::fromRGB(28, 30, 34));

    // Popup Menus and Tooltips
    laf->setColour(juce::PopupMenu::backgroundColourId, juce::Colour::fromRGB(40, 42, 48));
    laf->setColour(juce::PopupMenu::textColourId, juce::Colours::white);
    laf->setColour(juce::TooltipWindow::backgroundColourId, juce::Colour::fromRGB(40, 42, 48));
    laf->setColour(juce::TooltipWindow::textColourId, juce::Colours::white);
}

ThemeManager::Theme ThemeManager::getCurrentTheme() const
{
    return currentTheme;
}
