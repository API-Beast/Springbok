// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderContext2D.h"
#include <Springbok/Generic/PointerGuard.h>
#include "GLES2.h"
#include <Springbok/Utils/Debug.h>

#include <iostream>

RenderContext2D::RenderContext2D(RenderTarget* target)
{
	glEnable(GL_BLEND);
	setRenderTarget(target);
	setShader      (mShader);
	PrintGLError();
}

void RenderContext2D::setShader(ShaderProgram shader)
{
	mShader = shader;
	glUseProgram(mShader.Handle);
	PrintGLError();
}

void RenderContext2D::setRenderTarget(RenderTarget* target)
{
	mRenderTarget = target;
	mRenderTarget->bind();
	PrintGLError();
}

void RenderContext2D::clear(Vec3F clr)
{
	glClearColor(clr.X, clr.Y, clr.Z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	PrintGLError();
}

