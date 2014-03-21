//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "data.h"

KeyframeList<float> BallHeight;
KeyframeList<Vec2F> BallScale;

void InitData()
{
	BallHeight.insert(0.0f, 0.f);
	BallHeight.insert(0.5f, 150.f);
	BallHeight.insert(1.0f, 0.f);
	
	BallScale.insert(0.0f, Vec2F(1.f, 0.5f));
	BallScale.insert(0.3f, Vec2F(1.f, 1.5f));
	BallScale.insert(0.5f, Vec2F(1.f, 1.0f));
	BallScale.insert(0.9f, Vec2F(1.f, 1.5f));
	BallScale.insert(1.0f, Vec2F(1.f, 0.5f));
}