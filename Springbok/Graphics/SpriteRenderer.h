//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Core/BatchRenderer.h"
#include "Framebuffer.h"
#include <Springbok/Types.hpp>

class SpriteRenderer
{
public:
	SpriteRenderer(RenderTarget* target = nullptr);
	
	void clear(Color color = Colors::White);
	void flush();
	
	void drawRenderpass(const Framebuffer& buffer);
	template<typename T>
	void draw           (const T& obj, Transform2D transformation=Transform2D(), Vec4F color=Colors::White, Blending mode = Blending::Alpha);
	template<typename T>
	void draw           (const T& obj, Vec2F position, Vec4F color=Colors::White, Blending mode = Blending::Alpha, Transform2D transformation = Transform2D());
	template<typename T>
	void drawStretched  (const T& obj, Vec2F position, Vec2F size, Vec4F color=Colors::White, Blending mode = Blending::Alpha, Transform2D transformation = Transform2D());
	template<typename T>
	void drawRepeatedInf(const T& obj, Vec2F offset, Vec2F scale=1.f, Vec2F parralaxity=1.f, Vec4F color=Colors::White, Blending mode = Blending::Alpha);
public:
	BatchRenderer2D Batcher;
	RenderContext2D Context;
	bool IsBatcherStarted = false;
};

#include "SpriteRenderer_Templates.hpp"