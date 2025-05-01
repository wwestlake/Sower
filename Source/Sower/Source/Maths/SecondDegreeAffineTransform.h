#pragma once

#include <JuceHeader.h>

/*
    A simple 2D affine transform used to apply scale and offset
    to 2D data points. Intended for visualizing waveform or signal
    data in a scrollable, zoomable space.
*/

class SecondDegreeAffineTransform
{
public:
    SecondDegreeAffineTransform();

    void setScale(float sx, float sy);
    void setOffset(float ox, float oy);

    juce::Point<float> apply(const juce::Point<float>& input) const;
    juce::Point<float> inverse(const juce::Point<float>& screen) const;

    juce::Point<float> getScale() const;
    juce::Point<float> getOffset() const;

private:
    juce::Point<float> scale;
    juce::Point<float> offset;
};
