// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include <Springbok/Foundation/Vec2.h>
#include <Springbok/Foundation/ObjectPointer.h>
#include "SoundManager.h"

class SoundInstance;
class SoundSample;

//! @ingroup Audio
class SoundSource
{
public:
	float Volume = 1.f;
	float Pitch  = 1.f;
	float MinRange =  800.f;
	float MaxRange = 2500.f;
	int   Channel = 0;
	ObjectPointer<SoundSample> Sample = nullptr;
public:
	SoundSource() = default;
	SoundSource(const std::string& filename);
	SoundInstance* play(Vec2F position, SoundManager* s = SoundManager::GetInstance());
	SoundInstance* playGlobal(SoundManager* s = SoundManager::GetInstance());
};
