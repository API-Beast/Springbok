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
	setBlendingMode(Blending::Default);
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

void RenderContext2D::setBlendingMode(Blending mode)
{
	mBlendingMode = mode;
	switch(mBlendingMode)
	{
	case Blending::Default:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case Blending::Additive:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case Blending::Multiplicative:
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		break;
	}
	PrintGLError();
};

void RenderContext2D::clear(Color clr)
{
	glClearColor(clr.X, clr.Y, clr.Z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	PrintGLError();
}
