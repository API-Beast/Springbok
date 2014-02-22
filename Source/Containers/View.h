//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "List.h"

template<typename T>
struct ViewBase
{
public:
	ViewBase(List<T>& list) : mViewOf(&list){};
	void update();
	bool needsUpdate(){ return mViewOf->Version != mLastVersion; };
protected:
	virtual bool compare(const T& a, const T& b) = 0;
protected:
	List<T>* mViewOf;
	List<int> mData;
	int mLastVersion = -1;
};

template<typename T>
struct SortedView : public ViewBase<T>
{
public:
	template<typename X>
	SortedView(X& list) : ViewBase<T>(list){};
	T& operator[](int index)
	{
		ViewBase<T>::update();
		return (*ViewBase<T>::mViewOf)[ViewBase<T>::mData[index]];
	};
	virtual bool compare(const T& a, const T& b)
	{
		return a > b;
	};
};

#include "View_Templates.hpp"