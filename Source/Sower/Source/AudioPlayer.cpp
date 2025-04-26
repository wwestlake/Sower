#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
    formatManager.registerBasicFormats();
}

AudioPlayer::~AudioPlayer()
{
    transportSource.releaseResources();
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::releaseResources()
{
    transportSource.releaseResources();
}

void AudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);

    if (effectPipeline && bufferToFill.buffer != nullptr)
    {
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            float* channelData = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
            effectPipeline->processAll(channelData, bufferToFill.numSamples);
        }
    }
}

bool AudioPlayer::loadAudioFile(const juce::File& file)
{
    auto* reader = formatManager.createReaderFor(file);

    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
        return true;
    }
    return false;
}

void AudioPlayer::play()
{
    if (state == TransportState::Stopped || state == TransportState::Paused)
    {
        transportSource.start();
        state = TransportState::Playing;
    }
}

void AudioPlayer::pause()
{
    if (state == TransportState::Playing)
    {
        transportSource.stop();
        state = TransportState::Paused;
    }
}

void AudioPlayer::stop()
{
    transportSource.stop();
    transportSource.setPosition(0.0);
    state = TransportState::Stopped;
}

void AudioPlayer::setEffectPipeline(EffectPipeline* pipeline)
{
    effectPipeline = pipeline;
}
