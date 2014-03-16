// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

//! @ingroup Audio-Internals
struct SoundSample
{
	SoundSample(const std::string& filename);
	~SoundSample();
	unsigned int BufferIndex;
	int Channels = 1;
	std::string Location;
	bool WarnedAboutStereoPosition = false;
};