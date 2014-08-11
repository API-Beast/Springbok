// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <Springbok/Types/Rect.h>
#include "TextureData.h"

struct Texture
{
	Texture() = default;
	Texture(const std::string& filename);
	Texture(const TextureData& tex);
	Texture(int width, int height, int precision);
	Texture(Texture&& other);
	Texture(const Texture&) = delete;
	virtual ~Texture();
	
	Rect calcTextureCoordinates(Vec2I pos, Vec2I size);
	void enableFiltering();
	void enableFilteringMipmap();
	void disableFiltering();
	
	bool Valid = false;
	unsigned int Index = 0;
	Vec2I ImageSize;
	Vec2I TextureSize;
  Rect TextureCoordinates;
};