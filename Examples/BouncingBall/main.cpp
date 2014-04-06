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

#include <Springbok/Graphics/Image.h>
#include <Springbok/Graphics/SpriteRenderer.h>

#include <Springbok/Resources/ResourceManager.h>

#include "data.h"

int main()
{
	GameSurface surface("BouncingBall - Springbok Example", GameSurface::Windowed);
	InputMonitor       input(&surface);
	SpriteRenderer  renderer(&surface);
	
	ResourceManager::GetInstance()->findPrimaryResourcePath({FileInfo(__FILE__).up()+"/Assets", "./Assets"});
	
	InitData();
	
	PreciseClock timer;
	float currentTime = timer.elapsed();
	timer.start();
	
	Image ball("Ball.png");
	Image bg("BG.png");
	Image shadow("Shadow.png");
	
	while(!surface.closeRequested())
	{
		surface.switchBuffers();
		renderer.clear();
		
		float deltaTime = timer.elapsed();
		timer.start();
		currentTime += deltaTime;
		
		Vec2F cursor = input.getPrimaryPointerDevice()->getCursorPosition(0);
		renderer.Context.Camera.Position.X += deltaTime * 300 * cursor.X / 100;
		
		{
			renderer.drawRepeatedInf(bg, 0.0f);
			
			Vec2F pos[3];
			Vec2F scale[3];
			Vec2F shadowPos[3];
			Vec2F shadowScale[3];
			Vec4F shadowColor[3];
			for(int i = 0; i < 3; ++i)
			{
				pos[i] = {-400 - i*220 + currentTime * 350, +180 - BallHeight[currentTime + 0.32f*i] + i*20};
				scale[i] = BallScale[currentTime + 0.32f*i];
				shadowPos[i] = pos[i];
				shadowPos[i].Y = 200 + i*20;
				shadowColor[i] = {Colors::White, ShadowAlpha[currentTime+0.32f * i]};
				shadowScale[i] = ShadowScale[currentTime + 0.32f*i];
			}
			
			renderer.draw(shadow, shadowPos[0], shadowColor[0], Blending::Alpha, Scale2D(shadowScale[0]));
			renderer.draw(shadow, shadowPos[1], shadowColor[1], Blending::Alpha, Scale2D(shadowScale[1]));
			renderer.draw(shadow, shadowPos[2], shadowColor[2], Blending::Alpha, Scale2D(shadowScale[2]));
			renderer.draw(ball, pos[0], Colors::White, Blending::Alpha, Scale2D(scale[0]));
			renderer.draw(ball, pos[1], Colors::White, Blending::Alpha, Scale2D(scale[1]));
			renderer.draw(ball, pos[2], Colors::White, Blending::Alpha, Scale2D(scale[2]));
		}
		renderer.flush();
	}
};