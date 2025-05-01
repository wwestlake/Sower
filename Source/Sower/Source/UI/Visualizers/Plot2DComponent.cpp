#include "Plot2DComponent.h"

Plot2DComponent::Plot2DComponent()
{
    openGLContext.setRenderer(this);
    openGLContext.setPixelFormat(juce::OpenGLPixelFormat(8, 8, 8, 8)); // RGBA 8-bit

    openGLContext.attachTo(*this);
    openGLContext.setContinuousRepainting(true);
}

Plot2DComponent::~Plot2DComponent()
{
    openGLContext.detach();
}

void Plot2DComponent::setXRange(float min, float max) { xMin = min; xMax = max; }
void Plot2DComponent::setYRange(float min, float max) { yMin = min; yMax = max; }
void Plot2DComponent::setAutoFitX(bool enabled) { autoFitX = enabled; }
void Plot2DComponent::setAutoFitY(bool enabled) { autoFitY = enabled; }
void Plot2DComponent::setTitle(const juce::String& newTitle) { title = newTitle; }
void Plot2DComponent::setAxisLabels(const juce::String& xLabel, const juce::String& yLabel, const juce::String&) {
    xAxisLabel = xLabel;
    yAxisLabel = yLabel;
}

void Plot2DComponent::setShowGrid(bool enabled) { showGrid = enabled; }
void Plot2DComponent::setPadding(float percent) { paddingPercent = percent; }

void Plot2DComponent::setLineColor(juce::Colour color) { setGridLineColor(color); }
void Plot2DComponent::setMarkerColor(juce::Colour color) { markerColor = color; }
void Plot2DComponent::setGridLineColor(juce::Colour color) { gridLineColor = color; }
void Plot2DComponent::setAxisLineColor(juce::Colour color) { axisLineColor = color; }
void Plot2DComponent::setTickMarkColor(juce::Colour color) { tickMarkColor = color; }
void Plot2DComponent::setAxisAlpha(float alpha) 
{ 
    axisAlpha = juce::jlimit(0.0f, 1.0f, alpha); 
}

void Plot2DComponent::setVerticalMarker(int id, float x, const juce::String& label) {
    verticalMarkers[id] = { x, label };
}
void Plot2DComponent::setHorizontalMarker(int id, float y, const juce::String& label) {
    horizontalMarkers[id] = { y, label };
}
void Plot2DComponent::clearMarkers() {
    verticalMarkers.clear();
    horizontalMarkers.clear();
}

void Plot2DComponent::clearData() { dataBuffer.clear(); }
void Plot2DComponent::repaintPlot() { repaint(); }
void Plot2DComponent::appendPoint(float x, float y) { dataBuffer.append({ x, y }); }
void Plot2DComponent::appendBlock(const std::vector<juce::Point<float>>& points) { dataBuffer.appendBlock(points); }

void Plot2DComponent::newOpenGLContextCreated() 
{
    juce::gl::glEnable(juce::gl::GL_BLEND);
    juce::gl::glBlendFunc(juce::gl::GL_SRC_ALPHA, juce::gl::GL_ONE_MINUS_SRC_ALPHA);
}

void Plot2DComponent::openGLContextClosing() {}

void Plot2DComponent::renderOpenGL()
{
    juce::gl::glEnable(juce::gl::GL_BLEND);
    juce::gl::glBlendFunc(juce::gl::GL_SRC_ALPHA, juce::gl::GL_ONE_MINUS_SRC_ALPHA);

    juce::OpenGLHelpers::clear(juce::Colours::black);

    juce::gl::glMatrixMode(juce::gl::GL_PROJECTION);
    juce::gl::glLoadIdentity();
    juce::gl::glOrtho(xMin, xMax, yMin, yMax, -1.0, 1.0);

    juce::gl::glMatrixMode(juce::gl::GL_MODELVIEW);
    juce::gl::glLoadIdentity();

    renderGrid();
    renderAxes();
    renderTickMarks();
    renderMarkers();
    renderData();
}

