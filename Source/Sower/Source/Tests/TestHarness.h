#pragma once

#include <JuceHeader.h>
#include "../Effects/EffectPipeline.h"
#include "../AudioPlayer.h"
#include "../UI/IDataSource.h"
#include "../Effects/GainEffect.h"

class TestHarness : 
    public IDataSource,
    public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    TestHarness();
    ~TestHarness() override;

    void buildPipeline();

    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    virtual void attachDataSource(std::function<void(std::shared_ptr<VisualizerDataBase>)> callback) override;

private:
    void updateStatus();

    juce::TextButton playButton{ "Play" };
    juce::TextButton pauseButton{ "Pause" };
    juce::TextButton stopButton{ "Stop" };
    juce::Slider volumeSlider;
    juce::Label statusLabel;

    std::unique_ptr<juce::AudioDeviceSelectorComponent> deviceSelector;

    std::unique_ptr<EffectPipeline> pipeline;
    std::unique_ptr<AudioPlayer> audioPlayer;

    juce::AudioDeviceManager deviceManager;

    std::shared_ptr<GainEffect> gainEffect;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestHarness)
};
