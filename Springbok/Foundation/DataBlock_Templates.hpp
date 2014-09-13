//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "DataBlock.h"

template<typename T>
T& DataBlock2D<T>::at(int X, int Y)
{
	const int elSize = sizeof(T) + ElementPadding;
	return *(T*)(DataPtr  +  Y*(Width+RowPadding)*elSize   +  X*elSize);
};

template<typename T>
DataBlock2D<T> DataBlock2D<T>::subDataBlock(int X, int Y, int width, int height)
{
	const int elSize = sizeof(T) + ElementPadding;
	DataBlock2D<T> result;
	result.Width      = std::min(Width  - X, width);
	result.Height     = std::min(Height - Y, height);
	result.RowPadding = RowPadding + elSize * (Width-result.Width);
	result.DataPtr    = &at(X, Y);
	result.UsedBytes  = result.ReservedBytes = result.Height*result.Width*elSize + result.Height*result.RowPadding;
	return result;
};