//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "View.h"
#include "List.h"

// TODO
// All duplicate code from Map class with really minor differences... can we reuse something?

template<typename T> T& makeRef(T& x){ return  x; };
template<typename T> T& makeRef(T* x){ return *x; };

template<typename T, typename C>
void ViewBase<T, C>::update()
{
	// Resize the array to fit the actual data
	if(mData.UsedLength > mViewOf->UsedLength)
	{
		for(int i = 0; i < mViewOf->UsedLength; ++i)
			if(mData[i] >= mViewOf->UsedLength)
			{
				mData.quickRemove(i);
				i--;
			}
	}
	else if(mData.UsedLength < mViewOf->UsedLength)
		for(int i = mData.UsedLength; i < mViewOf->UsedLength; ++i)
			mData.pushBack(i);
	
	// Sort
	for(int i = 1; i < mData.UsedLength; ++i)
	{
		int temp = mData[i];
		int j = i -1;
		
		while((j >= 0) && (compare(makeRef(mViewOf->front(mData[j])), makeRef(mViewOf->front(temp)))))
		{
			mData[j + 1] = mData[j];
			j--;
		}
		
		mData[j+1] = temp;
	}
}

template <typename T, typename C>
int ViewBase<T, C>::findIndex(const C& searchFor, int minmin, int maxmax, int prevMid)
{
	int min = minmin;
	int max = maxmax;
	int mid = (min + ((max-min) / 2));

	if(min >= max)
	{
		min = Max(mid - 1, 0);
		max = Min(mid + 1, mData.UsedLength-1);
		int i = min;
		while(i < max)
		{
			auto& value  = makeRef((*mViewOf)[mData[i]]);
			auto& valueB = makeRef((*mViewOf)[mData[i+1]]);
			if(compareValEq(value, searchFor))
				return i;
			if(!compareVal(value, searchFor))
				if(compareVal(valueB, searchFor))
					return i;
			i++;
		}
		return max;
	}
	
	auto& value = makeRef((*mViewOf)[mData[mid]]);
	if(compareVal(value, searchFor))
		return findIndex(searchFor, min, mid-1, mid);
	if(!compareVal(value, searchFor))
		return findIndex(searchFor, mid+1, max, mid);
	return mid;
}

template<typename T, typename C>
int ViewBase<T, C>::findIndex(const C& searchFor)
{
	if(mData.Memory == nullptr)
		return 0;
	return findIndex(searchFor, 0, mData.UsedLength - 1, 0);
};

template<typename T, typename C>
ContainerSubrange<ViewBase<T, C>, T> ViewBase<T, C>::getRange(const C& start, const C& end)
{
	if(mViewOf->UsedLength == 0)
		return ContainerSubrange<ViewBase<T, C>, T>(*this, 0, 0);
	
	int startIndex = findIndex(start);
	int endIndex = findIndex(end, startIndex, mData.UsedLength - 1, startIndex);
	if(startIndex > endIndex)
		return ContainerSubrange<ViewBase<T, C>, T>(*this, startIndex, startIndex);
	return ContainerSubrange<ViewBase<T, C>, T>(*this, startIndex, endIndex);
};