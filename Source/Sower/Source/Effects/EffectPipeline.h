#pragma once

#include <vector>
#include <memory>
#include "EffectBase.h"

// EffectPipeline
// Manages a chain of effects to be applied to audio frames.
class EffectPipeline
{
public:
    EffectPipeline() = default;
    ~EffectPipeline() = default;

    // Add a new effect to the end of the pipeline
    void addEffect(std::unique_ptr<EffectBase> effect);

    // Clear all effects from the pipeline
    void clear();

    // Prepare all effects for playback
    void prepareAll(double sampleRate, int samplesPerBlock);

    // Process a block of samples through all effects
    void processAll(float* data, int numSamples);

    // Reset all effects
    void resetAll();

private:
    std::vector<std::unique_ptr<EffectBase>> effects;
};
