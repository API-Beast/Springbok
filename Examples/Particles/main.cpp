//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Platform/InputMonitor.h>
#include <Springbok/Platform/GameSurface.h>
#include <Springbok/Platform/PreciseClock.h>
#include <Springbok/Platform/FileInfo.h>
#include <Springbok/Platform/InputDevice.h>

#include <Springbok/Graphics/Core/RenderContext2D.h>
#include <Springbok/Graphics/Core/BatchRenderer.h>
#include <Springbok/Graphics/Image.h>

#include <Springbok/Resources/ResourceManager.h>
#include <Springbok/Procedural/RandomNumberGenerator.h>
#include "AssetDefinition.h"

int main()
{
	// Initialization
	GameSurface surface("Particles - Springbok Example", GameSurface::Windowed | GameSurface::NoVSync);
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
	
	int maxParticles = 500000;
	int kParticles = 5;
	ParticleSystem particles(maxParticles);
	BatchRenderer2D batcher(maxParticles * 4 * sizeof(BasicVertex));
	
	while(!surface.closeRequested())
	{
		surface.switchBuffers();
		renderer.clear(Palette::Orange / 2);
		
		for(ButtonPressEvent press : input.poll())
		{
			if(press.From->getButtonName(press.Button) == "F1")
				kParticles = BoundBy(1, kParticles-5, 500);
			if(press.From->getButtonName(press.Button) == "F2")
				kParticles = BoundBy(1, kParticles+5, 500);
			if(press.From->getButtonName(press.Button) == "Esc")
				surface.requestClose();
		}
		
		float dt = timer.elapsed() - gameTime;
		gameTime = timer.elapsed();
		
		// Add new particles on the left side
		
		particles.cleanUp();
		particleEmitAccum+=dt;
		while(particleEmitAccum > 0.002f)
		{
			for(int i = 0; i < kParticles; ++i)
			{
				Particle party;
				party.Definition = &gAssets.Spark;
				party.Position   = Vec2F(gRNG.getNumber(-surface.size().X/2, +surface.size().X/2), surface.size().Y/2 + 100);
				party.Velocity   = Vec2F(0.f, -surface.size().Y/2) + gRNG.getVec2(Vec2F(-400), Vec2F(400));
				party.Position  -= party.Velocity*particleEmitAccum;
				party.Age -= particleEmitAccum;
				party.Size = gRNG.getNumber(0.01f, 10.0f);
				party.Size.Y *= gRNG.getNumber(1.f, 3.0f);
				party.Color.X = 0.75f + gRNG.getFloat()/4;
				party.Color.Z = 0.75f + gRNG.getFloat()/4;
				party.Color.W = (10.f - party.Size.X) / 10;
				party.Rotation = Angle::FromTurn(gRNG.getFloat());
				if(gRNG.getFloat() < (0.20/kParticles))
					party.Color.W *= (kParticles/5);
				particles.addParticle(party);
			}
			particleEmitAccum -= 0.002f;
		}
		
		for(Particle& particle : particles.Particles)
		{
			particle.Age += dt;
			particle.Velocity += particle.Accleration*dt;
			particle.Position += particle.Velocity*dt;
			particle.Rotation += dt * 2.0_turn;
		}
		
		batcher.startBatching(renderer);
		{
			// TODO: Align seems not to work correctly, thus the Position2D(8, 8)
			Transform2D gui = PositionGUI(surface.topLeft()) + Position2D(8, 8) + Align2D(0.f, 0.f);
			auto drawText = [&](int row, const std::string& text)
			{
				batcher.draw(gAssets.SmallFont.text(text), gui+Position2D(0, 16*row));
			};
			
			drawText(0, std::to_string(int(dt*1000))+"ms = "+std::to_string(int(1.f/dt))+" FPS");
			drawText(1, "Particles: "+std::to_string(particles.Particles.UsedLength));
			drawText(2, "Target count: "+std::to_string(kParticles)+"000 (Change with F1 and F2 Keys.)");
			
			for(Particle& particle : particles.Particles)
			{
				Transform2D transformation =   Position2D(particle.Position)
				                             + Scale2D   (particle.Definition->Scale[particle.Age] * particle.Size)
																		 + Rotate2D  (particle.Rotation);
				Vec4F col = particle.Definition->Color[particle.Age] * particle.Color * Vec4F(1, 1, 1, 0.05f + 1.f / (kParticles / 5));
				batcher.draw(particle.Definition->Sprite, transformation, col, Blending::Additive);
			}
		}
		batcher.flushBatches();
	}
	return 0;
};