#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(juce::AudioDeviceManager& manager)
    : deviceManager(manager)
{
    audioSourcePlayer = std::make_unique<juce::AudioSourcePlayer>();
    audioSourcePlayer->setSource(this);
    deviceManager.addAudioCallback(audioSourcePlayer.get());
}

AudioPlayer::~AudioPlayer()
{
    deviceManager.removeAudioCallback(audioSourcePlayer.get());
    audioSourcePlayer = nullptr;
}

void AudioPlayer::loadSource(std::unique_ptr<IPlayableAudioSource> newSource)
{
    source = std::move(newSource);
}

void AudioPlayer::play()
{
    if (source)
        source->play();
}

void AudioPlayer::pause()
{
    if (source)
        source->pause();
}

void AudioPlayer::stop()
{
    if (source)
        source->stop();
}

void AudioPlayer::setVolume(float newVolume)
{
    volume = juce::jlimit(0.0f, 1.0f, newVolume);
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    if (source)
        source->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::releaseResources()
{
    if (source)
        source->releaseResources();
}

bool AudioPlayer::isPlaying() const
{
    if (source)
        return source->isPlaying();
    return false;
}

void AudioPlayer::shutdown()
{
    if (audioSourcePlayer)
    {
        deviceManager.removeAudioCallback(audioSourcePlayer.get());
        audioSourcePlayer = nullptr;
    }
}
void AudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (source)
    {
        source->getNextAudioBlock(bufferToFill);
        bufferToFill.buffer->applyGain(volume);
    }
    else
    {
        bufferToFill.clearActiveBufferRegion();
    }
}
