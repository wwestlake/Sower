#pragma once

#include <JuceHeader.h>

// Abstract base class for 2D and 3D plot components
class PlotComponentBase : public juce::Component
{
public:
    virtual ~PlotComponentBase() = default;

    // === Axis Ranges ===
    virtual void setXRange(float min, float max) = 0;
    virtual void setYRange(float min, float max) = 0;
    virtual void setZRange(float min, float max) = 0; // no-op in 2D

    virtual void setAutoFitX(bool enabled) = 0;
    virtual void setAutoFitY(bool enabled) = 0;

    // === Labels and Titles ===
    virtual void setTitle(const juce::String& newTitle) = 0;
    virtual void setAxisLabels(const juce::String& xLabel,
        const juce::String& yLabel,
        const juce::String& zLabel = {}) = 0;

    // === Grid and Styling ===
    virtual void setShowGrid(bool enabled) = 0;
    virtual void setPadding(float percent) = 0;

    virtual void setLineColor(juce::Colour color) = 0;
    virtual void setMarkerColor(juce::Colour color) = 0;

    // === Marker System ===
    virtual void setVerticalMarker(int id, float x, const juce::String& label = {}) = 0;
    virtual void setHorizontalMarker(int id, float y, const juce::String& label = {}) = 0;
    virtual void clearMarkers() = 0;

    // === Data Lifecycle ===
    virtual void clearData() = 0;
    virtual void repaintPlot() = 0;

protected:
    juce::String title;
    juce::String xAxisLabel, yAxisLabel, zAxisLabel;

    float xMin = 0.0f, xMax = 1.0f;
    float yMin = -1.0f, yMax = 1.0f;
    float zMin = 0.0f, zMax = 0.0f;

    bool showGrid = true;
    float paddingPercent = 0.05f;
};
