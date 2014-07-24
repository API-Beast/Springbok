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
#include "ColorGen.h"

// Warning, quick and ugly code to test features.

int main()
{
	// Initialization
	GameSurface  surface("VisTests - Springbok Example", GameSurface::Windowed, {800, 600}, 8);
	InputMonitor input(&surface);
	ResourceManager::GetInstance()->findPrimaryResourcePath({FileSystem::ParentPath(__FILE__)+"/Assets", "./Assets"});
	
	std::vector<VisTest*> tests;
	tests.push_back(new LineDrawing);
	tests.push_back(new ColorGen);
	
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
			if(press.From->buttonName(press.Button) == "Keypad +")
				curTest->onIncrement();
			if(press.From->buttonName(press.Button) == "Keypad -")
				curTest->onDecrement();
			auto activateTest = [&](const std::string& key, int i)
			{ if(press.From->buttonName(press.Button) == key && tests.size() >= i)
				{
					curTest = tests[i];
					curTest->initialize();
				}
				};
			activateTest("F1" , 0); activateTest("F2" ,  1); activateTest("F3" ,  2);
			activateTest("F4" , 3); activateTest("F5" ,  4); activateTest("F6" ,  5);
			activateTest("F7" , 6); activateTest("F8" ,  7); activateTest("F9" ,  8);
			activateTest("F10", 9); activateTest("F11", 10); activateTest("F12", 11);
			if(press.From->numberOfCursors())
				curTest->onClick(press.From->cursorPosition(0));
		}
		
		float dt = timer.elapsed() - gameTime;
		gameTime = timer.elapsed();
		
		renderer.clear(Colors::Black);
		curTest->draw(dt, renderer);
		
		renderer.draw(font.text(std::to_string(int(dt*1000))+"ms = "+std::to_string(int(1.f/dt))+" FPS"), surface.topLeft());
		renderer.draw(font.text(curTest->description()), surface.topLeft() + Vec2F(0, 16));
		renderer.draw(font.text(curTest->status()),      surface.topLeft() + Vec2F(0, 32));
		renderer.flush();
	}
	return 0;
};