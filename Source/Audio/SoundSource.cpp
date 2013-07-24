// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SoundInstance.h"
#include "SoundSource.h"
#include "SoundManager.h"
#include "SoundSample.h"

#include <Springbok/Resources/ResourceManager.h>

SoundSource::SoundSource(const std::string& filename)
{
	Sample = ResourceManager::GetInstance()->getResource<SoundSample>(filename);
}

SoundInstance* SoundSource::play(Vec2F position)
{
	SoundManager* s = SoundManager::GetInstance();
	if(!s->canManageMoreSoundInstances()) s->cleanUp();
	SoundInstance* instance = new SoundInstance(*this, position.X, position.Y);
	s->manageSoundInstance(instance);
	return instance;
}
