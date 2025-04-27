// AudioFileSource.h
#pragma once

#include <JuceHeader.h>
#include "IPlayableAudioSource.h"

class AudioFileSource : public IPlayableAudioSource
{
public:
    AudioFileSource(const juce::File& audioFile, juce::AudioFormatManager& formatManager);
    ~AudioFileSource() override;

    void play() override;
    void pause() override;
    void stop() override;
    bool isPlaying() const override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
};
