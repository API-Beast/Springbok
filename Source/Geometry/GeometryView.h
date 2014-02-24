//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Containers/View.h>
#include "BoundingShapes.h"

template<typename T, typename C, typename Base, C Base::*Member>
class NaiveGeometryView : public ViewBase<T, float>
{
public:
	template<typename... X>
	NaiveGeometryView(int axis, X&... args) : Axis(axis), ViewBase<T, float>(args...){ ViewBase<T, float>::update(); };
	T& operator[](int index)
	{
		return (*ViewBase<T, float>::mViewOf)[ViewBase<T, float>::mData[index]];
	};
	typedef typename WithoutPtr<T>::Type const& TRef;
	virtual bool compare(TRef a, TRef b) const
	{
		return (a.*Member).getAxis(Axis).Start > (b.*Member).getAxis(Axis).Start;
	};
	virtual bool compareVal(TRef a, const float& b) const
	{
		return (a.*Member).getAxis(Axis).Start > b;
	};
	virtual bool compareValEq(TRef a, const float& b) const
	{
		return (a.*Member).getAxis(Axis).Start == b;
	};
public:
	int Axis;
};

template<typename T, typename C, typename Base, C Base::*Member>
class GeometryView
{
public:
	NaiveGeometryView<T, C, Base, Member> XAxisView;
	NaiveGeometryView<T, C, Base, Member> YAxisView;
public:
	typedef typename WithoutPtr<T>::Type PureT;
	template<typename... X>
	GeometryView(X&... args) : XAxisView(0, args...), YAxisView(1, args...) {};
};

