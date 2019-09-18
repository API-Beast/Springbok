//  Copyright (C) 2015 Manuel Riecke <api.beast@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"

//~ ### Range2D
//~ *Dependencies: springUtils/Vec2.h*
//~
//~ A iterator to be used in conjunction with the 'for range' feature from C++11 that can iterate over the coordinates of a rectangle.

template<typename T>
struct Vec2Iterator
{
	Vec2<T> BaseValue;
	Vec2<T> Step;
	int    Width = 1;
	int Position = 0;
	
	Vec2Iterator<T>& operator++(   ){ Position++; return *this; };
	Vec2Iterator<T>  operator++(int){ Vec2Iterator<T> it(*this); Position++; return it; };
	Vec2Iterator<T>& operator--(   ){ Position--; return *this; };
	Vec2Iterator<T>  operator--(int){ Vec2Iterator<T> it(*this); Position--; return it; };
	
	Vec2<T> value() const{ return BaseValue + Vec2<T>((Position % Width) * Step.X, (Position / Width) * Step.Y); };
	
	// Okay, this is ugly, soooorry! You can't actually check if they are the same.
	// This is basically a operator <, but due to the way for-range-based loop works it has to be called operator==
	bool operator==(const Vec2Iterator<T>& other) const
	{
		return !this->operator!=(other);
	};
	bool operator!=(const Vec2Iterator<T>& other) const
	{
		auto sign  = [](T x){ return (x < 0) ? -1 : 1; };
		auto signV = [&sign](Vec2<T> val){ return Vec2<T>(sign(val.X), sign(val.Y));};
		auto sdiff = signV(this->value() - other.value());
		auto sstep = signV(Step);
		return sdiff.X != sstep.X && sdiff.Y != sstep.Y;
	};
	
	Vec2<T> operator* () const{ return value(); };
	Vec2<T> operator->() const{ return value(); };
};

template<typename T>
struct Vec2IteratorRange
{
	Vec2Iterator<T> Start;
	Vec2Iterator<T> End;
	
	Vec2Iterator<T> begin() const{ return Start; };
	Vec2Iterator<T> end()   const{ return End;   };
};

inline Vec2IteratorRange<int> Range2D(Vec2I start, Vec2I end, Vec2I step = Vec2I(1, 1), int width = -1)
{
	if(width == -1)
		width = (((end - start)/step).X);
	
	Vec2IteratorRange<int> retVal;
	retVal.Start.BaseValue = start;
	retVal.Start.Step      = step;
	retVal.Start.Width     = width;
	
	retVal.End           = retVal.Start;
	retVal.End.BaseValue = end;
	return retVal;
};

inline Vec2IteratorRange<int> Range2DIncl(Vec2I start, Vec2I end, Vec2I step = Vec2I(1, 1), int width = -1)
{
	if(width == -1)
		width = (((end - start)/step).X + 1);
	else
		width = width + 1;
	
	Vec2IteratorRange<int> retVal;
	retVal.Start.BaseValue = start;
	retVal.Start.Step      = step;
	retVal.Start.Width     = width;
	
	retVal.End           = retVal.Start;
	retVal.End.BaseValue = end + step;
	return retVal;
};
