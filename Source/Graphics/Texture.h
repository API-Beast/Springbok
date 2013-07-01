// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <Geometry/Rect.h>

//! @addtogroup Graphics
//! @{

struct Texture
{
	Texture(const std::string& filename);
	~Texture();
	
	unsigned int Index;
	int Width, Height;
	int TextureWidth, TextureHeight;
  RectF TextureCoordinates;
};

//! @}