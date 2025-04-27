// IPlayableAudioSource.h
#pragma once

#include <JuceHeader.h>

class IPlayableAudioSource : public juce::AudioSource
{
public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual bool isPlaying() const = 0;

    virtual ~IPlayableAudioSource() = default;
};
