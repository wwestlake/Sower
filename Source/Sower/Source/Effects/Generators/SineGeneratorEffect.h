#pragma once

#include "GeneratorBase.h"
#include <juce_dsp/juce_dsp.h>

class SineGeneratorEffect : public GeneratorBase
{
public:
    SineGeneratorEffect();

    void prepare(double sampleRate, int samplesPerBlockExpected) override;
    void processFrame(float* data, int numSamples) override;
    void reset() override;
    void setFrequency(float newFrequency); // no override

    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    juce::dsp::Oscillator<float> sineOscillator;

    static const EffectMetadata metadata;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SineGeneratorEffect)
};
