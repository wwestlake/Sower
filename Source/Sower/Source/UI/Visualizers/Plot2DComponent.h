#pragma once

#include <JuceHeader.h>
#include "PlotComponentBase.h"
#include "PlotDataBuffer.h"

class Plot2DComponent : public PlotComponentBase,
    private juce::OpenGLRenderer
{
public:
    Plot2DComponent();
    ~Plot2DComponent() override;

    // === PlotComponentBase overrides ===
    void setXRange(float min, float max) override;
    void setYRange(float min, float max) override;
    void setZRange(float, float) override {} // No-op for 2D

    void setAutoFitX(bool enabled) override;
    void setAutoFitY(bool enabled) override;

    void setTitle(const juce::String& newTitle) override;
    void setAxisLabels(const juce::String& xLabel, const juce::String& yLabel, const juce::String&) override;

    void setShowGrid(bool enabled) override;
    void setPadding(float percent) override;

    void setLineColor(juce::Colour color) override;       // Alias for setGridLineColor
    void setMarkerColor(juce::Colour color) override;

    void setGridLineColor(juce::Colour color);
    void setAxisLineColor(juce::Colour color);
    void setTickMarkColor(juce::Colour color);

    void setVerticalMarker(int id, float x, const juce::String& label = {}) override;
    void setHorizontalMarker(int id, float y, const juce::String& label = {}) override;
    void clearMarkers() override;

    void clearData() override;
    void repaintPlot() override;

    void appendPoint(float x, float y);
    void appendBlock(const std::vector<juce::Point<float>>& points);
    void setAxisAlpha(float alpha); // Adjusts opacity for grid, axis, and tick visuals

private:
    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

    void renderGrid();
    void renderAxes();
    void renderTickMarks();
    void renderMarkers();
    void renderData();

    juce::OpenGLContext openGLContext;
    PlotDataBuffer2D dataBuffer;

    bool autoFitX = false;
    bool autoFitY = false;

    juce::Colour gridLineColor = juce::Colours::grey;
    juce::Colour axisLineColor = juce::Colours::grey;
    juce::Colour tickMarkColor = juce::Colours::grey;
    juce::Colour markerColor = juce::Colours::lightgrey;

    float axisAlpha = 1.0f;

    float xMin = -1.0f;
    float xMax = 1.0f;
    float yMin = -1.0f;
    float yMax = 1.0f;

    juce::String title;
    juce::String xAxisLabel, yAxisLabel;
    float paddingPercent = 0.0f;

    std::map<int, std::pair<float, juce::String>> verticalMarkers;
    std::map<int, std::pair<float, juce::String>> horizontalMarkers;
};
