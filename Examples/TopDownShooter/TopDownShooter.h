// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Platform.h>

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
	GameSurface* mSurface;
	InputMonitor* mInput;
	PreciseClock* mClock;
};
