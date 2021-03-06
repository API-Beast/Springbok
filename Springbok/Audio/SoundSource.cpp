// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SoundInstance.h"
#include "SoundSource.h"
#include "SoundManager.h"
#include "SoundSample.h"

#include <Springbok/Foundation/ResourceManager.h>
#include <Springbok/Utils/Functions.h>

SoundSource::SoundSource(const std::string& filename)
{
	Sample = ResourceManager::GetInstance()->getResource<SoundSample>(filename);
}

SoundInstance* SoundSource::play(Vec2F position, SoundManager* s)
{
	if(!Sample) return nullptr;
	
	if(Sample->Channels > 1 && !Sample->WarnedAboutStereoPosition)
	{
		Sample->WarnedAboutStereoPosition = true;
		DebugLog("WARNING: Trying to play stereo sound $ at a position, non-global sound samples should be mono as attenuation doesn't work with Stereo.", Sample->Location);
	}
	if(Sample->Valid == false)
	{
		if(!Sample->WarnedAboutStereoPosition)
		{
			Sample->WarnedAboutStereoPosition = true;
			DebugLog("WARNING: Trying to play invalid sound, see errors above.");
		}
		return nullptr;
	}
		
	if(!s->canManageMoreSoundInstances()) s->cleanUp();
	SoundInstance* instance = new SoundInstance(*this, position.X, position.Y);
	s->manageSoundInstance(instance);
	return instance;
}

SoundInstance* SoundSource::playGlobal(SoundManager* s)
{
	if(!Sample) return nullptr;
	
	if(!s->canManageMoreSoundInstances()) s->cleanUp();
	SoundInstance* instance = new SoundInstance(*this);
	s->manageSoundInstance(instance);
	return instance;
}