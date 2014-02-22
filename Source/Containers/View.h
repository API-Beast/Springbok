//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "List.h"
#include "MemorySubrange.h"

template<typename T>
struct ViewIterator
{
public:
	ViewIterator(List<int>* data, List<T>* of, int index):  mData(data), mViewOf(of), mIndex(index){};
	ViewIterator() = delete;
	T& operator*(){ return (*mViewOf)[(*mData)[mIndex]]; };
	bool operator!=(const ViewIterator<T>& other){ return other.mIndex != mIndex; };
	ViewIterator<T> operator+(int index){ return ViewIterator<T>(mData, mViewOf, mIndex+index); };
	ViewIterator<T> operator-(int index){ return ViewIterator<T>(mData, mViewOf, mIndex-index); };
	ViewIterator<T>& operator++(){ mIndex++; return *this; };
	ViewIterator<T>& operator--(){ mIndex--; return *this; };
protected:
	List<int>* mData;
	List<T>* mViewOf;
	int mIndex;
};

template<typename T, typename C>
struct ViewBase
{
public:
	ViewBase(List<T>& list) : mViewOf(&list){};
	void update();
	bool needsUpdate(){ return mViewOf->Version != mLastVersion; };
	int findIndex(const C& searchFor, int minmin, int maxmax, int prevMid);
	int findIndex(const C& searchFor);
	ViewIterator<T> begin(){ return ViewIterator<T>(&mData, mViewOf, 0); };
	ViewIterator<T> end(){ return ViewIterator<T>(&mData, mViewOf, mData.UsedLength); };
	ContainerSubrange<ViewBase<T, C>, T> getRange(const C& start, const C& end);
protected:
	virtual bool compare(const T& a, const T& b) const = 0;
	virtual bool compareVal(const T& a, const C& b) const = 0;
	virtual bool compareValEq(const T& a, const C& b) const = 0;
protected:
	List<T>* mViewOf;
	List<int> mData;
	int mLastVersion = -1;	
};

template<typename T>
struct SortedView : public ViewBase<T, T>
{
public:
	template<typename... X>
	SortedView(X&... list) : ViewBase<T, T>(list...){};
	T& operator[](int index)
	{
		ViewBase<T, T>::update();
		return (*ViewBase<T, T>::mViewOf)[ViewBase<T, T>::mData[index]];
	};
	virtual bool compare(const T& a, const T& b) const
	{
		return a > b;
	};
	virtual bool compareVal(const T& a, const T& b) const
	{
		return a > b;
	};
	virtual bool compareValEq(const T& a, const T& b) const
	{
		return a == b;
	};
};

#include "View_Templates.hpp"