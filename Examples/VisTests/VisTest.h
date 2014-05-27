//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Types/Vec2.h>

class SpriteRenderer;
class GameSurface;

class VisTest
{
public:
	virtual ~VisTest(){};
	virtual void initialize(){};
	virtual void draw(float deltaTime, SpriteRenderer& r){};
	virtual void onClick(Vec2F pos){};
	virtual void onIncrement(){};
	virtual void onDecrement(){};
};