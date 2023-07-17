//------------------------------------------------------------------------
// Copyright(c) 2023 AFSAudio.
//------------------------------------------------------------------------

#include "params.h"
#include "myplugincontroller.h"
#include "myplugincids.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "pluginterfaces/base/ibstream.h"
#include "base/source/fstreamer.h"

using namespace Steinberg;

namespace MyCompanyName {

//------------------------------------------------------------------------
// Stuff2Controller Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}


	parameters.addParameter(STR16("GAIN"), nullptr, 0, GAIN_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kGain);

	parameters.addParameter(STR16("SINESHIFT"), nullptr, 0, SINE_SHIFT_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kSineShift);

	parameters.addParameter(STR16("SAWSHIFT"), nullptr, 0, SAW_SHIFT_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kSawShift);

	parameters.addParameter(STR16("SQUARESHIFT"), nullptr, 0, SQUARE_SHIFT_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kSquareShift);

	parameters.addParameter(STR16("TRIANGLESHIFT"), nullptr, 0, TRIANGLE_SHIFT_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kTriangleShift);

	parameters.addParameter(STR16("DRYWET"), nullptr, 0, DRY_WET_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kDryWet);

	parameters.addParameter(STR16("CLIPTHRESHOLD"), nullptr, 0, CLIP_THRESHOLD_DEFAULT,
		Vst::ParameterInfo::kCanAutomate, kClipThreshold);

	// Here you could register some parameters

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	IBStreamer streamer(state, kLittleEndian);

	float fVal;
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kGain, fVal);
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kSineShift, fVal);
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kSawShift, fVal);
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kSquareShift, fVal);
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kTriangleShift, fVal);
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kDryWet, fVal);
	if (streamer.readFloat(fVal) == false)
		return kResultFalse;
	setParamNormalized(kClipThreshold, fVal);


	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::setState (IBStream* state)
{
	// Here you get the state of the controller



	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor


	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API Stuff2Controller::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "myplugineditor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API Stuff2Controller::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
