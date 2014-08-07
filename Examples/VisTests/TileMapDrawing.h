//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "VisTest.h"

#include <Springbok/World.hpp>
#include <Springbok/Graphics/Image.h>

#include <map>

struct TileMapDrawing : public VisTest
{
	char                 Map[16][16];
	TileMapIterator      MapIter;
	
	Image TilesetImage;
	std::map<int, Image> Tiles;
	
	int DrawnTiles = 0;
	
	virtual void initialize();
	virtual void draw(float deltaTime, SpriteRenderer& r);
	virtual std::string description();
	virtual std::string status();
};