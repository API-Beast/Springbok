//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "TileMapDrawing.h"
#include <Springbok/Graphics/SpriteRenderer.h>
#include <Springbok/Serialization/ToString.h>

void TileMapDrawing::draw(float deltaTime, SpriteRenderer& r)
{
	DrawnTiles = 0;
	MapIter.setDrawingArea(r.Context.Camera.Position, r.Context.renderTarget()->size());
	while(MapIter.next())
	{
		if(MapIter.CurTile.isInBounds({0, 0}, {15, 15}))
		{
			DrawnTiles++;
			r.draw(Tiles[Map[MapIter.CurTile.X][MapIter.CurTile.Y]], MapIter.CurPos);
		}
	}
}

void TileMapDrawing::initialize()
{ 
	for(int x = 0; x < 16; ++x)
		for(int y = 0; y < 16; ++y)
			Map[x][y] = x % 2 ^ y % 2;
	
	MapIter.TileSize = 32;
	MapIter.Mode     = Orthogonal;
	MapIter.Origin   = MapIter.calcSize({16, 16}) / 2;
	MapIter.TileOverlap = 1;
	
	TilesetImage = Image("tilesetHouse.png");
	Tiles[0] = TilesetImage.cut({0, 160}, 32);
	Tiles[1] = TilesetImage.cut({160, 0}, 32); // The coordinates are purely coincidal
}

std::string TileMapDrawing::status()
{
	return ToString(DrawnTiles) + " Tiles rendered";
}

std::string TileMapDrawing::description()
{
	return "Tile map drawing";
}

