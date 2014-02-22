//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

template<typename T>
class MemorySubrange
{
public:
	MemorySubrange(T* start, T* end) : mBegin(start), mEnd(end){};
	const T& operator[](int index) const{ return *(mBegin + index); };
	T& operator[](int index){ return *(mBegin + index); };
	T* begin(){ return mBegin; };
	T* end(){ return mEnd; };
	int length(){ return mEnd - mBegin; };
protected:
	T* mBegin;
	T* mEnd;
};

template<typename Container, typename T>
class ContainerSubrange
{
protected:
	int mBegin;
	int mEnd;
	Container* mContainer;
public:
	ContainerSubrange(Container& container, int start, int end) : mContainer(&container), mBegin(start), mEnd(end){};
	const T& operator[](int index) const{ return (*mContainer)[mBegin + index]; };
	T& operator[](int index){ return (*mContainer)[mBegin + index]; };
	auto begin() -> decltype(mContainer->begin()+mBegin) { return mContainer->begin()+mBegin; };
	auto end() -> decltype(mContainer->begin()+mEnd) { return mContainer->begin()+mEnd; };
	int length(){ return mEnd - mBegin; };
};