//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Platform/InputMonitor.h>
#include <Springbok/Platform/GameSurface.h>
#include <Springbok/Platform/PreciseClock.h>
#include <Springbok/Platform/FileInfo.h>

#include <Springbok/Graphics/RenderContext2D.h>
#include <Springbok/Graphics/Image.h>
#include <Springbok/Graphics/BatchRenderer.h>

#include <Springbok/Resources/ResourceManager.h>
#include <Springbok/Procedural/RandomNumberGenerator.h>
#include "AssetDefinition.h"

int main()
{
	// Initialization
	GameSurface surface("Particles - Springbok Example", GameSurface::Windowed);
	InputMonitor       input(&surface);
	RenderContext2D renderer(&surface);
	ResourceManager::GetInstance()->findPrimaryResourcePath({FileInfo(__FILE__).up()+"/Assets", "./Assets"});

	// Start the timer
	PreciseClock timer;
	timer.start();
	float gameTime = 0.f;
	float particleEmitAccum = 0.f;
	
	// Load assets
	gAssets.initAll();
	
	int maxParticles = 100000;
	ParticleSystem particles(maxParticles);
	BatchRenderer2D batcher(maxParticles * 4 * sizeof(BasicVertex));
	
	while(!surface.closeRequested())
	{
		surface.switchBuffers();
		renderer.clear(Palette::Orange / 2);
		
		float dt = timer.elapsed() - gameTime;
		gameTime = timer.elapsed();
		
		// Add new particles on the left side
		
		particles.cleanUp();
		particleEmitAccum+=dt;
		while(particleEmitAccum > 0.002f)
		{
			for(int i = 0; i < 10; ++i)
			{
				Particle party;
				party.Definition = &gAssets.Spark;
				party.Position   = Vec2F(gRNG.getNumber(-surface.size().X/2, +surface.size().X/2), surface.size().Y/2 + 100);
				party.Velocity   = Vec2F(0.f, -surface.size().Y/2) + gRNG.getVec2(Vec2F(-400), Vec2F(400));
				party.Position  -= party.Velocity*particleEmitAccum;
				party.Age -= particleEmitAccum;
				party.Size = gRNG.getNumber(0.01f, 10.0f);
				party.Color.X = 0.75f + gRNG.getFloat()/4;
				party.Color.Z = 0.75f + gRNG.getFloat()/4;
				party.Color.W = (10.f - party.Size) / 10;
				particles.addParticle(party);
			}
			particleEmitAccum -= 0.002f;
		}
		
		for(Particle& particle : particles.Particles)
		{
			particle.Age += dt;
			particle.Velocity += particle.Accleration*dt;
			particle.Position += particle.Velocity*dt;
		}
		
		renderer.setBlendingMode(Blending::Additive);
		batcher.startBatching(renderer);
		{
			for(Particle& particle : particles.Particles)
			{
				Transform2D transformation = {particle.Position, particle.Definition->Scale[particle.Age] * particle.Size};
				batcher.DefaultVertex.Color = particle.Definition->Color[particle.Age] * particle.Color;
				batcher.addToBatch(particle.Definition->Sprite, transformation);
			}
		}
		batcher.flushBatches();
	}
};