#include "VisualizerDataBase.h"


struct SpectrumAnalyzerData : public VisualizerDataBase
{
    float* magnitude;
    float* phase;
    size_t numBins;
};
