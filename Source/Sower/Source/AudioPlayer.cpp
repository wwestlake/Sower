// AudioPlayer.cpp
#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(juce::AudioDeviceManager& manager)
    : deviceManager(manager)
{
    formatManager.registerBasicFormats();
    audioSourcePlayer = std::make_unique<juce::AudioSourcePlayer>();
    audioSourcePlayer->setSource(this);
    deviceManager.addAudioCallback(audioSourcePlayer.get());
}

AudioPlayer::~AudioPlayer()
{
    deviceManager.removeAudioCallback(audioSourcePlayer.get());
    audioSourcePlayer->setSource(nullptr);
    audioSourcePlayer = nullptr;
}

void AudioPlayer::setEffectPipeline(EffectPipeline* pipeline)
{
    effectPipeline = pipeline;
}

void AudioPlayer::loadAudioFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    }
}

void AudioPlayer::play()
{
    if (!transportSource.isPlaying())
        transportSource.start();
}

void AudioPlayer::pause()
{
    if (transportSource.isPlaying())
        transportSource.stop();
}

void AudioPlayer::stop()
{
    if (transportSource.isPlaying())
        transportSource.stop();
    transportSource.setPosition(0.0);
}

void AudioPlayer::setVolume(float newVolume)
{
    volume = juce::jlimit(0.0f, 1.0f, newVolume);
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    if (effectPipeline)
        effectPipeline->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::releaseResources()
{
    transportSource.releaseResources();

    if (effectPipeline)
        effectPipeline->releaseResources();
}

void AudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (effectPipeline)
    {
        juce::AudioBuffer<float> tempBuffer(bufferToFill.buffer->getNumChannels(), bufferToFill.numSamples);
        juce::AudioSourceChannelInfo tempInfo(&tempBuffer, 0, bufferToFill.numSamples);

        transportSource.getNextAudioBlock(tempInfo);
        effectPipeline->processBlock(tempBuffer);

        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            bufferToFill.buffer->copyFrom(channel, bufferToFill.startSample, tempBuffer, channel, 0, bufferToFill.numSamples);
        }
    }
    else
    {
        transportSource.getNextAudioBlock(bufferToFill);
    }

    bufferToFill.buffer->applyGain(volume);
}
