#include "SecondDegreeAffineTransform.h"

SecondDegreeAffineTransform::SecondDegreeAffineTransform()
    : scale(1.0f, 1.0f), offset(0.0f, 0.0f)
{
}

void SecondDegreeAffineTransform::setScale(float sx, float sy)
{
    scale.setXY(sx, sy);
}

void SecondDegreeAffineTransform::setOffset(float ox, float oy)
{
    offset.setXY(ox, oy);
}

juce::Point<float> SecondDegreeAffineTransform::apply(const juce::Point<float>& input) const
{
    return {
        scale.x * input.x + offset.x,
        scale.y * input.y + offset.y
    };
}

juce::Point<float> SecondDegreeAffineTransform::inverse(const juce::Point<float>& screen) const
{
    return {
        (screen.x - offset.x) / scale.x,
        (screen.y - offset.y) / scale.y
    };
}

juce::Point<float> SecondDegreeAffineTransform::getScale() const
{
    return scale;
}

juce::Point<float> SecondDegreeAffineTransform::getOffset() const
{
    return offset;
}
