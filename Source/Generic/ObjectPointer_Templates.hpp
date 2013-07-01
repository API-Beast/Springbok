// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "ObjectPointer.h"
#include <algorithm>
#include <iostream>

template<typename T>
ObjectPointer<T>::ObjectPointer()
{
	mPointer = nullptr;
	mIter = gInstances.insert(gInstances.begin(), this);
}

template<typename T>
ObjectPointer<T>::ObjectPointer(T* ptr)
{
	mPointer = ptr;
	mIter = gInstances.insert(gInstances.begin(), this);
}

template<typename T>
ObjectPointer<T>::ObjectPointer(const ObjectPointer<T>& other)
{
	mPointer = other.mPointer;
	mIter = gInstances.insert(gInstances.begin(), this);
}

template<typename T>
ObjectPointer<T>::~ObjectPointer()
{
	gInstances.erase(mIter);
}

template<typename T>
ObjectPointer<T>& ObjectPointer<T>::operator =(T* ptr)
{
	mPointer = ptr;
	return *this;
}

template<typename T>
ObjectPointer<T>& ObjectPointer<T>::operator =(const ObjectPointer<T>& other)
{
	mPointer = other.mPointer;
	return *this;
}

template<typename T>
ObjectPointer<T>::operator T*() const
{
	return mPointer;
}

template<typename T>
void ObjectPointer<T>::destroy(bool del)
{
	if(del) delete mPointer;
	for(AbstractObjectPointer* ptr : AbstractObjectPointer::gInstances)
		ptr->onDestruction((void*)mPointer);
}

template<typename T>
void ObjectPointer<T>::replaceWith(T* newPointer, bool del)
{
	if(del) delete mPointer;
	for(AbstractObjectPointer* ptr : AbstractObjectPointer::gInstances)
		ptr->onReplace(mPointer, newPointer);
}


template<typename T>
void ObjectPointer<T>::onDestruction(void* ptr)
{
	if(mPointer == ptr)
		mPointer = nullptr;
}

template<typename T>
void ObjectPointer<T>::onReplace(void* oldPtr, void* newPtr)
{
	if(mPointer == oldPtr)
		mPointer = (T*)newPtr;
}

template<typename T>
void ObjectPointer<T>::markAsDestroyed(T* memory)
{

}

template<typename X, template<typename> class T, typename Y>
X* dynamic_pointer_cast(const T<Y>& input)
{
	Y* inPtr = input;
	return dynamic_cast<X*>(inPtr);
}

template<typename X, template<typename> class T, typename Y>
X* reinterpret_pointer_cast(const T<Y>& input)
{
	Y* inPtr = input;
	return reinterpret_cast<X*>(inPtr);
}

template<typename X, template<typename> class T, typename Y>
X* static_pointer_cast(const T<Y>& input)
{
	Y* inPtr = input;
	return static_cast<X*>(inPtr);
}