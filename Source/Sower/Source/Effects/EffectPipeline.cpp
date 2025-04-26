#include "EffectPipeline.h"

void EffectPipeline::addEffect(std::unique_ptr<EffectBase> effect)
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
