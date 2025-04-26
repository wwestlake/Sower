#pragma once

#include <JuceHeader.h>
#include "Effects/EffectPipeline.h"

// AudioPlayer
// Loads an audio file, manages play/pause/stop, and routes audio through the EffectPipeline.
class AudioPlayer : public juce::AudioSource
{
public:
    AudioPlayer();
    ~AudioPlayer() override;

    // AudioSource overrides
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    // Control methods
    bool loadAudioFile(const juce::File& file);
    void play();
    void pause();
    void stop();

    // Attach an effect pipeline
    void setEffectPipeline(EffectPipeline* pipeline);

private:
    enum class TransportState
    {
        Stopped,
        Playing,
        Paused
    };

    TransportState state = TransportState::Stopped;

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::AudioFormatManager formatManager;

    EffectPipeline* effectPipeline = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};
