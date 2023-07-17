//------------------------------------------------------------------------
// Copyright(c) 2023 AFSAudio.
//------------------------------------------------------------------------

#pragma once
#include <cmath>
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "params.h"

namespace MyCompanyName {

//------------------------------------------------------------------------
//  Stuff2Processor
//------------------------------------------------------------------------
class Stuff2Processor : public Steinberg::Vst::AudioEffect
{
public:
	Stuff2Processor ();
	~Stuff2Processor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new Stuff2Processor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
	float fGain = GAIN_DEFAULT;
	float fSineShift = SINE_SHIFT_DEFAULT;
	float fSawShift = SAW_SHIFT_DEFAULT;
	float fSquareShift = SQUARE_SHIFT_DEFAULT;
	float fTriangleShift = TRIANGLE_SHIFT_DEFAULT;
	float fDryWet = DRY_WET_DEFAULT;
	float fClipThreshold = CLIP_THRESHOLD_DEFAULT;
	float pi = 1 / std::acos(-1.0);

};

//------------------------------------------------------------------------
} // namespace MyCompanyName
