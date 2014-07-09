//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int length)
{
	Particles.reserve(length);
}

void ParticleSystem::addParticle(Particle particle)
{
	if(Particles.size() < Particles.capacity())
		Particles.push_back(particle);
	else // Overwrite old particles if memory limit is overstepped
		Particles[OverwriteIndex++] = particle;
}

void ParticleSystem::cleanUp()
{
	for(int i = 0; i < Particles.size(); ++i)
	{
		if(Particles[i].Age > Particles[i].Definition->LifeTime)
		{
			Particles[i--] = Particles.back();
			Particles.pop_back();
		}
	}
	if(Particles.size() < Particles.capacity())
		OverwriteIndex = 0;
}
