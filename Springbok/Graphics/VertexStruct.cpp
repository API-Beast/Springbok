//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "VertexStruct.h"
#include "ShaderProgram.h"

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

void BasicElement::SetupUniforms(const ShaderProgram* shader)
{
	shader->setUniform("TextureSampler", 0);
}

void BasicElement::bindUniforms() const
{
	glBindTexture(GL_TEXTURE_2D, Texture);
}