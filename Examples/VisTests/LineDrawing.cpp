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
	if(Mode != Linear) r.draw(Line, 0, RGB(1.0f, 1.0f, 1.0f, 0.05f));
	r.draw(LineSubdivided, 0, Colors::White);
	
	if(LastClickTimer > 0)
		LastClickTimer -= deltaTime;
}

void LineDrawing::onClick(Vec2F pos)
{
	if(LastClickTimer <= 0)
	{
		Line.insert(pos, 5);
		Line.applyTexture(Image("Line.png"));
		LastClickTimer += 0.2f;
		subdivide();
	}
}

void LineDrawing::subdivide()
{
	LineSubdivided = Line;
	LineSubdivided.Points.front().Width = 0.0;
	LineSubdivided.Points.front().Color = Colors::Green;
	LineSubdivided.Points.back().Width = 0.0;
	LineSubdivided.Points.back().Color = Colors::Blue;
	
	if(Mode == CubicBezier)
		LineSubdivided.divideCubicBezier(5);
	else if(Mode == Smooth)
		LineSubdivided.divideSmooth(5);
	
	LineSubdivided.applyTexture(Image("LineDotted.png"), LineSubdivided.calcLength()/50);
}

void LineDrawing::onDecrement()
{
	     if(Mode == Linear)      Mode = CubicBezier;
	else if(Mode == CubicBezier) Mode = Smooth;
	else if(Mode == Smooth)      Mode = Linear;
	subdivide();
}

void LineDrawing::onIncrement()
{
	     if(Mode == Linear)      Mode = Smooth;
	else if(Mode == CubicBezier) Mode = Linear;
	else if(Mode == Smooth)      Mode = CubicBezier;
	subdivide();
}

std::string LineDrawing::description()
{
	return "Change interpolation method with Keypad +/-";
}

std::string LineDrawing::status()
{
	     if(Mode == Linear)      return "Linear";
	else if(Mode == CubicBezier) return "Cubic Bezier";
	else return "Smooth";
}


