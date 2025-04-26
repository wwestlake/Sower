#include <JuceHeader.h>
#include "SineGeneratorEffect.h"

const EffectMetadata SineGeneratorEffect::metadata = {
    "Sine Generator",
    "Generates a pure sine wave at a configurable frequency.",
    "Generator",
    "sine_icon"
};

SineGeneratorEffect::SineGeneratorEffect(float initialFrequency)
    : GeneratorBase(initialFrequency)
{
}

void SineGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = static_cast<float>(std::sin(phase));
        phase += phaseIncrement;

        if (phase >= juce::MathConstants<double>::twoPi)
            phase -= juce::MathConstants<double>::twoPi;
    }
}

const char* SineGeneratorEffect::getName() const
{
    return metadata.name;
}

const EffectMetadata& SineGeneratorEffect::getMetadata() const
{
    return metadata;
}
