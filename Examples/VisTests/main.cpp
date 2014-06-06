//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Platform/InputMonitor.h>
#include <Springbok/Platform/GameSurface.h>
#include <Springbok/Platform/PreciseClock.h>
#include <Springbok/Platform/FileSystem.h>
#include <Springbok/Platform/InputDevice.h>

#include <Springbok/Graphics/Core/RenderContext2D.h>
#include <Springbok/Graphics/Core/BatchRenderer.h>
#include <Springbok/Graphics/Image.h>

#include <Springbok/Resources/ResourceManager.h>
#include <Springbok/Procedural/RandomNumberGenerator.h>
#include <Springbok/Graphics/BitmapFont.h>

#include "VisTest.h"
#include "LineDrawing.h"

int main()
{
	// Initialization
	GameSurface  surface("VisTests - Springbok Example", GameSurface::Windowed, {800, 600}, 16);
	InputMonitor input(&surface);
	ResourceManager::GetInstance()->findPrimaryResourcePath({FileSystem::ParentPath(__FILE__)+"/Assets", "./Assets"});
	
	List<VisTest*> tests;
	tests.pushBack(new LineDrawing);
	
	BitmapFont font;
	font.loadGrid(Image("SmallFont.png"), 0, 16);	
	
	VisTest* curTest = tests[0];

	curTest->initialize();
	
	// Start the timer
	PreciseClock timer;
	timer.start();
	float gameTime = 0.f;
	
	SpriteRenderer renderer(&surface);
	while(!surface.closeRequested())
	{
		surface.switchBuffers();
		
		for(ButtonPressEvent press : input.poll())
		{
			if(press.From->buttonName(press.Button) == "Esc")
				surface.requestClose();
			if(press.From->numberOfCursors())
				curTest->onClick(press.From->cursorPosition(0));
		}
		
		float dt = timer.elapsed() - gameTime;
		gameTime = timer.elapsed();
		
		curTest->draw(dt, renderer);
		
		// TODO: Align seems not to work correctly, thus the Position2D(8, 8)
		Transform2D gui = PositionGUI(surface.topLeft()) + Position2D(8, 8) + Align2D(0.f, 0.f);
		renderer.draw(font.text(std::to_string(int(dt*1000))+"ms = "+std::to_string(int(1.f/dt))+" FPS"), gui);
		renderer.flush();
	}
	return 0;
};