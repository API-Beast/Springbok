//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int length)
{
	Particles = List<Particle>(length);
}

void ParticleSystem::addParticle(Particle particle)
{
	if(Particles.UsedLength < Particles.MemoryLength)
		Particles.pushBack(particle);
	else // Overwrite old particles if memory limit is overstepped
		Particles[OverwriteIndex++] = particle;
}

void ParticleSystem::cleanUp()
{
	for(int i = 0; i < Particles.UsedLength; ++i)
	{
		if(Particles[i].Age > Particles[i].Definition->LifeTime)
			Particles.quickRemove(i--);
	}
	if(Particles.UsedLength < Particles.MemoryLength)
		OverwriteIndex = 0;
}
