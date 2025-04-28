#include "SineGeneratorEffect.h"

const EffectMetadata SineGeneratorEffect::metadata = {
    "Sine Generator",
    "Generates a pure sine wave at a configurable frequency.",
    "Generator",
    "sine_icon"
};

SineGeneratorEffect::SineGeneratorEffect()
    : GeneratorBase(440.0f)
{
    sineOscillator.initialise([](float x) { return std::sin(x); });
}

void SineGeneratorEffect::prepare(double sampleRate, int samplesPerBlockExpected)
{
    GeneratorBase::prepare(sampleRate, samplesPerBlockExpected);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<uint32_t>(samplesPerBlockExpected);
    spec.numChannels = 1;
    sineOscillator.prepare(spec);

    sineOscillator.setFrequency(frequency); // important: set frequency AFTER prepare
}

void SineGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = sineOscillator.processSample(0.0f);
    }
}

void SineGeneratorEffect::reset()
{
    GeneratorBase::reset();
    //sineOscillator.reset();
}

void SineGeneratorEffect::setFrequency(float newFrequency)
{
    GeneratorBase::setFrequency(newFrequency);
    sineOscillator.setFrequency(newFrequency);
}

const char* SineGeneratorEffect::getName() const
{
    return metadata.name;
}

const EffectMetadata& SineGeneratorEffect::getMetadata() const
{
    return metadata;
}