void Plot2DComponent::renderGrid()
{
    if (!showGrid) return;

    auto gridColor = gridLineColor.withAlpha(axisAlpha);
    juce::gl::glColor4f(gridColor.getFloatRed(), gridColor.getFloatGreen(), gridColor.getFloatBlue(), gridColor.getFloatAlpha());

    juce::gl::glBegin(juce::gl::GL_LINES);

    const float xStep = (xMax - xMin) / 10.0f;
    const float yStep = (yMax - yMin) / 10.0f;

    for (float x = xMin; x <= xMax; x += xStep) {
        juce::gl::glVertex2f(x, yMin);
        juce::gl::glVertex2f(x, yMax);
    }

    for (float y = yMin; y <= yMax; y += yStep) {
        juce::gl::glVertex2f(xMin, y);
        juce::gl::glVertex2f(xMax, y);
    }

    juce::gl::glEnd();
}

void Plot2DComponent::renderAxes()
{
    auto axisColor = axisLineColor.withAlpha(axisAlpha);
    juce::gl::glColor4f(axisColor.getFloatRed(), axisColor.getFloatGreen(), axisColor.getFloatBlue(), axisColor.getFloatAlpha());

    juce::gl::glBegin(juce::gl::GL_LINES);

    if (xMin <= 0.0f && xMax >= 0.0f) {
        juce::gl::glVertex2f(0.0f, yMin);
        juce::gl::glVertex2f(0.0f, yMax);
    }

    if (yMin <= 0.0f && yMax >= 0.0f) {
        juce::gl::glVertex2f(xMin, 0.0f);
        juce::gl::glVertex2f(xMax, 0.0f);
    }

    juce::gl::glEnd();
}

void Plot2DComponent::renderTickMarks()
{
    const float xStep = (xMax - xMin) / 10.0f;
    const float yStep = (yMax - yMin) / 10.0f;
    const float minorX = xStep / 10.0f;
    const float minorY = yStep / 10.0f;

    const float shortTick = (yMax - yMin) * 0.007f;
    const float longTick = (yMax - yMin) * 0.015f;

    auto tickColor = tickMarkColor.withAlpha(axisAlpha);
    juce::gl::glColor4f(tickColor.getFloatRed(), tickColor.getFloatGreen(), tickColor.getFloatBlue(), tickColor.getFloatAlpha());

    juce::gl::glBegin(juce::gl::GL_LINES);

    // X-axis: vertical ticks at y = 0
    if (yMin <= 0.0f && yMax >= 0.0f) {
        for (float gx = xMin; gx <= xMax; gx += xStep) {
            for (int i = 0; i <= 10; ++i) {
                float x = gx + i * minorX;
                if (x > xMax) break;
                float len = (i == 0 || i == 5) ? longTick : shortTick;
                juce::gl::glVertex2f(x, -len);
                juce::gl::glVertex2f(x, len);
            }
        }
    }

    // Y-axis: horizontal ticks at x = 0
    if (xMin <= 0.0f && xMax >= 0.0f) {
        for (float gy = yMin; gy <= yMax; gy += yStep) {
            for (int i = 0; i <= 10; ++i) {
                float y = gy + i * minorY;
                if (y > yMax) break;
                float len = (i == 0 || i == 5) ? longTick : shortTick;
                juce::gl::glVertex2f(0.0f - len, y);
                juce::gl::glVertex2f(0.0f + len, y);
            }
        }
    }

    juce::gl::glEnd();
}

void Plot2DComponent::renderMarkers()
{
    auto markerCol = markerColor.withAlpha(axisAlpha);
    juce::gl::glColor4f(markerCol.getFloatRed(), markerCol.getFloatGreen(), markerCol.getFloatBlue(), markerCol.getFloatAlpha());

    juce::gl::glBegin(juce::gl::GL_LINES);

    for (const auto& [id, pair] : verticalMarkers) {
        float x = pair.first;
        juce::gl::glVertex2f(x, yMin);
        juce::gl::glVertex2f(x, yMax);
    }

    for (const auto& [id, pair] : horizontalMarkers) {
        float y = pair.first;
        juce::gl::glVertex2f(xMin, y);
        juce::gl::glVertex2f(xMax, y);
    }

    juce::gl::glEnd();
}

void Plot2DComponent::renderData()
{
    // Future waveform rendering
}
