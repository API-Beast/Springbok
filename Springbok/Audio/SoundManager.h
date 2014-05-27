// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <vector>
#include <AL/alc.h>
#include <Springbok/Types/Vec2.h>

class SoundInstance;

//! @ingroup Audio-Internals
class SoundManager
{
//!@name Static
///@{
public:
	static SoundManager* gInstance;
	static SoundManager* GetInstance();
///@}
public:
	SoundManager();
	~SoundManager();
	void makeCurrent();
	void manageSoundInstance(SoundInstance* instance);
	bool canManageMoreSoundInstances();
	void cleanUp();
	void setListenerPosition(Vec2F pos);
	void setChannelVolume(int channel, float volume);
private:
	ALCdevice* mDeviceIndex;
	ALCcontext* mContextIndex;
	std::vector<SoundInstance*> mSoundInstances;
	float mChannelVolume[16] = {1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
	                            1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f};
};