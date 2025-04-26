#include "../Effects/EffectPipeline.h"
#include "../Effects/SourceEffect.h"
#include "../Effects/GainEffect.h"
#include "../Effects/Generators/BasicGenerators.h"
#include "../Effects/Generators/SineGeneratorEffect.h"
#include "../AudioPlayer.h"

#include <JuceHeader.h>

class TestHarness : public juce::AudioAppComponent
{
public:
    TestHarness()
    {
        // Setup effect pipeline
        effectPipeline = std::make_unique<EffectPipeline>();

        // Use a Sine Generator at 440Hz
        auto sineGen = std::make_unique<SineGeneratorEffect>(440.0f);
        effectPipeline->addEffect(std::move(sineGen));

        // Apply a GainEffect at half volume
        auto gain = std::make_unique<GainEffect>(0.5f);
        effectPipeline->addEffect(std::move(gain));

        // Attach pipeline to the AudioPlayer
        audioPlayer.setEffectPipeline(effectPipeline.get());

        // Setup audio
        setAudioChannels(0, 2); // 0 input, 2 output
        audioPlayer.prepareToPlay(512, 44100.0);

        // Start playback
        audioPlayer.play();
    }

    ~TestHarness() override
    {
        shutdownAudio();
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        juce::ignoreUnused(samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        audioPlayer.getNextAudioBlock(bufferToFill);
    }

    void releaseResources() override
    {
        audioPlayer.releaseResources();
    }

private:
    std::unique_ptr<EffectPipeline> effectPipeline;
    AudioPlayer audioPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestHarness)
};
