#pragma once

#include "GeneratorBase.h"

class SineGeneratorEffect : public GeneratorBase
{
public:
    SineGeneratorEffect(float initialFrequency = 440.0f);
    ~SineGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;

    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    static const EffectMetadata metadata;
};
