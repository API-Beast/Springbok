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
	
	RenderManager::Setup2DEnvironment();
	RenderManager::GetInstance()->CameraPos = -Surface->getSize()/2;
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
		double thisTime = Clock->elapsed();
		double dTime = lastTime - thisTime;
		for(const ButtonPressEvent& press : Input->poll())
		{
			if(Buttons::Escape .matches(press)) // Escape was pressed
				Surface->requestClose();
		}
		
		glClearColor(0.7f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		EnemySprite.draw();
		
		Surface->switchBuffers();
	}
	return 0;
}