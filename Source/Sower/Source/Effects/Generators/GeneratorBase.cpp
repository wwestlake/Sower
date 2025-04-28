#include "GeneratorBase.h"
#include <JuceHeader.h>

GeneratorBase::GeneratorBase(float initialFrequency)
    : frequency(initialFrequency), sampleRate(44100.0), phase(0.0), phaseIncrement(0.0)
{
}

void GeneratorBase::prepare(double newSampleRate, int)
{
    sampleRate = newSampleRate;
    updatePhaseIncrement();
}

void GeneratorBase::reset()
{
    phase = 0.0;
}

void GeneratorBase::setFrequency(float newFrequency)
{
    frequency = newFrequency;
    updatePhaseIncrement();
}

void GeneratorBase::updatePhaseIncrement()
{
    phaseIncrement = (2.0 * juce::MathConstants<double>::pi * frequency) / sampleRate;
}

void GeneratorBase::processFrame(float* data, int numSamples)
{
}

const char* GeneratorBase::getName() const
{
    return nullptr;
}

const EffectMetadata& GeneratorBase::getMetadata() const
{
    static EffectMetadata emptyMetadata = { "Unknown", "No description", "Unknown", "unknown_icon" };
    return emptyMetadata;
}
