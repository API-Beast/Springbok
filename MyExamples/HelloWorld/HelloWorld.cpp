// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "HelloWorld.h"
#include <GL/gl.h>
#include "Springbok/Graphics/Camera.h"
#include <Source/Utils/Debug.h>

HelloWorld::HelloWorld()
{
	Surface = new GameSurface("Hello Springbok Example", GameSurface::Windowed);
	Input   = new InputMonitor(Surface);
	Clock   = new PreciseClock();

	
	RenderContext::Setup2DEnvironment();
	r.initShader();
	//r.CameraPos = Surface->getSize()/2;
	//r.CameraPos.X = Surface->getSize().X;
}

HelloWorld::~HelloWorld()
{
	delete Input;
	delete Surface;
	delete Clock;
}

bool imgSwitch = false;
double lastTime=0.0f, thisTime=0.0f;
int globalPos = 0;

void HelloWorld::render()
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
	
		batch.start();

		for(int i = 0; i < 4; i++)
		{
			if(!imgSwitch) {
				batch.draw(TestSprite.getTexture(), r.transformRect(TestSprite.getVertices(),{i * 100 + globalPos,0}));
			}
			else
			{
				batch.draw(TestSprite2.getTexture(), r.transformRect(TestSprite2.getVertices(),{i * 100 + globalPos,0}));
			}
			batch.draw(TestSprite3.getTexture(), r.transformRect(TestSprite3.getVertices(), {0,500})); 
			batch.draw(TestSprite4.getTexture(), r.transformRect(TestSprite4.getVertices(), {300,300})); 
			imgSwitch = !imgSwitch;
		}
		
		globalPos+= 1;
		
		batch.end();

		Surface->switchBuffers();

}

int HelloWorld::execute()
{
	TestSprite = Image("Enemy.png");
	TestSprite2 = Image("Enemy2.png");
	TestSprite3 = Image("Test.png");
	TestSprite4 = Image("Test2.png");

	Clock->start();
	return 0;
}
