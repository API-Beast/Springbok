// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Generic/ObjectPointer.h>

class SoundInstance;
class SoundSample;

//! @ingroup Audio
class SoundSource
{
public:
	float Volume = 1.f;
	float Pitch  = 1.f;
	float MinRange = 1500.f;
	float MaxRange = 2500.f;
	ObjectPointer<SoundSample> Sample = nullptr;
public:
	SoundSource() = default;
	SoundSource(const std::string& filename);
	SoundInstance* play(Vec2F position);
};
