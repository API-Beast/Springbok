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

#include "data.h"

int main()
{
	GameSurface surface("BouncingBall - Springbok Example", GameSurface::Windowed);
	InputMonitor       input(&surface);
	RenderContext2D renderer(&surface);
	
	ResourceManager::GetInstance()->findPrimaryResourcePath({FileInfo(__FILE__).up()+"/Assets", "./Assets"});
	
	InitData();
	
	PreciseClock timer;
	float currentTime = timer.elapsed();
	timer.start();
	
	Image ball("Ball.png");
	Image bg("BG.png");
	Image shadow("Shadow.png");
	BatchRenderer2D batcher;
	
	while(!surface.closeRequested())
	{
		surface.switchBuffers();
		renderer.clear();
		
		float deltaTime = timer.elapsed();
		timer.start();
		currentTime += deltaTime;
		
		batcher.startBatching(renderer);
		{
			batcher.addToBatch(bg);
			
			// First Shadow
			Transform2D t = Position2D(-400 + currentTime * 350, +200);
			t += Scale2D(ShadowScale[currentTime]);
			Vec4F color = {Colors::White, ShadowAlpha[currentTime]};
			batcher.addToBatch(shadow, t, color);
			
			// Second Shadow
			t = Position2D(-520 + currentTime * 350, +200);
			t += Scale2D(ShadowScale[currentTime]);
			color.W = ShadowAlpha[currentTime+0.32];
			batcher.addToBatch(shadow, t, color);
			
			
			// First Ball
			t = Position2D(-400 + currentTime * 350, +180 - BallHeight[currentTime]);
			t += Scale2D(BallScale[currentTime]);
			batcher.addToBatch(ball, t);
			
			
			// Second Ball
			t = Position2D(-520 + currentTime * 350, +180 - BallHeight[currentTime+0.32]);
			t += Scale2D(BallScale[currentTime+0.32]);
			batcher.addToBatch(ball, t);
		}
		batcher.flushBatches();
	}
};