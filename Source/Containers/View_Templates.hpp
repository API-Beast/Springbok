//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "View.h"
#include "List.h"

template<typename T>
void ViewBase<T>::update()
{
	if(needsUpdate())
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
			
			while((j >= 0) && (compare(mViewOf->front(mData[j]), mViewOf->front(temp))))
			{
				mData[j + 1] = mData[j];
				j--;
			}
			
			mData[j+1] = temp;
		}
	}
}