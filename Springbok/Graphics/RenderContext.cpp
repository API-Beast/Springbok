// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderContext.h"
#include <Springbok/Generic/PointerGuard.h>
#include "GLES2.h"

void RenderContext::setBlendingMode(RenderContext::BlendingMode mode)
{
	mSetBlendingMode = mode;
	if(mode == Default)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	else if(mode == Additive)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	else if(mode == Multiplicative)
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
}