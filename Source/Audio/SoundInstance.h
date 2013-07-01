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
	SoundInstance(const SoundSource& source, float x, float y, float z=0.0f);
	~SoundInstance();
	
	void pause();
	void resume();
	
	int getOffset();
	void setOffset(int offset);
	
	bool isFinished();
private:
	unsigned int mSourceIndex;
};