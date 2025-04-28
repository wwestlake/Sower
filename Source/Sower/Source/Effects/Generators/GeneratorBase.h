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
    void reset() override; // override because required by EffectBase, but no need to be virtual here
    void setFrequency(float newFrequency); // no virtual



protected:
    float frequency;
    double sampleRate;
    double phase;
    double phaseIncrement;

    void updatePhaseIncrement();

    // Inherited via EffectBase
    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;
};
