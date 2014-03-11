// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SoundInstance.h"
#include "SoundSource.h"
#include "SoundManager.h"
#include "SoundSample.h"

#include <Springbok/Resources/ResourceManager.h>
#include <Springbok/Utils/Debug.h>

SoundSource::SoundSource(const std::string& filename)
{
	Sample = ResourceManager::GetInstance()->getResource<SoundSample>(filename);
}

SoundInstance* SoundSource::play(Vec2F position, SoundManager* s)
{
	if(Sample->Channels > 1 && !Sample->WarnedAboutStereoPosition)
	{
		Sample->WarnedAboutStereoPosition = true;
		Debug::Write("WARNING: Trying to play stereo sound $ at a position, non-global sound samples should be mono as attenuation doesn't work with Stereo.", Sample->Location);
	}
		
	if(!s->canManageMoreSoundInstances()) s->cleanUp();
	SoundInstance* instance = new SoundInstance(*this, position.X, position.Y);
	s->manageSoundInstance(instance);
	return instance;
}

SoundInstance* SoundSource::playGlobal(SoundManager* s)
{
	if(!s->canManageMoreSoundInstances()) s->cleanUp();
	SoundInstance* instance = new SoundInstance(*this);
	s->manageSoundInstance(instance);
	return instance;
}