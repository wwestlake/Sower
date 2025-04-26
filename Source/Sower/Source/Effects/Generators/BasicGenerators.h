#pragma once

#include "GeneratorBase.h"
#include <JuceHeader.h>
#include <random>

// Basic waveform generator effect classes

class SquareGeneratorEffect : public GeneratorBase
{
public:
    SquareGeneratorEffect(float initialFrequency = 440.0f);
    ~SquareGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    static const EffectMetadata metadata;
};

class TriangleGeneratorEffect : public GeneratorBase
{
public:
    TriangleGeneratorEffect(float initialFrequency = 440.0f);
    ~TriangleGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    static const EffectMetadata metadata;
};

class SawtoothUpGeneratorEffect : public GeneratorBase
{
public:
    SawtoothUpGeneratorEffect(float initialFrequency = 440.0f);
    ~SawtoothUpGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    static const EffectMetadata metadata;
};

class SawtoothDownGeneratorEffect : public GeneratorBase
{
public:
    SawtoothDownGeneratorEffect(float initialFrequency = 440.0f);
    ~SawtoothDownGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    static const EffectMetadata metadata;
};

class ImpulseGeneratorEffect : public GeneratorBase
{
public:
    ImpulseGeneratorEffect();
    ~ImpulseGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    bool triggered = false;
    static const EffectMetadata metadata;
};

class WhiteNoiseGeneratorEffect : public GeneratorBase
{
public:
    WhiteNoiseGeneratorEffect();
    ~WhiteNoiseGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> distribution;
    static const EffectMetadata metadata;
};

class PinkNoiseGeneratorEffect : public GeneratorBase
{
public:
    PinkNoiseGeneratorEffect();
    ~PinkNoiseGeneratorEffect() override = default;

    void processFrame(float* data, int numSamples) override;
    const char* getName() const override;
    const EffectMetadata& getMetadata() const override;

private:
    float pink1 = 0.0f, pink2 = 0.0f, pink3 = 0.0f;
    std::mt19937 rng;
    std::uniform_real_distribution<float> distribution;
    static const EffectMetadata metadata;
};
