// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "SoundSource.h"

//! @ingroup Audio
class SoundInstance
{
public:
	bool Permanent = false; // If true, then the SoundManager will never delete this one.
	int  Channel;
public:
	SoundInstance(const SoundSource& source, float x, float y, float z = 0.0f);
	SoundInstance(const SoundSource& source);
	~SoundInstance();

	void pause();
	void resume();

	int getOffset();
	void setOffset(int offset);
	
	void setVolume(float volume);
	void setPitch(float pitch);

	bool isFinished();
private:
	unsigned int mSourceIndex;
};