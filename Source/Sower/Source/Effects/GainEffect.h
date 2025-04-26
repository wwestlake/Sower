#pragma once

#include "EffectBase.h"

// GainEffect
// Adjusts the amplitude of the input signal by a user-defined gain factor.
class GainEffect : public EffectBase
{
public:
    GainEffect(float initialGain = 1.0f);
    ~GainEffect() override = default;

    void prepare(double sampleRate, int samplesPerBlock) override;
    void processFrame(float* data, int numSamples) override;
    void reset() override;

    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

    void setGain(float newGain);
    float getGain() const;

private:
    float gain;
    static const EffectMetadata metadata;
};
