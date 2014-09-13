//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "data.h"

KeyframeList<float> BallHeight;
KeyframeList<Vec2F> BallScale;
KeyframeList<float> ShadowAlpha;
KeyframeList<Vec2F> ShadowScale;

void InitData()
{
	BallHeight.insert(0.0f, 0.f);
	BallHeight.insert(0.2f, 50.f);
	BallHeight.insert(0.5f, 350.f);
	BallHeight.insert(0.8f, 50.f);
	BallHeight.insert(1.0f, 0.f);
	BallHeight.Repeat = true;
	
	BallScale.insert(0.0f, Vec2F(1.0f, 0.9f));
	BallScale.insert(0.1f, Vec2F(0.9f, 1.1f));
	BallScale.insert(0.5f, Vec2F(1.0f, 1.0f));
	BallScale.insert(0.9f, Vec2F(0.9f, 1.1f));
	BallScale.insert(1.0f, Vec2F(1.0f, 0.9f));
	BallScale.Repeat = true;
	
	ShadowAlpha.insert(0.0f, 1.00f);
	ShadowAlpha.insert(0.1f, 0.75f);
	ShadowAlpha.insert(0.5f, 0.30f);
	ShadowAlpha.insert(0.9f, 0.75f);
	ShadowAlpha.insert(1.0f, 1.00f);
	ShadowAlpha.Repeat = true;
	
	ShadowScale.insert(0.0f, 0.7f);
	ShadowScale.insert(0.5f, 1.3f);
	ShadowScale.insert(1.0f, 0.7f);
	ShadowScale.Repeat = true;
}