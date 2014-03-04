// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <Springbok/Geometry/Rect.h>

//! @addtogroup Graphics
//! @{

struct Texture
{
	Texture() = delete;
	Texture(const std::string& filename);
	Texture(Texture&& other);
	Texture(const Texture&) = delete;
	virtual ~Texture();
	
	RectF calcTextureCoordinates(Vec2I pos, Vec2I size);
	
	bool Valid = false;
	unsigned int Index = 0;
	Vec2I ImageSize;
	Vec2I TextureSize;
 	RectF TextureCoordinates;
};

//! @}
