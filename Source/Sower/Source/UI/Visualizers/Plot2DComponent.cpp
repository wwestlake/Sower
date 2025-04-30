#include "Plot2DComponent.h"
#include <JuceHeader.h>

#include <algorithm>



Plot2DComponent::Plot2DComponent()
{
    openGLContext.setRenderer(this);
    openGLContext.attachTo(*this);
    openGLContext.setContinuousRepainting(true);
}

Plot2DComponent::~Plot2DComponent()
{
    openGLContext.detach();
}

// === PlotComponentBase ===

void Plot2DComponent::setXRange(float min, float max)
{
    xMin = min;
    xMax = max;
}

void Plot2DComponent::setYRange(float min, float max)
{
    yMin = min;
    yMax = max;
}

void Plot2DComponent::setAutoFitX(bool enabled)
{
    autoFitX = enabled;
}

void Plot2DComponent::setAutoFitY(bool enabled)
{
    autoFitY = enabled;
}

void Plot2DComponent::setTitle(const juce::String& newTitle)
{
    title = newTitle;
}

void Plot2DComponent::setAxisLabels(const juce::String& xLabel, const juce::String& yLabel, const juce::String&)
{
    xAxisLabel = xLabel;
    yAxisLabel = yLabel;
}

void Plot2DComponent::setShowGrid(bool enabled)
{
    showGrid = enabled;
}

void Plot2DComponent::setPadding(float percent)
{
    paddingPercent = percent;
}

void Plot2DComponent::setLineColor(juce::Colour color)
{
    lineColor = color;
}

void Plot2DComponent::setMarkerColor(juce::Colour color)
{
    markerColor = color;
}

void Plot2DComponent::setVerticalMarker(int id, float x, const juce::String& label)
{
    verticalMarkers[id] = { x, label };
}

void Plot2DComponent::setHorizontalMarker(int id, float y, const juce::String& label)
{
    horizontalMarkers[id] = { y, label };
}

void Plot2DComponent::clearMarkers()
{
    verticalMarkers.clear();
    horizontalMarkers.clear();
}

void Plot2DComponent::clearData()
{
    dataBuffer.clear();
}

void Plot2DComponent::repaintPlot()
{
    repaint(); // Triggers OpenGL paint via continuous repaint
}

void Plot2DComponent::appendPoint(float x, float y)
{
    dataBuffer.append({ x, y });
}

void Plot2DComponent::appendBlock(const std::vector<juce::Point<float>>& points)
{
    dataBuffer.appendBlock(points);
}

// === OpenGLRenderer ===

void Plot2DComponent::newOpenGLContextCreated()
{
    // Initialize GL resources here (shaders, VBOs, etc.) — TBD
}

void Plot2DComponent::renderOpenGL()
{
    juce::OpenGLHelpers::clear(juce::Colours::black);

    juce::gl::glMatrixMode(juce::gl::GL_PROJECTION);
    juce::gl::glLoadIdentity();
    juce::gl::glOrtho(xMin, xMax, yMin, yMax, -1.0, 1.0);

    juce::gl::glMatrixMode(juce::gl::GL_MODELVIEW);
    juce::gl::glLoadIdentity();

    renderGrid();
    renderMarkers();
    renderData(); // empty for now
}

void Plot2DComponent::renderGrid()
{
    if (!showGrid) return;

    juce::gl::glColor3f(0.25f, 0.25f, 0.25f); // light gray lines

    const float xStep = (xMax - xMin) / 10.0f;
    const float yStep = (yMax - yMin) / 10.0f;

    juce::gl::glBegin(juce::gl::GL_LINES);
    for (float x = xMin; x <= xMax; x += xStep)
    {
        juce::gl::glVertex2f(x, yMin);
        juce::gl::glVertex2f(x, yMax);
    }
    for (float y = yMin; y <= yMax; y += yStep)
    {
        juce::gl::glVertex2f(xMin, y);
        juce::gl::glVertex2f(xMax, y);
    }
    juce::gl::glEnd();
}

void Plot2DComponent::renderMarkers()
{
    juce::gl::glColor3f(markerColor.getFloatRed(), markerColor.getFloatGreen(), markerColor.getFloatBlue());

    juce::gl::glBegin(juce::gl::GL_LINES);

    for (const auto& [id, pair] : verticalMarkers)
    {
        float x = pair.first;
        juce::gl::glVertex2f(x, yMin);
        juce::gl::glVertex2f(x, yMax);
    }

    for (const auto& [id, pair] : horizontalMarkers)
    {
        float y = pair.first;
        juce::gl::glVertex2f(xMin, y);
        juce::gl::glVertex2f(xMax, y);
    }

    juce::gl::glEnd();
}

void Plot2DComponent::renderData()
{
    // Will implement this later
}


void Plot2DComponent::openGLContextClosing()
{
    // Free GL resources here (if allocated)
}
