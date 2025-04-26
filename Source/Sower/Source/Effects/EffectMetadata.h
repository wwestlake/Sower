#pragma once

struct EffectMetadata
{
    const char* name;        // Short name of the effect (e.g., "Gain")
    const char* description; // A sentence describing the effect purpose
    const char* category;    // Category for organizing (e.g., "Utility", "Filter")
    const char* iconName;    // Name or ID of the associated UI icon
};