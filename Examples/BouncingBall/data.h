//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Animation/KeyframeList.h>
#include <Springbok/Types/Vec2.h>

extern KeyframeList<float> BallHeight;
extern KeyframeList<Vec2F> BallScale;
extern KeyframeList<float> ShadowAlpha;
extern KeyframeList<Vec2F> ShadowScale;

extern void InitData();