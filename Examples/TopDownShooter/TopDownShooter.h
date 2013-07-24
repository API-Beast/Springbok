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

class TopDownShooter
{
public:
	TopDownShooter();
	~TopDownShooter();
	int execute();
	void updateViewport();
	void update(float deltaTime);
	void render();
private:
	GameSurface*  Surface;
	InputMonitor* Input;
	PreciseClock* Clock;
	
	//
	KeyframeList<float> EnemyHoming;
	KeyframeList<float> EnemyAccleration;
	Image EnemySprite = Image("Enemy.png");
};
