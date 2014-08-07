//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "TileMapIterator.h"

Vec2I TileMapIterator::pos2TileIndex(Vec2F pos)
{
	switch(Mode)
	{
		case Orthogonal:           return Vec2I((pos + Origin) / TileSize);
		case IsometricAlternating: return 0;
		case IsometricDiamond:     return 0;
			return 0;
	}
}

Vec2F TileMapIterator::tileIndex2Pos(Vec2I pos)
{
	switch(Mode)
	{
		case Orthogonal:           return pos * TileSize - Origin;
		case IsometricAlternating: return 0;
		case IsometricDiamond:     return 0;
	}
}

Vec2F TileMapIterator::calcSize(Vec2I size) const
{
	switch(Mode)
	{
		case Orthogonal:           return size * TileSize;
		case IsometricAlternating: return 0;
		case IsometricDiamond:     return 0;
	}
}

void TileMapIterator::setDrawingArea(Vec2F offset, Vec2F size)
{
	auto a = pos2TileIndex(offset-size/2);
	auto b = pos2TileIndex(offset+size/2);
	StartTile = Min(a, b) - TileOverlap;
	EndTile   = Max(a, b) + TileOverlap;
	CurTile   = StartTile;
	CurPos    = tileIndex2Pos(CurTile);
}

bool TileMapIterator::next()
{
	// Right to left so it works for both isometric and orthographic projection
	if(CurTile.X > StartTile.X)
		CurTile.X--;
	else
	{
		CurTile.X = EndTile.X;
		if(CurTile.Y == EndTile.Y)
			return false;
		else
			CurTile.Y++;
	}
	CurPos = tileIndex2Pos(CurTile);
	return true;
}

bool TileMapIterator::atEnd() const
{
	return CurTile.X <= StartTile.X &&
	       CurTile.Y >= StartTile.Y;
}
