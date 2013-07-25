// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "TopDownShooter.h"
#include <GL/gl.h>

TopDownShooter::TopDownShooter()
{
	Surface = new GameSurface("TopDownShooter Example", GameSurface::Windowed);
	Input   = new InputMonitor(Surface);
	Clock   = new PreciseClock();
	
	EnemyHoming[0.00f].insert(0.10f);
	EnemyHoming[0.25f].insert(0.02f);
	EnemyHoming[0.50f].insert(1.00f);
	EnemyHoming[0.70f].insert(0.10f);
	EnemyHoming[0.75f].insert(0.00f);
	
	EnemyAccleration[0.00f].insert(1.00f);
	EnemyAccleration[0.15f].insert(0.25f);
	EnemyAccleration[0.30f].insert(0.00f);
	EnemyAccleration[0.50f].insert(0.00f);
	EnemyAccleration[0.75f].insert(1.00f);
	EnemyAccleration[1.00f].insert(10.00f);
	
	TestAnimation[ 0.00f].insert(Vec2I(-200, 0));
	TestAnimation[ 2.00f].insert(Vec2I( 200, 0));
	TestAnimation[ 4.00f].insert(Vec2I(   0,  200));
	TestAnimation[ 6.00f].insert(Vec2I(   0, -200));
	
	RenderContext::Setup2DEnvironment();
	r.CameraPos = -Surface->getSize()/2;
}

TopDownShooter::~TopDownShooter()
{
	delete Input;
	delete Surface;
	delete Clock;
}

int TopDownShooter::execute()
{
	Clock->start();
	double lastTime=0.0f, thisTime=0.0f;
	while(!Surface->closeRequested())
	{
		lastTime = thisTime;
		thisTime = Clock->elapsed();
		double dTime = thisTime - lastTime;
		for(const ButtonPressEvent& press : Input->poll())
		{
			if(Buttons::Escape .matches(press)) // Escape was pressed
				Surface->requestClose();
		}
		
		glClearColor(0.7f, 0.4f, 0.6f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		
		r.Offset = TestAnimation[thisTime];
		EnemySprite.draw(r);
		
		Surface->switchBuffers();
	}
	return 0;
}