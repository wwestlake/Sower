// TestHarness.h
#pragma once

#include <JuceHeader.h>
#include "../Effects/EffectPipeline.h"
#include "../AudioPlayer.h"
#include "../Effects/Generators/SineGeneratorEffect.h"
#include "../Effects/GainEffect.h"

class TestHarness : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    TestHarness();
    ~TestHarness() override;

    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    juce::AudioDeviceManager deviceManager;
    std::unique_ptr<juce::AudioDeviceSelectorComponent> deviceSelector;

    juce::TextButton playButton{ "Play" };
    juce::TextButton pauseButton{ "Pause" };
    juce::TextButton stopButton{ "Stop" };
    juce::Slider volumeSlider;
    juce::Label statusLabel;

    std::unique_ptr<EffectPipeline> pipeline;
    std::unique_ptr<AudioPlayer> audioPlayer;

    bool isPlaying = false;
    bool isPaused = false;

    void buildPipeline();
    void updateStatus();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestHarness)
};
