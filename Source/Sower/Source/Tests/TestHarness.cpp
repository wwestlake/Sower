// TestHarness.cpp
#include "TestHarness.h"

TestHarness::TestHarness()
{
    deviceManager.initialise(0, 2, nullptr, true, {}, nullptr);

    deviceSelector = std::make_unique<juce::AudioDeviceSelectorComponent>(
        deviceManager,
        0, 0,
        2, 2,
        false, false, false, false);

    addAndMakeVisible(*deviceSelector);

    addAndMakeVisible(playButton);
    addAndMakeVisible(pauseButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(statusLabel);

    playButton.addListener(this);
    pauseButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(1.0);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    volumeSlider.setTooltip("Output Volume");

    statusLabel.setText("Status: Stopped", juce::dontSendNotification);

    buildPipeline();
}

TestHarness::~TestHarness()
{
    audioPlayer = nullptr;
    pipeline = nullptr;
    deviceSelector = nullptr;
    deviceManager.closeAudioDevice();
}

void TestHarness::buildPipeline()
{
    pipeline = std::make_unique<EffectPipeline>();

    auto sine = std::make_unique<SineGeneratorEffect>();
    sine->setFrequency(440.0f);

    auto gain = std::make_unique<GainEffect>();
    gain->setGain(0.5f);

    pipeline->addEffect(std::move(sine));
    pipeline->addEffect(std::move(gain));

    audioPlayer = std::make_unique<AudioPlayer>(deviceManager);
    audioPlayer->setEffectPipeline(pipeline.get());
}

void TestHarness::resized()
{
    auto area = getLocalBounds().reduced(10);
    deviceSelector->setBounds(area.removeFromTop(200).reduced(0, 10));

    auto buttonArea = area.removeFromTop(40);
    playButton.setBounds(buttonArea.removeFromLeft(80));
    pauseButton.setBounds(buttonArea.removeFromLeft(80));
    stopButton.setBounds(buttonArea.removeFromLeft(80));

    area.removeFromTop(10);
    volumeSlider.setBounds(area.removeFromTop(40));
    area.removeFromTop(10);

    statusLabel.setBounds(area.removeFromTop(30));
}

void TestHarness::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        if (!isPlaying)
        {
            audioPlayer->play();
            isPlaying = true;
            isPaused = false;
            updateStatus();
        }
        else if (isPaused)
        {
            audioPlayer->play();
            isPaused = false;
            updateStatus();
        }
    }
    else if (button == &pauseButton)
    {
        if (isPlaying && !isPaused)
        {
            audioPlayer->pause();
            isPaused = true;
            updateStatus();
        }
    }
    else if (button == &stopButton)
    {
        if (isPlaying)
        {
            audioPlayer->stop();
            isPlaying = false;
            isPaused = false;
            updateStatus();
        }
    }
}

void TestHarness::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider && audioPlayer)
    {
        audioPlayer->setVolume((float)volumeSlider.getValue());
    }
}

void TestHarness::updateStatus()
{
    if (isPlaying && !isPaused)
        statusLabel.setText("Status: Playing", juce::dontSendNotification);
    else if (isPaused)
        statusLabel.setText("Status: Paused", juce::dontSendNotification);
    else
        statusLabel.setText("Status: Stopped", juce::dontSendNotification);
}
