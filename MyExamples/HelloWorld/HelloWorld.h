// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Platform.h>
#include <Springbok/Animation.h>
#include <Springbok/Graphics.h>

struct Enemy
{
	Vec2F Position;
	Vec2F Speed;
};

class HelloWorld 
{
public:
	HelloWorld();
	~HelloWorld();
	int execute();
	void updateViewport();
	void update(float deltaTime);
	void render();
	bool isRunning() const { return Surface->closeRequested(); }
private:
	GameSurface*  Surface;
	InputMonitor* Input;
	PreciseClock* Clock;
	
	//
	RenderContext r;
	GraphicsBatch batch = GraphicsBatch(256);
	Image TestSprite,TestSprite2,TestSprite3,TestSprite4;
};
