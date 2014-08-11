//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "MemoryBlock.h"

template<typename T>
struct DataBlock2D : public MemoryBlock
{
	DataBlock2D(){};
	virtual ~DataBlock2D(){};
	
	int Width  = 0;
	int Height = 0;
	
	int ElementPadding = 0;
	int RowPadding     = 0;
	
	// A dense DataBlock is a DataBlock without padding
	bool isDense() const{ return !(ElementPadding || RowPadding); };
	void makeDenseCopy(DataBlock2D<T>& other);
	
	T& at(int X, int Y);
	DataBlock2D<T> subDataBlock(int X, int Y, int width, int height);
	
	T& at(Vec2I i){ return at(i.X, i.Y); };
	DataBlock2D<T> subDataBlock(Vec2I i, Vec2I size){ return subDataBlock(i.X, i.Y, size.X, size.Y); };
};