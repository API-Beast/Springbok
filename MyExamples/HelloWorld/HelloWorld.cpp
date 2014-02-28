// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "HelloWorld.h"
#include <GL/gl.h>
#include "Springbok/Graphics/Camera.h"

HelloWorld::HelloWorld()
{
	Surface = new GameSurface("Hello Springbok Example", GameSurface::Windowed);
	Input   = new InputMonitor(Surface);
	Clock   = new PreciseClock();

	
	RenderContext::Setup2DEnvironment();
	r.initShader();
	r.CameraPos = -Surface->getSize()/2;
}

HelloWorld::~HelloWorld()
{
	delete Input;
	delete Surface;
	delete Clock;
}

int HelloWorld::execute()
{
	Image TestSprite = Image("Enemy.png");
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
		glClear(GL_COLOR_BUFFER_BIT);
	
		batch.Start();

		batch.Draw(r.getDefaultCamera()->transformRect(TestSprite.getVertices()));
		batch.Draw(r.getDefaultCamera()->transformRect(TestSprite.getVertices()));
		batch.Draw(r.getDefaultCamera()->transformRect(TestSprite.getVertices()));

		batch.End();

		Surface->switchBuffers();
	}
	return 0;
}
