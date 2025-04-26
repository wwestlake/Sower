#pragma once

#include "../EffectBase.h"
#include <cmath>

// GeneratorBase
// Abstract base class for periodic signal generators
class GeneratorBase : public EffectBase
{
public:
    GeneratorBase(float initialFrequency = 440.0f);
    ~GeneratorBase() override = default;

    void prepare(double sampleRate, int samplesPerBlock) override;
    void reset() override;

    void setFrequency(float newFrequency);

protected:
    float frequency;
    double sampleRate;
    double phase;
    double phaseIncrement;

    void updatePhaseIncrement();
};
