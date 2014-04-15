//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "LineDrawing.h"
#include <Springbok/Platform/GameSurface.h>
#include <Springbok/Procedural/RandomNumberGenerator.h>

void LineDrawing::initialize()
{
}

void LineDrawing::draw(float deltaTime, SpriteRenderer& r)
{
	r.clear(Colors::Dawnbringer::Shadow[0]);
	r.draw(LineSubdivided, Align2D(0, 0), Colors::White);
	
	if(LastClickTimer > 0)
		LastClickTimer -= deltaTime;
}

void LineDrawing::onClick(Vec2F pos)
{
	if(LastClickTimer <= 0)
	{
		Line.insert(pos, 3 + gRNG.getNumber(2));
		LineSubdivided = Line;
		LineSubdivided.Points.front().Width = 0.0;
		LineSubdivided.Points.front().Color = Colors::Dawnbringer::Green[1];
		LineSubdivided.Points.back().Width = 0.0;
		LineSubdivided.Points.back().Color = Colors::Dawnbringer::Blue[2];
		LineSubdivided.divideEquidistant(5);
		LineSubdivided.applyTexture(Image("Line.png"), LineSubdivided.calcLength()/50);
		LastClickTimer += 0.2f;
	}
}
