// EffectPipeline.h
#pragma once

#include <JuceHeader.h>
#include "EffectBase.h"

class EffectPipeline
{
public:
    EffectPipeline();
    ~EffectPipeline();

    void addEffect(std::shared_ptr<EffectBase> effect);
    void clear();

    void prepareAll(double sampleRate, int samplesPerBlock);
    void processAll(float* data, int numSamples);
    void resetAll();

    // New DSP-friendly methods
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float>& buffer);

private:
    std::vector<std::shared_ptr<EffectBase>> effects;
};
