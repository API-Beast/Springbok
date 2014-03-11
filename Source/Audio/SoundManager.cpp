// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SoundManager.h"
#include "SoundInstance.h"
#include <cassert>
#include <Springbok/Generic/PointerGuard.h>
#include <AL/al.h>

SoundManager* SoundManager::gInstance = nullptr;

// Make sure that gInstance gets deleted when the application gets closed
namespace
{
PointerGuard<SoundManager> guard(&SoundManager::gInstance);
}


SoundManager* SoundManager::GetInstance()
{
	if(gInstance == nullptr)
		gInstance = new SoundManager;
	return gInstance;
}

SoundManager::SoundManager()
{
	mDeviceIndex = alcOpenDevice(NULL);
	if(mDeviceIndex != NULL)
	{
		mContextIndex = alcCreateContext(mDeviceIndex, NULL);
		if(mContextIndex != NULL)
			alcMakeContextCurrent(mContextIndex);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}
	assert(!alcGetError(mDeviceIndex));
}

SoundManager::~SoundManager()
{
	if(mContextIndex != NULL)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(mContextIndex);
	}
	if(mDeviceIndex != NULL)
		alcCloseDevice(mDeviceIndex);
}

void SoundManager::makeCurrent()
{
	alcMakeContextCurrent(mContextIndex);
}

void SoundManager::manageSoundInstance(SoundInstance* instance)
{
	mSoundInstances.push_back(instance);
}

bool SoundManager::canManageMoreSoundInstances()
{
	return mSoundInstances.size() < 32; // Arbitary number, most OpenAL implementations should atleast support this many.
}

void SoundManager::cleanUp()
{
	// Remove from normal list
	for(auto it = mSoundInstances.begin(); it != mSoundInstances.end();)
	{
		SoundInstance* value = *it;
		if(value->isFinished() && (!value->Permanent))
		{
			it = mSoundInstances.erase(it);
			delete value;
		}
		else
			++it;
	}
}

void SoundManager::setListenerPosition(Vec2F pos)
{
	alListener3f(AL_POSITION, pos[0], pos[1], 300.f);
}

