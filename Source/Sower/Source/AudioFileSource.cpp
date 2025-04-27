// AudioFileSource.cpp
#include "AudioFileSource.h"

AudioFileSource::AudioFileSource(const juce::File& audioFile, juce::AudioFormatManager& formatManager)
{
    if (auto* reader = formatManager.createReaderFor(audioFile))
    {
        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    }
}

AudioFileSource::~AudioFileSource()
{
    transportSource.setSource(nullptr);
}

void AudioFileSource::play()
{
    if (!transportSource.isPlaying())
        transportSource.start();
}

void AudioFileSource::pause()
{
    if (transportSource.isPlaying())
        transportSource.stop();
}

void AudioFileSource::stop()
{
    if (transportSource.isPlaying())
        transportSource.stop();
    transportSource.setPosition(0.0);
}

bool AudioFileSource::isPlaying() const
{
    return transportSource.isPlaying();
}

void AudioFileSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioFileSource::releaseResources()
{
    transportSource.releaseResources();
}

void AudioFileSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}
