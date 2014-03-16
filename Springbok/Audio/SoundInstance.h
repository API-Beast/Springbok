// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "SoundSource.h"

class SoundManager;

//! @ingroup Audio
class SoundInstance
{
public:
	bool Permanent = false; // If true, then the SoundManager will never delete this one.
	int  Channel = 0;
public:
	SoundInstance(const SoundSource& source, float x, float y, float z = 0.0f);
	SoundInstance(const SoundSource& source);
	~SoundInstance();

	virtual void pause();
	virtual void resume();

	virtual int getOffset();
	virtual void setOffset(int offset);
	
	void setVolume(float volume);
	void setPitch(float pitch);

	virtual bool isFinished();
private:
	unsigned int mSourceIndex;
	float mOriginalVolume = 1.0f;
	void setChannelVolume(float channelVolume);
	friend class SoundManager;
};