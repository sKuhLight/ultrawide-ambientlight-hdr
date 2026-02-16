#pragma once

#include <vector>
#include <string>

#include "windows.h"

#define DEFAULT_BLUR_SAMPLES        5
#define DEFAULT_BLUR_PASSES		    3
#define DEFAULT_BLUR_DOWNSCALE	    64
#define DEFAULT_ZOOM                1
#define DEFAULT_FRAMERATE	        30
#define DEFAULT_MIRRORED	        false
#define DEFAULT_STRETCHED           true
#define DEFAULT_VIGNETTE_ENABLED    true
#define DEFAULT_VIGNETTE_INTENSITY  1.0f
#define DEFAULT_VIGNETTE_RADIUS     0.99f
#define DEFAULT_VIGNETTE_SMOOTHNESS 0.4f
#define DEFAULT_AUTO_DETECTION      false
#define DEFAULT_AUTO_DETECTION_TIME 500
#define DEFAULT_AUTO_DETECTION_BRIGHTNESS_THRESHOLD 0.03f
#define DEFAULT_AUTO_DETECTION_BLACK_RATIO 0.60f
#define DEFAULT_AUTO_DETECTION_LIGHT_MASK true
#define DEFAULT_AUTO_DETECTION_SYMMETRIC_BARS false
#define DEFAULT_AUTO_DETECTION_RESERVED_AREA false
#define DEFAULT_AUTO_DETECTION_RESERVED_WIDTH 16
#define DEFAULT_AUTO_DETECTION_RESERVED_HEIGHT 9
#define DEFAULT_SHOW_IN_TASKBAR     true
#define DEFAULT_SATURATION          1.0f
#define DEFAULT_BRIGHTNESS          1.0f
#define DEFAULT_CONTRAST            1.0f
#define DEFAULT_HDR_BOOST_ENABLED   false
#define DEFAULT_HDR_BOOST_STRENGTH  1.0f
#define DEFAULT_HDR_OUTPUT_ENABLED  false
#define DEFAULT_HDR_PAPER_WHITE_NITS 200.0f

struct ResolutionSettings
{
    std::string name = "";
    UINT width = 0;
    UINT height = 0;
};

struct Resolutions
{
    std::string current;
    std::vector<ResolutionSettings> available;
};

struct AppSettings
{
    bool loaded = false;
    UINT gameWidth = 0;
    UINT gameHeight = 0;
    UINT blurDownscale = 0;
    UINT blurPasses = 0;
    UINT blurSamples = 0;
    UINT frameRate = 0;
    bool mirrored = false;
    bool stretched = true;
    UINT zoom = 1;
    bool vignetteEnabled = true;
    float vignetteIntensity = 0.0f;
    float vignetteRadius = 0.0f;
    float vignetteSmoothness = 0.0f;
    Resolutions resolutions;
    bool useAutoDetection = false;
    float autoDetectionBrightnessThreshold = DEFAULT_AUTO_DETECTION_BRIGHTNESS_THRESHOLD;
    float autoDetectionBlackRatio = DEFAULT_AUTO_DETECTION_BLACK_RATIO;
    int autoDetectionTime = DEFAULT_AUTO_DETECTION_TIME;
    bool autoDetectionLightMask = DEFAULT_AUTO_DETECTION_LIGHT_MASK;
    bool autoDetectionSymmetricBars = false;
    bool autoDetectionReservedArea = false;
    UINT autoDetectionReservedWidth = 0;
    UINT autoDetectionReservedHeight = 0;
    bool showInTaskbar = DEFAULT_SHOW_IN_TASKBAR;
    float saturation = DEFAULT_SATURATION;
    float brightness = DEFAULT_BRIGHTNESS;
    float contrast = DEFAULT_CONTRAST;
    bool hdrBoostEnabled = DEFAULT_HDR_BOOST_ENABLED;
    float hdrBoostStrength = DEFAULT_HDR_BOOST_STRENGTH;
    bool hdrOutputEnabled = DEFAULT_HDR_OUTPUT_ENABLED;
    float hdrPaperWhiteNits = DEFAULT_HDR_PAPER_WHITE_NITS;
};


bool ReadSettings(AppSettings& settings);
void SaveSettings(AppSettings& settings);
