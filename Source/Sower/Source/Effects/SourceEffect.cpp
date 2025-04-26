#include "SourceEffect.h"

const EffectMetadata SourceEffect::metadata = {
    "Source",
    "Provides audio input from a file or generator.",
    "Input",
    "source_icon"
};

SourceEffect::SourceEffect()
{
    formatManager.registerBasicFormats();
}

SourceEffect::~SourceEffect()
{
    transportSource.releaseResources();
}

void SourceEffect::prepare(double sampleRate, int samplesPerBlock)
{
    transportSource.prepareToPlay(samplesPerBlock, sampleRate);
}

void SourceEffect::processFrame(float* data, int numSamples)
{
    if (readerSource == nullptr)
    {
        // If no source, output silence
        std::fill(data, data + numSamples, 0.0f);
        return;
    }

    juce::AudioBuffer<float> tempBuffer(1, numSamples);
    juce::AudioSourceChannelInfo info(&tempBuffer, 0, numSamples);

    transportSource.getNextAudioBlock(info);

    auto* readData = tempBuffer.getReadPointer(0);
    for (int i = 0; i < numSamples; ++i)
    {
        data[i] = readData[i];
    }
}

void SourceEffect::reset()
{
    transportSource.stop();
    transportSource.setPosition(0.0);
}

const char* SourceEffect::getName() const
{
    return metadata.name;
}

const EffectMetadata& SourceEffect::getMetadata() const
{
    return metadata;
}

bool SourceEffect::loadAudioFile(const juce::File& file)
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
