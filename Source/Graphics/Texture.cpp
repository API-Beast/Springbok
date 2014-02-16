// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Texture.h"
#include "../Dependencies/lodepng.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>
#include <cassert>
#include <iostream>

namespace
{
  int makePowerOfTwo(int number)
  {
    int result=1;
    while (result < number) result <<= 1;
    return result;
  };
}

RectF Texture::calcTextureCoordinates(Vec2I pos, Vec2I size)
{
	return RectF(pos / Vec2F(TextureSize), (size) / Vec2F(TextureSize));
}

Texture::Texture(const std::string& filename)
{
	std::vector<unsigned char> bitmap;
	unsigned int width;
	unsigned int height;
	
	Index = 0xFFFE;
	glGenTextures(1, &Index);
  glBindTexture(GL_TEXTURE_2D, Index);
	
	if(glGetError() || Index == 0xFFFE)
	{
		Valid = false;
		Index = 0;
		return ;
	}
	
	lodepng::decode(bitmap, width, height, filename);
  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	
	ImageSize = Vec2I{width, height};
	TextureSize = Vec2I{makePowerOfTwo(width), makePowerOfTwo(height)};
	
	if(!(TextureSize == ImageSize))
	{
		std::vector<uint32_t> empty(TextureSize.X * TextureSize.Y, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TextureSize.X, TextureSize.Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, empty.data());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ImageSize.X, ImageSize.Y, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.data());
	}
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TextureSize.X, TextureSize.Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.data());
	
	TextureCoordinates = calcTextureCoordinates(0, ImageSize);
	
	assert(!glGetError());
	
	Valid = true;
	
	return;
}

Texture::Texture(Texture&& other)
{
	this->Valid  = other.Valid;
	this->ImageSize = other.ImageSize;
	this->Index  = other.Index;
	this->TextureCoordinates = other.TextureCoordinates;
	this->TextureSize = other.TextureSize;
	
	other.Valid  = false;
}

Texture::~Texture()
{
	if(Valid)
		glDeleteTextures(1, &Index);
}
