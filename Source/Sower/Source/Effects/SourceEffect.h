#pragma once

#include "EffectBase.h"
#include <JuceHeader.h>

// SourceEffect
// Provides an audio source for the pipeline (currently file-based, future: generators and mixers)
class SourceEffect : public EffectBase
{
public:
    SourceEffect();
    ~SourceEffect() override;

    void prepare(double sampleRate, int samplesPerBlock) override;
    void processFrame(float* data, int numSamples) override;
    void reset() override;

    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

    // Load an audio file into the source
    bool loadAudioFile(const juce::File& file);

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    static const EffectMetadata metadata;
};
