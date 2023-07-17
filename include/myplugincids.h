//------------------------------------------------------------------------
// Copyright(c) 2023 AFSAudio.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kStuff2ProcessorUID (0x68FA6256, 0x24FD5C38, 0xAC484B6E, 0xD455688A);
static const Steinberg::FUID kStuff2ControllerUID (0x3C8AABA8, 0x28BC5CA3, 0x8F13D24A, 0xC9B3E0EF);

#define Stuff2VST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName
