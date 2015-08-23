//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <vector>

#include <cstdint>

#include <Springbok/Foundation/DataBlock.h>
#include <Springbok/Utils/Color.h>
#include "Rect.h"

struct TextureData
{
	static TextureData FromFile(const std::string& path);
	bool exportToPNG(const std::string& path);
	std::vector<Vec4I> findFrames(Vec4F borderColor = Colors::Transparent, bool findBaseline = true);
	
	DataBlock2D<unsigned int> Data;
};