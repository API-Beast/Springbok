//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "VertexStruct.h"

template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

void BasicVertex::bindOffsets() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), &(Position[0]));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), &(TexCoords[0]));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), &(Color[0]));
}

void BasicElement::bindUniforms(const BasicElement& previous) const
{
	if(previous.Texture != Texture)
		glBindTexture(GL_TEXTURE_2D, Texture);
}

void BasicElement::bindUniforms() const
{
	glBindTexture(GL_TEXTURE_2D, Texture);
}