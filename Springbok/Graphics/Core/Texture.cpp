// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Texture.h"
#include "Springbok/Dependencies/lodepng.h"
#include "GLES2.h"
#include <vector>
#include <cassert>
#include <iostream>

#include <Springbok/Utils/Functions.h>

namespace
{
  int makePowerOfTwo(int number)
  {
    int result=1;
    while (result < number) result <<= 1;
    return result;
  };
}

Rect Texture::calcTextureCoordinates(Vec2I pos, Vec2I size)
{
	return Rect((Vec2F(pos) + 0.375f) / Vec2F(TextureSize), (Vec2F(size) - 0.375f) / Vec2F(TextureSize));
}

Texture::Texture(const std::string& filename)
 :
 Texture(TextureData::FromFile(filename))
{
}

Texture::Texture(const TextureData& tex)
{
	Index = 0xFFFE;
	glGenTextures(1, &Index);
  glBindTexture(GL_TEXTURE_2D, Index);

	if(PrintGLError() || Index == 0xFFFE)
	{
		Valid = false;
		Index = 0;
		return ;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	PrintGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	PrintGLError();

	ImageSize = Vec2I{tex.Data.Width, tex.Data.Height};
	TextureSize = ImageSize;
	//TextureSize = Vec2I{makePowerOfTwo(width), makePowerOfTwo(height)};

	// TODO: Handle non-dense texture data
	if(!(TextureSize == ImageSize))
	{
		std::vector<uint32_t> empty(TextureSize.X * TextureSize.Y, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureSize.X, TextureSize.Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, empty.data());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ImageSize.X, ImageSize.Y, GL_RGBA, GL_UNSIGNED_BYTE, tex.Data.DataPtr);
		PrintGLError();
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureSize.X, TextureSize.Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.Data.DataPtr);
		PrintGLError();
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	PrintGLError();

	TextureCoordinates = calcTextureCoordinates(0, ImageSize);
	Valid = true;
}

Texture::Texture(int width, int height, int precision)
{
	Index = 0xFFFE;
	glGenTextures(1, &Index);
  glBindTexture(GL_TEXTURE_2D, Index);
	
	if(PrintGLError() || Index == 0xFFFE)
	{
		Valid = false;
		Index = 0;
		return ;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	PrintGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	PrintGLError();
	
	GLenum format = GL_RGBA;
	if(precision == 16)
		format = GL_RGBA16F_EXT;
	if(precision == 32)
		format = GL_RGBA32F_EXT;
	ImageSize = TextureSize = Vec2I{width, height};
	glTexImage2D(GL_TEXTURE_2D, 0, format, TextureSize.X, TextureSize.Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	PrintGLError();
	
	TextureCoordinates = calcTextureCoordinates(0, ImageSize);
	Valid = true;
}

void Texture::enableFiltering()
{
	glBindTexture(GL_TEXTURE_2D, Index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::enableFilteringMipmap()
{
	glBindTexture(GL_TEXTURE_2D, Index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::disableFiltering()
{
	glBindTexture(GL_TEXTURE_2D, Index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
