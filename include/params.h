#pragma once
enum {
	kGain = 100,
	kSineShift = 101,
	kDryWet = 102,
	kSawShift = 103,
	kSquareShift = 104,
	kTriangleShift = 105,
	kClipThreshold = 106,
};

#define SINE_SHIFT_DEFAULT 0.5f
#define SAW_SHIFT_DEFAULT 0.2f
#define SQUARE_SHIFT_DEFAULT 0.1f
#define TRIANGLE_SHIFT_DEFAULT 0.3f

#define DRY_WET_DEFAULT 0.5f
#define CLIP_THRESHOLD_DEFAULT 0.8f
#define GAIN_DEFAULT 0.5f