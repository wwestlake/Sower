#pragma once

#include "EffectMetadata.h"

class EffectBase
{
public:
    virtual ~EffectBase() = default;

    // Prepare the effect (e.g., on sample rate changes)
    virtual void prepare(double sampleRate, int samplesPerBlock) = 0;

    // Process a frame of audio data
    virtual void processFrame(float* data, int numSamples) = 0;

    // Reset internal effect state
    virtual void reset() = 0;

    // Retrieve a human-readable name for the effect
    virtual const char* getName() const = 0;

    // Retrieve static metadata about the effect for UI display
    virtual const EffectMetadata& getMetadata() const = 0;
};
