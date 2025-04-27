// AudioGeneratorSource.cpp
#include "AudioGeneratorSource.h"

AudioGeneratorSource::AudioGeneratorSource(EffectPipeline* pipeline)
    : effectPipeline(pipeline)
{
}

void AudioGeneratorSource::play()
{
    playing = true;
}

void AudioGeneratorSource::pause()
{
    playing = false;
}

void AudioGeneratorSource::stop()
{
    playing = false;
}

bool AudioGeneratorSource::isPlaying() const
{
    return playing;
}

void AudioGeneratorSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    if (effectPipeline)
        effectPipeline->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioGeneratorSource::releaseResources()
{
    if (effectPipeline)
        effectPipeline->releaseResources();
}

void AudioGeneratorSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (effectPipeline && playing)
    {
        effectPipeline->processBlock(*bufferToFill.buffer);
    }
    else
    {
        bufferToFill.clearActiveBufferRegion();
    }
}
