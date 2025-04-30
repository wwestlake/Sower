#pragma once

enum class ThemeColorId : int
{
    // === Oscilloscope ===
    OscilloscopeGrid = 0x3001000,
    OscilloscopeTimeMarker,
    OscilloscopeTriggerLine,
    OscilloscopeMeasurementWindow,
    OscilloscopeWaveform,
    OscilloscopeWaveformInactive,

    // Future categories (Spectrogram, EQ, etc.) could follow...
};

// Utility function to convert ThemeColorId to int
inline int toColourId(ThemeColorId id)
{
    return static_cast<int>(id);
}
