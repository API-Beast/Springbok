// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SoundInstance.h"
#include "SoundSource.h"
#include "SoundSample.h"
#include <iostream>
#include <AL/al.h>
#include <cassert>

SoundInstance::SoundInstance(const SoundSource& source, float x, float y, float z)
{
  alGenSources(1, &mSourceIndex);
  alSourcei(mSourceIndex, AL_BUFFER, source.Sample->BufferIndex);
  alSourcef(mSourceIndex, AL_PITCH,  source.Pitch);
  alSourcef(mSourceIndex, AL_GAIN,   source.Volume);
  alSource3f(mSourceIndex, AL_POSITION, x, y, z);
  alSourcePlay(mSourceIndex);
	assert(!alGetError());
}

SoundInstance::~SoundInstance()
{
	alSourceStop(mSourceIndex);
	alDeleteSources(1, &mSourceIndex);
}

int SoundInstance::getOffset()
{
	int value;
	alGetSourcei(mSourceIndex, AL_SAMPLE_OFFSET, &value);
	return value;
}

void SoundInstance::setOffset(int offset)
{
	alSourcei(mSourceIndex, AL_SAMPLE_OFFSET, offset);
}

void SoundInstance::pause()
{
	alSourcePause(mSourceIndex);
}

void SoundInstance::resume()
{
	alSourcePlay(mSourceIndex);
}

bool SoundInstance::isFinished()
{
	int state;
	alGetSourcei(mSourceIndex, AL_SOURCE_STATE, &state);
	return state == AL_STOPPED;
}