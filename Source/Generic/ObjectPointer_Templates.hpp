// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "ObjectPointer.h"
#include <algorithm>
#include <cassert>

template<typename T>
ObjectPointer<T>::ObjectPointer()
{
	mPointer = nullptr;
}

template<typename T>
void Destructor<T>::destroy(void* pointer)
{
	delete reinterpret_cast<T*>(pointer);
};

template<typename T>
template<typename U>
ObjectPointer<T>::ObjectPointer(U* ptr)
{
	auto nodePath = ObjectData::gObjects.findNode(ptr);
	if(nodePath.hasFoundValue() == false)
	{
		nodePath.insert();
		mPointer = &(nodePath.BaseNode->Data);
		mPointer->Destructor = new Destructor<U>;
		mPointer->MemoryLocation = ptr;
	}
	else
		mPointer = &(nodePath.BaseNode->Data);
}

template<typename T>
ObjectPointer<T>::ObjectPointer(const ObjectPointer<T>& other)
{
	mPointer = other.mPointer;
}

template<typename T>
ObjectPointer<T>::ObjectPointer(std::nullptr_t null)
{
	mPointer = nullptr;
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
	if(!mPointer)
		return nullptr;
	return reinterpret_cast<T*>(mPointer->MemoryLocation);
}

template<typename T>
T* ObjectPointer<T>::operator->() const
{
	if(!mPointer)
		return nullptr;
	return reinterpret_cast<T*>(mPointer->MemoryLocation);
}

template<typename T>
void ObjectPointer<T>::replaceWith(T* newPtr)
{
	// Ensure that the right destructor is called.
	mPointer->MemoryLocation = newPtr;
}

template<typename T>
void ObjectPointer<T>::destroy()
{
	// Ensure that the right destructor is called.
	mPointer->Destructor->destroy(mPointer->MemoryLocation);
	mPointer->MemoryLocation = nullptr;
}

template<typename X, template<typename> class T, typename Y>
X dynamic_pointer_cast(const T<Y>& input)
{
	Y* inPtr = input;
	return dynamic_cast<X>(inPtr);
}

template<typename X, template<typename> class T, typename Y>
X reinterpret_pointer_cast(const T<Y>& input)
{
	Y* inPtr = input;
	return reinterpret_cast<X>(inPtr);
}

template<typename X, template<typename> class T, typename Y>
X static_pointer_cast(const T<Y>& input)
{
	Y* inPtr = input;
	return static_cast<X>(inPtr);
}