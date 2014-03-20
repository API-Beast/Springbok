//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "../Geometry/Vec2.h"

class RenderTarget
{
public:
	virtual Vec2F size() = 0;
	virtual void  bind() = 0;
};