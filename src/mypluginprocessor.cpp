//------------------------------------------------------------------------
// Copyright(c) 2023 AFSAudio.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "waves.h"
#include "pluginterfaces/base/ibstream.h"
#include "public.sdk/source/vst/vsthelpers.h"


using namespace Steinberg;

namespace MyCompanyName {
//------------------------------------------------------------------------
// Stuff2Processor
//------------------------------------------------------------------------
Stuff2Processor::Stuff2Processor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kStuff2ControllerUID);
}

//------------------------------------------------------------------------
Stuff2Processor::~Stuff2Processor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
				
				if (paramQueue->getPoint(numParamsChanged - 1, sampleOffset, value) == kResultTrue) {
					switch (paramQueue->getParameterId())
					{
					case kGain: {
						fGain = (float)value;
						break;
					}

					case kSineShift: {
						fSineShift = (float)value;
						break;
					}

					case kDryWet: {
						fDryWet = (float)value;
						break;
					}

					case kSawShift: {
						fSawShift = (float)value;
						break;
					}

					case  kSquareShift: {
						fSquareShift = (float)value;
						break;
					}

					case kTriangleShift: {
						fTriangleShift = (float)value;
						break;
					}

					case kClipThreshold: {
						fClipThreshold = (float)value;
						break;
					}
					}
				}
			}
		}
	}
	
	//--- Here you have to implement your processing
	if (data.numInputs == 0 || data.numOutputs == 0) {
		return kResultOk;
	}

	int32 numChannels = data.inputs[0].numChannels;
	Vst::Sample32** in = data.inputs[0].channelBuffers32;
	Vst::Sample32** out = data.outputs[0].channelBuffers32;

	for (int32 ch = 0; ch < numChannels; ch++) {
		Vst::Sample32* pIn = in[ch];
		Vst::Sample32* pOut = out[ch];
		Vst::Sample32 tmp;

		for (int32 i = 0; i < data.numSamples; i++) {
			//Sine shift
			tmp = *pIn * sin(i * fSineShift);

			//Saw shift
			if (fSawShift > 0) {
				tmp += *pIn * saw(100, i * fSawShift);
			}

			//Square shift
			if (fSquareShift > 0) {
				tmp += *pIn * square(100, i * fSquareShift);
			}

			//Triangle shift
			if (fTriangleShift > 0) {
				tmp += *pIn * triangle(100, i * fTriangleShift);
			}

			//DryWetMix
			tmp = ((*pIn * (1 - fDryWet)) + ((tmp) * fDryWet)) * fGain;
			*pOut = (tmp > fClipThreshold) ? tmp * fClipThreshold : (tmp < (fClipThreshold * -1)) ? tmp * (fClipThreshold * -1) : tmp;

			pIn++;
			pOut++;
		}
	}

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	if (!state)
		return kInvalidArgument;

	IBStreamer streamer(state, kLittleEndian);
	float savedGain = GAIN_DEFAULT;
	if (streamer.readFloat(savedGain) == false)
		return kResultFalse;


	float savedSineShift = SINE_SHIFT_DEFAULT;
	if (streamer.readFloat(savedSineShift) == false)
		return kResultFalse;
	
	float savedSawShift = SAW_SHIFT_DEFAULT;
	if (streamer.readFloat(savedSawShift) == false)
		return kResultFalse;


	float savedSquareShift = SQUARE_SHIFT_DEFAULT;
	if (streamer.readFloat(savedSquareShift) == false)
		return kResultFalse;
	

	float savedTriangleShift = TRIANGLE_SHIFT_DEFAULT;
	if (streamer.readFloat(savedSquareShift) == false)
		return kResultFalse;
	

	float savedDryWet = DRY_WET_DEFAULT;
	if (streamer.readFloat(savedDryWet) == false)
		return kResultFalse;
	fDryWet = savedDryWet;

	float savedClipThreshold = CLIP_THRESHOLD_DEFAULT;
	if (streamer.readFloat(savedClipThreshold) == false)
		return kResultFalse;
	fClipThreshold = savedClipThreshold;

	
	fGain = savedGain;
	fSineShift = savedSineShift;
	fSawShift = savedSawShift;
	fSquareShift = savedSquareShift;
	fTriangleShift = savedTriangleShift;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Processor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	streamer.writeFloat(fGain);
	streamer.writeFloat(fSineShift);
	streamer.writeFloat(fSawShift);
	streamer.writeFloat(fSquareShift);
	streamer.writeFloat(fTriangleShift);
	streamer.writeFloat(fDryWet);
	streamer.writeFloat(fClipThreshold);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
