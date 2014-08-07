//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Types/Vec2.h>

enum MapMode
{
	Orthogonal,
	IsometricAlternating,
	IsometricDiamond
};

struct TileMapIterator
{
	Vec2I StartTile = 0;
	Vec2I EndTile   = 0;
	
	Vec2I CurTile   = 0;
	Vec2F CurPos    = 0;
	
	Vec2F Origin    = 0;
	
	Vec2F TileSize    = 32;
	Vec2I TileOverlap = 1;
	
	MapMode Mode = Orthogonal;
	
	void  setDrawingArea(Vec2F offset, Vec2F size);
	
	Vec2I pos2TileIndex(Vec2F pos);
	Vec2F tileIndex2Pos(Vec2I pos);
	
	Vec2F calcSize(Vec2I size) const;
	
	bool  atEnd() const;
	bool  next();
};