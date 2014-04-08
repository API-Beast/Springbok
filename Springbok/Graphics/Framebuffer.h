//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "../Generic/ObjectPointer.h"

#include "Core/RenderTarget.h"
#include "Core/Texture.h"

class Framebuffer : public RenderTarget
{
public:
	Framebuffer(int width, int height, int precision = 8);
	~Framebuffer();
	virtual Vec2F size() const;
	virtual void bind();
public:
	ObjectPointer<Texture> ColorAttachment = nullptr;
	unsigned int Index = 0;
	bool Valid = false;
};