#include "TestHarness.h"
#include "../AudioSourceFactory.h"
#include "../Effects/Generators/SineGeneratorEffect.h"
#include "../Effects/GainEffect.h"

TestHarness::TestHarness()
{
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

    deviceSelector = std::make_unique<juce::AudioDeviceSelectorComponent>(
        deviceManager, 0, 2, 0, 2, true, true, true, false);
    addAndMakeVisible(deviceSelector.get());

    audioPlayer = std::make_unique<AudioPlayer>(deviceManager);

    buildPipeline();
    updateStatus();
}

TestHarness::~TestHarness()
{
    if (audioPlayer)
        audioPlayer->shutdown(); 

    playButton.removeListener(this);
    pauseButton.removeListener(this);
    stopButton.removeListener(this);
    volumeSlider.removeListener(this);
}

void TestHarness::buildPipeline()
{
    pipeline = std::make_unique<EffectPipeline>();
    pipeline->addEffect(std::make_unique<SineGeneratorEffect>());
    pipeline->addEffect(std::make_unique<GainEffect>());

    auto source = AudioSourceFactory::createGeneratorSource(pipeline.get());
    audioPlayer->loadSource(std::move(source));
}

void TestHarness::resized()
{
    auto area = getLocalBounds().reduced(10); // Add a little border around everything

    auto left = area.removeFromLeft(200); // Left 200 pixels for buttons etc
    auto buttonArea = left.reduced(10);   // Add internal padding

    playButton.setBounds(buttonArea.removeFromTop(30).reduced(5));
    pauseButton.setBounds(buttonArea.removeFromTop(30).reduced(5));
    stopButton.setBounds(buttonArea.removeFromTop(30).reduced(5));
    volumeSlider.setBounds(buttonArea.removeFromTop(30).reduced(5));
    statusLabel.setBounds(buttonArea.removeFromTop(30).reduced(5));

    deviceSelector->setBounds(area.reduced(10)); // Device selector on the right, also padded
}

void TestHarness::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        audioPlayer->play();
        updateStatus();
    }
    else if (button == &pauseButton)
    {
        audioPlayer->pause();
        updateStatus();
    }
    else if (button == &stopButton)
    {
        audioPlayer->stop();
        updateStatus();
    }
}

void TestHarness::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        audioPlayer->setVolume((float)slider->getValue());
    }
}

void TestHarness::updateStatus()
{
    if (audioPlayer)
        statusLabel.setText(audioPlayer->isPlaying() ? "Playing" : "Stopped", juce::dontSendNotification);
    else
        statusLabel.setText("No Audio", juce::dontSendNotification);
}
