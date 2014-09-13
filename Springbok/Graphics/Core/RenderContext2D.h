// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Foundation/Angle.h>
#include <Springbok/Foundation/Vec3.h>

#include "ShaderProgram.h"
#include "RenderTarget.h"
#include "Transform2D.h"

struct CameraData
{
	Vec2F Position  = 0.0f;
	Vec2F Zoom      = 1.0f;
};

class RenderContext2D
{
public:
	RenderContext2D(RenderTarget* target);
	
	void setShader      (ShaderProgram shader);
	void setRenderTarget(RenderTarget* target);
	
	const ShaderProgram& shader()       const { return mShader;       };
	      RenderTarget*  renderTarget() const { return mRenderTarget; };
				
	void clear(Vec3F clr);
	
	Vec2F cameraCenter() const { return Camera.Position; };
public:
	CameraData Camera;
private:
	ShaderProgram  mShader       = ShaderProgram::GetDefaultShader();
	RenderTarget*  mRenderTarget = nullptr;
};
