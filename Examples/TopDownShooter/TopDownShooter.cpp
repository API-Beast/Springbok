// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "TopDownShooter.h"

TopDownShooter::TopDownShooter()
{
	mSurface = new GameSurface("TopDownShooter Example", GameSurface::Windowed);
	mInput = new InputMonitor(mSurface);
	mClock = new PreciseClock();
}

TopDownShooter::~TopDownShooter()
{
	delete mInput;
	delete mSurface;
	delete mClock;
}

int TopDownShooter::execute()
{
	mClock->start();
	double lastTime=0.0f, thisTime=0.0f;
	while(!mSurface->closeRequested())
	{
		double thisTime = mClock->elapsed();
		double dTime = lastTime - thisTime;
		for(const ButtonPressEvent& press : mInput->poll())
		{
			if(Buttons::Escape .matches(press)) // Escape was pressed
				mSurface->requestClose();
		}
	}
	return 0;
}