#pragma once

#include <JuceHeader.h>
#include "Effects/EffectPipeline.h"
#include "IPlayableAudioSource.h"

class AudioPlayer : public juce::AudioSource
{
public:
    AudioPlayer(juce::AudioDeviceManager& manager);
    ~AudioPlayer() override;

    void play();
    void pause();
    void stop();
    void setVolume(float newVolume);

    void loadSource(std::unique_ptr<IPlayableAudioSource> newSource);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    bool isPlaying() const;
    void shutdown();
private:
    juce::AudioDeviceManager& deviceManager;
    std::unique_ptr<juce::AudioSourcePlayer> audioSourcePlayer;

    std::unique_ptr<IPlayableAudioSource> source;
    float volume = 1.0f; // default full volume
};
