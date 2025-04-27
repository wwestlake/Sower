// AudioPlayer.h
#pragma once

#include <JuceHeader.h>
#include "Effects/EffectPipeline.h"

class AudioPlayer : public juce::AudioSource
{
public:
    AudioPlayer(juce::AudioDeviceManager& manager);
    ~AudioPlayer() override;

    void play();
    void pause();
    void stop();
    void setVolume(float newVolume);
    void setEffectPipeline(EffectPipeline* pipeline);
    void loadAudioFile(const juce::File& file);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    juce::AudioDeviceManager& deviceManager;
    std::unique_ptr<juce::AudioSourcePlayer> audioSourcePlayer;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    EffectPipeline* effectPipeline = nullptr;
    float volume = 1.0f; // default full volume
};
