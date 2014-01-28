//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <initializer_list>

struct AllocatedMemoryFull{};

template <typename T>
class SimpleList
{
public:
	SimpleList(T* memory, int length, int used=0);
	SimpleList(char* memory, int length);
	template<int ArraySize>
	SimpleList(T (&array)[ArraySize]);
	SimpleList(int length);
	SimpleList(const std::initializer_list<T>& list);
	SimpleList();
	~SimpleList();
	
	T& operator[](int index){ return *(Memory+index); };
	T& pushBack(const T& value);
	T   popBack();
	
	T&  back(int i=0){ return operator[](UsedLength - 1 - i); };
	T& front(int i=0){ return operator[](i); };
	
	T* begin(){ return Memory; };
	T*   end(){ return Memory+UsedLength; };
	
	void moveMemoryTo(T* memory, int length);
	void reallocate(int elements);
	
	T& insert(int position, const T& value);
	T& makeSpace(int position, int elements=1);
protected:
	void memMove(T* dst, const T* src, int length);
public:
	bool OwnsMemory = false;
	bool AllowReallocation = false;
	T* Memory = nullptr;
	int MemoryLength = 0;
	int UsedLength = 0;
};

/** A @ref SimpleList that is assumed to be sorted by \a Member of \a T.  */
template <typename T, typename C, C T::*Member>
class SimpleMap
{
public:
	/** Constructor, data will get sorted. */
	SimpleMap(const std::initializer_list<T>& list) : Data(list) { sort(); };
	SimpleMap(T* memory, int length, int used=0) : Data(memory, length, used){ sort(); };
	template<int ArraySize>
	SimpleMap(T (&array)[ArraySize]) : Data(array) { sort(); };
	SimpleMap(int length) : Data(length){};
	SimpleMap() : Data(){};
	T& operator[](const C& item);
	template<typename X, X T::*member>
	void findBy(const X& item){};
	T& insert(const T& t);
	void sort();
protected:
	int findIndex(const C& item);
public:
	SimpleList<T> Data;
};

#include "SimpleList_Templates.hpp"