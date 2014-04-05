// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Angle.h>
#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Rect.h>

#include "Color.h"
#include "ShaderProgram.h"
#include "RenderTarget.h"
#include "Transform2D.h"

class RenderContext2D
{
public:
	RenderContext2D(RenderTarget* target);
	
	void setShader      (ShaderProgram shader);
	void setRenderTarget(RenderTarget* target);
	
	const ShaderProgram& shader()       const { return mShader;       };
	      RenderTarget*  renderTarget() const { return mRenderTarget; };
				
	void clear(Color clr = Colors::Black);
public:
	Vec2F CameraPos       = 0.0f;
	Vec2F CamaraZoom      = 1.0f;
	Vec2F CameraAlignment = 0.5f;
private:
	ShaderProgram  mShader       = ShaderProgram::GetDefaultShader();
	RenderTarget*  mRenderTarget = nullptr;
};
