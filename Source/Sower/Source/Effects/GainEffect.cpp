#include "GainEffect.h"

const EffectMetadata GainEffect::metadata = {
    "Gain",
    "Adjusts the volume of the incoming audio signal.",
    "Utility",
    "gain_icon"
};

GainEffect::GainEffect(float initialGain)
    : gain(initialGain)
{
}

void GainEffect::prepare(double, int)
{
    // Nothing needed for gain
}

void GainEffect::processFrame(float* data, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] *= gain;
    }
}

void GainEffect::reset()
{
    // No state to reset
}

const char* GainEffect::getName() const
{
    return metadata.name;
}

const EffectMetadata& GainEffect::getMetadata() const
{
    return metadata;
}

void GainEffect::setGain(float newGain)
{
    gain = newGain;
}

float GainEffect::getGain() const
{
    return gain;
}
