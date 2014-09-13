//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Foundation/Vec2.h>

class RenderTarget
{
public:
	virtual Vec2F size() const = 0;
	virtual void  bind() = 0;
	Vec2F   left() const { return size() * Vec2F(-0.5f, 0);};
	Vec2F  right() const { return size() * Vec2F(+0.5f, 0);};
	Vec2F    top() const { return size() * Vec2F(0, -0.5f);};
	Vec2F bottom() const { return size() * Vec2F(0, +0.5f);};
	Vec2F center() const { return 0; };
	
	Vec2F      topLeft() const { return size() * Vec2F(-0.5f, -0.5f);};
	Vec2F   bottomLeft() const { return size() * Vec2F(-0.5f, +0.5f);};
	Vec2F     topRight() const { return size() * Vec2F(+0.5f, -0.5f);};
	Vec2F  bottomRight() const { return size() * Vec2F(+0.5f, +0.5f);};
};