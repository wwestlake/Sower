// AudioSourceFactory.h
#pragma once

#include <JuceHeader.h>
#include "IPlayableAudioSource.h"
#include "AudioFileSource.h"
#include "AudioGeneratorSource.h"
#include "../Effects/EffectPipeline.h"

class AudioSourceFactory
{
public:
    static std::unique_ptr<IPlayableAudioSource> createFileSource(const juce::File& file, juce::AudioFormatManager& formatManager)
    {
        return std::make_unique<AudioFileSource>(file, formatManager);
    }

    static std::unique_ptr<IPlayableAudioSource> createGeneratorSource(EffectPipeline* pipeline)
    {
        return std::make_unique<AudioGeneratorSource>(pipeline);
    }
};
