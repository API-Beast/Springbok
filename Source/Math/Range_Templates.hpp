// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Range.h"
#include <Math/Operations.h>

template<typename T>
Range<T>::Range(T start, T end)
{
	this->Start = Start;
	this->End   = End;
}

template<typename T>
Range<T>::operator bool()
{
	return Start != End;
}

template<typename T>
Range<T> Range::getIntersection(const Range<T>& other)
{
	Range<T> retVal;
	retVal.Start = Max(other.Start, Start);
	retVal.End   = Min(other.End, End);
	if(retVal.Start > retVal.End) return Range<T>();
	return retVal;
}

Range Range::getUnion(const Range& other)
{
	Range retVal;
	retVal.Start = Min(other.Start, Start);
	retVal.End   = Max(other.End, End);
	return retVal;
}
