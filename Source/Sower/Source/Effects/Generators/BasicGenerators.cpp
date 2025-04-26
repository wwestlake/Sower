#include "BasicGenerators.h"

// ================== SquareGeneratorEffect ==================

const EffectMetadata SquareGeneratorEffect::metadata = {
    "Square Generator",
    "Generates a square wave at a configurable frequency.",
    "Generator",
    "square_icon"
};

SquareGeneratorEffect::SquareGeneratorEffect(float initialFrequency)
    : GeneratorBase(initialFrequency)
{
}

void SquareGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = (std::sin(phase) >= 0.0) ? 1.0f : -1.0f;
        phase += phaseIncrement;
        if (phase >= juce::MathConstants<double>::twoPi)
            phase -= juce::MathConstants<double>::twoPi;
    }
}

const char* SquareGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& SquareGeneratorEffect::getMetadata() const { return metadata; }

// ================== TriangleGeneratorEffect ==================

const EffectMetadata TriangleGeneratorEffect::metadata = {
    "Triangle Generator",
    "Generates a triangle wave at a configurable frequency.",
    "Generator",
    "triangle_icon"
};

TriangleGeneratorEffect::TriangleGeneratorEffect(float initialFrequency)
    : GeneratorBase(initialFrequency)
{
}

void TriangleGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        double value = 2.0 * std::abs(2.0 * (phase / juce::MathConstants<double>::twoPi) - 1.0) - 1.0;
        data[i] = static_cast<float>(value);
        phase += phaseIncrement;
        if (phase >= juce::MathConstants<double>::twoPi)
            phase -= juce::MathConstants<double>::twoPi;
    }
}

const char* TriangleGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& TriangleGeneratorEffect::getMetadata() const { return metadata; }

// ================== SawtoothUpGeneratorEffect ==================

const EffectMetadata SawtoothUpGeneratorEffect::metadata = {
    "Sawtooth Up Generator",
    "Generates a rising sawtooth wave.",
    "Generator",
    "sawup_icon"
};

SawtoothUpGeneratorEffect::SawtoothUpGeneratorEffect(float initialFrequency)
    : GeneratorBase(initialFrequency)
{
}

void SawtoothUpGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = static_cast<float>((phase / juce::MathConstants<double>::twoPi) * 2.0 - 1.0);
        phase += phaseIncrement;
        if (phase >= juce::MathConstants<double>::twoPi)
            phase -= juce::MathConstants<double>::twoPi;
    }
}

const char* SawtoothUpGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& SawtoothUpGeneratorEffect::getMetadata() const { return metadata; }

// ================== SawtoothDownGeneratorEffect ==================

const EffectMetadata SawtoothDownGeneratorEffect::metadata = {
    "Sawtooth Down Generator",
    "Generates a falling sawtooth wave.",
    "Generator",
    "sawdown_icon"
};

SawtoothDownGeneratorEffect::SawtoothDownGeneratorEffect(float initialFrequency)
    : GeneratorBase(initialFrequency)
{
}

void SawtoothDownGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = static_cast<float>((1.0 - (phase / juce::MathConstants<double>::twoPi)) * 2.0 - 1.0);
        phase += phaseIncrement;
        if (phase >= juce::MathConstants<double>::twoPi)
            phase -= juce::MathConstants<double>::twoPi;
    }
}

const char* SawtoothDownGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& SawtoothDownGeneratorEffect::getMetadata() const { return metadata; }

// ================== ImpulseGeneratorEffect ==================

const EffectMetadata ImpulseGeneratorEffect::metadata = {
    "Impulse Generator",
    "Generates a single-sample impulse.",
    "Generator",
    "impulse_icon"
};

ImpulseGeneratorEffect::ImpulseGeneratorEffect()
    : GeneratorBase()
{
}

void ImpulseGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = triggered ? 0.0f : 1.0f;
        triggered = true;
    }
}

const char* ImpulseGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& ImpulseGeneratorEffect::getMetadata() const { return metadata; }

// ================== WhiteNoiseGeneratorEffect ==================

const EffectMetadata WhiteNoiseGeneratorEffect::metadata = {
    "White Noise Generator",
    "Generates white noise.",
    "Generator",
    "whitenoise_icon"
};

WhiteNoiseGeneratorEffect::WhiteNoiseGeneratorEffect()
    : GeneratorBase(), distribution(-1.0f, 1.0f)
{
    rng.seed(std::random_device{}());
}

void WhiteNoiseGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = distribution(rng);
    }
}

const char* WhiteNoiseGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& WhiteNoiseGeneratorEffect::getMetadata() const { return metadata; }

// ================== PinkNoiseGeneratorEffect ==================

const EffectMetadata PinkNoiseGeneratorEffect::metadata = {
    "Pink Noise Generator",
    "Generates pink noise (approximate).",
    "Generator",
    "pinknoise_icon"
};

PinkNoiseGeneratorEffect::PinkNoiseGeneratorEffect()
    : GeneratorBase(), distribution(-1.0f, 1.0f)
{
    rng.seed(std::random_device{}());
}

void PinkNoiseGeneratorEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        float white = distribution(rng);
        pink1 = 0.99886f * pink1 + white * 0.0555179f;
        pink2 = 0.99332f * pink2 + white * 0.0750759f;
        pink3 = 0.96900f * pink3 + white * 0.1538520f;
        data[i] = 0.535675f * (pink1 + pink2 + pink3 + white * 0.5362f);
    }
}

const char* PinkNoiseGeneratorEffect::getName() const { return metadata.name; }
const EffectMetadata& PinkNoiseGeneratorEffect::getMetadata() const { return metadata; }
