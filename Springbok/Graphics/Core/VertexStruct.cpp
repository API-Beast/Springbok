//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "VertexStruct.h"
#include "ShaderProgram.h"
#include "RenderContext2D.h"

template<typename T, typename U> constexpr const void* offsetOf(U T::*member)
{
    return (const void*)((char*)&((T*)nullptr->*member) - (char*)nullptr);
}

void BasicVertex::SetupOffsets()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, offsetOf(&BasicVertex::Position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, offsetOf(&BasicVertex::TexCoords));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, offsetOf(&BasicVertex::Color));
}

void BasicElement::SetupUniforms(const RenderContext2D* context)
{
	context->shader().setUniform("TextureSampler", 0);
	context->shader().setUniform("CoordMult", Vec2F(1) / (context->renderTarget()->size()/2) * context->Camera.Zoom);
}

void BasicElement::bindUniforms() const
{
	glBindTexture(GL_TEXTURE_2D, Texture);
	switch(BlendMode)
	{
	case Blending::Alpha:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case Blending::Additive:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case Blending::Multiplicative:
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		break;
	}
}