#pragma once

#include <JuceHeader.h>
#include "PlotComponentBase.h"
#include "PlotDataBuffer.h" // includes PlotDataBuffer2D

class Plot2DComponent : public PlotComponentBase,
    private juce::OpenGLRenderer
{
public:
    Plot2DComponent();
    ~Plot2DComponent() override;

    // === PlotComponentBase overrides ===
    void setXRange(float min, float max) override;
    void setYRange(float min, float max) override;
    void setZRange(float, float) override {} // no-op for 2D
    void setAutoFitX(bool enabled) override;
    void setAutoFitY(bool enabled) override;

    void setTitle(const juce::String& newTitle) override;
    void setAxisLabels(const juce::String& xLabel, const juce::String& yLabel, const juce::String&) override;

    void setShowGrid(bool enabled) override;
    void setPadding(float percent) override;

    void setLineColor(juce::Colour color) override;
    void setMarkerColor(juce::Colour color) override;

    void setVerticalMarker(int id, float x, const juce::String& label = {}) override;
    void setHorizontalMarker(int id, float y, const juce::String& label = {}) override;
    void clearMarkers() override;

    void clearData() override;
    void repaintPlot() override;

    // === Custom API ===
    void appendPoint(float x, float y);
    void appendBlock(const std::vector<juce::Point<float>>& points);

private:
    // === OpenGLRenderer ===
    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;
    void renderGrid();
    void renderMarkers();
    void renderData();

    // === Helpers ===
    void drawGrid(juce::Graphics&);
    void drawMarkers(juce::Graphics&);

    juce::OpenGLContext openGLContext;

    PlotDataBuffer2D dataBuffer;

    // Rendering state
    bool autoFitX = false;
    bool autoFitY = false;

    juce::Colour lineColor = juce::Colours::cyan;
    juce::Colour markerColor = juce::Colours::yellow;

    std::map<int, std::pair<float, juce::String>> verticalMarkers;
    std::map<int, std::pair<float, juce::String>> horizontalMarkers;
};
