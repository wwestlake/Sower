// EffectPipeline.cpp
#include "EffectPipeline.h"

EffectPipeline::EffectPipeline()
{
}

EffectPipeline::~EffectPipeline()
{
}

void EffectPipeline::addEffect(std::shared_ptr<EffectBase> effect)
{
    effects.push_back(std::move(effect));
}

void EffectPipeline::clear()
{
    effects.clear();
}

void EffectPipeline::prepareAll(double sampleRate, int samplesPerBlock)
{
    for (auto& effect : effects)
        effect->prepare(sampleRate, samplesPerBlock);
}

void EffectPipeline::processAll(float* data, int numSamples)
{
    for (auto& effect : effects)
        effect->processFrame(data, numSamples);
}

void EffectPipeline::resetAll()
{
    for (auto& effect : effects)
        effect->reset();
}

// ===== New DSP-friendly methods =====

void EffectPipeline::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    prepareAll(sampleRate, samplesPerBlockExpected);
}

void EffectPipeline::releaseResources()
{
    resetAll();
}

void EffectPipeline::processBlock(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        processAll(channelData, numSamples);
    }
}
