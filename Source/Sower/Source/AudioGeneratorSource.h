// AudioGeneratorSource.h
#pragma once

#include <JuceHeader.h>
#include "IPlayableAudioSource.h"
#include "Effects/EffectPipeline.h"

class AudioGeneratorSource : public IPlayableAudioSource
{
public:
    AudioGeneratorSource(EffectPipeline* pipeline);
    ~AudioGeneratorSource() override = default;

    void play() override;
    void pause() override;
    void stop() override;
    bool isPlaying() const override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    EffectPipeline* effectPipeline = nullptr;
    bool playing = false;
};
