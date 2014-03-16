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
	alSourcei(mSourceIndex,  AL_BUFFER,   source.Sample->BufferIndex);
	alSourcef(mSourceIndex,  AL_PITCH,    source.Pitch);
	alSourcef(mSourceIndex,  AL_GAIN,     source.Volume);
	alSourcef(mSourceIndex,  AL_REFERENCE_DISTANCE, source.MinRange);
	alSourcef(mSourceIndex,  AL_MAX_DISTANCE, source.MaxRange);
	alSource3f(mSourceIndex, AL_POSITION, x, y, z);
	alSourcePlay(mSourceIndex);
	
	Channel = source.Channel;
	mOriginalVolume = source.Volume;
}

SoundInstance::SoundInstance(const SoundSource& source)
{
	alGenSources(1, &mSourceIndex);
	alSourcei(mSourceIndex,  AL_BUFFER,   source.Sample->BufferIndex);
	alSourcef(mSourceIndex,  AL_PITCH,    source.Pitch);
	alSourcef(mSourceIndex,  AL_GAIN,     source.Volume);
	alSourcei(mSourceIndex,  AL_SOURCE_RELATIVE,  true);
	alSourcePlay(mSourceIndex);

	Channel = source.Channel;
	mOriginalVolume = source.Volume;
}

SoundInstance::~SoundInstance()
{
	alSourceStop(mSourceIndex);
	alDeleteSources(1, &mSourceIndex);
}

void SoundInstance::setPitch(float pitch)
{
	alSourcef(mSourceIndex,  AL_PITCH, pitch);
}

void SoundInstance::setVolume(float volume)
{
	alSourcef(mSourceIndex,  AL_GAIN, volume);
	mOriginalVolume = volume;
}

void SoundInstance::setChannelVolume(float channelVolume)
{
	alSourcef(mSourceIndex,  AL_GAIN, mOriginalVolume * channelVolume);
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