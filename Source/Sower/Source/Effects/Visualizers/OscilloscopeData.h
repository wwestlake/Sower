#pragma once

#include "VisualizerDataBase.h"

struct OscilloscopeData : public VisualizerDataBase
{
    const float* buffer;
    size_t numSamples;
    double startTimeSeconds;
    double sampleRate;

    OscilloscopeData(const float* buf, size_t count, double start, double rate)
        : buffer(buf), numSamples(count), startTimeSeconds(start), sampleRate(rate) {
    }
};
