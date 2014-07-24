//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ColorGen.h"
#include <Springbok/Graphics/SpriteRenderer.h>


void ColorGen::draw(float deltaTime, SpriteRenderer& r)
{
	for(int i = 0; i < 10; ++i)
	{
		r.draw(Blob, (i-5) * Vec2F(70, 0), HCL(0.0_turn+0.05_turn*i+0.1_turn*x, 0.5+y/10.f, 0.1+i/11.f));
	}
}

void ColorGen::initialize()
{
	Blob = Image("RoundedBlock.png");
}

void ColorGen::onClick(Vec2F pos)
{
	x=pos.X/100.f;
	y=pos.Y/100.f;
}

void ColorGen::onDecrement()
{
	x--;
}

void ColorGen::onIncrement()
{
	x++;
}
