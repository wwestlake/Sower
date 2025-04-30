#include "VisualizerDataBase.h"

struct OscilloscopeData : public VisualizerDataBase
{
    const float* buffer;
    size_t numSamples;

    OscilloscopeData(const float* buf, size_t count)
        : buffer(buf), numSamples(count) {
    }
};
